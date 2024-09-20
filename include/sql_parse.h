#ifndef SQL_PARSE_H
#define SQL_PARSE_H

#define TOKEN_SIZE 256

/* List of tokens which are allowed */
typedef enum {
  SELECT_TOKEN,
  DELETE_TOKEN,
  UPDATE_TOKEN,
  WHERE_TOKEN,
  IDENTIFIER_TOKEN,
  COMMA_TOKEN,
  FROM_TOKEN,
  SEMICOLON_TOKEN,
  EQUAL_TOKEN,
  GT_TOKEN, /* GT refers to greater than */
  LT_TOKEN, /* LT refers to less than */
  NOT_EQUAL_TOKEN,
  EQUAL_GT_TOKEN,
  EQUAL_LT_TOKEN,
  INVALID_TOKEN,
  EOF_TOKEN
} TokenType;

typedef enum {
  EQUAL_COND,
  LT_COND, /* LT refers to less than */
  GT_COND, /* GT refers to greater than */
  NOT_EQUAL_COND,
  EQUAL_LT_COND,
  EQUAL_GT_COND
} ConditionType;

typedef struct {
  TokenType type;
  char value[TOKEN_SIZE];
} Token;

/* Shape of a select query */
typedef struct {
  /* Querying table name */
  char* table_name;
  /* Number of columns to be queried */
  int num_columns;
  /* Holding all the column names */
  char (*columns)[TOKEN_SIZE];
  /* condition for WHERE */
  Condition condition;
} SelectQuery;

/* Structing the way to interpret a condition */
typedef struct {
  char identifier[TOKEN_SIZE];
  ConditionType type;
  char value;
} Condition;

SelectQuery build_select_query(char* sql);
Token next_token(const char** sql);

SelectQuery build_select_query(char* sql) {
  SelectQuery query;
}

#endif