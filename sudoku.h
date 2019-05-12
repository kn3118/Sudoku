#ifndef SUDOKU_H
#define SUDOKU_H


/* Loading Sudoku board */
void load_board(const char* filename, char board[9][9]);

/* internal helper function */
void print_frame(int row);

/* internal helper function */
void print_row(const char* data, int row);

/* Displaying Sudoku board */
void display_board(const char board[9][9]);

/* Checking if Sudoku board is complete */
bool is_complete(char board[9][9]);

/* Placing a digit onto a Sudoku board at a given position */
bool make_move(const char position[], char digit, char board[9][9]);

/* Checking the input digit is allowed */
bool invalid_digit(char digit);

/* Checking the input row and column are allowed */
bool invalid_position(int row, int col);

/* Checking if the input number not already exists in the same row, column, or 3x3 sub-board */
bool digit_duplicate(int row, int col, char digit, char board[9][9]);

/* Checking for a duplicate number in the same row */
bool dublicate_in_row(int row, char digit, char board[9][9]);

/* Checking for a duplicate number in the same column */
bool duplicate_in_column(int col, char digit, char board[9][9]);

/* Checking for the number input in the 3x3 sub-board */
bool duplicate_in_submatrix(int row, int col, char digit, char board[9][9]);

/* Return the starting row and column for the 3x3 sub-board check */
int get_starting_point(int current_place);

/* Outputs the two-dimensional character array board to a file with name filename */
bool save_board(const char *filename, const char board[9][9]);

/* Returns true if the Sudoku puzzle is solvable using a backtracking algorithm and starting from the top left corner, and false otherwise */
bool solve_board(char board[9][9]);

/* Attempts to solve recursively (backtracking) the Sudoku puzzle starting from the top left corner */
bool help_solve_board(int row, int col, char board[9][9]);

/* Check whether the board has been solved correctly */
bool check_board(char board[9][9]);

/* Checking whether original values of the assigned Sudoku puzzle have been changed */
bool correct_original_values(const char *filename, char board[9][9]);

#endif
