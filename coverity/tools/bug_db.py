#!/usr/bin/env python3
import json
import uuid
from pathlib import Path
from collections import OrderedDict, defaultdict
from typing import Dict, List, Optional, Union
import copy


class BugDatabase:
    def __init__(self):
        self.bug_id_index: Dict[str, dict] = {}
        self.bug_group_index: Dict[str, List[dict]] = defaultdict(list)

    def transform_file(self, input_file: str, output_file: str) -> None:
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

    def lookup_by_group_id(self, bug_group_id: str) -> List[dict]:
        """
        Look up all bugs with a specific bug_group_id.

        Args:
            bug_group_id (str): The bug_group_id to look up

        Returns:
            List[dict]: List of bug objects with the specified bug_group_id
        """
        return self.bug_group_index.get(bug_group_id, [])

    def prepare_for_display(self, bug: dict) -> dict:
        """
        Prepare a bug object for display by truncating the code field.

        Args:
            bug: Bug dictionary to prepare

        Returns:
            dict: Modified bug dictionary with truncated code field
        """
        # Make a deep copy to avoid modifying the original
        display_bug = copy.deepcopy(bug)
        if "code" in display_bug:
            display_bug["code"] = "..."
        return display_bug

    def print_bug(self, bug: Union[dict, List[dict]], indent: int = 2) -> None:
        """
        Pretty print bug(s) to console with truncated code field.

        Args:
            bug: Single bug dict or list of bug dicts
            indent: Number of spaces for JSON indentation
        """
        if isinstance(bug, list):
            print(f"Found {len(bug)} bugs:")
            for b in bug:
                display_bug = self.prepare_for_display(b)
                print(json.dumps(display_bug, indent=indent, ensure_ascii=False))
                print()
        else:
            display_bug = self.prepare_for_display(bug)
            print(json.dumps(display_bug, indent=indent, ensure_ascii=False))
