#include "gameboard.hh"
#include <iostream>

GameBoard::GameBoard(char pieceChar) : moveCount(0), pieceCount(SIZE * SIZE - 4 * 4)
{
    // Assign the piece character to the member variable
    this->pieceCharacter = pieceChar;

    // Call the initializeBoard to set up the initial state of the game
    initializeBoard();
}

void GameBoard::initializeBoard()
{
    // Loop through each row of the game board.
    for (unsigned int i = 0; i < SIZE; i++)
    {
        // Create a new row (a vector of characters) with SIZE(8) elements
        std::vector<char> row(SIZE);

        if (i >= 2 && i <= 5)
        {
            // For rows 3 to 6, add the piece character only to indexes 1-2 and 7-8
            row.at(0) = row.at(1) = row.at(6) = row.at(7) = pieceCharacter;
            // Add spaces to indexes 3-6
            row.at(2) = row.at(3) = row.at(4) = row.at(5) = ' ';
        }
        else
        {
            // For other rows, initialize all elements to the piece character
            std::fill(row.begin(), row.end(), pieceCharacter);
        }

        // Add the newly created row to the game board,
        // a new row in the 2D game board vector
        board.push_back(row);
    }
}


void GameBoard::print() const
{
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Printing the actual content of the gameboard
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            // Print here empty or the element (i, j) in the gameboard
            std::cout << board.at(i).at(j) << " ";

        }
        std::cout << "|" << std::endl;
    }

    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

bool GameBoard::isValidPoint(int x, int y) const {
    // Returns True if move is on the gameboard false if not
    return x >= 1 && x <= 8 && y >= 1 && y <= 8;
}

bool GameBoard::canMove(int startX, int startY, int destX, int destY) const {
    // Initialize startPiece
    char startPiece = board.at(startY - 1).at(startX - 1);

    // Initialize destPiece
    char destPiece = board.at(destY - 1).at(destX - 1);

    // Check is there a piece on start point and is there a piece on destination point
    if (startPiece != pieceCharacter || destPiece == pieceCharacter) {
        return false;
    }

    // Check if the move is exactly two squares diagonally (indicative of a valid jump over another piece)
    if (abs(destX - startX) != 2 || abs(destY - startY) != 2) {
        return false;
    }

    // Determine the piece that lies between the starting point and the destination point.
    // If there's no game piece present to jump over, the move isn't valid.
    char middlePiece = board.at((startY + destY) / 2 - 1).at((startX + destX) / 2 - 1);
    if (middlePiece != pieceCharacter) {
        return false;
    }

    return true;
}

void GameBoard::movePiece(int startX, int startY, int destX, int destY) {
    // Update counters
    moveCount++;
    pieceCount--;

    // Clear the starting point on the board, indicating the piece has moved.
    board.at(startY - 1).at(startX - 1) = ' ';

    // Place the game piece at the destination point, signifying its new position.
    board.at(destY - 1).at(destX - 1) = pieceCharacter;

    // Remove the piece that was between the starting and destination points, as it's been jumped over and captured.
    board.at((startY + destY) / 2 - 1).at((startX + destX) / 2 - 1) = ' ';
}

unsigned int GameBoard::getMoveCount() const {
    return moveCount;
}

unsigned int GameBoard::getPieceCount() const {
    return pieceCount;
}
