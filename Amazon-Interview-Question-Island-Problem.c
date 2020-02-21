/*************************************************************************************/
/*                                     Oguzhan SENTURK                               */
/*                                      	                                     */
/*                                   osenturk@gtu.edu.tr                             */
/*************************************************************************************/

#include <stdio.h>
#include <sys/resource.h>
#define MAX 512						/*Maximum number of grid*/
FILE *inp;
short matrix[MAX][MAX];				/*variable to store date from input.txt*/
short island_number = 1;			/*variable to mark island*/
short water_level;					/*variable to store water level*/
short count_of_island = 0;			/*variable to store count of island*/

void find_island(short x, short y);	/*function to find island from array*/
void read_text();					/*function to remove read data from input.txt*/
void edit_matrix();					/*function to change land to 1, water to 0*/
void find_land();					/*function to find land from array*/

void read_text()
{
	short i, j;
	inp = fopen("input.txt","r");
	fscanf(inp, "%hd", &water_level);
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			fscanf(inp,"%hd", &matrix[i][j]);
		}
	}
}

void edit_matrix()
{
	short i, j;
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			if(matrix[i][j] <= water_level)
			{
				matrix[i][j] = 0;
			}
			else
			{
				matrix[i][j] = 1;
			}
		}
	}
}

void find_land()
{
	short i, j;
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			if(matrix[i][j] == 1)
			{
				find_island(i, j);
				count_of_island ++;
				island_number ++;
			}
		}
	}
}

void find_island(short x, short y)
{
	matrix[x][y] = -island_number;
	if(x+1 < MAX)
	{
		if(matrix[x+1][y] > 0 )
		{
			find_island(x+1, y);
		}
	}
	if(x-1 >= 0)
	{

		if(matrix[x-1][y] > 0)
		{
			find_island(x-1, y);
		}
	}
	if(y+1 < MAX)
	{
		if(matrix[x][y+1] > 0)
		{
			find_island(x, y+1);
		}
	}
	if(y-1 >= 0)
	{
		if(matrix[x][y-1] > 0)
		{
			find_island(x, y-1);
		}
	}
}

int main()
{
	FILE* outp = fopen("output.txt", "w");
	short i = 0 ;
	short j = 0;
	const rlim_t kStackSize = 16 * 1024 * 1024;
	struct rlimit rl;
	int result;
	result = getrlimit(RLIMIT_STACK,&rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK,&rl);
			if (result != 0)
			{
				fprintf(stderr,"setrlimit returned result = %d\n", result);
			}
		}
	}
	read_text();
	edit_matrix();
	find_land();
	fprintf(outp",%hd\n", count_of_island );
	label:
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			if(matrix[i][j] == -count_of_island && count_of_island != 0)
			{
				fprintf(outp,"%hd %hd\n", i, j);
				count_of_island--;
				goto label;
	 		}
	 	}
	 }
	fclose(inp);
	fclose(outp);
}
