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
for((l=`expr $k + 1`; l<=12; l++)); do

	ARGSTR="$a $b $c $d $e $f $g $h $i $j $k $l"

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $ARGSTR > tmp12.train.arff
	perl selectAttrs.pl wq-test.arff $ARGSTR > tmp12.test.arff

	# Run the weka program
	java -cp /usr/share/java/weka.jar weka.classifiers.trees.J48 -t tmp12.train.arff -T tmp12.test.arff | tail -16 | head -1 | awk '{print "'12-`echo $ARGSTR | sed 's/ /,/g'`='" $5}'

	# Clean up
	rm tmp12.*

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
done
