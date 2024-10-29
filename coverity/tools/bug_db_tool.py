#!/usr/bin/env python3
import argparse
from bug_db import BugDatabase

# python script.py update input.jsonl output.jsonl
# python script.py lookup output.jsonl --bug-id "bug-id"
# python script.py lookup output.jsonl --bug-group-id "bug-group-id"


def main():
    parser = argparse.ArgumentParser(
        description="Update and lookup bugs in JSONLines file"
    )
    subparsers = parser.add_subparsers(dest="command", help="Commands")

    # Update command
    update_parser = subparsers.add_parser("update", help="Update input file with UUIDs")
    update_parser.add_argument("input_file", help="Input JSONLines file path")
    update_parser.add_argument("output_file", help="Output JSONLines file path")

    # Lookup commands
    lookup_parser = subparsers.add_parser("lookup", help="Look up bugs by ID")
    lookup_parser.add_argument("file", help="Processed JSONLines file to search in")
    lookup_parser.add_argument("--bug-id", help="Look up by specific bug_id")
    lookup_parser.add_argument("--bug-group-id", help="Look up by bug_group_id")

    args = parser.parse_args()
    processor = BugDatabase()

    try:
        if args.command == "transform":
            processor.transform_file(args.input_file, args.output_file)
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

            elif args.bug_group_id:
                bugs = processor.lookup_by_group_id(args.bug_group_id)
                if bugs:
                    processor.print_bug(bugs)
                else:
                    print(f"No bugs found with bug_group_id: {args.bug_group_id}")

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
