/**

Program name: CSV reader
Description: This is a simple commandline utility to modify and create csv files
Author: Rasuwan Kalhara (kalharaweragala@gmail.com)
Liscence: GPL

**/

#include "../include/read_csv.h"
#include "../include/sql_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUERY_SIZE 200

int main() {
  /* Filename of the csv */
  char filename[400];
  SelectQuery q;
  CSVFILE csvfile;
  char sql[QUERY_SIZE];

  printf("csv reader 1.0\n");
  printf("Filename (example: datafile.csv): ");
  scanf("%[^\n]", filename);
  /* To consume the extra newline character */
  getchar();
  csvfile = read_csv(filename);
  int filesize = get_file_size(filename);
  printf("\'%s\' read successfully.\n", filename);
  printf("File size: %d | Columns: %d | Rows: %d\n", filesize,
         get_columns(csvfile.column_sizes, csvfile.rows), csvfile.rows);
  printf("Query > ");

  /* Reads in a single line */
  if (fgets(sql, QUERY_SIZE, stdin) != NULL) {
    size_t len = strlen(sql);

    /* Replace the extra added newline character with a null termination */
    if (len > 0 && sql[len - 1] == '\n') {
      sql[len - 1] = '\0';
    }
  }

  /* Reads in the SQL query from the user */

  q = build_select_query(sql);
  printf("Invalid: %d\n", q.invalid);
  free_table(csvfile.table, csvfile.rows, csvfile.column_sizes);

  return 0;
}
