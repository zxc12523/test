#include "connect4.h"
#include <bits/stdc++.h>

int op = 0;
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int height[7];
int valid[7];
int grid[6][7];
int val[6][7];

// The columns are numbered from 0 to 6

void check_valid()
{
    for (int j = 0; j < 7; j++)
        valid[j] = (height[j] != 7);
}

void update_grid(int p, int col)
{
    grid[height[col]++][col] = p;
}

void update_val(int p, int i, int j)
{
    for (int k = 0; k < 8; k++)
    {
    }
}

int decide(int yp_move)
{
    if (yp_move == -1)
    {
        // A new game starts
        // TODO: Please remember to reset everything here (if needed)
        op = 0;

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 7; j++)
                grid[i][j] = val[i][j] = 0;

        for (int j = 0; j < 7; j++)
            valid[j] = 1, height[j] = 0;
    }
    else
    {
        // YP placed his piece at column `yp_move`
        update_grid(2, yp_move);
    }

    if (op < 3)
    {
    }

    return 6; // always place at the rightmost column
}
