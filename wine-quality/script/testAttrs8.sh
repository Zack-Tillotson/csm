#!/bin/bash

# For each 10 attr combination
for((a=1; a<=12; a++)); do
for((b=`expr $a + 1`; b<=12; b++)); do
for((c=`expr $b + 1`; c<=12; c++)); do
for((d=`expr $c + 1`; d<=12; d++)); do
for((e=`expr $d + 1`; e<=12; e++)); do
for((f=`expr $e + 1`; f<=12; f++)); do
for((g=`expr $f + 1`; g<=12; g++)); do
for((h=`expr $g + 1`; h<=12; h++)); do

	ARGSTR="$a $b $c $d $e $f $g $h $i $j $k $l"

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $ARGSTR > tmp8.train.arff
	perl selectAttrs.pl wq-test.arff $ARGSTR > tmp8.test.arff

	# Run the weka program
	./runModels.sh "$ARGSTR" tmp8.train.arff tmp8.test.arff

	# Clean up
	rm tmp8.*

done
done
done
done
done
done
done
done
