# Solutions for Travelling Salesman Problem

## Instructions to Build code
1. goto TravellingSalesman/Travelling-Salesman-Problem folder using command:
   ```
   cd TravellingSalesman/Travelling-Salesman-Problem
   ```
2. run make command: 
   ```
   make
   ```
   This make command will create an executable called `agent`


## Instructions to Execute code for 1 file

1. The agent take 2 parameters:
1. parameter 1 : bnb OR sls OR dp
            - bnb - runs BnB DFS algorithm
            - sls - runs Simulated Annealing SLS algorithm
            - dp - runs Dynamic programming algorithm

- For Example:
   ```
   ./agent bnb tests/tsp-problem-25-6-100-5-1.txt
   ./agent sls tests/tsp-problem-25-6-100-5-1.txt
   ./agent dp tests/tsp-problem-25-6-100-5-1.txt
  ```

All programs prints the last result only.

Output Format:
   1. BnB: file_path, timeout, time taken to caluclate result in ms, cost, number of expanded nodes, number of pruned nodes, path
   2. SLS: file_path, timeout,  time taken to caluclate result in ms, cost, number of iterations taken
   3. DP: file_path, timeout,  time taken to caluclate result in ms, cost
    
NOTE: if program did not timeout, then second column would be empty

## Instructions to Execute code for more than 1 files

1. To run multiple files in one go, just edit the run_tests.sh file accordingly.
2. The script produces csv files with outputs : result_bnb.csv, result_sls.csv
3. For example:
        1. To run both BnB and SLS, no need to modify the file, just run the command:
            chmod +x run_tests.sh
            ./run_tests.sh
        2. To run only BnB algo, comment SLS part inside the script and run it
        3. To run only SLS algo, comment BnB part inside the script and run it
