#include "mazelib.h"

typedef char* maze;

typedef struct
{
	int colum;
	int row;
	bool isInit;
}mazesize;

// private variables
maze privatemaze = NULL;
mazesize privatemazesize = {-1, -1, FALSE};

static mazesize CacluateMazeSize(FILE* mazefile);
static int GetMazeColumNum(FILE* mazefile);
static int GetMazeRowNum(FILE* mazefile);
static maze MallocMazeMemory(mazesize size);
static void FillCharacterInMaze(maze mazememory, mazesize size, FILE* mazefile);
static int FindStartIndex(maze mazeinstance, mazesize size);
static pointT IndexToPosition(int index);
static int PositionToIndex(pointT position);
static pointT AdjacentPoint(pointT pt, directionT dir);
static bool IsPointLegal(pointT pt);
static void FreeMazeMemory(maze p);

// Test Function
static void PrintMaze(maze mazememory, mazesize size);


void ReadMazeMap(string filename)
{
	FILE* mazefile = fopen(filename, "rt");

	if (mazefile != NULL)
	{
		if (privatemaze != NULL)
		{
			FreeMazeMemory(privatemaze);

			privatemaze = NULL;
		}

		// This should be improve by checking whether a file is mazefile;

		privatemazesize = CacluateMazeSize(mazefile);

		privatemaze = MallocMazeMemory(privatemazesize);

		FillCharacterInMaze(privatemaze, privatemazesize, mazefile);

		fclose(mazefile);
	}
	else
	{
		Error("Maze file open failed, Please check if the file exist.\n");
	}

	return;
}

static mazesize CacluateMazeSize(FILE* mazefile)
{
	mazesize size;

	size.colum = GetMazeColumNum(mazefile);
	size.row = GetMazeRowNum(mazefile);
	size.isInit = TRUE;

	return size;
}

static int GetMazeColumNum(FILE* mazefile)
{
	char c = '\0';
	int columsize = 0;

	while ((c = getc(mazefile)) != '\n' && c != EOF)
	{
		columsize++;
	}

	// 重置文件指针
	rewind(mazefile);

	return columsize;
}

static int GetMazeRowNum(FILE* mazefile)
{
	char c = '\0';
	char end = '\0';
	int rowsize = 0;

	while ((c = getc(mazefile)) != EOF)
	{
		if (c == '\n')
		{
			rowsize++;
		}
	}

	// 重置文件指针到文件开头
	rewind(mazefile);

	return rowsize;
}

static maze MallocMazeMemory(mazesize size)
{
	maze ret = (maze)malloc(sizeof(char) * size.colum * size.row);

	return ret;
}

static void FreeMazeMemory(maze p)
{
	free(p);

	return;
}


static void FillCharacterInMaze(maze mazememory, mazesize size, FILE* mazefile)
{
	char c = '\0';
	char *buff = (char*)malloc(sizeof(char) * (size.colum + 2));
	// considered '\n', and the

	int count = 0;

	while (fgets(buff, (size.colum + 2), mazefile) != NULL)
	{
		// printf("%s", buff);

		int length = strlen(buff) - 1;

		for (int i = 0; i < length; i++)
		{
			mazememory[count * size.colum + i] = buff[i];
		}

		count++;
	}

	rewind(mazefile);
	free(buff);

	return;
}

static void PrintMaze(maze mazememory, mazesize size)
{
	for (int i = 0; i < size.row; i++)
	{
		for (int j = 0; j < size.colum; j++)
		{
			printf("%c", mazememory[i * size.colum + j]);
		}

		printf("\n");
	}

	printf("colum size = %d\n", size.colum);
	printf("row size = %d\n", size.row);
}

pointT GetStartPosition(void)
{
	mazesize size = privatemazesize;
	maze mazeinstance = privatemaze;

	int index = 0;

	if (size.isInit == TRUE && mazeinstance != NULL)
	{
		int index = FindStartIndex(mazeinstance, size);

		return IndexToPosition(index);
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

static int FindStartIndex(maze mazeinstance, mazesize size)
{
	for (int i = 0; i < size.colum * size.row; i++)
	{
		if (mazeinstance[i] == 'S')
		{
			return i;
		}
	}
}

static pointT IndexToPosition(int index)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		pointT ret;

		ret.x = index % privatemazesize.colum;
		ret.y = privatemazesize.row - (index / privatemazesize.colum) - 1;

		return ret;
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

static int PositionToIndex(pointT position)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		if (IsPointLegal(position))
		{
			int ret;

			ret = (privatemazesize.row - position.y - 1) * privatemazesize.colum + position.x;

			return ret;
		}
		else
		{
			Error("Please Check if Coordinate point value correct.\n");
		}
		
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

bool OutsideMaze(pointT pt)
{
	// 横坐标或纵坐标达到最大
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		if (IsPointLegal(pt))
		{
			return (pt.x == privatemazesize.colum - 1) || (pt.y == privatemazesize.row - 1);
		}
		else
		{
			Error("Calculated Coordinate point value has an error.\n");
		}
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
	
}

bool WallExists(pointT pt, directionT dir)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		if (IsPointLegal(pt))
		{
			pointT point = AdjacentPoint(pt, dir);

			return isWallCharacter(point);
		}
		else
		{
			Error("Please Check if Coordinate point value correct.\n");
		}
		
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

static bool isWallCharacter(pointT pt)
{
	int index = PositionToIndex(pt);

	return (privatemaze[index] == '+' || privatemaze[index] == '-' || privatemaze[index] == '|');
}

static pointT AdjacentPoint(pointT pt, directionT dir)
{
	pointT newpt;

	newpt = pt;

	switch (dir)
	{
		case North:
		{
			(newpt.y)++;
			break;
		}
		case East:
		{
			(newpt.x)++;
			break;
		}
		case South:
		{
			(newpt.y)--;
			break;
		}
		case West:
		{
			(newpt.x)--;
			break;
		}
	}

	return newpt;
}

void MarkSquare(pointT pt)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		if (IsPointLegal(pt))
		{
			int index = PositionToIndex(pt);

			privatemaze[index] = 'x';
		}
		else
		{
			Error("Calculated Coordinate point value has an error.\n");
		}

	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

void UnmarkSquare(pointT pt)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		if (IsPointLegal(pt))
		{
			int index = PositionToIndex(pt);

			privatemaze[index] = '0';
		}
		else
		{
			Error("Calculated Coordinate point value has an error.\n");
		}

	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

bool IsMarked(pointT pt)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		if (IsPointLegal(pt))
		{
			int index = PositionToIndex(pt);

			return (privatemaze[index] == 'x');
		}
		else
		{
			Error("Please Check if Coordinate point value correct.\n");
		}

	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

void PrintChar(pointT point)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		if (IsPointLegal(point))
		{
			int index = PositionToIndex(point);

			printf("%c\n", privatemaze[index]);
		}
		else
		{
			Error("Please Check if Coordinate point value correct.\n");
		}
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

static bool IsPointLegal(pointT pt)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		bool XposLegal = (pt.x >= 0) && (pt.x < privatemazesize.colum);
		bool YposLegal = (pt.y >= 0) && (pt.y < privatemazesize.row);

		return (XposLegal && YposLegal);
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

void PrintSolveRoute(pointT pt)
{
	if (privatemazesize.isInit == TRUE && privatemaze != NULL)
	{
		
	}
	else
	{
		Error("Please ReadMazeMap First.\n");
	}
}

static void PrintMarkedPoint(pointT pt)
{
	printf("(%d,%d)", pt.x, pt.y);
}

bool SolveMaze(pointT pt)
{
	if (OutsideMaze(pt))
	{
		return TRUE;
	}
	else if (IsMarked(pt))
	{
		return FALSE;
	}
	else
	{
		MarkSquare(pt);

		for (directionT dir = North; dir <= West; dir++)
		{
			if (WallExists(pt, dir))
			{
				if (SolveMaze(AdjacentPoint(pt, dir)))
				{
					return TRUE;
				}
			}
		}

		UnmarkSquare(pt);
		return FALSE;
	}
}
