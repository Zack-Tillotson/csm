#!/bin/bash

# For each 1 attr combination
for((a=1; a<=12; a++)); do

	ARGSTR="$a"

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $ARGSTR > tmp1.train.arff
	perl selectAttrs.pl wq-test.arff $ARGSTR > tmp1.test.arff

	# Run the weka program
	./runModels.sh "$ARGSTR" tmp1.train.arff tmp1.test.arff

	# Clean up
	rm tmp1.*

done
