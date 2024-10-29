#!/usr/bin/env python3
import json
import uuid
import argparse
from pathlib import Path
from collections import OrderedDict, defaultdict
from typing import Dict, List, Optional, Union

# python script.py update input.jsonl output.jsonl
# python script.py lookup output.jsonl --bug-id "bug-id"
# python script.py lookup output.jsonl --bug-group-id "bug-group-id"


class BugProcessor:
    def __init__(self):
        self.bug_id_index: Dict[str, dict] = {}
        self.bug_group_index: Dict[str, List[dict]] = defaultdict(list)

    def update_file(self, input_file: str, output_file: str) -> None:
        """
        Process a JSONLines file by adding bug_id and bug_group_id UUID fields
        and creating indices for lookups.

        Args:
            input_file (str): Path to input JSONLines file
            output_file (str): Path to output JSONLines file
        """
        # Create output directory if it doesn't exist
        output_path = Path(output_file)
        output_path.parent.mkdir(parents=True, exist_ok=True)

        # Process the file line by line
        with open(input_file, "r") as infile, open(output_file, "w") as outfile:
            for line in infile:
                try:
                    json_obj = json.loads(line.strip())

                    # Create new ordered dictionary with UUIDs as first fields
                    new_obj = OrderedDict(
                        [
                            ("bug_id", str(uuid.uuid4())),
                            ("bug_group_id", str(uuid.uuid4())),
                        ]
                    )
                    new_obj.update(json_obj)

                    # Update indices
                    self.bug_id_index[new_obj["bug_id"]] = new_obj
                    self.bug_group_index[new_obj["bug_group_id"]].append(new_obj)

                    # Write modified object to output file
                    outfile.write(json.dumps(new_obj, ensure_ascii=False) + "\n")

                except json.JSONDecodeError as e:
                    print(f"Error parsing JSON line: {e}")
                    continue

    def load_existing_file(self, file_path: str) -> None:
        """
        Load an existing processed file to build indices for lookups.

        Args:
            file_path (str): Path to processed JSONLines file
        """
        with open(file_path, "r") as f:
            for line in f:
                try:
                    obj = json.loads(line.strip())
                    if "bug_id" in obj and "bug_group_id" in obj:
                        self.bug_id_index[obj["bug_id"]] = obj
                        self.bug_group_index[obj["bug_group_id"]].append(obj)
                except json.JSONDecodeError as e:
                    print(f"Error parsing JSON line: {e}")
                    continue

    def lookup_by_bug_id(self, bug_id: str) -> Optional[dict]:
        """
        Look up a bug by its bug_id.

        Args:
            bug_id (str): The bug_id to look up

        Returns:
            Optional[dict]: The bug object if found, None otherwise
        """
        return self.bug_id_index.get(bug_id)

    def lookup_by_group_id(self, group_id: str) -> List[dict]:
        """
        Look up all bugs with a specific bug_group_id.

        Args:
            group_id (str): The bug_group_id to look up

        Returns:
            List[dict]: List of bug objects with the specified group_id
        """
        return self.bug_group_index.get(group_id, [])

    def print_bug(self, bug: Union[dict, List[dict]], indent: int = 2) -> None:
        """
        Pretty print bug(s) to console.

        Args:
            bug: Single bug dict or list of bug dicts
            indent: Number of spaces for JSON indentation
        """
        if isinstance(bug, list):
            print(f"Found {len(bug)} bugs:")
            for b in bug:
                print(json.dumps(b, indent=indent, ensure_ascii=False))
                print()
        else:
            print(json.dumps(bug, indent=indent, ensure_ascii=False))


def main():
    parser = argparse.ArgumentParser(
        description="Update and lookup bugs in JSONLines file"
    )
    subparsers = parser.add_subparsers(dest="command", help="Commands")

    # Update command (renamed from process)
    update_parser = subparsers.add_parser("update", help="Update input file with UUIDs")
    update_parser.add_argument("input_file", help="Input JSONLines file path")
    update_parser.add_argument("output_file", help="Output JSONLines file path")

    # Lookup commands
    lookup_parser = subparsers.add_parser("lookup", help="Look up bugs by ID")
    lookup_parser.add_argument("file", help="Processed JSONLines file to search in")
    lookup_parser.add_argument("--bug-id", help="Look up by specific bug_id")
    lookup_parser.add_argument("--bug-group-id", help="Look up by bug_group_id")

    args = parser.parse_args()
    processor = BugProcessor()

    try:
        if args.command == "update":
            processor.update_file(args.input_file, args.output_file)
            print(f"Successfully updated {args.input_file} to {args.output_file}")

        elif args.command == "lookup":
            processor.load_existing_file(args.file)

            if args.bug_id:
                bug = processor.lookup_by_bug_id(args.bug_id)
                if bug:
                    print("Found bug:")
                    processor.print_bug(bug)
                else:
                    print(f"No bug found with bug_id: {args.bug_id}")

            elif args.group_id:
                bugs = processor.lookup_by_group_id(args.group_id)
                if bugs:
                    processor.print_bug(bugs)
                else:
                    print(f"No bugs found with bug_group_id: {args.group_id}")

            else:
                print("Please specify either --bug-id or --bug-group-id")

    except FileNotFoundError as e:
        print(f"Error: File not found - {e.filename}")
        exit(1)
    except PermissionError:
        print("Error: Permission denied when accessing files")
        exit(1)
    except Exception as e:
        print(f"Error: {e}")
        exit(1)


if __name__ == "__main__":
    main()
