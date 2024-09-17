/**

Program name: CSV reader
Description: This is a simple commandline utility to modify and create csv files
Author: Rasuwan Kalhara (kalharaweragala@gmail.com)
Liscence: GPL

**/

#include "../include/read_csv.h"
#include "../include/ui.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  /* Filename of the csv */
  char filename[FILENAME_SIZE];

  printf("csv reader 1.0\n");
  printf("file name (eg: sample.csv): ");
  scanf("%s", filename);

  /* Content of the csv */
  CSVFILE csv_file = read_csv(filename);

  int columns = get_columns(csv_file.column_sizes, csv_file.rows);
  /* Size of the csv file in bytes */
  long int file_size = get_file_size(filename);
  char *unit;

  if (file_size < 1024) {
    unit = "Bytes";
  } else {
    file_size = file_size / 1024;
    unit = "KB";
  }

  /* After reading the file , info is displayed */
  /* eg: filename.csv 200 rows  */
  printf("%s | %d %s | %d %s | %ld %s\n", filename, columns,
         columns > 1 ? "columns" : "column", csv_file.rows,
         csv_file.rows > 1 ? "rows" : "row", file_size, unit);

  // printf("size = %lu", strlen(csv_file.table[0][3]));

  printf("\n");

  print_table(csv_file.table, 4, csv_file.rows - 1, 10);

  /* TODO: Need exceptions for empty rows (print table) */

  free_table(csv_file.table, csv_file.rows, csv_file.column_sizes);
  free(csv_file.column_sizes);

  return 0;
}
