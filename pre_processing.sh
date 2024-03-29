#!/bin/bash
START=$(date +%s)

mkdir sorted_texts sorted_titles
g++ -o organize_text -std=c++11 organize_text.cpp
./organize_text
python sorting_data.py
g++ -o generators -std=c++11 generators.cpp -lboost_iostreams
./generators
rm unsorted_texts.txt unsorted_titles.txt words_to_insert.txt sorted_words_to_insert.txt organize_text generators tries_wc

END=$(date +%s)
DIFF=$(( $END - $START ))
echo "It took $DIFF seconds"
