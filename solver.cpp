#include <bits/stdc++.h>
using namespace std;

int board[81];
int backtracks = 0, nodes = 0;

bool isValid(int pos, int val) {
    int r = pos / 9, c = pos % 9;
    for (int i = 0; i < 9; i++) {
        if (board[r*9+i] == val && i != c) return false;
        if (board[i*9+c] == val && i != r) return false;
    }
    int br = (r/3)*3, bc = (c/3)*3;
    for (int dr = 0; dr < 3; dr++)
        for (int dc = 0; dc < 3; dc++) {
            int ni = (br+dr)*9+(bc+dc);
            if (ni != pos && board[ni] == val) return false;
        }
    return true;
}

int pickCell() {
    int best = -1, bestLen = 10;
    for (int i = 0; i < 81; i++) {
        if (board[i] == 0) {
            int cnt = 0;
            for (int v = 1; v <= 9; v++)
                if (isValid(i, v)) cnt++;
            if (cnt < bestLen) { bestLen = cnt; best = i; }
            if (bestLen == 1) break;
        }
    }
    return best;
}

bool solve() {
    int pos = pickCell();
    if (pos == -1) return true;
    nodes++;
    for (int v = 1; v <= 9; v++) {
        if (isValid(pos, v)) {
            board[pos] = v;
            if (solve()) return true;
            board[pos] = 0;
            backtracks++;
        }
    }
    return false;
}

void printBoard() {
    for (int r = 0; r < 9; r++) {
        if (r % 3 == 0 && r != 0) cout << "------+-------+------\n";
        for (int c = 0; c < 9; c++) {
            if (c % 3 == 0 && c != 0) cout << " | ";
            cout << board[r*9+c];
            if (c < 8) cout << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    string line;
    int i = 0;
    ifstream fin(argc > 1 ? argv[1] : "/dev/stdin");
    if (!fin) { cerr << "Cannot open file.\n"; return 1; }

    while (getline(fin, line))
        for (char ch : line)
            if (ch >= '0' && ch <= '9') board[i++] = ch - '0';

    if (i != 81) { cerr << "Invalid puzzle: need exactly 81 digits.\n"; return 1; }

    cout << "\nInput puzzle:\n";
    printBoard();

    auto t0 = chrono::high_resolution_clock::now();
    bool ok = solve();
    auto t1 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t1 - t0).count();

    if (ok) {
        cout << "\nSolved:\n";
        printBoard();
        cout << "\n✓ Solved in " << fixed << setprecision(3) << ms << " ms"
             << " | Backtracks: " << backtracks
             << " | Nodes: " << nodes << "\n";
    } else {
        cout << "\n✗ No solution exists.\n";
    }
    return 0;
}
