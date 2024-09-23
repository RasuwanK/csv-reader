/**

Program name: CSV reader
Description: This is a simple commandline utility to modify and create csv files
Author: Rasuwan Kalhara (kalharaweragala@gmail.com)
Liscence: GPL

**/

#include "../include/read_csv.h"
#include "../include/ui.h"
#include "../include/sql_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
  /* Filename of the csv */
  char filename[400];
  SelectQuery q;
  CSVFILE csvfile;

  printf("csv reader 1.0\n");
  printf("Filename (example: datafile.csv): ");
  scanf("%s", filename);
  csvfile = read_csv(filename);
  char** row;
  int row_index = 0;
  while((row = *(csvfile.table + row_index)) != NULL) {
    printf("Row: %d\n", row_index++);
  }
  printf("Rows: %d\n", csvfile.rows);

  const char* sql = "SELECT name, age FROM users WHERE name = Kay";
  /* Reads in the SQL query from the user */
  // printf("Query> ");
  // query_nread = getline(&query, &query_length, stdin);

  q = build_select_query(sql);
  printf("Invalid: %d\n", q.invalid);
  printf("Number of columns: %d\n", q.num_columns); 
  printf("Table name: %s\n", q.table_name);
  printf("WHERE clause:\n");
  printf("Column: %s\n", q.conditions->identifier);
  printf("Condition: %d\n", q.conditions->type);
  printf("Value: %s\n", q.conditions->value);

  free(q.conditions);

  close_csv(csvfile);

  return 0;
}