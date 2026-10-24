#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Maze
// 0 = Free cell
// 1 = Wall
int maze[5][5] = {
    {0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
};

int rows = 5;
int cols = 5;

// Directions: Up, Down, Left, Right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// Manhattan Distance Heuristic
int heuristic(int r, int c, int gr, int gc)
{
    return abs(r - gr) + abs(c - gc);
}

// Check whether a cell is valid
bool isValid(int r, int c)
{
    return r >= 0 && r < rows &&
           c >= 0 && c < cols &&
           maze[r][c] == 0;
}

void hillClimbing(int sr, int sc, int gr, int gc)
{
    int r = sr;
    int c = sc;

    vector<pair<int, int>> path;

    path.push_back({r, c});

    cout << "Hill Climbing Search" << endl;
    cout << "---------------------" << endl;

    while (true)
    {
        int currentH = heuristic(r, c, gr, gc);

        cout << "Current: (" << r << "," << c << ")";
        cout << "  Heuristic = " << currentH << endl;

        // Goal reached
        if (r == gr && c == gc)
        {
            cout << "\nGoal reached!" << endl;
            break;
        }

        int bestR = r;
        int bestC = c;
        int bestH = currentH;

        // Check all neighbors
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (isValid(nr, nc))
            {
                int h = heuristic(nr, nc, gr, gc);

                cout << "  Neighbor (" << nr << "," << nc
                     << ") -> h = " << h << endl;

                // Select neighbor with lower heuristic
                if (h < bestH)
                {
                    bestH = h;
                    bestR = nr;
                    bestC = nc;
                }
            }
        }

        // No better neighbor found
        if (bestR == r && bestC == c)
        {
            cout << "\nHill Climbing stopped." << endl;
            cout << "No better neighboring state found." << endl;
            break;
        }

        // Move to the best neighbor
        r = bestR;
        c = bestC;

        path.push_back({r, c});
    }

    // Display path
    cout << "\nPath followed:" << endl;

    for (auto p : path)
    {
        cout << "(" << p.first << "," << p.second << ") ";
    }

    cout << "\nTotal moves = " << path.size() - 1 << endl;
}

int main()
{
    // Start position
    int startRow = 0;
    int startCol = 0;

    // Goal position
    int goalRow = 4;
    int goalCol = 4;

    hillClimbing(startRow, startCol, goalRow, goalCol);

    return 0;
} 