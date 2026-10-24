#include <iostream>
#include <vector>
#include <limits>

using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

const char AI = 'X';
const char HUMAN = 'O';

// Display the board
void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
                cout << " | ";
        }

        cout << endl;

        if (i < 2)
            cout << "---+---+---" << endl;
    }

    cout << endl;
}

// Check whether a player has won
bool isWinner(char player)
{
    // Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }
    }

    // Columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == player &&
            board[1][j] == player &&
            board[2][j] == player)
        {
            return true;
        }
    }

    // Diagonal
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }

    return false;
}

// Check whether board is full
bool isFull()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
                return false;
        }
    }

    return true;
}

// Minimax with Alpha-Beta Pruning
int minimax(int depth, bool maximizing, int alpha, int beta)
{
    // Terminal states
    if (isWinner(AI))
        return 10 - depth;

    if (isWinner(HUMAN))
        return depth - 10;

    if (isFull())
        return 0;

    // Maximizing player - AI
    if (maximizing)
    {
        int bestScore = numeric_limits<int>::min();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = AI;

                    int score = minimax(
                        depth + 1,
                        false,
                        alpha,
                        beta
                    );

                    board[i][j] = ' ';

                    bestScore = max(bestScore, score);
                    alpha = max(alpha, bestScore);

                    // Alpha-Beta pruning
                    if (beta <= alpha)
                        break;
                }
            }

            if (beta <= alpha)
                break;
        }

        return bestScore;
    }

    // Minimizing player - Human
    else
    {
        int bestScore = numeric_limits<int>::max();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = HUMAN;

                    int score = minimax(
                        depth + 1,
                        true,
                        alpha,
                        beta
                    );

                    board[i][j] = ' ';

                    bestScore = min(bestScore, score);
                    beta = min(beta, bestScore);

                    // Alpha-Beta pruning
                    if (beta <= alpha)
                        break;
                }
            }

            if (beta <= alpha)
                break;
        }

        return bestScore;
    }
}

// Find the best move for AI
void findBestMove()
{
    int bestScore = numeric_limits<int>::min();

    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = AI;

                int score = minimax(
                    0,
                    false,
                    numeric_limits<int>::min(),
                    numeric_limits<int>::max()
                );

                board[i][j] = ' ';

                if (score > bestScore)
                {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    board[bestRow][bestCol] = AI;
}

int main()
{
    cout << "TIC-TAC-TOE AI" << endl;
    cout << "You = O, AI = X" << endl;

    displayBoard();

    while (true)
    {
        int row, col;

        // Human move
        cout << "Enter your move (row and column 1-3): ";
        cin >> row >> col;

        row--;
        col--;

        if (row < 0 || row >= 3 ||
            col < 0 || col >= 3 ||
            board[row][col] != ' ')
        {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        board[row][col] = HUMAN;

        displayBoard();

        if (isWinner(HUMAN))
        {
            cout << "You win!" << endl;
            break;
        }

        if (isFull())
        {
            cout << "Game Draw!" << endl;
            break;
        }

        // AI move
        cout << "AI is thinking..." << endl;

        findBestMove();

        displayBoard();

        if (isWinner(AI))
        {
            cout << "AI wins!" << endl;
            break;
        }

        if (isFull())
        {
            cout << "Game Draw!" << endl;
            break;
        }
    }

    return 0;
}