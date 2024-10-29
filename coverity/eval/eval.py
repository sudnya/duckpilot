from lamini.generation.generation_node import GenerationNode
from lamini.generation.generation_pipeline import GenerationPipeline
from lamini.generation.base_prompt_object import PromptObject
from tools.bug_db import BugDatabase

import argparse
from tqdm import tqdm

import asyncio
import jsonlines
import csv
import lamini
import os
from dotenv import load_dotenv

from pathlib import Path

# Build path using current directory
dotenv_path = Path(".") / ".env"
load_dotenv(dotenv_path=dotenv_path)
lamini.api_key = os.environ.get("LAMINI_API_KEY")


import logging

logger = logging.getLogger(__name__)


def load_data(eval_file_path):

    with jsonlines.open(eval_file_path) as reader:
        data = list(reader)

    return data


def load_bug_db(eval_file_path):

    with jsonlines.open(eval_file_path) as reader:
        data = list(reader)

    return data


def run_eval_pipeline(data, model_hash):
    return asyncio.run(eval_pipeline(data, model_hash))


async def eval_pipeline(data, model_hash):

    answer_ops = EvalPipeline(model_hash).call(get_data_async(data))

    answers = []

    pbar = tqdm(desc="Saving answers", unit=" answers", total=len(data))

    async for answer_op in answer_ops:
        answers.append(answer_op)
        pbar.update(1)

    return answers


async def get_data_async(data):
    for item in data:
        yield PromptObject(prompt="", data=item)


class EvalPipeline(GenerationPipeline):
    def __init__(self, model_hash):
        super().__init__()

        self.answer_question = AnswerGenerator(model_hash)

    def forward(self, x):
        x = self.answer_question(x)
        return x


class AnswerGenerator(GenerationNode):
    def __init__(self, model_hash):
        super().__init__(model_name=model_hash, max_new_tokens=500)

    def postprocess(self, obj: PromptObject):
        logger.info(f"Generated answer for {obj}")
        obj.data["generated_diff"] = obj.response["output"]

    def preprocess(self, obj: PromptObject):
        obj.prompt = self.make_prompt(obj)

    def make_prompt(self, obj: PromptObject):
        # prompt = "<|start_header_id|>user<|end_header_id|>"
        prompt = "<s>[INST]"
        prompt += "Consider the following github diff format.\n"
        prompt += "============ Diff format ============\n"
        prompt += "```diff\n"
        prompt += "diff --git a/file1 b/file2\n"
        prompt += "index 1234567..89abcdef 100644\n"
        prompt += "--- a/file1\n"
        prompt += "+++ b/file2\n"
        prompt += "@@ -1,3 +1,3 @@\n"
        prompt += "-old line\n"
        prompt += "+new line\n"
        prompt += "```"
        prompt += "====================================\n"
        prompt += "Read through the following source code carefully.\n"
        prompt += "============ Source Code ============\n"
        prompt += "File: " + obj.data["source_code_path"] + "\n"
        prompt += "Line: " + str(obj.data["line_number"]) + "\n"
        prompt += get_source_code(obj.data)
        prompt += "====================================\n"
        prompt += "Read the following bug report.\n"
        prompt += "============ Bug Report ============\n"
        prompt += obj.data["bug_report_text"]
        prompt += "====================================\n"
        prompt += "Based on the source code and the bug report, write a diff that fixes the bug.\n"
        prompt += "Use github diff format.\n"
        prompt += "Don't explain your diff, answer directly with the diff.\n"
        # prompt += "<|eot_id|><|start_header_id|>assistant<|end_header_id|>"
        prompt += "[/INST]"

        return prompt


def get_source_code(data):
    # Before and after lines to show
    before_lines = 5
    after_lines = 5

    source_code = data["code"]

    lines = source_code.split("\n")

    line_number = data["line_number"]

    start_line = max(0, line_number - before_lines)
    end_line = min(len(lines), line_number + after_lines)

    source_code_with_line_numbers = ""

    for i, line in enumerate(lines[start_line:end_line], start=start_line):
        source_code_with_line_numbers += f"{line}\n"

    return source_code_with_line_numbers


def save_results(results, results_path):
    jsonlines_path = results_path

    with jsonlines.open(jsonlines_path, "w") as writer:
        for result in results:
            writer.write(result.data)

    # Split the file path into directory, filename without extension, and current extension
    base = os.path.splitext(jsonlines_path)[0]

    # Add the new extension to the base filename
    # Also save the results as csv
    csv_path = f"{base}" + ".csv"

    # Select the following column names to be saved in the CSV file
    columns = ["bug_report_path", "bug_report_text", "diff_text", "generated_diff"]

    with open(csv_path, "w") as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=columns)
        writer.writeheader()

        for result in results:
            writer.writerow({k: result.data[k] for k in columns})


def main():
    # Set up command-line argument parser
    parser = argparse.ArgumentParser(
        description="Build an evaluation pipeline for a coverity fixer LLM."
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="Enable verbose mode (sets logging to DEBUG level)",
    )
    parser.add_argument(
        "-i",
        "--input",
        default="/app/duckpilot-coverity/dataset/tuning/inputs/gold-test-set-full.jsonlines",
        help="Path to the input dataset file to evaluate on",
    )
    parser.add_argument(
        "-o",
        "--output",
        default="/app/duckpilot-coverity/dataset/tuning/results/gold-test-results.jsonlines",
        help="Name of the file to write eval results to",
    )
    parser.add_argument(
        "-m",
        "--model",
        default="c7fbc6924bafd2885ea18a6e109126aecb44530d4cd0a3a0a016b83b3ebd4ce7",
        help="Model hash that eval should use",
    )
    parser.add_argument(
        "-b",
        "--bug_id",
        # default="6a999345-2e04-4adf-94b1-63fa6aa230bb",
        default=None,
        help="Bug ID that the eval should use",
    )
    parser.add_argument(
        "-g",
        "--bug_group_id",
        # default="31fbc1f5-ed37-4c7a-9550-90e9aa77e2e9",
        default=None,
        help="Bug group ID that the eval should use",
    )
    args = parser.parse_args()

    # Set up logging based on verbose flag
    log_level = logging.DEBUG if args.verbose else logging.INFO
    logging.basicConfig(level=log_level, format="%(levelname)s: %(message)s")
    logger.info(f"\nlamini api key {lamini.api_key}\n")

    logger.info(f"\nLoading data from {args.input}\n")

    logger.info(f"\nWriting eval results to {args.output}\n")

    if args.bug_id:
        logger.info(f"\nEvaluating on bug_id {args.bug_id}\n")
        data = load_bug_db(eval_file_path=args.input, bug_id=args.bug_id)
    elif args.bug_group_id:
        logger.info(f"\nEvaluating on bug_group_id {args.bug_group_id}\n")
        data = load_bug_db(eval_file_path=args.input, bug_group_id=args.bug_group_id)
    else:
        data = load_data(eval_file_path=args.input)

    results = run_eval_pipeline(data, args.model)

    save_results(results, args.output)


# Entry point of the script
if __name__ == "__main__":
    main()
