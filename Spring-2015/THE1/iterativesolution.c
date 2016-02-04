#include <stdio.h>

int main()
{
	int rows, columns, bobrow, bobcol, i, j,again=0;
	char  teambefore, teamafter;
	char tents[1000][1000];
	scanf(" %d",&rows);       
	scanf(" %d",&columns);	
	
	for (i=0; i<rows; i++)
	{
		for (j=0; j<columns; j++)
		{
		
			scanf(" %c",&tents[i][j]);
		}
	}

	scanf(" %d",&bobrow);
	scanf(" %d",&bobcol);
	scanf(" %c",&teamafter);
	teambefore = tents[bobrow][bobcol];
	tents[bobrow][bobcol] = 'x';
	for (i=0; i<rows; i++)
	{
		for (j=0; j<columns; j++)
		{
		
			if (tents[i][j]== teambefore)
			{
				if (tents[i-1][j]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					
				}
				if (tents[i-1][j+1]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					

				}
				if (tents[i][j+1]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					
				}
				if (tents[i+1][j+1]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					
				}
				if (tents[i+1][j]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					
				}
				if (tents[i+1][j-1]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					
				}
				if (tents[i][j-1]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					
				}
				if (tents[i-1][j-1]== 'x')
				{
					tents[i][j] = 'x';
					again=1;
					
				}
			}

		}
		if (again==1)
		{ 
			i=0;
			j=0;
			again=0;
		}
	
	}
	for (i=0; i<rows; i++)
	{
		for (j=0; j<columns; j++)
		{
		
			if (tents[i][j]== teambefore)
			{
				if (tents[i-1][j]== 'x')
				{
					tents[i][j] = 'x';
					
					
				}
				if (tents[i-1][j+1]== 'x')
				{
					tents[i][j] = 'x';
					
					

				}
				if (tents[i][j+1]== 'x')
				{
					tents[i][j] = 'x';
					
				}
				if (tents[i+1][j+1]== 'x')
				{
					tents[i][j] = 'x';
					
					
				}
				if (tents[i+1][j]== 'x')
				{
					tents[i][j] = 'x';
					
				}
				if (tents[i+1][j-1]== 'x')
				{
					tents[i][j] = 'x';
					
					
				}
				if (tents[i][j-1]== 'x')
				{
					tents[i][j] = 'x';
					
					
				}
				if (tents[i-1][j-1]== 'x')
				{
					tents[i][j] = 'x';
					
					
				}
			}

		}
		
	
	}
	for (i=0; i<rows; i++)
	{
		for (j=0; j<columns; j++)
		{
			if (tents[i][j]== 'x')
				{
					tents[i][j] = teamafter;
					
					
				}
			
		}
		
	}
	for (i=0; i<rows; i++)
	{
		for (j=0; j<columns; j++)
		{
		
			printf("%c", tents[i][j]);
		}
		printf("\n");
	}

	return 0;

}
