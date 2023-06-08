#!/bin/bash

## To run BnB DFS algorithm
echo "BNB" > result_bnb.csv
for file in tests/tsp-problem-*.txt
do
    echo $file
    ./agent sls $file >> result_bnb.csv
    echo "sleeping for 5s"
    sleep 5s
done

## To run SA SLS algorithm
echo "SLS" > result_sls.csv
for file in tests/tsp-problem-*.txt
do
    echo $file
    ./agent sls $file >> result_sls.csv
    echo "sleeping for 2s"
    sleep 2s
done

## To run DP algorithm
echo "DP" > result_dp.csv
for file in tests/tsp-problem-*.txt
do
    echo $file
    ./agent dp $file >> result_sls.csv
    echo "sleeping for 2s"
    sleep 2s
done