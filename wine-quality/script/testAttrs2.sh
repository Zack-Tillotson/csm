#!/bin/bash

# For each 10 attr combination
for((a=1; a<=12; a++)); do
for((b=`expr $a + 1`; b<=12; b++)); do

	ARGSTR="$a $b"

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $ARGSTR > tmp2.train.arff
	perl selectAttrs.pl wq-test.arff $ARGSTR > tmp2.test.arff

	# Run the weka program
	java -cp /usr/share/java/weka.jar weka.classifiers.trees.J48 -t tmp2.train.arff -T tmp2.test.arff | tail -16 | head -1 | awk '{print "'2-`echo $ARGSTR | sed 's/ /,/g'`='" $5}'

	# Clean up
	rm tmp2.*

done
done
