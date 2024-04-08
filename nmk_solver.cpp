#include <iostream>
#include <string.h>

#define PLAYER1 '1'
#define PLAYER2 '2'
#define ALPHA -1000
#define BETA 1000
#define MAX_DEPTH 1000
#define INITIAL_DEPTH 1
#define PLAYER1WON -10
#define PLAYER2WON 10

using namespace std;

void printArray(char **arr, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void writeArray(char **arr, int rows, int columns)  ///Function to type in a board for NMK GAME
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            cin >> arr[i][j];
        }
    }
}

void copyArray(char** src, char** dst, int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            dst[i][j] = src[i][j];
        }
    }
}

/// Checking a horizontal line for a win ///

bool checkRow(char **arr, int row, int column, int rows, int columns, char activePlayer, int howManyToWin)
{
    int counter = 0;
    for(int k = 0; k < columns; k++)
    {
        if(columns - k < howManyToWin && counter == 0)
        {
            break;
        }
        if(column + k < columns)
        {
            if(arr[row][column + k] == activePlayer)
            {
                counter++;
                if(counter >= howManyToWin)
                {
                    break;
                }
            }
            else 
            {
                counter = 0;
            }
        }
    }
    if(counter >= howManyToWin)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//// Checking a vertical line for a win ////

bool checkColumn(char **arr, int row, int column, int rows, int columns, char activePlayer, int howManyToWin)
{
    int counter = 0;
    for(int k = 0; k < rows; k++)
    {
        if(rows - k < howManyToWin && counter == 0)
        {
            break;
        }
        if(row + k < rows)
        {
            if(arr[row + k][column] == activePlayer)
            {
                counter++;
                if(counter >= howManyToWin)
                {
                    break;
                }
            }    
            else 
            {
                counter = 0;
            }  
        }
    }
    if(counter >= howManyToWin)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//// Checking one diagonal for a win ////

bool checkOneDiagonal(char **arr, int row, int rows, int column, int columns, char activePlayer, int howManyToWin)
{
    int counter = 0;
    for(int k = -columns; k < columns; k++)
    {
        if(row + k < rows && column + k < columns && row + k >=0 && column + k >= 0)
        {
            if(arr[row + k][column + k] == activePlayer)
            {
                counter++;
                if(counter >= howManyToWin)
                {
                    break;
                }
            }
            else
            {
                counter = 0;
            }
        }
    }
    if(counter >= howManyToWin)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//// Checking second diagonal for a win ////

bool checkSecondDiagonal(char **arr, int row, int rows, int column, int columns, char activePlayer, int howManyToWin)
{
    int counter = 0;
    for(int k = -columns; k < columns; k++)
    {
        if(row - k >= 0 && column + k < columns && row - k < rows && column + k >=0)
        {
            if(arr[row - k][column + k] == activePlayer)
            {
                counter++;
                if(counter >= howManyToWin)
                {
                    break;
                }
            }
            else
            {
                counter = 0;
            }
        }
    }
    if(counter >= howManyToWin)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool checkDiagonals(char **arr, int row, int rows, int column, int columns, char activePlayer, int howManyToWin)
{
    if(checkOneDiagonal(arr, row, rows, column, columns, activePlayer, howManyToWin) || checkSecondDiagonal(arr, row, rows, column, columns, activePlayer, howManyToWin))
    {
        return true;
    }
    return false;
}

/// Checking all combinations for a win ///

bool checkCombinations(char **arr, int row, int rows, int column, int columns, char activePlayer, int howManyToWin)
{
    if(checkRow(arr, row, column, rows, columns, activePlayer, howManyToWin))
    {
        return true;
    }
    else
    {
        if(checkColumn(arr, row, column, rows, columns, activePlayer, howManyToWin))
        {
            return true;
        }
        else 
        {
            if(checkDiagonals(arr, row, rows, column, columns, activePlayer, howManyToWin))
            {
                return true;
            }
        }
    }
    return false;
}

/// Checking if somebody won a game ///

bool somebodyWon(char **arr, int rows, int columns, char activePlayer, int howManyToWin)
{
    for(int i = 0; i < rows; i++)
    {
        if(checkCombinations(arr, i, rows, 0, columns, activePlayer, howManyToWin))
        {
            return true;
        }
    }
    for(int i = 0; i < columns; i++)
    {
        if(checkCombinations(arr, 0, rows, i, columns, activePlayer, howManyToWin))
        {
            return true;
        }
    }
    for(int i = 0; i < columns; i++)
    {
        if(checkCombinations(arr, rows-1, rows, i, columns, activePlayer, howManyToWin))
        {
            return true;
        }
    }
    return false;
}

/// Checking if a move is a winning move ///

bool isWinningMove(char **arr, int row, int column, int rows, int columns, char activePlayer, int howManyToWin)
{
    for(int i = row - (howManyToWin - 1); i < row + (howManyToWin - 1); i++)
    {
        for(int j = column - (howManyToWin - 1); j < column + (howManyToWin - 1); j++)
        {
            if(i >=0 && i < rows && j >= 0 && j < columns)
            {
                if(checkCombinations(arr, i, rows, j, columns, activePlayer, howManyToWin))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int howManyMoves(char **arr, int rows, int columns, int howManyToWin) /// Check how many moves are possible ///
{
    unsigned short int counter = 0;
    if(somebodyWon(arr, rows, columns, PLAYER1, howManyToWin) || somebodyWon(arr, rows, columns, PLAYER2, howManyToWin))
    {
        return 0;
    }
    else 
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                if(arr[i][j] == '0')
                {
                    counter++;
                }
            }
        }
        return counter;
    }
}

void printAllPossibleMoves(char **src, int rows, int columns, char activePlayer, int howManyToWin)
{
    char** dst = new char* [rows];
    for(int i = 0; i < rows; i++)
    {
        dst[i] = new char[columns];
    }
    copyArray(src, dst, rows, columns);
    if(somebodyWon(src, rows, columns, PLAYER1, howManyToWin) || somebodyWon(src, rows, columns, PLAYER2, howManyToWin))
    {
        delete[] dst;
        return;
    }
    else
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                if(dst[i][j] == '0')
                {
                    if(activePlayer == PLAYER1)
                    {
                        dst[i][j] = PLAYER1;
                    }
                    else if(activePlayer == PLAYER2)
                    {
                        dst[i][j] = PLAYER2;
                    }
                    printArray(dst, rows, columns);
                    copyArray(src, dst, rows, columns);
                }   
            }
        }
    }
    delete[] dst;
}

void printAllPossibleMovesCutIfGameOver(char **src, int rows, int columns, char activePlayer, int howManyToWin)
{
    int counter = howManyMoves(src, rows, columns, howManyToWin);
    char** dst = new char* [rows];
    for(int i = 0; i < rows; i++)
    {
        dst[i] = new char[columns];
    }
    char** winningArray = new char* [rows];
    for(int i = 0; i < rows; i++)
    {
        winningArray[i] = new char[columns];
    }
    copyArray(src, dst, rows, columns);
    if(somebodyWon(src, rows, columns, PLAYER1, howManyToWin) || somebodyWon(src, rows, columns, PLAYER2, howManyToWin))
    {
        cout << 0 << endl;
        delete[] winningArray;
        delete[] dst;
        return;
    }
    else
    {
        bool winning = 0;
        for(int i = 0; i < rows; i++)
        {
            if(winning)
            {
                break;
            }
            else
            {
                for(int j = 0; j < columns; j++)
                {
                    if(dst[i][j] == '0')
                    {
                        if(activePlayer == PLAYER1)
                        {
                            dst[i][j] = PLAYER1;
                        }
                        else if(activePlayer == PLAYER2)
                        {
                            dst[i][j] = PLAYER2;
                        }
                        if(isWinningMove(dst, i, j, rows, columns, activePlayer, howManyToWin))
                        {
                            copyArray(dst, winningArray, rows, columns);
                            winning = 1;
                            break;
                        }
                        copyArray(src, dst, rows, columns);
                    }   
                }
            }
        }
        if(winning)
        {
            cout << 1 << endl;
            printArray(winningArray, rows, columns);
        }
        else
        {
            cout << counter << endl;
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < columns; j++)
                {
                    if(dst[i][j] == '0')
                    {
                        if(activePlayer == PLAYER1)
                        {
                            dst[i][j] = PLAYER1;
                        }
                        else if(activePlayer == PLAYER2)
                        {
                            dst[i][j] = PLAYER2;
                        }
                        printArray(dst, rows, columns);
                        copyArray(src, dst, rows, columns);
                    }   
                }
            }
        }
    }
    delete[] dst;
    delete[] winningArray;
}

bool isMovesLeft(char **arr, int rows, int columns) //// Checking if there are any moves left to do ////
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(arr[i][j] == '0')
            {
                return true;
            }
        }
    }
    return false;
}

//// Minimax algorithm which evaluates who will win a match ////

int minimax(char **arr, int rows, int columns, int howManyToWin, int depth, bool isMax, int howDeep, int alpha, int beta)
{
    if (depth == howDeep) 
    {
        return 0;
    }
    if(isMax)
    {
        if(somebodyWon(arr, rows, columns, PLAYER1, howManyToWin))
        {
            return PLAYER1WON;
        }
    }
    else
    {
        if(somebodyWon(arr, rows, columns, PLAYER2, howManyToWin))
        {
            return PLAYER2WON;
        }
    }
    if(isMovesLeft(arr, rows, columns) == false)
    {
        return 0;
    }
    if(isMax)
    {
        int best = -100;
        int tmp = 0;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
               if(arr[i][j] == '0')
               {
                    arr[i][j] = PLAYER2;
                    tmp = minimax(arr, rows, columns, howManyToWin, depth+1, !isMax, howDeep, alpha, beta);
                    arr[i][j] = '0';
                    if (tmp > best) 
                    {
                        best = tmp;
                    }
                    if (best > alpha) 
                    {
                        alpha = best;
                    }
                    if (beta <= alpha) 
                    {
                        break;
                    }
               } 
            }  
        }
        return best;
    }
    else
    {
        int best = 100;
        int tmp = 0;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                if(arr[i][j] == '0')
                {
                    arr[i][j] = PLAYER1;
                    tmp = minimax(arr, rows, columns, howManyToWin, depth+1, !isMax, howDeep, alpha, beta);
                    arr[i][j] = '0';
                    if (tmp < best) 
                    {
                        best = tmp;
                    }
                    if (best < beta) 
                    {
                        beta = best;
                    }
                    if (beta <= alpha) 
                    {
                        break;
                    }
                }
            }
        }
        return best;
    }
}

//// NMK solver which uses Minimax algorithm with alpha-beta pruning////

void solveGameState(char **arr, int rows, int columns, int howManyToWin, char activePlayer)
{
    int evaluation = 0;
    if(activePlayer == PLAYER2)
    {
        evaluation = minimax(arr, rows, columns, howManyToWin, INITIAL_DEPTH, true, MAX_DEPTH, ALPHA, BETA);
    }
    else if(activePlayer == PLAYER1)
    {
        evaluation = minimax(arr, rows, columns, howManyToWin, INITIAL_DEPTH, false, MAX_DEPTH, ALPHA, BETA);
    }
    if(evaluation == PLAYER1WON)
    {
        cout << "FIRST_PLAYER_WINS" << endl;
    }
    else if(evaluation == PLAYER2WON)
    {
        cout << "SECOND_PLAYER_WINS" << endl;
    }
    else 
    {
        cout << "BOTH_PLAYERS_TIE" << endl;
    }
}

int main()
{
    char command[35];    
    while(cin >> command)
    {
        if(strcmp(command, "GEN_ALL_POS_MOV") == 0)
        {
            int n;
            int m;
            int k;
            char activePlayer;
            cin >> n >> m >> k;
            cin >> activePlayer;
            char** board = new char* [n];
            for(int i = 0; i < n; i++)
            {
                board[i] = new char[m];
            }
            writeArray(board, n, m);
            int moves = howManyMoves(board, n, m, k);
            cout << moves << endl;
            printAllPossibleMoves(board, n, m, activePlayer, k);
            delete[] board;
        }
        else if(strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
        {
            int n;
            int m;
            int k;
            char activePlayer;
            cin >> n >> m >> k;
            cin >> activePlayer;
            char** board = new char* [n];
            for(int i = 0; i < n; i++)
            {
                board[i] = new char[m];
            }
            writeArray(board, n, m);
            printAllPossibleMovesCutIfGameOver(board, n, m, activePlayer, k);
            delete[] board;
        }
        else if(strcmp(command, "SOLVE_GAME_STATE") == 0)
        {
            int n;
            int m;
            int k;
            char activePlayer;
            cin >> n >> m >> k;
            cin >> activePlayer;
            char** board = new char* [n];
            for(int i = 0; i < n; i++)
            {
                board[i] = new char[m];
            }
            writeArray(board, n, m);
            solveGameState(board, n, m, k, activePlayer);
            delete[] board;
        }
    }
    return 0;
}
