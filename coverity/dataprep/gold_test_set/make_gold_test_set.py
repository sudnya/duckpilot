import os
import jsonlines
import argparse
import dataprep.gold_test_set.constants as constvals
import logging
logger = logging.getLogger(__name__)


def get_bug_reports():
    path = constvals.TEST_SET_PATH
    bug_reports = []

    for file_path in os.listdir(path):
        # bugs end with _report.txt
        if file_path.endswith("_report.txt"):
            bug_reports.append({"bug_report_path": file_path, "root": path})

    # Get the corresponding diff for the bug report
    # diffs are in the same directory as the bug reports and end with _diff.txt
    diffs = {}

    for file_path in os.listdir(path):
        if file_path.endswith("_diff.txt"):
            bug_report_id = file_path.split("_diff.txt")[0]
            diffs[bug_report_id] = file_path

    # Add the diff path to the bug report
    for bug_report in bug_reports:
        bug_report_id = bug_report["bug_report_path"].split("_report.txt")[0]
        bug_report["diff_path"] = diffs[bug_report_id]

    return bug_reports


def add_code_to_bug_reports(bug_reports):
    bug_reports_with_code = []

    for bug_report in bug_reports:
        bug_report_with_code = get_code_for_bug_report(bug_report)
        bug_reports_with_code.append(bug_report_with_code)

    return bug_reports_with_code


def get_code_for_bug_report(bug_report):
    code_path = "/app/lamini-coverity/data/raw-data/code"

    code_files = get_code_files(code_path)

    # get the file name from the bug report, File: <file_name>.c
    file_name = get_file_name_from_bug_report(bug_report)

    assert file_name is not None, f"file_name is None for {bug_report['bug_report_path']}"

    # assert that the file_name is in the code_files
    assert file_name in code_files, f"{file_name} not in {code_files}"

    # get the code from the file
    code = get_code_from_file(file_name)

    # Get the line number from the bug report
    line_number = get_line_number_from_bug_report(bug_report)

    # Get the bug report text
    bug_report_text = get_bug_report_text(bug_report)

    # Get the diff text
    diff_text = get_diff_text(bug_report)

    return {
        "bug_report_path": bug_report["bug_report_path"],
        "bug_report_text": bug_report_text,
        "diff_path": bug_report["diff_path"],
        "diff_text": diff_text,
        "code": code,
        "source_code_path": file_name,
        "line_number": line_number,
    }


def get_code_files(code_path):
    code_files = []

    for file_path in os.listdir(code_path):
        if file_path.endswith(".c"):
            code_files.append(file_path)

    return code_files


def get_file_name_from_bug_report(bug_report):
    bug_report_path = (
        f"{bug_report['root']}/{bug_report['bug_report_path']}"
    )
    with open(bug_report_path, "r") as f:
        for line in f:
            if line.startswith("File:"):
                file_name = line.split("File: ")[1].strip()
                return os.path.basename(file_name)


def get_code_from_file(file_name):
    code_path = "/app/lamini-coverity/data/raw-data/code"

    with open(os.path.join(code_path, file_name), "r") as f:
        code = f.read()

    return code


def get_line_number_from_bug_report(bug_report):
    bug_report_path = (
        f"{bug_report['root']}/{bug_report['bug_report_path']}"
    )
    with open(bug_report_path, "r") as f:
        for line in f:
            if line.startswith("Line:"):
                line_number = line.split("Line: ")[1].strip()
                return int(line_number)


def get_bug_report_text(bug_report):
    bug_report_path = (
        f"{bug_report['root']}/{bug_report['bug_report_path']}"
    )
    with open(bug_report_path, "r") as f:
        bug_report_text = f.read()

    return bug_report_text


def get_diff_text(bug_report):
    diff_path = f"{bug_report['root']}/{bug_report['diff_path']}"
    with open(diff_path, "r") as f:
        diff_text = f.read()

    return diff_text


def save_bug_reports_with_code(bug_reports_with_code):
    output_path = constvals.GOLD_TEST_PATH

    with jsonlines.open(output_path, "w") as writer:
        for bug_report_with_code in bug_reports_with_code:
            writer.write(bug_report_with_code)


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

    args = parser.parse_args()

    # Set up logging based on verbose flag
    log_level = logging.DEBUG if args.verbose else logging.INFO
    logging.basicConfig(level=log_level, format="%(levelname)s: %(message)s")

    bug_reports = get_bug_reports()

    bug_reports_with_code = add_code_to_bug_reports(bug_reports)

    save_bug_reports_with_code(bug_reports_with_code)


# Entry point of the script
if __name__ == "__main__":
    main()
