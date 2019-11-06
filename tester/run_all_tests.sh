#/usr/bin/env bash

DIR=$(readlink -f $(dirname $0))
set -e

for i in $(find $DIR/../code -name "*.test.cpp")
do
	cur="${i%.test.cpp}.cpp"
	echo testing $cur
	$DIR/run_test.sh $cur >> logs.txt
	echo done testing $cur
done

echo all done
sleep 3
