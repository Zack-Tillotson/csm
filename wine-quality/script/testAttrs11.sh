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
for((i=`expr $h + 1`; i<=12; i++)); do
for((j=`expr $i + 1`; j<=12; j++)); do
for((k=`expr $j + 1`; k<=12; k++)); do

	ARGSTR="$a $b $c $d $e $f $g $h $i $j $k"

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $ARGSTR > tmp11.train.arff
	perl selectAttrs.pl wq-test.arff $ARGSTR > tmp11.test.arff

	# Run the weka program
	./runModels.sh "$ARGSTR" tmp11.train.arff tmp11.test.arff

	# Clean up
	rm tmp11.*

done
done
done
done
done
done
done
done
done
done
done
