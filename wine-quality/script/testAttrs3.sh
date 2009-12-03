#!/bin/bash

# For each 10 attr combination
for((a=1; a<=12; a++)); do
for((b=`expr $a + 1`; b<=12; b++)); do
for((c=`expr $b + 1`; c<=12; c++)); do

	ARGSTR="$a $b $c"

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $ARGSTR > tmp3.train.arff
	perl selectAttrs.pl wq-test.arff $ARGSTR > tmp3.test.arff

	# Run the weka program
	./runModels.sh "$ARGSTR" tmp3.train.arff tmp3.test.arff

	# Clean up
	rm tmp3.*

done
done
done
