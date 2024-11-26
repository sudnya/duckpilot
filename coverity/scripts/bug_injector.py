import re
import random
import os
import argparse
import logging

##### DEPRECATED!!!! Do not use. Instead call an LLM to generate more training samples.

# Set up logging
logging.basicConfig(
    level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s"
)
logger = logging.getLogger(__name__)


def inject_null_pointer_dereference(content):
    r"""This function attempts to inject a null pointer dereference bug into the given C code content

    Find all pointer declarations in the code
    The regex pattern '\w+\s*\*\s*\w+' matches:
      \w+ : one or more word characters (for the type)
      \s* : zero or more whitespace characters
      \* : the asterisk for pointer declaration
      \s* : zero or more whitespace characters
      \w+ : one or more word characters (for the variable name)
    """
    pointer_declarations = re.findall(r"\w+\s*\*\s*\w+", content)

    # If no pointer declarations are found, return the original content unchanged
    if not pointer_declarations:
        return content

    # Randomly select one of the found pointer declarations
    chosen_declaration = random.choice(pointer_declarations)

    # Extract the name of the pointer variable
    # This splits the declaration at the '*' and takes the last part (the variable name)
    # The strip() removes any leading or trailing whitespace
    pointer_name = chosen_declaration.split("*")[-1].strip()

    # Split the content into individual lines
    lines = content.split("\n")

    # Find all suitable lines where we could inject the bug
    # A line is suitable if it contains the pointer name but doesn't have an assignment (=)
    # This helps avoid injecting the bug in a declaration or assignment statement
    suitable_lines = [
        i for i, line in enumerate(lines) if pointer_name in line and "=" not in line
    ]

    # If no suitable lines are found, return the original content unchanged
    if not suitable_lines:
        return content

    # Randomly choose one of the suitable lines for bug injection
    chosen_line = random.choice(suitable_lines)

    # Construct the bug injection code
    # This creates an if statement that checks if the pointer is NULL, then dereferences it
    # The original line is kept after the injected code
    # TODO: Sudnya - rm the text '// Injected bug: Null pointer dereference' before feeding model
    # otherwise model will learn to use that crutch, which won't exist in actual code.
    bug_code = f"    if ({pointer_name} == NULL) {{ *{pointer_name} = 0; }}  // Injected bug: Null pointer dereference\n"
    lines[chosen_line] = bug_code + lines[chosen_line]

    # Join the modified lines back into a single string and return it
    return "\n".join(lines)


def inject_buffer_overflow(content):
    """
    Injects a buffer overflow bug into the given C code content.

    This function identifies array declarations, selects one randomly,
    and injects a for loop that intentionally causes a buffer overflow.

    Args:
    content (str): The original C code content

    Returns:
    str: The modified C code content with an injected buffer overflow bug,
         or the original content if injection was not possible
    """

    # Find all array declarations in the code
    # This regex pattern matches array declarations like "int arr[10]"
    # It captures the array name and size as separate groups
    array_declarations = re.findall(r"(\w+)\s*\[(\d+)\]", content)

    # If no array declarations are found, return the original content unchanged
    if not array_declarations:
        return content

    # Randomly select one of the found array declarations
    # 'chosen_array' will be the array name, 'size' will be its declared size
    chosen_array, size = random.choice(array_declarations)

    # Split the content into individual lines for easier manipulation
    lines = content.split("\n")

    # Find all suitable lines for bug injection
    # A line is suitable if it contains the chosen array name and a square bracket
    # This helps target lines where the array is likely being accessed
    suitable_lines = [
        i for i, line in enumerate(lines) if chosen_array in line and "[" in line
    ]

    # If no suitable lines are found, return the original content unchanged
    if not suitable_lines:
        return content

    # Randomly choose one of the suitable lines for bug injection
    chosen_line = random.choice(suitable_lines)

    # Construct the bug injection code
    # This creates a for loop that intentionally accesses the array out of bounds
    # The loop goes from 0 to size (inclusive), causing an overflow on the last iteration
    # TODO: Sudnya - rm the text '// Injected bug: Buffer overflow' before feeding model
    # otherwise model will learn to use that crutch, which won't exist in actual code.
    bug_code = f"    for(int i = 0; i <= {size}; i++) {{ {chosen_array}[i] = 0; }}  // Injected bug: Buffer overflow\n"

    # Insert the bug code before the chosen line
    # This preserves the original line while adding our bug-inducing code
    lines[chosen_line] = bug_code + lines[chosen_line]

    # Join the modified lines back into a single string and return it
    return "\n".join(lines)


def inject_memory_leak(content):
    """
    Inject a memory leak bug into the given C code.

    This function finds malloc calls in the provided C code, randomly selects
    one, and removes a corresponding free() call, thus introducing a
    memory leak.

    Args:
        content (str): A string containing C code.

    Returns:
        str: The modified C code with an injected memory leak, or the original
             code if no suitable injection point was found.

    Note:
        This function is intended for educational or testing purposes only.
        Intentionally introducing bugs in production code is not recommended.
    """
    # Find all lines where memory is allocated using malloc
    malloc_lines = re.findall(r"(\w+)\s*=\s*malloc\(", content)

    # If no malloc calls are found, return the original content
    if not malloc_lines:
        return content

    # Randomly choose one of the variables that had memory allocated
    chosen_var = random.choice(malloc_lines)

    # Split the content into individual lines
    lines = content.split("\n")

    # Find all line numbers where the chosen variable is being freed
    suitable_lines = [i for i, line in enumerate(lines) if "free(" + chosen_var in line]

    # If no lines are found where the chosen variable is freed, return the original content
    if not suitable_lines:
        return content

    # Randomly choose one of the lines where the variable is freed
    chosen_line = random.choice(suitable_lines)

    # Remove the free() call line
    del lines[chosen_line]

    # Insert a comment explaining the injected bug
    # TODO: Sudnya - rm the text '// Injected bug: ...' before feeding model
    # otherwise model will learn to use that crutch, which won't exist in actual code.
    lines.insert(
        chosen_line, f"    // Injected bug: Memory leak (free({chosen_var}) removed)"
    )

    # Join the modified lines back into a single string and return it
    return "\n".join(lines)


def inject_use_after_free(content):
    """
    Inject a use-after-free bug into the given C code.

    This function finds free() calls in the provided C code, randomly selects
    one, and inserts a line of code that uses the freed variable immediately
    after the free() call, thus introducing a use-after-free bug.

    Args:
        content (str): A string containing C code.

    Returns:
        str: The modified C code with an injected use-after-free bug, or the
             original code if no suitable injection point was found.

    Note:
        This function is intended for educational or testing purposes only.
        Intentionally introducing bugs in production code is not recommended.
    """
    # Find all variables being freed using free()
    free_lines = re.findall(r"free\((\w+)\)", content)

    # If no free() calls are found, return the original content
    if not free_lines:
        return content

    # Randomly choose one of the variables that was freed
    chosen_var = random.choice(free_lines)

    # Split the content into individual lines
    lines = content.split("\n")

    try:
        # Find the index of the line where the chosen variable is freed
        free_line_index = next(
            i for i, line in enumerate(lines) if f"free({chosen_var})" in line
        )

        # Insert a line that uses the freed variable right after the free() call
        lines.insert(
            free_line_index + 1,
            # TODO: Sudnya - rm the text '// Injected bug: ...' before feeding model
            # otherwise model will learn to use that crutch, which won't exist in actual code.
            f"    *{chosen_var} = 0;  // Injected bug: Use after free\n",
        )
    except StopIteration:
        # If we can't find the free() call, return the original content
        return content

    # Join the modified lines back into a single string and return it
    return "\n".join(lines)


import re
import random


def inject_integer_overflow(content):
    """
    Inject an integer overflow bug into the given C code.

    This function finds integer variable declarations in the provided C code,
    randomly selects one, and adds INT_MAX to it before its first assignment,
    thus potentially causing an integer overflow.

    Args:
        content (str): A string containing C code.

    Returns:
        str: The modified C code with an injected integer overflow bug, or the
             original code if no suitable injection point was found.

    Note:
        This function is intended for educational or testing purposes only.
        Intentionally introducing bugs in production code is not recommended.
    """
    # Find all integer variable declarations
    int_declarations = re.findall(r"int\s+(\w+)", content)

    # If no integer declarations are found, return the original content
    if not int_declarations:
        return content

    # Randomly choose one of the declared integer variables
    chosen_var = random.choice(int_declarations)

    # Split the content into individual lines
    lines = content.split("\n")

    # Find all line numbers where the chosen variable is assigned a value
    suitable_lines = [
        i for i, line in enumerate(lines) if chosen_var in line and "=" in line
    ]

    # If no suitable lines are found, return the original content
    if not suitable_lines:
        return content

    # Randomly choose one of the suitable lines
    chosen_line = random.choice(suitable_lines)

    # Insert a line that adds INT_MAX to the chosen variable before its assignment
    lines[chosen_line] = (
        # TODO: Sudnya - rm the text '// Injected bug: Integer overflow before feeding model
        # otherwise model will learn to use that crutch, which won't exist in actual code.
        f"    {chosen_var} += INT_MAX;  // Injected bug: Integer overflow\n"
        + lines[chosen_line]
    )

    # Join the modified lines back into a single string and return it
    return "\n".join(lines)


def inject_bug(file_path, output_path):
    with open(file_path, "r") as file:
        ref_content = file.read()

    bug_injectors = {
        "null_ptr_deref": inject_null_pointer_dereference,
        "buff_overflow": inject_buffer_overflow,
        "mem_leak": inject_memory_leak,
        "use_after_free": inject_use_after_free,
        "int_overflow": inject_integer_overflow,
    }

    content = ref_content
    for k, v in bug_injectors.items():
        logger.info(f"Injecting bug: {k} in file {file_path}\n")
        # logger.info(content)
        modified_content = v(content)
        # logger.info(modified_content)
        if modified_content != content:
            with open(output_path, "w") as output_file:
                output_file.write(modified_content)
        content = modified_content


def process_directory(input_dir, output_dir):
    for root, _, files in os.walk(input_dir):
        for file in files:
            if file.endswith(".c"):
                input_path = os.path.join(root, file)
                output_path = os.path.join(
                    output_dir, os.path.relpath(input_path, input_dir)
                )
                os.makedirs(os.path.dirname(output_path), exist_ok=True)
                if inject_bug(input_path, output_path):
                    logger.debug(f"Injected bug in {output_path}")
                else:
                    logger.debug(f"Failed to inject bug in {input_path}")
            else:
                logger.info(f"Skipping non C file {file}")


def main():
    """
    Main function
    """
    # Set up command-line argument parser
    parser = argparse.ArgumentParser(
        description="Inject bugs in the C files under input directory"
    )
    parser.add_argument(
        "-i",
        "--inputdir",
        type=str,
        default="/tmp/cov/input/",
        help="input dir containing source C files",
    )
    parser.add_argument(
        "-o",
        "--outputdir",
        type=str,
        default="/tmp/cov/buggy/",
        help="output dir containing C files with bugs",
    )

    args = parser.parse_args()

    input_directory = args.inputdir  # "/tmp/cov/input/"
    output_directory = args.outputdir  # "/tmp/cov/buggy/"
    process_directory(input_directory, output_directory)


# Entry point of the script
if __name__ == "__main__":
    main()
