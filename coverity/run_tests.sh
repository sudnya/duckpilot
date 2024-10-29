#!/bin/bash -x

MODEL_ID="42f0b54244212e2b899857690f4b211ff6de8b82af2e81c22165daec8a95233f"
INPUT_FILE="/app/duckpilot-coverity/dataset/tuning/inputs/long-diff-variants.jsonlines"
GOLD_RESULT_FILE="/app/duckpilot-coverity/dataset/tuning/visualize_diffs/long-diff-variants-1.txt"

# long-diff-variants-1.txt is the gold result for the test

index=2

while [ $index -le 20 ]
do
    LLM_OUTPUT_FILE="/app/duckpilot-coverity/dataset/tuning/results/long-diff-variants-${index}.jsonlines"
    RESULT_FILE="/app/duckpilot-coverity/dataset/tuning/visualize_diffs/long-diff-variants-${index}.txt"

    # print to the console only what's explicitly printed here with echo
    echo "Running test ${index}"

    # run eval and measure time taken
    start_time=$(date +%s)
    ./eval/run.sh -i ${INPUT_FILE} -o ${LLM_OUTPUT_FILE} -m ${MODEL_ID}  > /dev/null 2>&1
    end_time=$(date +%s)
    eval_time=$(( $end_time - $start_time ))
    echo "Eval time: ${eval_time} seconds"

    # print results
    ./visualize/run.sh -i ${LLM_OUTPUT_FILE} -o ${RESULT_FILE} > /dev/null 2>&1

    # compare the printed results with the gold result
    echo "Comparing ${GOLD_RESULT_FILE} with ${RESULT_FILE}"

    # print success if the files are the same.
    # Otherwise, print failed and also print the diff
    result=$(diff ${GOLD_RESULT_FILE} ${RESULT_FILE} || true)

    if [ -z "$result" ]; then
        echo "Test ${index} succeeded"
    else
        echo "Test ${index} failed"
        echo $result
    fi

    # sleep for 3 seconds
    echo "Sleeping for 3 seconds"
    sleep 3

    index=$(( $index + 1 ))
done