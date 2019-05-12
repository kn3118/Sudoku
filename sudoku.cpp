#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>


using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}


/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}


/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}


/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}


/* Checking if Sudoku board is complete */
bool is_complete(char board[9][9])
{
  for (int row = 0; row < 9 ; row++)
      for (int col = 0; col < 9; col++)
	  if ((board[row][col] < '1') || (board[row][col] > '9'))
	    return false;
  
  return true;
}


/* Placing a digit onto a Sudoku board at a given position */
bool make_move(const char position[], char digit, char board[9][9])
{
  int row, col;
  
  // Verifying that the input characters for row and column are always just 2    
  if (strlen(position) != 2)
      return false;
  
  // Verifying that the input digit is indeed an integer in the range 1-9
  if (invalid_digit(digit))
      return false;

  // Convert rows and columns from input characters to integer numbers
  row = position[0] - 'A';
  col = position[1] - '1';

  // Verifying that row and column inputs indeed fall within the 9x9 size of the matrix
  if (invalid_position(row, col))
      return false;

  // Verifying that there is no duplicate in the same row, column, or 3x3 sub-board
  if (digit_duplicate(row, col, digit, board))
    return false;

  // Valid digit, can be inserted in the board
  board[row][col] = digit;
  return true;
}


/* Checking the input digit is allowed */
bool invalid_digit(char digit)
{
  if ((digit < '1') || (digit > '9'))
    return true;
  
  return false;
}


/* Checking the input row and column are allowed */
bool invalid_position(int row, int col)
{
  if ((row < 0) || (row > 8) || (col < 0) || (col > 8))
    return true;
  
  return false;
}


/* Checking if the input number does not already exist in the same row, column, or 3x3 sub-board */
bool digit_duplicate(int row, int col, char digit, char board[9][9])
{
  if (dublicate_in_row(row, digit, board)) // checking for the digit in the row
    return true;
  else if (duplicate_in_column(col, digit, board)) // checking for the digit in the column
    return true;
  else if (duplicate_in_submatrix(row, col, digit, board)) // checking for the digit in the 3x3 sub-board
    return true;
  else
    return false;
}


/* Checking for a duplicate number in the same row */
bool dublicate_in_row(int row, char digit, char board[9][9])
{
  for (int i = 0; i < 9; i++)
    if (board[row][i] == digit)
      return true;

  return false;
}


/* Checking for a duplicate number in the same column */
bool duplicate_in_column(int col, char digit, char board[9][9])
{
  for (int i = 0; i < 9; i++)
    if (board[i][col] == digit)
      return true;

  return false;
}


/* Checking for the number input in the 3x3 sub-board */
bool duplicate_in_submatrix(int row, int col, char digit, char board[9][9])
{
  int starting_row = get_starting_point(row);
  int starting_col = get_starting_point(col);

  for (int i = starting_row; i < starting_row + 3; i++)
    for (int j = starting_col; j < starting_col + 3; j++)
      if (board[i][j] == digit)
	return true;

  return false;
}


/* Return the starting row and column for the 3x3 sub-board check */
int get_starting_point(int current_place)
{
  switch(current_place)
    {
    case 0:
    case 3:
    case 6:
      return current_place;
    case 1:
    case 4:
    case 7:
      return (current_place - 1);
    case 2:
    case 5:
    case 8:
      return (current_place - 2);
    default:
      return -1;
    }
}


/* Outputs the two-dimensional character array board to a file with name filename */
bool save_board(const char *filename, const char board[9][9])
{
  ofstream out_stream;
  out_stream.open(filename);

  if (out_stream.fail())
    {
      out_stream.close();
      return false;
    }
  else
    {
     for (int i = 0; i < 9; i++)
       {
	 for (int j = 0; j < 9; j++)
	     out_stream.put(board[i][j]);
	 out_stream.put('\n');
       }
     out_stream.close();
     return true;
    }
}


/* Returns true if the Sudoku puzzle is solvable starting from the top left corner, and false otherwise */
bool solve_board(char board[9][9])
{
  return help_solve_board(0, 0, board);
}


/* Attempts to solve recursively (backtracking) the Sudoku puzzle starting from the top left corner */
bool help_solve_board(int row, int col, char board[9][9])
{
  char char_number;
  char position[2];
  
  
  // Skipping all the pre-suplied digits in the Sudoku
  while (row < 9 && board[row][col] != '.')
    {
      col ++;
      if (col == 9)
	{
	  col = 0;
	  row ++;
	}
    }

  // Successfully solving the Sudoku
  if (row == 9)
    return true;

  position[0] = static_cast<char>(row + 'A');
  position[1] = static_cast<char>(col + '1');
  
  // Input values. If a value is successful then recursively call the 'help_solve_board' function
  for (int number = 1; number <= 9; number++)
    {
      char_number = static_cast<char>(number + '0');
      if (make_move(position, char_number, board) && help_solve_board(row, col, board))
	  return true;
    }

  // If this recursion is unsuccessful, then reset the value to '.', return false and try another recursion
  board[row][col] = '.';
  return false;
}

 
/* Extra Tests for Q4, check whether the board has been solved correctly */
bool check_board(char board[9][9])
{
  int count_row, count_col, count_submatrix, starting_row, starting_col;
  bool valid_board = true;
  
  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
      {
	// Checking if all cells contain digits from 1 to 9
	if ((board[row][col] < '1') && (board[row][col] > '9'))
	  {
	    cout << "Invalid digit has been entered in row " << row + 1 << " column " << col + 1 << endl;
	    valid_board = false;
	    continue;
	  }
	
	count_row = 0;
	count_col = 0;
	for (int i = 0; i < 9; i++)
	  {
	    // Checking for duplicate in the same row
	    if (board[row][col] == board[row][i])
	      {
		count_row++;
		if (count_row == 2)
		  {
		    cout << "There is at least 1 duplicate in row " << row + 1 << endl;
		    valid_board = false;
		    break;
		  }
	      }
	    // Checking for duplicate in the same column
	    if (board[row][col] == board[i][col])
	      {
		count_col++;
		if (count_col == 2)
		  {
		    cout << "There is at least 1 duplicate in column " << col + 1 << endl;
		    valid_board = false;
		    break;
		  }
	      }
	  }
	// Checking for duplicate in the 3x3 submatrix
	count_submatrix = 0;
	starting_row = get_starting_point(row);
	starting_col = get_starting_point(col);
	for (int i = starting_row; i < starting_row + 3; i++)
	  for (int j = starting_col; j < starting_col + 3; j++)
	    {
	      if (board[row][col] == board[i][j])
		{
		  count_submatrix++;
		  if (count_submatrix == 2)
		    {
		      cout << "There is at least one duplicate in the 3x3 submatrix, part of which is the cell positioned in the " << row + 1 << " row and " << col + 1 << " column" << endl;
		      valid_board = false;
		      break;
		    }
		}
	    }
      }

  return valid_board;
}


/* Extra Test for Q4, checking whether original values of the assigned Sudoku puzzle have been changed */
bool correct_original_values(const char *filename, char board[9][9])
{
  char unsolved_board[9][9];
  load_board(filename, unsolved_board);
  
  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
      if ((unsolved_board[row][col] != '.') && (unsolved_board[row][col] != board[row][col]))
	return false;

  return true;
}
