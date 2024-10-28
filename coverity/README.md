# Step 1: dataprep
 currently done manually

# Step 2: eval pipeline
`➜  coverity git:(sudnya.diff-pilot) ✗ ./eval/run.sh -i /app/duckpilot-coverity/dataset/tuning/inputs/input-perturbed-gold-test-set.jsonlines -o /app/duckpilot-coverity/dataset/tuning/results/input-perturbed-gold-test-set-200trainingsteps.jsonlines -m model_hash_here`

use the file that you want to run eval on. jsonlines format expected

# Step 3: visualize
`➜  coverity git:(sudnya.diff-pilot) ✗ ./visualize/run.sh -i /app/duckpilot-coverity/dataset/tuning/results/input-perturbed-gold-test-set.jsonlines -o /app/duckpilot-coverity/dataset/tuning/visualize_diffs/gold-diff.txt`

diffs that will need to be manually inspected. #TODO: best open src tool to do this easily.

# Step 4: train
` ➜  coverity git:(sudnya.diff-pilot) ✗ ./train/run.sh -i /app/duckpilot-coverity/dataset/input-perturbed-gold-test-set.jsonlines`

use the file that contains all the examples that you'd like to fine tune the model on


