#include "simpio.h"
#include "genlib.h"
#include "strlib.h"
#include "random.h"
#include "graphics.h"
#include "mazelib.h"

#include <math.h>
#include <string.h>
#include <stdio.h>

#define NoGoodMove -1
#define MaxTake 3

bool IsGoodPosition(int nCoins);
bool IsBadPosition(int nCoins);
int FindGoodMove(int nCoins);


bool IsGoodPosition(int nCoins)
{
	if (nCoins % 1 != 1
		&& nCoins % 2 != 1
		&& nCoins % 3 != 1)
	{
		return TRUE;
	}
	else
	{
		return !(FindGoodMove(nCoins) == NoGoodMove);
	}
}

bool IsBadPosition(int nCoins)
{
	if (nCoins == 1)
	{
		return TRUE;
	}
	else
	{
		return (FindGoodMove(nCoins) == NoGoodMove);
	}
}

int FindGoodMove(int nCoins)
{
	for (int nTaken = 1; nTaken <= MaxTake; nTaken++)
	{
		if (IsBadPosition(nCoins - nTaken))
		{
			return (nTaken);
		}
	}

	return NoGoodMove;
}

int ShortestPathLength(pointT pt)
{

}

int main(void)
{
	ReadMazeMap("C:/VsProject/test.txt");

	pointT p = GetStartPosition();

	if (SolveMaze(p))
	{
		printf("Maze could be solved\n");
	}
	else
	{
		printf("Maze solve failed\n");
	}


	return 0;
}