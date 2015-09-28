#include "TicTacToe.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

TicTacToe::TicTacToe()
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
            grid[i][j] = 0;
    }

    for (int i=0; i<3; i++)
    {
        rowSum[i] = 0;
        colSum[i] = 0;
    }

    diagSum[0] = 0;
    diagSum[1] = 0;

    moves = 0;
    first = true;
    gameStatus = 0;
    scores[0] = 0;
    scores[1] = 0;

    cout << "Initiating..." << endl;
}

TicTacToe::~TicTacToe()
{
    cout << "Done..." << endl;
}

void TicTacToe::printGrid()
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (grid[i][j] == 0)
                cout << '-' << ' ';

            if (grid[i][j] == 1)
                cout << 'o' << ' ';

            if(grid[i][j] == -1)
                cout << 'x' << ' ';
        }
        cout << endl;
    }
}

void TicTacToe::play()
{
    char again;
    char hardChar;
    bool playerThisRound;

    while (true)
    {
        if (first)
        {
            srand(time(NULL));
            playerThisRound = rand() % 2 == 0;
            first = false;
            cout << "Press Y to play with TicTacToe master Cat Killer, N to play with newbie Dumb Dumb." << endl;
            cin >> hardChar;
        }
        else
        {
            cout << "Your current score is " << scores[0] << '/' << scores[1] << endl;
            cout << "Your win rate is " << double(scores[0]) / double(scores[1]) << endl;
            if (scores[1] >= 6 && hardChar == 'Y')
                cout << "Opps! Looks like master Cat Killer is kicking your ass!" << endl;
            cout << "Do you want another round? Y for yes and N for no." << endl;
            cin >> again;
            if (again == 'N')
                return;

            clear();
        }

        cout << (playerThisRound ? "You" : "Opponent") << " get to move first." << endl;

        while (gameStatus == 0)
        {
            if (playerThisRound)
            {
                playerMove();
            }
            else
            {
                if (hardChar == 'Y')
                    minMaxMove();
                else
                    randomMove();
                printGrid();
            }
            playerThisRound = !playerThisRound;
        }

        if (gameStatus == 3)
        {
            cout << "You win!!" << endl;
            scores[0]++;
        }
        if (gameStatus == -3)
            cout << "You lose!!" << endl;

        if (gameStatus == 2)
            cout << "It's a draw." << endl;

        scores[1]++;
    }
}

void TicTacToe::clear()
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
            grid[i][j] = 0;
    }

    for (int i=0; i<3; i++)
    {
        rowSum[i] = 0;
        colSum[i] = 0;
    }

    diagSum[0] = 0;
    diagSum[1] = 0;
    moves = 0;
    gameStatus = 0;
}

void TicTacToe::move(int i, int j, int value)
{
    grid[i-1][j-1] += value;
    moves++;
    updateSum(i, j, value);
    return;
}

void TicTacToe::updateSum(int i, int j, int value)
{
    rowSum[i-1] += value;

    colSum[j-1] += value;

    if ((i + j) % 2 == 0)
    {
        if (i == j)
        {
            diagSum[0] += value;
            if (i == 2)
                diagSum[1] += value;
        }
        else
            diagSum[1] += value;

        if (abs(diagSum[0]) == 3)
        {
            gameStatus = diagSum[0];
            return;
        }

        if (abs(diagSum[1]) == 3)
        {
            gameStatus = diagSum[1];
            return;
        }
    }

    if (abs(rowSum[i-1]) == 3)
    {
        gameStatus = rowSum[i-1];
        return; 
    }

    if (abs(colSum[j-1]) == 3)
    {
        gameStatus = colSum[j-1];
        return;
    }

    if (moves == 9)
    {
        gameStatus = 2;
        return;
    }

    return;
}

void TicTacToe::randomMove()
{
    int i;
    int j;
    srand(time(NULL));

    do
    {
        i = rand() % 3 + 1;
        j = rand() % 3 + 1;
    } while (grid[i-1][j-1] != 0);

    cout << "Dumb Dumb is taking (" << i << ',' << j << ')' << endl;
    move(i, j, -1);
    return;
}

void TicTacToe::playerMove()
{
    int i;
    int j;

    do
    {
        cout << "Please enter row coordinates(1-3)." << endl;
        cin >> i;
        cout << "Please enter col coordinates(1-3)." << endl;
        cin >> j;
        if (grid[i-1][j-1] != 0)
            cout << "Space already occupied!" << endl;
        if (i < 1 || i > 3 || j < 1 || j > 3)
            cout << "Irregular coordinates!" << endl;
    } while (grid[i-1][j-1] != 0 || i < 1 || i > 3 || j < 1 || j > 3);

    cout << "You are taking (" << i << ',' << j << ')' << endl;
    move(i, j, 1);

    return; 
}

bool TicTacToe::compareMyTuple(const myTuple &lhs, const myTuple &rhs)
{
    return get<2>(lhs) < get<2>(rhs);
}

void TicTacToe::minMaxMove()
{
    int i;
    int j;

    myTuple bestMove = minMaxAI(-1);
    tie(i, j, ignore) = bestMove;

    cout << "Cat Killer is taking (" << i << ',' << j << ')' << endl;
    move(i, j, -1);

    return;
}

myTuple TicTacToe::minMaxAI(int value)
{
    vector<myTuple> scoreList;
    int score;

    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (grid[i][j] == 0)
            {
                move(i + 1, j + 1, value);

                if (abs(gameStatus) == 3)
                {
                    scoreList.push_back(make_tuple(i + 1, j + 1, gameStatus == 3 ? -10 : 10));
                    gameStatus = 0;
                }
                else if (gameStatus == 2)
                {
                    scoreList.push_back(make_tuple(i + 1, j + 1, 0));
                    gameStatus = 0;
                }
                else
                {
                    tie(ignore, ignore, score) = minMaxAI(-value);
                    scoreList.push_back(make_tuple(i + 1, j + 1, score));
                }

                moves = moves - 2;
                move(i + 1, j + 1, -value);
            }
        }
    }

    sort(scoreList.begin(), scoreList.end(), compareMyTuple);

    return value == 1 ? scoreList.front() : scoreList.back();   
}
