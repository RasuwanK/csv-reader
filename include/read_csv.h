#ifndef READ_CSV_H
#define READ_CSV_H

#define VALUE_SIZE 200 /* Length of chatacter a cell can get maximumlu */
#define TRUE 1
#define FALSE 0

/* Struct which contain all the data of the csv file */
typedef struct {
  int rows;
  int *column_sizes;
  char ***table;
} CSVFILE;

/* Read csv data from a text file and write it to a data structure */
CSVFILE read_csv(char *filename);

/* Allocating memory for a 1 dimensional string array */
char ***table_alloc(int rows, int *column_sizes, int value_size);

/* Get maximum number of columns that a file has */
int get_columns(int *column_sizes, int rows);

/* get the file size in bytes */
long int get_file_size(const char *filename);

/* Frees the allocated memory for the table */
void free_table(char ***table, int rows, int *columns);

/* Closes the content read by csv file */
void close_csv(CSVFILE csvfile);

#endif
