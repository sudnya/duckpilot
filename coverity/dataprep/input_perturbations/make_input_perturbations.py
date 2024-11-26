import json
import argparse
import os


import logging

logger = logging.getLogger(__name__)


# NOTE: this script is currently not used as input perturbations are generated manually
# TODO: call LLM to generate different "descriptions" instead.


def process_jsonlines(file_path):
    with open(file_path, "r") as file:
        for line in file:
            try:
                data = json.loads(line.strip())
                logger.info(data.get("bug_report_text", "Bug report text not found"))
            except json.JSONDecodeError:
                logger.error(f"Error decoding JSON: {line}")


def main():
    # Set up command-line argument parser
    parser = argparse.ArgumentParser(
        description="Create a gold dataset using coverity bug reports"
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
        default="dataset/gold-test-set.jsonlines",
        help="Path to the input file to use for perturbations",
    )

    args = parser.parse_args()

    current_directory = os.getcwd()
    input_file_path = os.path.join(current_directory, str(args.input))

    # Set up logging based on verbose flag
    log_level = logging.DEBUG if args.verbose else logging.INFO
    logging.basicConfig(level=log_level, format="%(levelname)s: %(message)s")

    process_jsonlines(input_file_path)


# Entry point of the script
if __name__ == "__main__":
    main()
