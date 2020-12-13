#!/usr/bin/env bash

DIR=$(readlink -f $(dirname $0))
DIR2=$(readlink -f $(dirname $1))
TEST=$(basename ${1%.*})

#echo $DIR >> $DIR/logs.txt
#echo $DIR2 >> $DIR/logs.txt

cd $DIR2
rm -f $DIR/tmp.cpp
cp $DIR/header.cpp $DIR/tmp.cpp
echo "" >> $DIR/tmp.cpp
echo "#include \"$DIR2/$TEST.cpp\"" >> $DIR/tmp.cpp
cat $DIR/test_header.cpp >> $DIR/tmp.cpp
echo "" >> $DIR/tmp.cpp
echo "#line 1 \"$DIR2/$TEST.test.cpp\"" >> $DIR/tmp.cpp
cat "$DIR2/$TEST.test.cpp" >> $DIR/tmp.cpp
echo "" >> $DIR/tmp.cpp
cat $DIR/test_footer.cpp >> $DIR/tmp.cpp
set -e

echo -------------------------- >> $DIR/logs.txt
echo start testing $1 >> $DIR/logs.txt
${CXX-g++} $DIR/tmp.cpp -Wall -Wshadow -Wpedantic -Wno-long-long -Wno-sign-compare -std=c++17 -g -o $DIR/tmp.exe >> $DIR/logs.txt
echo compiled $1 >> $DIR/logs.txt
$DIR/tmp.exe >> $DIR/logs.txt
echo done testing $1 >> $DIR/logs.txt
