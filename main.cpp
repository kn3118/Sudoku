#include "sudoku.h"
#include <iostream>
#include <cstdio>
#include <chrono>


using namespace std;
using namespace std::chrono;


int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << endl << endl;

  
  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  
  cout << "=================== Question 1 ===================" << endl << endl;

  
  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  
  cout << "=================== Question 2 ===================" << endl << endl;

  
  load_board("easy.dat", board);

  // Should work fine and input the value in the board
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Test for invalid row input -> invalid character
  cout << "Putting '1' into K1 is ";
  if (!make_move("K1", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Test for invalid row input -> using digit instead of letter for row input
  cout << "Putting '9' into 19 is ";
  if (!make_move("19", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Test for invalid column input
  cout << "Putting '9' into A16 is ";
  if (!make_move("A16", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Test for invalid digit input
  cout << "Putting '0' into D1 is ";
  if (!make_move("D1", '0', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Test for entering a number that already exists in a row
  cout << "Putting '1' into A2 is ";
  if (!make_move("A2", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Test for entering a number that already exists in a column
  cout << "Putting '2' into D1 is ";
  if (!make_move("D1", '2', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Test for a digit that already exists in the 3x3 sub-board
  cout << "Putting '9' into I9 is ";
  if (!make_move("I9", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  
  cout << "=================== Question 3 ===================" << endl << endl;

  
  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  
  cout << "=================== Question 4 ===================" << endl << endl;

  
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
    // if (!correct_original_values("easy.dat", board))
    //cout << "The board changes the original values, which is not allowed! The solved board is wrong!" << endl;
    //if (!check_board(board))
    // cout << "The board is NOT valid ";
  }
  else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
    //  if (!correct_original_values("medium.dat", board))
    //cout << "The board changes the original values, which is not allowed! The solved board is wrong!" << endl;
    //if (!check_board(board))
    // cout << "The board is NOT valid ";
  }
  else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  

  cout << "=================== Question 5 ===================" << endl << endl;

  // Solve mystery1.dat starting from the top left corner
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  }
  else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  // Solve mystery2.dat starting from the top left corner
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  }
  else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  // Solve mystery3.dat starting from the top left corner
  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  }
  else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  
  return 0;

}
