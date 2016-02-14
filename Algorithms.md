# Explanation of the checking algorithm #

As you know, the game has a 8x8 matrix with one gem on each square. I had to write an algorithm that checks for horizontal and vertical groups of three or more gems.

## Data types ##
A **`Coord`** is an object that stores the coordinates of a square. It's just got the horizontal and vertical position of the square and some methods.

A **`Match`** is a set (actually a vector) of three or more adjacent **`Coords`**, either horizontally or vertically aligned. It's got a method called `matched` that looks if a coordinated was matched in that match.

A **`MultipleMatch`** is a set of **`Matches`**. It's just a plain `vector` with an additional method called `matched` that checks if a given coordinate was matched in any of the stored matches.

## Algorithm ##

The **checking algorithm** returns a `MultipleMatch` objects with all the found matches. How does it find the matches? Easy.

First, it looks for matching rows (that is, horizontal groups of three or more equal gems). For the first row, it checks every column.

So we're at the first square, x=0, y=0. A temporary `Match` object is created to store the matching squares. Then, we begin to loop over the squares to the right of the current stage, checking if the gem equals the gem at 0,0. Is it the same? Yes: we add the square to the `Match` object. No: we break the loop, because now it's impossible to find a consecutive matching group. Also, we jump the column loop to the last read square, because we know that there are no groups so far.

Every `Match` object with three or more squares is added to the `MultipleMatch` object that the function will return.

Here's the code for the row checking:
```
    MultipleMatch matches;    

    for(int y = 0; y < 8; ++y){

	for(int x = 0; x < 8; ++x){

	    Match currentRow;
	    currentRow.push_back(coord(x,y));

	    for(k = x+1; k < 8; ++k){
		if(squares[x][y] == squares[k][y] &&
		   squares[x][y] != sqEmpty){
		    currentRow.push_back(coord(k,y));
		}else{
		    break;
		}
	    }

	    if(currentRow . size() > 2){
		matches.push_back(currentRow);
	    }

	    x = k - 1;
	}	
    }
```

The very same happens when we check for matching vertical groups.