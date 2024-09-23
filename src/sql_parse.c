#include "../include/sql_parse.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

Token next_token(const char** sql) {
  while(isspace(**sql)) (*sql)++;
  /* Saving the current token */
  Token token;
  token.type = INVALID_TOKEN;
  token.value[0] = '\0';

  /* Iterate and skip over empty spaces */
  if(strncmp(*sql, "SELECT", 6) == 0 && *((*sql + 6)) == ' ') {
    /* Statement is select */
    token.type = SELECT_TOKEN;
    strcpy(token.value, "SELECT");
    *sql += 6;
  } else if(strncmp(*sql, "UPDATE", 6) == 0 && *((*sql + 6)) == ' ') {
    /* Statement is update */
    token.type = UPDATE_TOKEN;
    strcpy(token.value, "UPDATE");
    *sql += 6;
  } else if(strncmp(*sql, "FROM", 4) == 0 && *((*sql + 4)) == ' ') {
    /* FROM token */
    token.type = FROM_TOKEN;
    strcpy(token.value, "FROM");
    *sql += 4;
  } else if(strncmp(*sql, "WHERE", 5) == 0 && *((*sql + 5)) == ' ') {
    /* WHERE token */
    token.type = WHERE_TOKEN;
    strcpy(token.value, "WHERE");
    *sql += 5;
  } else if(**sql == ',') {
    /* Comma token */
    token.type = COMMA_TOKEN;
    strcpy(token.value, ",");
    *sql += 1;
  } else if(**sql == '=') {
    /* Equal token */
    token.type = EQUAL_TOKEN;
    strcpy(token.value, "=");
    *sql += 1;
  } else if(**sql == '>') {
    /* Greater than token */
    token.type = GT_TOKEN;
    strcpy(token.value, ">");
    *sql += 1;
  } else if(**sql == '<') {
    /* Less than token */
    token.type = LT_TOKEN;
    strcpy(token.value, "<");
    *sql += 1;
  } else if(**sql == '>' && *(*sql + 1) == '=') {
    /* Greater than or equal token */
    /* Less than token */
    token.type = EQUAL_GT_TOKEN;
    strcpy(token.value, ">=");
    *sql += 2;
  } else if(**sql == '<' && *(*sql + 1) == '=') {
    /* Less than or equal token */
    token.type = EQUAL_LT_TOKEN;
    strcpy(token.value, "<=");
    *sql += 2;
  } else if(**sql == '<' && *(*sql + 1) == '>') {
    /* Not equal to token */
    token.type = NOT_EQUAL_TOKEN;
    strcpy(token.value, "<>");
    *sql += 2;
  } else if(isalnum(**sql) && **sql != '\0') {
    /* Parsing identifier names */
    token.type = IDENTIFIER_TOKEN;
    int index = 0;
    while(isalnum(**sql) || **sql == '_') {
      token.value[index++] = **sql;
      (*sql)++;
    }
    token.value[index] = '\0';
  } else if(**sql == '\0') {
    token.type = EOF_TOKEN;
  }

  return token;
}
 
SelectQuery build_select_query(const char* sql) {
  SelectQuery query;
  query.num_columns = 1;
  query.invalid = FALSE;

  Token token = next_token(&sql);
  /* Checking whether its a select */
  if(token.type == SELECT_TOKEN) {
    while((token = next_token(&sql)).type != FROM_TOKEN) {
      if(token.type == IDENTIFIER_TOKEN) {
        /* Taking all the column names */
        strcpy(query.columns[query.num_columns - 1], token.value);
      } else if(token.type == COMMA_TOKEN) {
        /* Incrementing column count */
        ++query.num_columns; 
      } else {
        /* If any other token presents */
        query.invalid = TRUE;
        return query;
      }
    }

    /* Definitely it (next token) must be a table name */
    token = next_token(&sql);
    
    if(token.type == IDENTIFIER_TOKEN) {
      strcpy(query.table_name, token.value);
      /* Next token must be a where clause */
      token = next_token(&sql);
      printf("Token type: %d\n", token.type);
      if(token.type == WHERE_TOKEN) {
        int condition_count = 0;
        /* Allocating memory for one condition */
        query.conditions = (Condition *) malloc(sizeof(Condition) * (condition_count + 1));

        if(query.conditions == NULL) {
          printf("Error while allocating memory for a condition");
          exit(1);
        }


        /* Taking all the condition */
        while((token = next_token(&sql)).type != EOF_TOKEN) {
          printf("token type: %d", token.type);
          /* Taking the first identifier (1st condtion) */
          if(token.type == IDENTIFIER_TOKEN) {
            strcpy(query.conditions[condition_count].identifier, token.value);
            /* Taking the logical operation */
            token = next_token(&sql);
            if(token.type == EQUAL_TOKEN) {
              query.conditions[condition_count].type = EQUAL_COND;
            } else if(token.type == GT_TOKEN) {
              query.conditions[condition_count].type == GT_COND;
            } else if(token.type == LT_TOKEN) {
              query.conditions[condition_count].type == LT_COND;
            } else if(token.type == EQUAL_GT_TOKEN) {
              query.conditions[condition_count].type = EQUAL_GT_COND;
            } else if(token.type == EQUAL_LT_TOKEN) {
              query.conditions[condition_count].type = EQUAL_LT_COND;
            } else {
              query.invalid = TRUE;
              return query;
            }

            /* Taking the value inolving in the operation */
            token = next_token(&sql);

            if(token.type == IDENTIFIER_TOKEN) {
              strcpy(query.conditions[condition_count].value, token.value);
            } else {
              query.invalid = TRUE;
              return query;
            }
          } else {
            query.invalid = TRUE;
            return query;
          }

          /* Incrementing number of conditions */
          ++condition_count;
          /* Allocating memory for the next condition */
          query.conditions = (Condition *) realloc(query.conditions, sizeof(Condition) * (condition_count + 1));
        }

      } else {
        query.invalid = TRUE;
        return query;
      }
    } else {
      query.invalid = TRUE;
      return query;
    }

  } else {
    query.invalid = TRUE;
    return query;
  }

  return query;
}