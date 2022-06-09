#include "simpio.h"
#include "genlib.h"

// Question 1

typedef enum
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
}weekdayT;

weekdayT NextDay(weekdayT weekday)
{
	return (weekday + 1) % 7;
}

weekdayT PreviousDay(weekdayT weekday)
{
	return (weekday - 1 + 7) % 7;
}

weekdayT IncrementDay(weekdayT weekday, int delta)
{
	weekdayT ret;

	if (delta >= 0)
	{
		ret = (weekday + delta) % 7;
	}
	else
	{
		ret = (weekday + delta + 7) % 7;
	}

	return ret;
}

void PrintWeekday(weekdayT weekday)
{
	switch (weekday)
	{
	case(Monday):
		printf("Monday\n");
		break;
	case(Tuesday):
		printf("Tuesday\n");
		break;
	case(Wednesday):
		printf("Wednesday\n");
		break;
	case(Thursday):
		printf("Thursday\n");
		break;
	case(Friday):
		printf("Friday\n");
		break;
	case(Saturday):
		printf("Saturday\n");
		break;
	case(Sunday):
		printf("Sunday\n");
		break;
	default:
		printf("WeekDay Error\n");
		break;
	}
}

int main(void)
{
	weekdayT day = Sunday;
	PrintWeekday(PreviousDay(day));
	PrintWeekday(NextDay(day));
	PrintWeekday(IncrementDay(day, 3));
	PrintWeekday(IncrementDay(day, -6));
}

// Question 2

#define Pi 3.1415926

// input
void GetHeightAndRadius(double* height, double* radius)
{
	printf("Please input Height of the Cylinder\n");
	*height = GetReal();
	printf("Please input Radius of the Cylinder\n");
	*radius = GetReal();

	return;
}

// calculate
void Calculate(double height, double radius, double* Surface, double* Volume)
{
	*Surface = 2 * Pi * height * radius;
	*Volume = Pi * height * radius * radius;
}

// output

void DisplayResults(double A, double V)
{
	printf("Cylinder Surface Area is %lf\n", A);
	printf("Cylinder Volume is %lf\n", V);
}

int main(void)
{
	double height, radius;
	GetHeightAndRadius(&height, &radius);
	double A, V;
	Calculate(height, radius, &A, &V);
	DisplayResults(A, V);

}

// Question 3
#define MinScore 0.0
#define MaxScore 10.0
static double Mean(double array[], int n)
{
    int i;
    double total = 0;

    double maxScore = MinScore;
    double minScore = MaxScore;

    for (int i = 0; i<n; i++)
    {
        total += array[i]

        if (array[i] > maxScore)
        {
            maxScore = array[i];
        }

        if (array[i] < minScore)
        {
            minScore = array[i];
        }
    }

    return (total - maxScore - minScore) / (n - 2);
    
}

// Question 4
bool isSorted(int array[], int n)
{
	if (n > 1)
	{
		for (int i = 0; (i < n - 1) ; i++)
		{
			if (array[i] > array[i + 1])
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

int main(void)
{
	int array[] = { 1, 2, 3, 7, 5, 6 };

	printf("isSort: %d\n", isSorted(array, sizeof(array) / sizeof(array[0])));
}

// Question 5

void PrintEratosthenes()
{
	// init array;
	bool isPrimeArray[999];
	for (int i = 0; i < sizeof(isPrimeArray) / sizeof(isPrimeArray[0]); i++)
	{
		isPrimeArray[i] = TRUE;
	}
	
	
	// calculate
	for (int i = 2; i < sizeof(isPrimeArray) / sizeof(isPrimeArray[0]); i++)
	{
		if (isPrimeArray[i])
		{
			for (int j = 2; (j * i) < sizeof(isPrimeArray) / sizeof(isPrimeArray[0]); j++)
			{
				isPrimeArray[i * j] = FALSE;
			}
		}
	}
	
	// print
	for (int i = 2; i < sizeof(isPrimeArray) / sizeof(isPrimeArray[0]); i++)
	{
		if (isPrimeArray[i])
		{
			printf("%d, ", i);
		}
	}

	printf("\n");
}

// Question 6

void DisplayHorizontalHistogram(int array[], int n)
{
	int ScoreSeg[11] = { 0 };

	for (int i = 0; i < n; i++)
	{
		if (array[i] >= 0 && array[i] <= 9)
		{
			ScoreSeg[0]++;
		}
		else if (array[i] >= 10 && array[i] <= 19)
		{
			ScoreSeg[1]++;
		}
		else if (array[i] >= 20 && array[i] <= 29)
		{
			ScoreSeg[2]++;
		}
		else if (array[i] >= 30 && array[i] <= 39)
		{
			ScoreSeg[3]++;
		}
		else if (array[i] >= 40 && array[i] <= 49)
		{
			ScoreSeg[4]++;
		}
		else if (array[i] >= 50 && array[i] <= 59)
		{
			ScoreSeg[5]++;
		}
		else if (array[i] >= 60 && array[i] <= 69)
		{
			ScoreSeg[6]++;
		}
		else if (array[i] >= 70 && array[i] <= 79)
		{
			ScoreSeg[7]++;
		}
		else if (array[i] >= 80 && array[i] <= 89)
		{
			ScoreSeg[8]++;
		}
		else if (array[i] >= 90 && array[i] <= 99)
		{
			ScoreSeg[9]++;
		}
		else if (array[i] == 100)
		{
			ScoreSeg[10]++;
		}
	}

	for (int i = 0; i < 11; i++)
	{
		printf("%d:", 10 * i);
		for (int j = 0; j < ScoreSeg[i]; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}

int main(void)
{
	int array[] = { 100, 95, 47, 88, 86, 92, 75, 89, 81, 70, 55, 80 };
	DisplayHorizontalHistogram(array, sizeof(array) / sizeof(array[0]));
	return 0;
}

// Question 7

void DisplayVerticalHistogram(int array[], int n)
{
	int ScoreSeg[11] = { 0 };

	for (int i = 0; i < n; i++)
	{
		if (array[i] >= 0 && array[i] <= 9)
		{
			ScoreSeg[0]++;
		}
		else if (array[i] >= 10 && array[i] <= 19)
		{
			ScoreSeg[1]++;
		}
		else if (array[i] >= 20 && array[i] <= 29)
		{
			ScoreSeg[2]++;
		}
		else if (array[i] >= 30 && array[i] <= 39)
		{
			ScoreSeg[3]++;
		}
		else if (array[i] >= 40 && array[i] <= 49)
		{
			ScoreSeg[4]++;
		}
		else if (array[i] >= 50 && array[i] <= 59)
		{
			ScoreSeg[5]++;
		}
		else if (array[i] >= 60 && array[i] <= 69)
		{
			ScoreSeg[6]++;
		}
		else if (array[i] >= 70 && array[i] <= 79)
		{
			ScoreSeg[7]++;
		}
		else if (array[i] >= 80 && array[i] <= 89)
		{
			ScoreSeg[8]++;
		}
		else if (array[i] >= 90 && array[i] <= 99)
		{
			ScoreSeg[9]++;
		}
		else if (array[i] == 100)
		{
			ScoreSeg[10]++;
		}
	}

	int maxSize = 0;

	for (int i = 0; i < 11; i++)
	{
		if (ScoreSeg[i] > maxSize)
		{
			maxSize = ScoreSeg[i];
		}
	}

	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (ScoreSeg[j] == maxSize - i)
			{
				printf("*\t");
				ScoreSeg[j]--;
			}
			else
			{
				printf("\t");
			}
		}

		printf("\n");
	}


	for (int i = 0; i < 11; i++)
	{
		printf("%d\t", i * 10);
	}
}

int main(void)
{
	int array[] = { 100, 95, 47, 88, 86, 92, 75, 89, 81, 70, 55, 80 };
	DisplayVerticalHistogram(array, sizeof(array) / sizeof(array[0]));
	return 0;
}

// Question 8
int RemoveZeroElements(int array[], int n)
{
	int count = 0;

	int lastIndex = -1;

	for (int i = 0; i < n-1; i++)
	{
		if (array[i] == 0)
		{
			for (int j = i+1; j < n; j++)
			{
				if (array[j] != 0)
				{
					array[i] = array[j];
					array[j] = 0;
					lastIndex = i;
					break;
				}
			}
		}
		else
		{
			lastIndex = i;
		}
	}

	count = lastIndex + 1;

	return count;
}

// Question 9
// 略

// Question 10
// 略

// Question 11
int* IndexArray(int n)
{
	int* ret = (int*)malloc(sizeof(int) * n);

	if (ret == NULL)
	{
		Error("Memory not enough");
	}

	int* p = ret;

	if (p)
	{
		for (int i = 0; i < n; i++)
		{
			*p++ = i;
		}
	}

	return ret;
}

// Question 12 13
#define WITHHOLDING 1
#define TAXRATE 0.25

typedef struct
{
	string name;
	string title;
	string ssnum;
	double salary;
	int withholding;
}*employeeP, employeeT;

typedef struct
{
	int employees;
	employeeP emp;
}*payrollP, payrollT;

payrollP GetPayroll()
{
	payrollP ret = NULL;

	printf("How many employees: ");
	int n = GetInteger();

	if (n > 0)
	{
		employeeP emps = (employeeP)malloc(sizeof(employeeT) * n);
		ret = (payrollP)malloc(sizeof(payrollT));

		if (emps && ret)
		{
			for (int i = 0; i < n; i++)
			{
				printf("Employee #%d:", i + 1);
				printf("\n    Name: ");
				(emps + i)->name = GetLine();
				printf("    Title: ");
				(emps + i)->title = GetLine();
				printf("    SSNum: ");
				(emps + i)->ssnum = GetLine();
				printf("    Salary: ");
				(emps + i)->salary = GetReal();
				printf("    Withholding exemptions: ");
				(emps + i)->withholding = GetInteger();
			}

			ret->employees = n;
			ret->emp = emps;
		}
		else
		{
			Error("No Enough Memory");
		}
	}
	else
	{
		Error("Please input a positive number");
	}
}

double CalculateTax(employeeP emp)
{
	double taxpart = (emp->salary - emp->withholding * WITHHOLDING) * TAXRATE;

	return taxpart;
}

void PrintSalaryList(payrollP roll)
{
	int n = roll->employees;
	employeeP emp = roll->emp;

	printf("Name\t\t\tGross\t\tTax\t\t\tNet\n");
	printf("---------------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < n; i++)
	{
		employeeP tmp = emp + i;

		printf("%s\t\t", tmp->name);
		printf("%lf  -\t", tmp->salary);
		printf("%lf\t=", CalculateTax(tmp));
		printf("\t%lf", tmp->salary - CalculateTax(tmp));
		printf("\n");
	}
}


int main(void)
{
	payrollP roll = GetPayroll();
	PrintSalaryList(roll);

	return 0;
}

// Question 14


// Question 15
int* GetDynamicIntegerArray(int sentinel, int* pN)
{
	*pN = 0;

	int count = 10;

	int* initalArray = (int*)malloc(sizeof(int) * count);
	int* p = initalArray;
	int* pEnd = initalArray + count;

	int current;
	if (p && pEnd && initalArray)
	{
		while ((current = GetInteger()) != sentinel)
		{
			if (p != pEnd)
			{
				*p = current;
				p++;
				(*pN)++;
			}
			else
			{
				int count2 = count * 2;
				int* newArray = (int*)malloc(sizeof(int) * count2);

				if (newArray)
				{
					for (int i = 0; i < count; i++)
					{
						*(newArray + i) = *(initalArray + i);
					}

					initalArray = newArray;
					p = newArray + count;
					pEnd = newArray + count2;

					*p = current;
					p++;
					(*pN)++;
				}
				else
				{
					Error("No Enough Memory When malloc New Array");
					free(initalArray);
				}
			}
			
		}
	}
	else
	{
		Error("No Enough Memory");
	}

	return initalArray;
}

// Question 16

#define MAXMEMORYSIZE 10000
char memory[MAXMEMORYSIZE];
int memoryStamp[MAXMEMORYSIZE];
int currentIndex = 0;

void* myalloc(int nBytes)
{
	void* ret = NULL;

	if (nBytes <= MAXMEMORYSIZE - currentIndex && nBytes > 0)
	{
		ret = &memory[currentIndex];
	}

	return ret;
}

void myfree(void* alloc)
{

}