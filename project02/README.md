# Project02

| Mode    | Size     | Elapsed Time  |
|---------|----------|---------------|
| STL     | 10       | 0.003s        | 
| STL     | 100      | 0.003s        | 
| STL     | 1000     | 0.005s        | 
| STL     | 10000    | 0.036s        | 
| STL     | 100000   | 0.345s        |
| STL     | 1000000  | 7.165s        | 
| STL     | 10000000 | 1m 27.27s     | 
| QSORT   | 10       | 0.002s        | 
| QSORT   | 100      | 0.002s        | 
| QSORT   | 1000     | 0.004s        | 
| QSORT   | 10000    | 0.036s        | 
| QSORT   | 100000   | 0.348s        |
| QSORT   | 1000000  | 7.424s        | 
| QSORT   | 10000000 | 1m 29.84s     | 
| MERGE   | 10       | 0.002s        | 
| MERGE   | 100      | 0.002s        | 
| MERGE   | 1000     | 0.005s        | 
| MERGE   | 10000    | 0.036s        | 
| MERGE   | 100000   | 0.349s        |
| MERGE   | 1000000  | 6.921s        | 
| MERGE   | 10000000 | 1m 26.91s     | 
| QUICK   | 10       | N/A           | 
| QUICK   | 100      | N/A           | 
| QUICK   | 1000     | N/A           | 
| QUICK   | 10000    | N/A           | 
| QUICK   | 100000   | N/A           |
| QUICK   | 1000000  | N/A           | 
| QUICK   | 10000000 | N/A           | 

Discuss the relative performance of each sorting method and try to explain the differences.
  -Each sorting method performed essentially the same in our testings with marginal differences between them of only a couple of seconds even when soring 10 million elements. The fastest was consistently xxxxx sort because it is an O(n(log(n)) sort.
  
What do these results reveal about the relationship between theoretical complexity discussed in class and actual performance? 
  -Although in theorry some of these sorting methods are supposed to be much faster than others, in practice they perform on about the same level. So complexity in theory doesn't necessarily translate to reality.
  
In your opinion, which sorting mode is the best? Justify your conclusion by examining the trade-offs for the chosen mode.
  -The arguably best sorting method in our opinion is merge sort, programming quicksort was cumbersome and complex while merge sort makes sense in theory and in code
  
In addition to the questions, please provide a brief summary of each individual group members contributions to the project
  
  -Grant:
    
    -STL.cpp
    
    -Qsort.cpp: The only difficulty in programming tis was typecasting the void * into a Node *. I was segfaulting initially due to lacking understanding of how to fomrat the variables within the comparison function. Also the format for qsort if more confusing than STL that caused me some problems as well
    
    -Markdown Table
    
  -Matthew:
  
     -Merge.cpp
     
   -Logan:
   
    -List.cpp
    
    -Quick.cpp
