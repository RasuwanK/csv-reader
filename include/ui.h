#ifndef UI_H
#define UI_H

/* Prints out a row of a table */
void print_table(char ***table, int max_cols, int max_rows, int column_width);

/* Prints out the border */
void print_border(int columns, int column_width);

/* Prints out a single row of a table */
void print_row(char **row, int columns, int column_width);

#endif
