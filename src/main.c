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
#include <string.h>

#define SELECT 0
#define UPDATE 1
#define DELETE 2
#define INVALID -1

/* Data type to store select query info */
typedef struct {
  int type;
  char* table;
  char** columns;
  char* filter;
} Query;

char **tokenize(char *str, char delim);
Query build_query(char* sql);

int main() {
  /* Filename of the csv */
  char filename[400];
  Query q;

  printf("csv reader 1.0\n");
  printf("file name (eg: sample.csv): ");
  //scanf("%s", filename);
  /* Reads in the SQL query from the user */
  // printf("Query> ");
  // query_nread = getline(&query, &query_length, stdin);

  /* error while reading query */

  q = build_query("SELECT name, age FROM users");
  printf("Query type: %d\n", q.type);
  printf("Columns: %s,%s\n", q.columns[0], q.columns[1]);
  printf("Table: %s\n", q.table);
  printf("Condition: %s\n", q.filter);
  /* TODO: Need exceptions for empty rows (print table) */

  //free_table(csv_file.table, csv_file.rows, csv_file.column_sizes);
  //free(csv_file.column_sizes);

  return 0;
}

char **tokenize(char *str, char delim) { 
  char **tokens;
  size_t token_length = 0;
  size_t token_count = 0;
  
  /* Allocating memory for a single token */
  tokens = (char **) malloc(sizeof(char *));
  /* Allocating memory for a single character */
  tokens[token_count] = (char *) malloc(sizeof(char)); 

  if(tokens == NULL) {
    printf("Error while allocating memory\n");
    exit(1);
  }

  for(int index = 0; index <= strlen(str); ++index) {
    if(str[index] == delim) {
      if(str[index - 1] == ' ') {
        continue;
      }
      tokens[token_count][token_length] = '\0';
      token_length = 0;
      token_count++;
      if(token_count >= 1) {
        tokens = (char **) realloc(tokens,  (token_count + 1) * sizeof(char *));
        tokens[token_count] = (char *) malloc(sizeof(char));
        if(tokens == NULL) {
          printf("Error while allocating memory\n");
          exit(1);
        }
      }
    } else if(str[index] == '\0') {
      tokens[token_count][token_length] = '\0';
      ++token_count;
    } else {
      tokens[token_count][token_length++] = str[index];
      if(token_length >= 1) {
        tokens[token_count] = (char *) realloc(tokens[token_count],(token_length + 1) * sizeof(char));
      }
    }
  }

  tokens[token_count] = NULL;
  return tokens;
}

Query build_query(char* sql) {
  Query query;
  char** sql_tokens = tokenize(sql, ' ');

  /* In case query is not SELECT */
  if(strcmp(sql_tokens[0],"SELECT") == 0) {
    return query;
  } else if (strcmp(sql_tokens[0], "UPDATE") == 0) {

    return query;
  } else if (strcmp(sql_tokens[0], "DELETE") == 0) {

    return query;
  } else {
    return query;
  }

}