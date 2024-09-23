#include "../include/read_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int get_columns(int *column_sizes, int rows) {
  int columns = column_sizes[0];
  for (int index = 1; index < rows; ++index) {
    if (columns < column_sizes[index]) {
      columns = column_sizes[index];
    }
  }

  return columns;
}

/* get the file size in bytes */
long int get_file_size(const char *filename) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Error while opening the file\n");
    exit(1);
  }

  fseek(fp, 0, SEEK_END);

  long int size = ftell(fp);

  fclose(fp);

  return size;
}

char ***table_alloc(int rows, int *column_sizes, int value_size) {
  /* Need to increment rows for a null termination */
  ++rows;
  char ***table = (char ***)malloc(rows * sizeof(char **));
  table[rows - 1] = NULL; /* For row termination */

  if (table == NULL) {
    printf("Error while allocating memory for data rows\n");
    return NULL;
  }

  for (int row = 0; row < rows - 1; ++row) {
    int cols = column_sizes[row];
    int columns = cols + 1; /* ((col + 1) is for extra NULL character ) */
    /* Allocating memory for columns  */
    table[row] = (char **)malloc((columns) * sizeof(char *));

    table[row][columns - 1] = NULL; /* For column termination */

    if (table[row] == NULL) {
      printf("Error while allocating memory for data rows\n");
      return NULL;
    }

    for (int col = 0; col < cols; ++col) {
      /* Allocating memory for column values */
      table[row][col] = (char *)malloc(VALUE_SIZE * sizeof(char));

      if (table[row][col] == NULL) {
        printf("Error while allocating memory for column data");
        return NULL;
      }
    }

  }

  return table;
}

void free_table(char ***table, int rows, int *columns) {

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < columns[row]; ++col) {
      free(table[row][col]);
    }

    free(table[row]);
  }

  free(table);

  return;
}

CSVFILE read_csv(char *filename) {
  FILE *fp;
  char temp_ch;
  int is_quote = FALSE; /* Cheking whether currently reading  */

  /* Main data structure to store all csv data */
  CSVFILE csv_file;

  /* Allocating sizes for the number of columns for each row */
  csv_file.column_sizes = (int *)malloc(sizeof(int));

  if (csv_file.column_sizes == NULL) {
    printf("Error while allocating memory for sizes\n");
    exit(1);
  }

  csv_file.column_sizes[0] = 1; /* First cell is always counted before */

  /* Count of the data rows */
  csv_file.rows = 1;

  /* Pointers to currently reading column */
  int column = 1;
  /* Pointers to currently reading row */
  int row = 1;
  /* char index */
  int char_index = 0;

  fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Error while reading the file\n");
    free(csv_file.column_sizes);
    exit(1);
  }

  /* since temp_ch is already '\n' */
  while (TRUE) {
    temp_ch = fgetc(fp);

    if (temp_ch == EOF) {
      break;
    };

    /* Determined a new row */
    if (temp_ch == '\n') {

      ++csv_file.rows;

      /* Allocating memory for new column sizes */
      csv_file.column_sizes = (int *)realloc(csv_file.column_sizes, csv_file.rows * sizeof(int));
      
      if (csv_file.column_sizes == NULL) {
        printf("Error while allocating sizes for new column\n");
        free(csv_file.column_sizes);
        fclose(fp);
        exit(1);
      }
      
      csv_file.column_sizes[csv_file.rows - 1] = 1;

      if (csv_file.column_sizes == NULL) {
        printf("Error  while allocating memory for sizes\n");
        free(csv_file.column_sizes);
        fclose(fp);
        exit(1);
      }
    }

    if (temp_ch == '\"') {
      if (!is_quote)
        is_quote = TRUE;
      else
        is_quote = FALSE;
    }

    /* Determined a new column */
    if (temp_ch == ',' && !is_quote) {
      ++csv_file.column_sizes[csv_file.rows -
                              1]; /* Assigning the column count for each row */
    }
  }

  /* Resetting the file pointer to the top */
  fseek(fp, 0, SEEK_SET);

  /* Resetting is is_quote */
  is_quote = FALSE;

  /* Saving all the content of the csv */
  /* Multidimensional array of strings */
  // char ***data;

  /* allocating number of rows */
  csv_file.table =
      table_alloc(csv_file.rows, csv_file.column_sizes, VALUE_SIZE);

  if (csv_file.table == NULL) {
    printf("Error while allocating memory for table");
    free(csv_file.column_sizes);
    fclose(fp);
    exit(1);
  }

  /* Reading the entire file */
  while (TRUE) {
    temp_ch = fgetc(fp);

    /* Loop is quit when all the characters have read */
    if (temp_ch == EOF) {
      /* Adding null termination character to make it a string for final cell */
      csv_file.table[row - 1][column - 1][char_index++] = '\0';
      break;
    }

    /* When a row is determined */
    if (temp_ch == '\n') {
      char_index = 0;
      column = 1;
      ++row;
    } else if (temp_ch == ',' && !is_quote)
    /* When a row is determined */
    {
      /* Adding null termination character to make it a string */
      csv_file.table[row - 1][column - 1][char_index++] = '\0';
      char_index = 0;
      ++column;
    } else if (temp_ch == '\"')
    /* Whenever its the beggining of a string */
    {
      /* ending string record */
      if (is_quote)
        is_quote = FALSE;
      else
        is_quote = TRUE;

      /* Reads in the " character */
      csv_file.table[row - 1][column - 1][char_index] = temp_ch;
      ++char_index;
    } else
    /* Saving the necessary characters as data of a particular cell */
    {
      /* Ignoring all the spaces */
      csv_file.table[row - 1][column - 1][char_index] = temp_ch;
      ++char_index;
    }
  }

  fclose(fp);

  return csv_file;
}

void close_csv(CSVFILE csvfile) {
  free_table(csvfile.table, csvfile.rows, csvfile.column_sizes);
  free(csvfile.column_sizes);
}