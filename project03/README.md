# Project 3 - Superball!

**[Project 3 Write Up](https://github.com/Logant08/cs_302/blob/master/project03/project03.pdf)**

## Data Structures / Algorithms Used

* Disjoint Sets

## Scoring Chart

* P - Purple: worth 2 points
* B - Blue: worth 3 points
* Y - Yellow: worth 4 points
* R - Red: worth 5 points
* G - Green: worth 6 points

## Compile Instructions

This project can be compiled by typing `make` in the base directory

```
~/project03>
$ make
```

## Running the Programs

### Sb-read
The first program, `Sb-read`, takes in four parameters along with a game board, and prints out information about it.  

```
$ sb-read <rows> <cols> <min-score-size> <colors> < <game-board>
```

Example:  

`input-1.txt`

``` 
...yyryy.p
y.rg.yppyp
**gg.yrpPP
GGgbgybp**
R*bg.yrp*P
G*gygyypY*
yyybpby.pb
.pgg.yp.bb
```

<a href="url"><img src="https://i.imgur.com/K52Wrfx.png" align="center" height="310" width="370" ></a>  
*(Visual representation of `input-1.txt`)*

Running `sb-read` with `input-1.txt`

```
$ sb-read 8 10 h pbyrg < input-1.txt
Empty cells:                    20
Non-Empty cells:                60
Number of pieces in goal cells:  8
Sum of their values:            33
```
*There are three purple pieces in goal cells. There's one yellow, three green and one red. That makes a total of 3\*2 + 4 + 5 + 3\*6 = 33.*

### Sb-analyze

The second program, `Sb-analyze`, takes in the same parameters as `Sb-read`. Using a disjoint set, it prints out all possible scoring sets.

```
$ sb-analyze 8 10 5 pbyrg < input-1.txt
Scoring sets:
  Size: 10  Char: p  Scoring Cell: 2,8
  Size:  6  Char: g  Scoring Cell: 3,0
```

### Sb-play

The third program, `Sb-play`, requires the same input as the other two programs, however, it can take extra inputs depending on how you want to view the output. The program prints a single move, either `SWAP` or `SCORE`, instructing the game of what to do.

```
$ ~/sb-player 8 10 5 pbyrg sb-play <manual-turns> <result-format> <seed>
```

```
$ ~/sb-player 8 10 5 pbyrg sb-play y y -
Empty Cells: 75     Score: 0

g.........
..........
**......**
*Pr.....**
**......**
**..p...**
........b.
..........

Type Return for the next play
```

`RETURN`

```
Move is: SWAP 5 4 3 2

Empty Cells: 70     Score: 0

b........g
.......y..
**..b...**
*Pp.g...**
**.....gG*
**..r...**
..g.....g.
.p...p..g.
```

*a bunch of output skipped...*

```
Empty Cells: 1      Score: 505

yyrrgggpyy
grrbppg.yg
GYbgygggPB
GBggpgbpPB
PPgggggrYB
YBbybgpbYR
pprrrggggr
byyrppppgg

Move is: SWAP 0 1 7 5

Game over. Final score = 505
```

Using `n` as the 7th argument, it will only print out the end result.

```
$ ~/sb-player 8 10 5 pbyrg sb-play n n -
Game over. Final score = 505
```

To run multiple times, we used a shell script.

```
$ sh run_multiple.sh <rows> <cols> <min-score-size> <player> <num-runs> <seed>
```

```
$ sh run_multiple.sh 8 10 5 pbyrg s-play 10 1
Run   1 - Score:    38  - Average   38.000
Run   2 - Score:     0  - Average   19.000
Run   3 - Score:     0  - Average   12.667
Run   4 - Score:    57  - Average   23.750
Run   5 - Score:     0  - Average   19.000
Run   6 - Score:     0  - Average   15.833
Run   7 - Score:    89  - Average   26.286
Run   8 - Score:    15  - Average   24.875
Run   9 - Score:     0  - Average   22.111
Run  10 - Score:    20  - Average   21.900
```