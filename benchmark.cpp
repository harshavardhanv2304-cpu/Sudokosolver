#include <bits/stdc++.h>
using namespace std;

// ── Solver core (self-contained) ─────────────────────────
struct Solver {
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
};

// ── 20 mixed-difficulty puzzles ──────────────────────────
const vector<string> PUZZLES = {
    "530070000600195000098000060800060003400803001700020006060000280000419005000080079",
    "010020300002003040400500001370600000800000007000008065100007009040900800007040020",
    "000000907000420180000705026100904000050000040000507009920108000034059000507000000",
    "030050040008010500460000012070502080000603000040109030250000098003080600080060020",
    "000000000000003085001020000000507000004000100090000000500000073002010000000040009",
    "800000000003600000070090200060005030000040070000100080001806040008500010090000400",
    "000006000059000008200008000045000000003000000006003054000325006000000000000000000",
    "010000000000000706090300020007000800000700090003080600000030004508000000000900010",
    "200080300060070084030500209000105408000000000402706000301007040720040060004010003",
    "000000000000000000000000000000000000000000000000000000000000000000000000000000001",
    "500000000000000000000000000000000000000000000000000000000000000000000000000000002",
    "300000000000000000000000000000000000000000000000000000000000000000000000000000003",
    "003020600900305001001806400008102900700000008006708200002609500800203009005010300",
    "200000060000075030000000000900006200006000700001200005000000000080950000030000001",
    "000000012000000003002300400001800005060070800000009000008500000900040500470006000",
    "010030000040000700602000000000700030000010005080000000000500400006000090000090020",
    "700000600060010050004000000000060800030000070005090000000000300080020040002000009",
    "000174000000000000070000000010000400000000050006000030000080000000000700000593000",
    "300000000050703008000028070700000043000000000003904100500800000060070800000006007",
    "000000000000000000000000000000000000000000000000000000000000000000000000012345678"
};

int main() {
    cout << "Sudoku Solver Benchmark\n";
    cout << string(50, '=') << "\n\n";
    cout << left << setw(6) << "#"
         << setw(12) << "Time (ms)"
         << setw(14) << "Backtracks"
         << setw(12) << "Nodes"
         << "Status\n";
    cout << string(50, '-') << "\n";

    double totalMs = 0;
    int totalBt = 0, totalNodes = 0, solved = 0;

    for (int i = 0; i < (int)PUZZLES.size(); i++) {
        Solver s;
        int j = 0;
        for (char ch : PUZZLES[i])
            s.board[j++] = ch - '0';

        auto t0 = chrono::high_resolution_clock::now();
        bool ok = s.solve();
        auto t1 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t1 - t0).count();

        totalMs    += ms;
        totalBt    += s.backtracks;
        totalNodes += s.nodes;
        if (ok) solved++;

        cout << left << setw(6) << (i+1)
             << setw(12) << fixed << setprecision(3) << ms
             << setw(14) << s.backtracks
             << setw(12) << s.nodes
             << (ok ? "✓ Solved" : "✗ No solution") << "\n";
    }

    int n = PUZZLES.size();
    cout << string(50, '=') << "\n";
    cout << "Puzzles   : " << solved << "/" << n << " solved\n";
    cout << "Total time: " << fixed << setprecision(3) << totalMs    << " ms\n";
    cout << "Avg time  : " << fixed << setprecision(3) << totalMs/n  << " ms\n";
    cout << "Avg BT    : " << totalBt / n    << "\n";
    cout << "Avg nodes : " << totalNodes / n << "\n";
    return 0;
}
