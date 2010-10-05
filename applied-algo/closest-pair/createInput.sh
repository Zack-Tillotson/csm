SIZE=$1

echo $SIZE
for((i=0; i<$SIZE; i++)); do
	echo $((RANDOM % 40000)).$((RANDOM % 100)) $((RANDOM % 40000)).$((RANDOM % 100))
done
echo 0
