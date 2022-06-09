/*
 *	File:mazelib.h
 *
 *	This interface provides a library of primitive operations
 *	to simplify the solution to the maze problem.
 *		
*/

#ifndef _MAZELIB_H_
#define _MAZELIB_H_

#include "genlib.h"
#include "simpio.h"
#include "strlib.h"
#include "string.h"

/*
 *	Type: pointT
 *	--------------
 *	The type pointT is used to encapsulate a pair of integer 
 *	coordinates into a single value with x and y componerts.
*/

typedef struct
{
	int x;
	int y;
}pointT;

/*
 *	Type: directionT
 *	--------------
 *	The type pointT is used to represent the four compass directions.
*/

typedef enum
{
	North,
	East,
	South,
	West
}directionT;

/*
 *  Function: ReadMazeMap
 *  Usage: ReadMazeMap(filename);
 *  ---------------------------------
 *  This function reads in map of the maze from the specified
 *  file and stores it in private data structures maintained by 
 *  this module. In the data file, the character '+', '-', and '|' 
 *	represent cornets, horizontal walls, and vertical walls,
 *  respectively; spaces represent open passgeway squares. The
 *  starting position is indicated by the character 'S'. For
 *  example, the following data file defines a simple maze:
 *  +-+-+-+-+-+
 *  |     |
 *  + +-+ + +-+
 *  |S  |     |
 *  +-+-+-+-+-+
 *  Coordinates are numbered starting at (0, 0) in the lower left.
 * 
 *  Note: the space can not type in '\t' and '\n', it must type enough ' ' or number 0,
 *        so that we can realize it was a space square;
 * 
 *		  Please type '\n', after the last character was typed in.
*/

void ReadMazeMap(string filename);

/*
 *  Function: GetStartPosition
 *  Usage: pt = GetStartPosition();
 *  -------------------------------
 *  This function returns a point indicating the coordinates of
 *  the start square.
*/

pointT GetStartPosition(void);

/*
 *  Function: OutsideMaze
 *  Usage: if (OutsideMaze(pt)) ...
 *  -------------------------------
 *  This function returns TRUE if the specified point is outside
 *  the boundary of the maze.
*/

bool OutsideMaze(pointT pt);

/*
 *  Function: WallExists
 *  Usage: if (WallExists(pt, dir)) ...
 *  -----------------------------------
 *  This fucntion returns TRUE if there is a wall in the indicated
 *  direction from the square at position pt.
*/

bool WallExists(pointT pt, directionT dir);

/*
 *  Function: MarkSquare, UnmarkSquare, IsMarked
 *  Usage: MarkSquare(pt);
 *		   UnmarkSquare(pt);
 *		   if (IsMarked(pt)) ...
 *  ----------------------------
 *  These functions mark, unmark, and test the status of the
 *  square specified by the coordinates pt.
*/

void MarkSquare(pointT pt);
void UnmarkSquare(pointT pt);
bool IsMarked(pointT pt);


/*
 *  Function: SolveMaze
 *  Usage: if (SolveMaze(pt)) ...
 *  -----------------------------
 *  This function attempts to generate a solution to the current
 *  maze from point pt. SolveMaze returns TRUE if the maze has a
 *  solution and FALSE otherwise. The implementation uses recursion
 *  to solve the submazes that result form marking the current square
 *  and moving on step along each open passage.
*/
bool SolveMaze(pointT pt);

/*
 *  Function: PrintSolveRoute
 *  Usage: if (SolveMaze(pt)) {PrintSolveRoute(pt)}...
 *  -----------------------------
 *  This function use parameter point value as start point, 
 *	and will print a set of coordinate points value
 *  to discribe how does a maze been solved if the SolveMaze()
 *  function return TRUE, otherwise PrintSolveRoute() will
 *  print an error message. 
 *  
*/

void PrintSolveRoute(pointT pt);


// This is a test function;
void PrintChar(pointT point);



#endif


