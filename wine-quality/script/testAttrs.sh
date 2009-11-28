#!/bin/bash

# For each 1 attr combination
for((i=1; i<=12; i++)); do

	# Create training and test arff files
	perl selectAttrs.pl wq-train.arff $i > tmp.train.arff
	perl selectAttrs.pl wq-test.arff $i > tmp.test.arff

	# Run the weka program
	java -cp /usr/share/java/weka.jar weka.classifiers.trees.J48 -t tmp.train.arff -T tmp.test.arff | tail -16 | head -1 | awk '{print "'1-$i='" $5}'

	# Clean up
	rm tmp.*

done

# For each 2 attr combination
for((i=1; i<=12; i++)); do
	for((j=$i; j<=12; j++)); do

		if [ $i -eq $j ]; then continue; fi

		# Create training and test arff files
		perl selectAttrs.pl wq-train.arff $i $j > tmp.train.arff
		perl selectAttrs.pl wq-test.arff $i $j > tmp.test.arff

		# Run the weka program
		java -cp /usr/share/java/weka.jar weka.classifiers.trees.J48 -t tmp.train.arff -T tmp.test.arff | tail -16 | head -1 | awk '{print "'2-$i,$j='" $5}'

		# Clean up
		rm tmp.*

	done
done

# For each 3 attr combination
for((i=1; i<=12; i++)); do
	for((j=$i; j<=12; j++)); do
		for((k=$j; k<=12; k++)); do

			if [ $i -eq $j ]; then continue; fi
			if [ $i -eq $k ]; then continue; fi
			if [ $j -eq $k ]; then continue; fi

			# Create training and test arff files
			perl selectAttrs.pl wq-train.arff $i $j $k > tmp.train.arff
			perl selectAttrs.pl wq-test.arff $i $j $k > tmp.test.arff

			# Run the weka program
			java -cp /usr/share/java/weka.jar weka.classifiers.trees.J48 -t tmp.train.arff -T tmp.test.arff | tail -16 | head -1 | awk '{print "'3-$i,$j,$k='" $5}'

			# Clean up
			rm tmp.*

		done
	done
done
