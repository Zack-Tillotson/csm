#!/bin/bash

ARGSTR="$1"
TRAINFILE="$2"
TESTFILE="$3"

# Trees - J48
java -cp /usr/share/java/weka.jar weka.classifiers.trees.J48 -t $TRAINFILE -T $TESTFILE | tail -16 | head -1 | awk '{print "'1-j48-`echo $ARGSTR | sed 's/ /,/g'`='" $5}'

# Boosting - J48
java -cp /usr/share/java/weka.jar weka.classifiers.meta.AdaBoostM1 -P 100 -S 1 -I 5 -t $TRAINFILE -T $TESTFILE -W weka.classifiers.trees.J48 -- -C 0.25 -M 2  | tail -16 | head -1 | awk '{print "'1-boostedJ48-`echo $ARGSTR | sed 's/ /,/g'`='" $5}'	

# KNN - IBk with 1/n weights
for((i=1; i<20; i++)); do 
	java -cp /usr/share/java/weka.jar weka.classifiers.lazy.IBk -K $i -W 0 -I -A "weka.core.neighboursearch.LinearNNSearch -A \"weka.core.EuclideanDistance -R first-last\"" -t $TRAINFILE -T $TESTFILE | tail -16 | head -1 | awk '{print "'1-"$i"NN-`echo $ARGSTR | sed 's/ /,/g'`='" $5}'
done

# ANN - MultilayerPerceptron
java -cp /usr/share/java/weka.jar weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 1000 -V 5 -S 0 -E 20 -H 2 -t $TRAINFILE -T $TESTFILE | tail -16 | head -1 | awk '{print "'1-ann-`echo $ARGSTR | sed 's/ /,/g'`='" $5}'
