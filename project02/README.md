# Project 2 - Sorting List-Based Strings and Numbers

**[Project 2 Write Up](https://github.com/logantillman/cs_302/blob/master/project02/project02.pdf)**

## Data Structures / Algorithms Used

* STL Sort
* Qsort
* Merge Sort
* Quick Sort

## Compile Instructions

This project can be compiled by typing `make` in the base directory

    ~/project02>
    $ make

## Running the Program

To run `volsort` correctly, you need to specify the mode flag `-m` followed by the sorting method (`oblivious`, `stl`, `qsort`, `merge`, or `quick`). Then, you need to pipe in numbers from a `.txt` file for the program to sort.

    $ volsort -h
    usage: volsort
        -m MODE   Sorting mode (oblivious, stl, qsort, merge, quick)
        -n        Perform numerical ordering

Example:

`input.txt`

    90
    97
    50
    12
    32
    37
    71
    69
    37
    61

Running `volsort` on `input.txt`:

    $ volsort -m quick < input.txt
    12
    32
    37
    37
    50
    61
    69
    71
    90
    97

## Benchmarks

| Mode    | Size     | Elapsed Time  |
|---------|----------|---------------|
| STL     | 10       | 0.003s        | 
| STL     | 100      | 0.003s        | 
| STL     | 1000     | 0.005s        | 
| STL     | 10000    | 0.036s        | 
| STL     | 100000   | 0.345s        |
| STL     | 1000000  | 7.165s        | 
| STL     | 10000000 | 87.27s        | 
| QSORT   | 10       | 0.002s        | 
| QSORT   | 100      | 0.002s        | 
| QSORT   | 1000     | 0.004s        | 
| QSORT   | 10000    | 0.036s        | 
| QSORT   | 100000   | 0.348s        |
| QSORT   | 1000000  | 7.424s        | 
| QSORT   | 10000000 | 89.84s        | 
| MERGE   | 10       | 0.002s        | 
| MERGE   | 100      | 0.002s        | 
| MERGE   | 1000     | 0.005s        | 
| MERGE   | 10000    | 0.036s        | 
| MERGE   | 100000   | 0.349s        |
| MERGE   | 1000000  | 6.921s        | 
| MERGE   | 10000000 | 86.91s        | 
| QUICK   | 10       | N/A           | 
| QUICK   | 100      | N/A           | 
| QUICK   | 1000     | N/A           | 
| QUICK   | 10000    | N/A           | 
| QUICK   | 100000   | N/A           |
| QUICK   | 1000000  | N/A           | 
| QUICK   | 10000000 | N/A           | 
  
## Contributions
  
Grant:
    
    -STL.cpp
    -Qsort.cpp
    -Markdown Table
    
Matthew:
  
     -Merge.cpp
     
Logan:
   
    -List.cpp
    
    -Quick.cpp
