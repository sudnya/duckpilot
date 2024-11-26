# Data Processing Documentation
## Source Files
`gold-test-set.jsonlines`
Original dataset created from the raw data in `dataset/raw_data/bugs/gold-test-set`

`test-overfit-input-perturbed-gold-test-set.jsonlines`
Generated from gold-test-set.jsonlines

For each example, 3 variant bug descriptions were generated

Used playground with the following prompt:
```please rephrase the following bug report and mainly focus on rewording the description. do this 3 times [FOLLOWED BY VALUE in the bug_report_text]```


## Flow

### Test Overfitting
1. Start with base dataset `gold-test-set.jsonlines`
2. Generate variations using playground
3. Store perturbed versions in `test-overfit-input-perturbed-gold-test-set.jsonlines`

The purpose of the input perturbation was to create variant descriptions while maintaining the core bug information, providing more diverse training examples.

### Test Generalization
1. Evaluate `gold-test-set.jsonlines`
2. Add examples in training set for misses `dataset/raw_data/bugs/dev-set` 
3. Generate `training-set.jsonlines`
3. Tune a new model with `training-set.jsonlines`
4. Evaluate `training-set.jsonlines`
5. Go to step 1.
