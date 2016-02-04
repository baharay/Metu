#include <stdio.h>
int rows, columns, bobrow, bobcol, i, j;
	char  teambefore, teamafter;
	char tents[1000][1000];

void convert(bobrow,bobcol)
{ 
	tents[bobrow][bobcol] = teamafter;
	if ((bobrow>0 )&& tents[bobrow-1][bobcol]== teambefore)
	{
		tents[bobrow-1][bobcol] = teamafter;
		convert(bobrow-1,bobcol);
	}
	if ((bobrow>0) && (bobcol<columns)&& tents[bobrow-1][bobcol+1]== teambefore)
	{
		tents[bobrow-1][bobcol+1] = teamafter;
		convert(bobrow-1,bobcol+1);
	}
	if ((bobcol<columns-1) && tents[bobrow][bobcol+1]== teambefore)
	{
		tents[bobrow][bobcol+1] = teamafter;
		convert(bobrow,bobcol+1);
	}
	if ((bobrow<rows-1) && (bobcol<columns-1 )&&tents[bobrow+1][bobcol+1]== teambefore)
	{
		tents[bobrow+1][bobcol+1] = teamafter;
		convert(bobrow+1,bobcol+1);
	}
	if ((bobrow<rows-1 )&& tents[bobrow+1][bobcol]== teambefore)
	{
		tents[bobrow+1][bobcol] = teamafter;
		convert(bobrow+1,bobcol);
	}
	if ((bobrow<rows-1 )&& (bobcol>0) && tents[bobrow+1][bobcol-1]== teambefore)
	{
		tents[bobrow+1][bobcol-1] = teamafter;
		convert(bobrow+1,bobcol-1);
	}
	if ((bobcol>0) && tents[bobrow][bobcol-1]== teambefore)
	{
		tents[bobrow][bobcol-1] = teamafter;
		convert(bobrow,bobcol-1);
	}
	if ((bobrow>0) && (bobcol>0) &&tents[bobrow-1][bobcol-1]== teambefore)
	{
		tents[bobrow-1][bobcol-1] = teamafter;
		convert(bobrow-1,bobcol-1);
	}
}

int main()
{
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
	
	convert(bobrow,bobcol);

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
