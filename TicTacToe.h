#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <tuple>
using namespace std;

typedef tuple<int, int, int> myTuple;

class TicTacToe
{
    public:
        TicTacToe();
        ~TicTacToe();
        void play();
    private:
        int grid[3][3];
        int rowSum[3];
        int colSum[3];
        int diagSum[2];
        int scores[2];
        int moves;
        int gameStatus;
        bool first;
        void printGrid();
        void clear();
        void updateSum(int i, int j, int value);
        void move(int i, int j, int value);
        void randomMove();
        void playerMove();
        static bool compareMyTuple(const myTuple &lhs, const myTuple &rhs);
        void minMaxMove();
        myTuple minMaxAI(int value);
         
};

#endif
