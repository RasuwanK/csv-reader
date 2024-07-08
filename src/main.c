/**

Program name: CSV reader
Description: This is a simple commandline utility to modify and create csv files
Author: Rasuwan Kalhara (kalharaweragala@gmail.com)
Liscence: GPL

**/

#include <stdio.h>
#include <stdlib.h>
#define VALUE_SIZE 200
#define TRUE 1
#define FALSE 0

/* Struct which contain all the data of the csv file */
typedef struct csv_file
{
	int rows;
	int* column_sizes;
	char*** table;
} CSVFILE;

/* Read csv data from a text file and write it to a data structure */
CSVFILE read_csv(char *filename);

/* Allocating memory for a 1 dimensional string array */
char ***table_alloc(int rows, int *column_sizes, int value_size);

/* Safely opens the file with runtime error catching */

int main()
{
	/* Filename of the csv */
	char* filename;
	/* Content of the csv */
	CSVFILE csv_file;
	printf("csv reader 1.0\n");
	printf("file name (ex: sample.csv): ");
	scanf("%s", filename);

	/* Exit when an error while allocating data for the filename */
	if(filename == NULL)
	{
		printf("Error while allocating memory for filename\n");
		exit(1);
	}

	csv_file = read_csv(filename);

	printf("Contains %d rows.\n", csv_file.rows);

	return 0;
}

char ***table_alloc(int rows, int *column_sizes, int value_size)
{
	char ***table;
	table = (char ***)malloc(rows * sizeof(char **));

	if (table == NULL)
	{
		printf("Error while allocating memory for data rows\n");
		return NULL;
	}

	for (int row = 0; row < rows; ++row)
	{
		int cols = column_sizes[row];
		/* Allocating memory for columns */
		table[row] = (char **)malloc(cols * sizeof(char *));

		if (table[row] == NULL)
		{
			printf("Error while allocating memory for data rows\n");
			return NULL;
		}

		for (int col = 0; col < cols; ++col)
		{
			/* Allocating memory for column values */
			table[row][col] = (char *)malloc(VALUE_SIZE * sizeof(char));

			if (table[row][col] == NULL)
			{
				printf("Error while allocating memory for column data");
				return NULL;
			}
		}
	}

	return table;
}

CSVFILE read_csv(char *filename)
{
	FILE *fp;
	char temp_ch;
	int is_quote = FALSE; /* Cheking whether currently reading  */
	
	/* Main datastructure to store all csv data */
	CSVFILE csv_file;

	/* Allocating sizes for the number of columns for each row */
	csv_file.column_sizes = (int *)malloc(1 * sizeof(int));

	if (csv_file.column_sizes == NULL)
	{
		printf("Error while allocating memory for sizes\n");
		exit(1);
	}

	csv_file.column_sizes[0] = 1;  /* First cell is always counted before */

	/* Count of the data rows */
	csv_file.rows = 1;

	/* Pointers to currently reading column */
	int column = 1;
	/* Pointers to currently reading row */
	int row = 1;
	/* char index */
	int char_index = 0;

	fp = fopen("sample.csv", "r");

	if(fp == NULL)
	{
		printf("Error while reading the file\n");
		exit(1);
	}

	/* since temp_ch is already '\n' */
	while (TRUE)
	{
		temp_ch = fgetc(fp);

		if (temp_ch == EOF)
		{
			/* Final column boundary */
			++csv_file.column_sizes[csv_file.rows - 1];
			break;
		};

		/* Determined a new row */
		if (temp_ch == '\n')
		{
			/* End of a column increments the column count */
			++csv_file.column_sizes[csv_file.rows - 1];

			++csv_file.rows;

			/* Reallocating more memory to store more column sizes */
			csv_file.column_sizes = (int *)realloc(csv_file.column_sizes, sizeof(int) * (csv_file.rows));
			csv_file.column_sizes[csv_file.rows - 1] = 0;

			if (csv_file.column_sizes == NULL)
			{
				printf("Error  while allocating memory for sizes\n");
				exit(1);
			}
		}

		/* Determined a new column */
		if (temp_ch == ',')
		{
			++csv_file.column_sizes[csv_file.rows - 1]; /* Assigning the column count for each row */
		}
	}

	/* Resetting the file pointer to the top */
	fseek(fp, 0, SEEK_SET);

	/* Saving all the content of the csv */
	/* Multidimensional array of strings */
	// char ***data;

	/* allocating number of rows */
	csv_file.table = table_alloc(csv_file.rows, csv_file.column_sizes, VALUE_SIZE);

	if (csv_file.table == NULL)
	{
		printf("Error while allocating memory for table");
		exit(1);
	}

	/* Reading the entire file */
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
		else if (temp_ch == ',' && !is_quote)
		/* When a row is determined */
		{
			char_index = 0;
			++column;
		}
		else if (temp_ch == '\"')
		/* Whenever its the beggining of a string */
		{
			/* ending string record */
			if (is_quote)
				is_quote = FALSE;
			else
				is_quote = TRUE;
		}
		else
		/* Saving the necessary characters as data of a particular cell */
		{
			/* Ignoring all the spaces */
			csv_file.table[row - 1][column - 1][char_index] = temp_ch;
			++char_index;
		}
	}

	return csv_file;
}