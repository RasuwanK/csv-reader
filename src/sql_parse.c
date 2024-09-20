#include "../include/sql_parse.h";

Token next_token(const char** sql) {
  /* Saving the current token */
  Token token;
  token.type = INVALID_TOKEN;
  token.value[0] = '\0';

  /* Iterate and skip over empty spaces */
  while(isspace(**sql)) (*sql)++;

  if(strncmp(*sql, "SELECT", 6) == 0 && isspace(*(*sql + 1))) {
    /* Statement is select */
    token.type = SELECT_TOKEN;
    strcpy(token.value, "SELECT");
    *sql += 6;
  } else if(strncmp(*sql, "UPDATE", 6) == 0 && isspace(*(*sql + 1))) {
    /* Statement is update */
    token.type = UPDATE_TOKEN;
    strcpy(token.value, "UPDATE");
    *sql += 6;
  } else if(strncmp(*sql, "FROM", 4) == 0 && isspace(*(*sql + 1))) {
    /* FROM token */
    token.type = FROM_TOKEN;
    strcpy(token.value, "FROM");
    *sql += 4;
  } else if(strncmp(*sql, "WHERE", 5) == 0 && isspace(*(*sql + 1))) {
    /* WHERE token */
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