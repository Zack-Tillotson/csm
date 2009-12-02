#!/bin/bash

# For each 1 attr combination
for((a=1; a<=12; a++)); do

	ARGSTR="$a"

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $ARGSTR > tmp1.train.arff
	perl selectAttrs.pl wq-test.arff $ARGSTR > tmp1.test.arff

	# Run the weka program
	java -cp /usr/share/java/weka.jar weka.classifiers.trees.J48 -t tmp1.train.arff -T tmp1.test.arff | tail -16 | head -1 | awk '{print "'1-`echo $ARGSTR | sed 's/ /,/g'`='" $5}'

	# Clean up
	rm tmp1.*

done
