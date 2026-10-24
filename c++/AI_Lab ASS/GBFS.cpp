#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

struct Node
{
    int x, y;
    int h;

    bool operator>(const Node& other) const
    {
        return h > other.h;
    }
};

// Heuristic function
int heuristic(int x, int y, int gx, int gy)
{
    return abs(x - gx) + abs(y - gy);
}

void greedyBestFirst(vector<string> maze,
                     int sx, int sy,
                     int gx, int gy)
{
    int rows = maze.size();
    int cols = maze[0].size();

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    vector<vector<bool>> visited(rows,
                                 vector<bool>(cols, false));

    vector<vector<pair<int, int>>> parent(
        rows,
        vector<pair<int, int>>(cols, {-1, -1})
    );

    // Insert starting position
    pq.push({sx, sy, heuristic(sx, sy, gx, gy)});
    visited[sx][sy] = true;

    // Up, Down, Left, Right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        int x = current.x;
        int y = current.y;

        // Goal reached
        if (x == gx && y == gy)
        {
            cout << "Goal reached!\n";

            // Trace the path
            int px = gx;
            int py = gy;

            while (!(px == sx && py == sy))
            {
                maze[px][py] = '*';

                int tempX = parent[px][py].first;
                int tempY = parent[px][py].second;

                px = tempX;
                py = tempY;
            }

            maze[sx][sy] = 'S';
            maze[gx][gy] = 'G';

            cout << "\nPath:\n";

            for (int i = 0; i < rows; i++)
            {
                cout << maze[i] << endl;
            }

            return;
        }

        // Generate neighbors
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Check valid position
            if (nx >= 0 && nx < rows &&
                ny >= 0 && ny < cols &&
                maze[nx][ny] != '#' &&
                !visited[nx][ny])
            {
                visited[nx][ny] = true;

                // Store parent
                parent[nx][ny] = {x, y};

                // Calculate heuristic
                int h = heuristic(nx, ny, gx, gy);

                // Add to priority queue
                pq.push({nx, ny, h});
            }
        }
    }

    cout << "Goal cannot be reached.\n";
}

int main()
{
    vector<string> maze =
    {
        "S....#....",
        ".##..#....",
        "....##....",
        "..........",
        "....###...",
        ".........G"
    };

    // Start position
    int sx = 0;
    int sy = 0;

    // Goal position
    int gx = 5;
    int gy = 9;

    cout << "Original Maze:\n";

    for (string row : maze)
    {
        cout << row << endl;
    }

    cout << "\nGreedy Best-First Search:\n";

    greedyBestFirst(maze, sx, sy, gx, gy);

    return 0;
}