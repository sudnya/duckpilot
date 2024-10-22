
import jsonlines
import os
import argparse

# Import constants
import constants as constval

import logging
logger = logging.getLogger(__name__)

import difflib


def compare_git_diffs(diff1, diff2):
    """
    Compare two git diff strings and return their difference.
    
    :param diff1: First git diff string
    :param diff2: Second git diff string
    :return: A string representing the difference between the two diffs, or None if there's no difference
    """
    # Split the diffs into lines
    diff1_lines = diff1.splitlines()
    diff2_lines = diff2.splitlines()
    
    # Create a differ object
    differ = difflib.Differ()
    
    # Compare the two diffs
    diff = list(differ.compare(diff1_lines, diff2_lines))
    
    # Filter and format the output
    result = []
    for line in diff:
        if line.startswith('  '):  # Lines that are the same in both diffs
            continue
        elif line.startswith('- '):  # Lines only in diff1
            result.append(f"Only in diff1: {line[2:]}")
        elif line.startswith('+ '):  # Lines only in diff2
            result.append(f"Only in diff2: {line[2:]}")
    
    # Check if the result is empty
    if not result:
        return None
    
    return '\n'.join(result)


def load_results(results_jsonlines_path):
    with jsonlines.open(results_jsonlines_path) as reader:
        results = list(reader)

    return results

def visualize_results(results):
    #path = constval.RESULTS_PATH

    #os.makedirs(path, exist_ok=True)

    for result in results:
        #result_path = os.path.join(path, result["bug_report_path"])

        #with open(result_path, "w") as writer:
        print("========================================\n")
        print(result["bug_report_text"])
        print("\n")
        print("========================================\n")

        print("============= reference diff =============\n")
        print(result["diff_text"])
        print("\n")
        print("========================================\n")

        print("============= generated diff =============\n")
        print(result["generated_diff"])
        print("\n")
        print("========================================\n")

        '''diff_of_diffs = compare_git_diffs(result["diff_text"], result["generated_diff"])
        if diff_of_diffs:
            writer.write("*************** diff of diffs :-D ************\n")
            writer.write(diff_of_diffs)
            writer.write("\n")
            writer.write("***********************************************\n")
        else:
            writer.write("\n")
            writer.write("***********************************************\n")
            writer.write("Generated diff matches reference diff exactly.")'''



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
        default="/Users/sudnya/checkout/duckpilot/coverity/dataset/results.jsonlines",
        help="Path to the input dataset file to do diff on",
    )
    args = parser.parse_args()

    # Set up logging based on verbose flag
    log_level = logging.DEBUG if args.verbose else logging.INFO
    logging.basicConfig(level=log_level, format="%(levelname)s: %(message)s")

    results = load_results(results_jsonlines_path=args.input)

    visualize_results(results)

# Entry point of the script
if __name__ == "__main__":
    main()
