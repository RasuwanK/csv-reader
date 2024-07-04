/**

Program name: CSV reader
Description: This is a simple commandline utility to modify and create csv files
Author: Rasuwan Kalhara (kalharaweragala@gmail.com)
Liscence: GPL

**/

#include <stdio.h>
#include <stdlib.h>
#define COLUMN_SIZE 60
#define TRUE 1
#define FALSE 0

int main()
{
	FILE *fp;
	char **header;
	int *sizes = (int *)malloc(1 * sizeof(int)); /* Number of columns and rows */
	char temp_ch;
	int data_rows = 1; /* Count of the data rows */
	sizes[0] = 0;

	/* Pointers to currently reading column */
	int column = 1;
	/* Pointers to currently reading row */
	int row = 1;
	/* char index */
	int char_index = 0;

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
	while (TRUE)
	{
		temp_ch = fgetc(fp);

		if (temp_ch == EOF)
		{
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

	/* Resetting the file pointer to the top */
	fseek(fp, 0, SEEK_SET);

	/* Saving all the content of the csv */
	/* Multidimensional array of strings */
	char ***data;

	/* allocating number of rows */
	data = (char ***)malloc(data_rows * sizeof(char **));

	if (data == NULL)
	{
		printf("Error while allocating memory for data rows\n");
		return -1;
	}

	for (int row = 0; row < data_rows; ++row)
	{
		int data_cols = sizes[row];
		/* Allocating memory for columns */
		data[row] = (char **)malloc(data_cols * sizeof(char *));

		if (data[row] == NULL)
		{
			printf("Error while allocating memory for data rows\n");
			return -1;
		}

		for (int col = 0; col < data_cols; ++col)
		{
			/* Allocating memory for column values */
			data[row][col] = (char *)malloc(COLUMN_SIZE * sizeof(char));

			if (data[row][col] == NULL)
			{
				printf("Error while allocating memory for column data");
				return -1;
			}
		}
	}

	while (TRUE)
	{
		temp_ch = fgetc(fp);

		/* Loop is quit when all the characters have read */
		if (temp_ch == EOF)
			break;

		/* When a row is determined */
		if (temp_ch == '\n')
		{
			char_index = 0;
			column = 1;
			++row;
		}
		else if (temp_ch == ',')
		/* When a row is determined */
		{
			char_index = 0;
			++column;
		}
		else
		/* Saving the necessary characters as data of a particular cell */
		{	
			/* Ignoring all the spaces */
			if (temp_ch != ' ')
			{
				data[row - 1][column - 1][char_index] = temp_ch;
				++char_index;
			}
		}
	}

	return 0;
}