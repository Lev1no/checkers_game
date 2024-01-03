/* Tammipeli (yhdelle pelaajalle)
 *
 * Kuvaus:
 *   Ohjelma toteuttaa tammipelin yhdelle pelaajalle. Pelilaudan koko
 * on 8 x 8, ja se täytetään tyhjillä sekä pelinappuloilla (käyttäjän
 * valitsema merkki).
 *   Pelilauta on aluksi täynnä nappuloita, mutta keskellä on 4 x 4
 * -kokoinen alue tyhjää. Tarkoitus on saada pelilauta tyhjennettyä
 * niin, että jäljellä on vain yksi pelinappula. Nappulaa voi siirtää
 * viistosti toisen nappulan yli, jolloin poistetaan se nappula, jonka
 * yli hypättiin.
 *   Joka kierroksella käyttäjältä kysytään kahta pistettä (neljää
 * koordinaattia): siirrettävää nappulaa ja sen kohdesijaintia.
 * Ohjelma tarkistaa, voidaanko siirto tehdä.
 *   Ohjelma päättyy, kun pelilaudalla on enää yksi pelinappula tai kun
 * käyttäjä antaa lopetuskomennon (merkki 'q' tai 'Q'). Tällöin ohjelma
 * tulostaa, kuinka monta siirtoa tehtiin ja kuinka monta nappulaa on
 * vielä jäljellä.
 *
 * */

#include "gameboard.hh"
#include <iostream>
#include <sstream>

using namespace std;

int main()
{

    // Initialize the game piece and ask the user to input it
    char pieceChar = ' ';

    cout << "Enter piece character: ";
    cin >> pieceChar;

    // Capture the leftover newline character
    string discard;
    getline(cin, discard);

    // Create an instance of the GameBoard class named 'gameBoard'
    // Initialize it with the provided 'pieceChar'
    GameBoard gameBoard(pieceChar);

    gameBoard.print();

    int startX, startY, destX, destY;
    while (true) {
        cout << "Enter start point (x, y) and destination point (x, y), or q to quit: ";
        string input;
        getline(cin, input);

        // If user input is "q" print the required information and end the program
        if (input == "q") {
            cout << gameBoard.getMoveCount() << " move(s) made." << endl;
            cout << gameBoard.getPieceCount() << " piece(s) left." << endl;
            break;
        }
        // Check is the input given valid
        istringstream ss(input);
        if (!(ss >> startX >> startY >> destX >> destY)) {
            cout << "Invalid start/destination point." << endl;
            continue;
        }
        // Check if the input given is on the board
        if (!gameBoard.isValidPoint(startX, startY) || !gameBoard.isValidPoint(destX, destY)) {
            cout << "Invalid start/destination point." << endl;
            continue;
        }

        // Check if it possible to move the piece if True then move it and print new gameboard
        if (gameBoard.canMove(startX, startY, destX, destY)) {
            gameBoard.movePiece(startX, startY, destX, destY);
            gameBoard.print();
        } else {
            cout << "Cannot move from start point to destination point." << endl;
        }

    }

    return 0;
}
