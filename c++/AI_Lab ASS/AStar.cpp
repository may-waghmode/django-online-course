#include <bits/stdc++.h>
using namespace std;

string goal = "123456780";

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Manhattan Distance
int heuristic(string s)
{
    int h = 0;

    for (int i = 0; i < 9; i++)
    {
        if (s[i] == '0')
            continue;

        int value = s[i] - '1';

        int goalRow = value / 3;
        int goalCol = value % 3;

        int row = i / 3;
        int col = i % 3;

        h += abs(row - goalRow) + abs(col - goalCol);
    }

    return h;
}

// A* Algorithm
int aStar(string start)
{
    priority_queue<
        tuple<int, int, string>,
        vector<tuple<int, int, string>>,
        greater<tuple<int, int, string>>
    > pq;

    set<string> visited;

    int h = heuristic(start);

    // f = g + h
    pq.push(make_tuple(h, 0, start));

    while (!pq.empty())
    {
        tuple<int, int, string> current = pq.top();
        pq.pop();

        int f = get<0>(current);
        int g = get<1>(current);
        string state = get<2>(current);

        if (visited.count(state))
            continue;

        visited.insert(state);

        // Goal reached
        if (state == goal)
            return g;

        // Find blank position
        int pos = state.find('0');

        int x = pos / 3;
        int y = pos % 3;

        // Try four possible moves
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 3 &&
                ny >= 0 && ny < 3)
            {
                string next = state;

                swap(next[x * 3 + y],
                     next[nx * 3 + ny]);

                if (!visited.count(next))
                {
                    int newG = g + 1;
                    int newH = heuristic(next);
                    int newF = newG + newH;

                    pq.push(make_tuple(newF, newG, next));
                }
            }
        }
    }

    return -1;
}

int main()
{
    string start = "";

    cout << "Enter puzzle (use 0 for blank): ";

    for (int i = 0; i < 9; i++)
    {
        char x;
        cin >> x;w
        start += x;
    }

    int answer = aStar(start);

    if (answer == -1)
        cout << "Puzzle cannot be solved." << endl;
    else
        cout << "Minimum moves = " << answer << endl;

    return 0;
}