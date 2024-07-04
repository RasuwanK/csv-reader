/**

Program name: CSV reader
Description: This is a simple commandline utility to modify and create csv files
Author: Rasuwan Kalhara (kalharaweragala@gmail.com)
Liscence: GPL

**/

#include <stdio.h>
#include <stdlib.h>
#define COLUMN_SIZE 60

int main()
{
	FILE *fp;
	char **header;
	int *sizes = (int *)malloc(1 * sizeof(int)); /* Number of columns and rows */
	char temp_ch;
	int data_rows = 1;	  /* Count of the data rows */
	sizes[0] = 0;

	if (sizes == NULL)
	{
		printf("Error while allocating memory for sizes\n");
		return -1;
	}

	fp = fopen("sample.csv", "r");

	/* Greeting the user */
	printf("CSV reader 1.0\n");

	/* File doesen't exist */
	if (fp == NULL)
	{
		printf("Error while reading the file");
		return -1;
	}

	/* Reading header values */
	/* since temp_ch is already '\n' */
	while (1)
	{
		temp_ch = fgetc(fp);

		if(temp_ch == EOF) {
			/* Final column boundary */
			++sizes[data_rows - 1];
			break;
		};

		/* Determined a new row */
		if (temp_ch == '\n')
		{
			/* End of a column increments the column count */
			++sizes[data_rows - 1];

			++data_rows;
			
			/* Reallocating more memory to store more column sizes */
			sizes = (int *)realloc(sizes, sizeof(int) * (data_rows));
			sizes[data_rows - 1] = 0;


			if (sizes == NULL)
			{
				printf("Error  while allocating memory for sizes\n");
				return -1;
			}
		}

		/* Determined a new column */
		if (temp_ch == ',')
		{
			++sizes[data_rows - 1]; /* Assigning the column count for each row */
		}
	}

	printf("File info\n");
	printf("----------\n");
	printf("Rows: %d\n", data_rows);
	printf("Columns: \n");
	
	for(int index = 0; index < data_rows; ++index) {
		printf("Row %d -> Columns %d\n", index + 1, sizes[index]);
	}


	return 0;
}