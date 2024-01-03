#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
// Size of the gameboard
const unsigned int SIZE = 8;

// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard class
class GameBoard
{
public:

    // Constructor: you can add parameters if needed, pieceChar added to constructor
    GameBoard(char pieceChar);

    // Prints the gameboard (after you have finished the method).
    void print() const;

    // Checks if the move is on the gameboard
    bool isValidPoint(int x, int y) const;

    // Checks if the move is possible to make
    bool canMove(int startX, int startY, int destX, int destY) const;

    // Moves the game piece
    void movePiece(int startX, int startY, int destX, int destY);

    // Getter for moveCount
    unsigned int getMoveCount() const;

    // Getter for pieceCount
    unsigned int getPieceCount() const;

private:
    // Vector which includes vectors of characters
    std::vector<std::vector< char >> board;

    // Member variable to store the piece character
    char pieceCharacter;

    // Prints a line with the given length and fill character.
    void print_line(unsigned int length, char fill_character) const;

    // Method to initialize the game board with the piece character
    void initializeBoard();

    // Member variable to store the number of moves made by player
    unsigned int moveCount;

    // Member variable to store the number of pieces on the board
    unsigned int pieceCount;

};

#endif // GAMEBOARD_HH
