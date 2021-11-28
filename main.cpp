#include <iostream>
#include <array>

using namespace std;

const int rows = 6;
const int cols = 7;

const char p1Color = 'R';
const char p2Color = 'B';

void initialize(array<array <char, cols>, rows>& board);

bool isNotFull(array<array <char, cols>, rows> board);

void ausgabe(array<array <char, cols>, rows> board);

void setStone(array<array <char, cols>, rows>& board, int inputCol, bool& playerTurn);

int checkIfWon(array<array <char, cols>, rows> board);

bool checkColFull(array<array <char, cols>, rows> board, int col);

void changePlayer(bool& playerTurn);

int main()
{
    array<array <char, cols>, rows> board {};
    bool p1Turn = true;
    initialize(board);
    ausgabe(board);

    int inputCol = 0;

    while (isNotFull(board) != false) {
        if (p1Turn == false) {
            cout << "Spieler 2 (R = Rot) bitte Spalte waehlen (1-7): " << endl;
        }
        else {
            cout << "Spieler 1 (B = Blau) bitte Spalte waehlen (1-7): " << endl;
        }
        cin >> inputCol;
        while (inputCol > cols || inputCol < 0) {
            cout << "Bitte Spalte 1-7 waehlen: " << endl;
            cin >> inputCol;
        }
        setStone(board, inputCol - 1, p1Turn);
        ausgabe(board);
        if (checkIfWon(board) == 1) {
            cout << "Player 1 (R = Rot) hat gewonnen" << endl;
            break;
        }
        if (checkIfWon(board) == 2) {
            cout << "Player 2 (B = Blau) hat gewonnen" << endl;
            break;
        }
    }
    return 0;
}

void initialize(array<array <char, cols>, rows>& board) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            board.at(i).at(j) = 'O';
        }
    }
}

void ausgabe(array<array <char, cols>, rows> board) {

    cout << "  ";
    for (int i = 0; i < cols; ++i) {
        cout << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < rows; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < cols; ++j) {
            cout << board.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

bool isNotFull(array<array <char, cols>, rows> board){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board.at(i).at(j) == 'O'){
                return true;
            }
        }
    }
    return false;
}

void setStone(array<array <char, cols>, rows>& board, int inputCol, bool& playerTurn){
    int inputRow = rows - 1;
    if (checkColFull(board, inputCol) == true) {
        return;
    }
    if (playerTurn == 0) {
        while (board.at(inputRow).at(inputCol) == p1Color || board.at(inputRow).at(inputCol) == p2Color ) {
            --inputRow;
        }
        board.at(inputRow).at(inputCol) = p1Color;
        changePlayer(playerTurn);
    }
    else {
        while (board.at(inputRow).at(inputCol) == p1Color || board.at(inputRow).at(inputCol) == p2Color) {
            --inputRow;
        }
        board.at(inputRow).at(inputCol) = p2Color;
        changePlayer(playerTurn);
    }

}

void changePlayer(bool& playerTurn) {
    if (playerTurn == false) {
        playerTurn = true;
    }
    else {
        playerTurn = false;
    }
}

bool checkColFull(array<array <char, cols>, rows> board, int col) {
    for (int i = 0; i < rows; ++i) {
        if (board.at(i).at(col) == 'O') {
            return false;
        }
    }
    return true;
}

int checkIfWon(array<array <char, cols>, rows> board) {
    //Check for Horizontal
    int countP1 = 0;
    int countP2 = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board.at(i).at(j) == p1Color) {
                ++countP1;
                countP2 = 0;
            }
            else if (board.at(i).at(j) == p2Color) {
                ++countP2;
                countP1 = 0;
            }
            if (countP1 >= 4) {
                return 1;
            }
            if (countP2 >= 4) {
                return 2;
            }
        }
        countP1 = 0;
        countP2 = 0;
    }

    //Check for Vertical

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (board.at(j).at(i) == p1Color) {
                ++countP1;
                countP2 = 0;
            }
            else if (board.at(j).at(i) == p2Color) {
                ++countP2;
                countP1 = 0;
            }
            if (countP1 >= 4) {
                return 1;
            }
            if (countP2 >= 4) {
                return 2;
            }
        }
        countP1 = 0;
        countP2 = 0;
    }
    return 0;
}
