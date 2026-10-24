#include <bits/stdc++.h>
using namespace std;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    string start = "", goal = "123456780";

    cout << "Enter puzzle:\n";
    for (int i = 0; i < 9; i++) {
        char x;
        cin >> x;
        start += x;
    }

    queue<pair<string, int>> q;
    unordered_set<string> vis;

    q.push({start, 0});
    vis.insert(start);

    while (!q.empty()) {

    pair<string, int> current = q.front();
    q.pop();

    string board = current.first;
    int moves = current.second;

    if (board == goal) {
        cout << "Minimum moves = " << moves << endl;
        return 0;
    }

    int pos = board.find('0');
    int r = pos / 3;
    int c = pos % 3;

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
            string next = board;
            swap(next[pos], next[nr * 3 + nc]);

            if (!vis.count(next)) {
                vis.insert(next);
                q.push({next, moves + 1});
            }
        }
    }
}

    cout << "Puzzle cannot be solved.";
}