#include "../include/ui.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_border(int columns, int column_width) {
  for (int column = 1; column <= columns; ++column) {
    /* First column contains + at top left corner */
    if (column == 1) {
      printf("+");
    }

    /* Always extra 3 strokes are printed for visual enhancements */
    for (int char_index = 0; char_index < column_width; ++char_index) {
      printf("-");
    }

    printf("+");
  }
  printf("\n");
}

void print_row(char **row, int columns, int column_width) {
  int *str_pointers;
  str_pointers = (int *)malloc(columns * sizeof(int));

  /* Initializing str_pointers to zero */
  for (int index = 0; index < columns; ++index) {
    str_pointers[index] = 0;
  }

  /* Determining maximum height of a row */
  /* cell with largest text size */
  int max_len_str = strlen(row[0]);

  for (int col = 0; col < columns; ++col) {
    if (strlen(row[col]) > max_len_str) {
      max_len_str = strlen(row[col]);
    }
  }

  /* Therefore can get the height of the row */
  float row_height = (float)max_len_str / column_width;
  row_height = ceil(row_height);

  for (int row_index = 0; row_index < row_height; ++row_index) {
    for (int col = 0; col < columns; ++col) {
      if (col == 0)
        printf("|");
      for (int char_index = 0; char_index < column_width; ++char_index) {
        if (str_pointers[col] < strlen(row[col])) {
          printf("%c", row[col][str_pointers[col]]);
          ++str_pointers[col];
        } else {
          printf(" ");
        }
      }
      printf("|");
    }
    printf("\n");
  }

  free(str_pointers);
}

void print_table(char ***table, int max_cols, int max_rows, int column_width) {
  /* In case an empty table has provided */
  if (table == NULL) {
    perror("Error ! table is empty");
    return;
  }

  for (int row = 1; row <= max_rows; ++row) {
    /* Displaying the rows */
    /* Top border */
    if (row == 1)
      print_border(max_cols, column_width);

    /* Printing out the column values */
    print_row(table[row - 1], max_cols, column_width);

    /* Bottom border */
    print_border(max_cols, column_width);
  }

  return;
}
