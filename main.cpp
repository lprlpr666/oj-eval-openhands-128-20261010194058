#include <bits/stdc++.h>
using namespace std;

bool checkWin(const vector<string>& b, char p) {
    // rows
    for (int i = 0; i < 3; ++i) {
        if (b[i][0] == p && b[i][1] == p && b[i][2] == p) return true;
    }
    // cols
    for (int j = 0; j < 3; ++j) {
        if (b[0][j] == p && b[1][j] == p && b[2][j] == p) return true;
    }
    // diagonals
    if (b[0][0] == p && b[1][1] == p && b[2][2] == p) return true;
    if (b[0][2] == p && b[1][1] == p && b[2][0] == p) return true;
    return false;
}

vector<pair<int,int>> winningCells(const vector<string>& b, char p) {
    vector<pair<int,int>> cells;
    // rows
    for (int i = 0; i < 3; ++i) {
        if (b[i][0] == p && b[i][1] == p && b[i][2] == p) {
            cells.emplace_back(i,0);
            cells.emplace_back(i,1);
            cells.emplace_back(i,2);
            return cells;
        }
    }
    // cols
    for (int j = 0; j < 3; ++j) {
        if (b[0][j] == p && b[1][j] == p && b[2][j] == p) {
            cells.emplace_back(0,j);
            cells.emplace_back(1,j);
            cells.emplace_back(2,j);
            return cells;
        }
    }
    // diag
    if (b[0][0] == p && b[1][1] == p && b[2][2] == p) {
        cells.emplace_back(0,0);
        cells.emplace_back(1,1);
        cells.emplace_back(2,2);
        return cells;
    }
    if (b[0][2] == p && b[1][1] == p && b[2][0] == p) {
        cells.emplace_back(0,2);
        cells.emplace_back(1,1);
        cells.emplace_back(2,0);
        return cells;
    }
    return cells;
}

bool validAfterWin(const vector<string>& board, char winner) {
    int cntX = 0, cntO = 0;
    for (auto &row: board) for (char c: row) {
        if (c=='x') cntX++; else if (c=='o') cntO++; }
    // winner must have just played
    if (winner=='x' && !(cntX == cntO + 1)) return false;
    if (winner=='o' && !(cntX == cntO)) return false;
    // find winning cells
    auto winCells = winningCells(board, winner);
    if (winCells.empty()) return false;
    // try removing each winning cell and see if board becomes non-winning and counts match previous turn
    for (auto [r,c]: winCells) {
        vector<string> b = board;
        b[r][c] = '-';
        if (!checkWin(b, 'x') && !checkWin(b, 'o')) {
            // counts after removal
            int nx = cntX - (winner=='x');
            int no = cntO - (winner=='o');
            if (winner=='x') {
                if (nx == no) return true; // previous turn was o's turn
            } else {
                if (nx == no + 1) return true; // previous turn was x's turn
            }
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> board(3);
    for (int i=0;i<3;i++) {
        if(!(cin>>board[i])) return 0;
        if(board[i].size()!=3){
            cout<<"invalid";return 0;}
    }
    int cntX=0,cntO=0,cntDash=0;
    for (auto &row: board) for(char c: row){
        if(c=='x') cntX++; else if(c=='o') cntO++; else if(c=='-') cntDash++; else {cout<<"invalid";return 0;}
    }
    // basic count validation
    if(!(cntX==cntO || cntX==cntO+1)) {cout<<"invalid";return 0;}
    bool xWin = checkWin(board,'x');
    bool oWin = checkWin(board,'o');
    if (xWin && oWin) {cout<<"invalid";return 0;}
    if (xWin) {
        if (validAfterWin(board,'x')) cout<<"win"; else cout<<"invalid";
        return 0;
    }
    if (oWin) {
        if (validAfterWin(board,'o')) cout<<"lose"; else cout<<"invalid";
        return 0;
    }
    if (cntDash==0) cout<<"tie"; else cout<<"ongoing";
    return 0;
}
