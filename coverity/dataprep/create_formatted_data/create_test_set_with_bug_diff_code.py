import os
import jsonlines
import argparse
import logging
import constants as constvals
from pathlib import Path
from typing import List, Dict

# Configure logger for this module
logger = logging.getLogger(__name__)


def extract_file_info(bug_report_path: str, prefix: str) -> str | None:
    """
    Extract file path or line number from bug report based on prefix.

    Args:
        bug_report_path: Path to bug report file
        prefix: Line prefix to search for ('File:' or 'Line:')
    """
    try:
        with open(bug_report_path) as file:
            return next(
                (
                    line[len(prefix) :].strip()
                    for line in file
                    if line.startswith(prefix)
                ),
                None,
            )
    except (FileNotFoundError, IOError) as e:
        raise type(e)(f"Error accessing {bug_report_path}: {e}")


def get_bug_fix_path(
    bug_report_dir: str, report_path: str, report_suffix: str, fix_suffix: str
) -> str:
    """Convert a bug report path to its corresponding bug fix path."""
    assert report_path.endswith(report_suffix), f"Invalid suffix: {report_path}"
    return os.path.join(
        bug_report_dir, f"{report_path[:-len(report_suffix)]}{fix_suffix}"
    )


def extract_text(file_path: str) -> str:
    """Read and return file contents."""
    with open(file_path) as f:
        return f.read()


def get_bug_reports(bug_report_dir: str) -> list[dict]:
    """
    Collect bug reports and their corresponding diffs from a directory.

    Args:
        bug_report_dir: Directory containing bug reports and diffs

    Returns:
        List of dictionaries with bug report and diff information
    """
    logger.info(f"Collecting bug reports from: {bug_report_dir}")

    bug_reports = []
    for file_path in os.listdir(bug_report_dir):
        if not file_path.endswith(constvals.BUG_REPORT_SUFFIX):
            continue

        full_path = os.path.join(bug_report_dir, file_path)
        diff_path = get_bug_fix_path(
            bug_report_dir,
            file_path,
            constvals.BUG_REPORT_SUFFIX,
            constvals.BUG_FIX_SUFFIX,
        )

        assert os.path.exists(diff_path), f"Missing diff file: {diff_path}"

        bug_reports.append(
            {
                "bug_report_path": full_path,
                "bug_report_text": extract_text(full_path),
                "diff_path": diff_path,
                "diff_text": extract_text(diff_path),
                "source_code_path": extract_file_info(full_path, "File:"),
                "line_number": int(extract_file_info(full_path, "Line:")),
            }
        )

    logger.info(f"Found {len(bug_reports)} bug reports with matching diffs")
    return bug_reports


def get_code_for_bug_report(bug_report: dict, code_dir: str) -> str:
    """
    Extracts code from source file for a given bug report.

    Args:
        bug_report: Dictionary containing source_code_path and line_number
        code_dir: Base directory for source code files

    Returns:
        str: Extracted source code

    Raises:
        AssertionError: If line_number is None
        Exception: If code extraction fails
    """
    src_path = os.path.join(code_dir, bug_report["source_code_path"])
    logger.debug(f"Extracting code from: {src_path}")

    try:
        code = extract_text(src_path)
        assert bug_report["line_number"], f"Missing line number for {src_path}"
        logger.info(
            f"Code extracted from {src_path} (line {bug_report['line_number']})"
        )
        return code
    except Exception as e:
        logger.error(f"Failed to extract code from {src_path}: {str(e)}")
        raise


def add_code_to_bug_reports(bug_reports: List[Dict], code_dir: Path) -> List[Dict]:
    """
    Adds source code to bug reports by reading from a code directory.

    Args:
        bug_reports: List of bug report dictionaries containing 'source_code_path'
        code_dir: Directory path containing source code files

    Returns:
        List of bug reports with added 'code' field

    Raises:
        ValueError: If inputs are invalid
        FileNotFoundError: If code_dir doesn't exist
    """
    if not bug_reports:
        logger.warning("Empty bug reports list provided")
        return []

    if not isinstance(code_dir, Path):
        code_dir = Path(code_dir)

    if not code_dir.exists():
        raise FileNotFoundError(f"Code directory not found: {code_dir}")

    logger.info(f"Starting to process {len(bug_reports)} bug reports for code addition")
    processed_count = 0
    errors = []

    for bug_report in bug_reports:
        source_path = bug_report.get("source_code_path", "Unknown path")

        try:
            logger.debug(f"Processing bug report from {source_path}")
            bug_report["code"] = get_code_for_bug_report(bug_report, code_dir)
            processed_count += 1
            logger.debug(f"Successfully processed bug report: {source_path}")

        except Exception as e:
            error_msg = f"Failed to process {source_path}: {str(e)}"
            logger.error(error_msg)
            errors.append(error_msg)
            bug_report["code"] = None  # Or some other error indicator
            continue

    logger.info(
        f"Processed {processed_count}/{len(bug_reports)} bug reports successfully. "
        f"Failed: {len(errors)}"
    )

    if errors:
        logger.warning(f"Errors encountered: {errors}")

    return bug_reports


def save_bug_reports_with_code(bug_reports_with_code, output_path):
    """
    Save processed bug reports to a JSONL file.

    Args:
        bug_reports_with_code (list): List of processed bug reports
        output_path (str): Path where the output file should be written
    """
    logger.info(f"Saving {len(bug_reports_with_code)} bug reports to: {output_path}")
    with jsonlines.open(output_path, "w") as writer:
        for bug_report_with_code in bug_reports_with_code:
            writer.write(bug_report_with_code)
    logger.info("Successfully saved bug reports")


def main():
    """
    Main function to process bug reports and create a dataset.

    Collects bug reports, their corresponding diffs, and relevant source code,
    then combines them into a single dataset file.
    """
    # Set up command-line argument parser
    parser = argparse.ArgumentParser(
        description="Create a dataset using coverity bug reports and source code"
    )

    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="Enable verbose mode (sets logging to DEBUG level)",
    )
    parser.add_argument(
        "-b",
        "--bug-dir",
        default="/app/duckpilot-coverity/dataset/raw-data/bugs/test-set",
        help="Path to raw the bug reports to be used",
    )
    parser.add_argument(
        "-c",
        "--code-dir",
        default="/app/duckpilot-coverity/dataset/raw_data/code/drivers/gpu/drm/amd/amdgpu/",
        help="Path to code to be used",
    )
    parser.add_argument(
        "-o",
        "--output-file",
        default="/app/duckpilot-coverity/dataset/gold-test-set.jsonlines",
        help="Path to output file to be written, that combines bug {report, diff, code}",
    )
    args = parser.parse_args()

    # Set up logging based on verbose flag
    log_level = logging.DEBUG if args.verbose else logging.INFO
    logging.basicConfig(
        level=log_level, format="%(asctime)s - %(levelname)s - %(message)s"
    )

    logger.info("Starting bug report processing")
    logger.info(f"Bug directory:  {args.bug_dir}")
    logger.info(f"Code directory: {args.code_dir}")
    logger.info(f"Output file:    {args.output_file}")

    # Process bug reports
    bug_reports = get_bug_reports(args.bug_dir)
    bug_reports_with_code = add_code_to_bug_reports(bug_reports, args.code_dir)
    save_bug_reports_with_code(bug_reports_with_code, args.output_file)

    logger.info("Bug report processing completed successfully")


# Entry point of the script
if __name__ == "__main__":
    main()
