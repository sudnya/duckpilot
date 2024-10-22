# Data Processing Documentation
## Source Files
`gold-test-set.jsonlines`
Original dataset copied from preprocessing done by lamini-coverity

`input-perturbed-gold-test-set.jsonlines`
Generated from gold-test-set.jsonlines

For each example, 3 variant bug descriptions were generated

Used lamini playground with the following prompt:
```please rephrase the following bug report and mainly focus on rewording the description. do this 3 times [FOLLOWED BY VALUE in the bug_report_text]```


## Process Flow

1. Start with base dataset (gold-test-set.jsonlines)
2. Generate variations using lamini playground
3. Store perturbed versions in input-perturbed-gold-test-set.jsonlines

The purpose of this perturbation was to create variant descriptions while maintaining the core bug information, providing more diverse training examples.