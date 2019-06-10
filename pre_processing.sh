#!/bin/bash
START=$(date +%s)

g++ -o organize_text -std=c++11 organize_text.cpp
./organize_text
python sorting_data.py
g++ -o generators -std=c++11 generators.cpp -lboost_iostreams
./generators

END=$(date +%s)
DIFF=$(( $END - $START ))
echo "It took $DIFF seconds"
