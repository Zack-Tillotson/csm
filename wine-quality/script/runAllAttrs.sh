#!/bin/bash

rm results.txt 2>/dev/null

# Run all the attr tests
for((z=1; z<=12; z++)); do

	echo "Running testAttrs$z.sh"
	./testAttrs$z.sh >> results.txt &

done
