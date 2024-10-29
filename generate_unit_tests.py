# Import required libraries
import argparse  # For parsing command-line arguments
import requests  # For making HTTP requests

# from anthropic import Anthropic, HUMAN_PROMPT, AI_PROMPT  # Anthropic API client and constants
import anthropic


def get_api_key(client_type):
    import json

    # Load the config.json file
    with open("config.json") as config_file:
        config = json.load(config_file)

    if client_type == "anthropic":
        # Fetch the API key
        api_key = config.get("anthropic_api_key")
    if client_type == "openai":
        # Fetch the API key
        api_key = config.get("openai_api_key")

    if api_key:
        print(f"API Key loaded successfully {api_key}")
    else:
        print("API Key not found")
        assert True, "API Key not found"
    return api_key


def download_code_snippet(url):
    """
    Download the content of a code snippet from a given URL.

    Args:
    url (str): The URL of the code snippet.

    Returns:
    str or None: The content of the code snippet if successful, None otherwise.
    """
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an exception for bad status codes
        return response.text
    except requests.RequestException as e:
        print(f"Error downloading code snippet: {e}")
        return None


def call_claude_api(api_key, content, user_prompt):
    """
        Call the Claude API with the given content and user prompt.

        Args:
        api_key (str): The Anthropic API key.
        content (str): The code snippet content.
        user_prompt (str): The user's instruction for Claude.

        Returns:
        str or None: Claude's response if successful, None otherwise.
        message = client.messages.create(
    model="claude-3-opus-20240229",
    max_tokens=1000,
    temperature=0,
    system="Your task is to analyze the provided Python code snippet and suggest improvements to optimize its performance. Identify areas where the code can be made more efficient, faster, or less resource-intensive. Provide specific suggestions for optimization, along with explanations of how these changes can enhance the code's performance. The optimized code should maintain the same functionality as the original code while demonstrating improved efficiency.",
    messages=[
    {
    "role": "user",
    "content": [
    {
    "type": "text",
    "text": "def fibonacci(n):\n if n <= 0:\n return []\n elif n == 1:\n return [0]\n elif n == 2:\n return [0, 1]\n else:\n fib = [0, 1]\n for i in range(2, n):\n fib.append(fib[i-1] + fib[i-2])\n return fib"
    }
    ]
    }
    ]
    )
    """
    client = anthropic.Anthropic(api_key=api_key)
    try:
        completion = client.messages.create(
            model="claude-3-5-sonnet-20240620",
            max_tokens=3000,
            temperature=0,
            system=user_prompt,
            messages=[{"role": "user", "content": [{"type": "text", "text": content}]}],
        )
        return completion.content
    except Exception as e:
        print(f"Error calling Claude API: {e}")
        return None


def call_openai_api(api_key, code_snippet_content, user_prompt):
    # Define the endpoint and headers
    url = "https://api.openai.com/v1/chat/completions"
    headers = {"Authorization": f"Bearer {api_key}", "Content-Type": "application/json"}

    # Create the payload
    payload = {
        "model": "gpt-3.5-turbo",  # Change to the desired model
        "messages": [
            {"role": "user", "content": user_prompt},
            {"role": "user", "content": code_snippet_content},
        ],
        "max_tokens": 150,  # Adjust as needed
    }

    # Make the API request
    response = requests.post(url, headers=headers, json=payload)

    # Check for successful response
    if response.status_code == 200:
        # Extract and return the response text
        return response.json()["choices"][0]["message"]["content"]
    else:
        # Handle errors
        print(f"Error: {response.status_code} - {response.text}")
        return None


def main():
    """
    Main function to orchestrate the code snippet download and Claude API call process.
    """
    # Set up command-line argument parser
    parser = argparse.ArgumentParser(
        description="Download a code snippet and generate unit tests for it."
    )
    parser.add_argument(
        "-l",
        "--llm",
        type=str,
        default="anthropic",
        help="LLM Service to use (openai, anthropic)",
    )
    parser.add_argument(
        "-p",
        "--prompt",
        type=str,
        default="Write comprehensive unit tests for maximum coverage with comments",
        help="User prompt for LLM",
    )
    parser.add_argument(
        "-u",
        "--url",
        type=str,
        default="https://raw.githubusercontent.com/karpathy/llm.c/refs/heads/master/llmc/gelu.cuh",
        help="URL of the code snippet to download",
    )

    args = parser.parse_args()

    # Download the code snippet
    code_snippet_content = download_code_snippet(args.url)
    llm_service = args.llm
    api_key = get_api_key(llm_service)
    user_prompt = args.prompt

    if code_snippet_content:
        print("Code snippet content downloaded successfully.")
        if llm_service == "anthropic":
            print("Calling Claude API...")
            # Call anthropic API with the code snippet and user's prompt
            response = call_claude_api(api_key, code_snippet_content, user_prompt)
            if response:
                print("\nClaude's response:")
                print(response)
        if llm_service == "openai":
            print(f"Calling OpenAI API...{api_key}")
            # Call OpenAI API with the code snippet and user's prompt
            response = call_openai_api(api_key, code_snippet_content, user_prompt)
            if response:
                print("\ChatGPT's response:")
                print(response)
    else:
        print("Failed to process the code snippet.")


# Entry point of the script
if __name__ == "__main__":
    main()
