import jsonlines
import argparse
import logging

logger = logging.getLogger(__name__)


def load_results(results_jsonlines_path):
    with jsonlines.open(results_jsonlines_path) as reader:
        results = list(reader)

    return results


def visualize_results(results, diff_path):
    with open(diff_path, "w") as writer:
        for result in results:
            writer.write("\n\n\n")

            writer.write("========================================\n")
            writer.write(f"{result['bug_report_text']}\n")
            writer.write("========================================\n")

            # Write reference diff section
            writer.write("============= reference diff =============\n")
            writer.write(f"{result['diff_text']}\n")
            writer.write("========================================\n")

            # Write generated diff section
            writer.write("============= generated diff =============\n")
            writer.write(f"{result['generated_diff']}\n")
            writer.write("========================================\n")

            writer.write("\n\n\n")


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
        default="/Users/sudnya/checkout/duckpilot/coverity/dataset/tuning/results/results.jsonlines",
        help="Path to the input results file to do diff on",
    )

    parser.add_argument(
        "-o",
        "--output",
        default="/app/duckpilot-coverity/dataset/tuning/visualize_diffs/diff.txt",
        help="Name of the file to write diff to",
    )
    args = parser.parse_args()

    # Set up logging based on verbose flag
    log_level = logging.DEBUG if args.verbose else logging.INFO
    logging.basicConfig(level=log_level, format="%(levelname)s: %(message)s")

    results = load_results(results_jsonlines_path=args.input)

    visualize_results(results, args.output)


# Entry point of the script
if __name__ == "__main__":
    main()
