#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int board[9][9];
int answer[9][9];
void solve(int row, int col);
bool isExist(int row, int col, int num);
void generateSudoku();
void removeNumbers(int numToRemove);


int main() {
    // 生成数独题目
    generateSudoku();

    // 输出数独题目
    cout << "Sudoku Problem:\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    // 等待用户按下任意键
    cout << "Press any key to see the solution...";
    cin.get();

   
    cout << "Sudoku Solution:\n";
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
		   cout<<answer[i][j]<<" ";
	   }
	   cout<<endl;
   }

    return 0;
}

void solve(int row, int col) {
    if (row == 9) {
        return;
    }

    int nextRow = row + (col + 1) / 9;
    int nextCol = (col + 1) % 9;

    if (board[row][col] == 0) {
        vector<int> candidates;
        for (int num = 1; num <= 9; num++) {
            if (!isExist(row, col, num)) {
                candidates.push_back(num);
            }
        }
        // 随机打乱候选数字顺序
        random_shuffle(candidates.begin(), candidates.end());
        // 依次尝试每个候选数字
        for (int num : candidates) {
            board[row][col] = num;
            solve(nextRow, nextCol);
            if (board[8][8] != 0) {
                return;
            }
        }
        // 如果所有候选数字都尝试过仍无法解出数独，回溯
        board[row][col] = 0;
    }
    else {
        solve(nextRow, nextCol);
    }
}

bool isExist(int row, int col, int num) {
    for (int c = 0; c < 9; c++) {
        if (board[row][c] == num) {
            return true;
        }
    }

    for (int r = 0; r < 9; r++) {
        if (board[r][col] == num) {
            return true;
        }
    }

    int rowMin = (row / 3) * 3;
    int colMin = (col / 3) * 3;
    int rowMax = rowMin + 2;
    int colMax = colMin + 2;

    for (int r = rowMin; r <= rowMax; r++) {
        for (int c = colMin; c <= colMax; c++) {
            if (board[r][c] == num) {
                return true;
            }
        }
    }

    return false;
}


void generateSudoku() {
    // 使用当前时间作为种子重新设置随机数生成器
    srand(static_cast<unsigned int>(time(nullptr)));

    // 生成一个完整的数独题目
    solve(0, 0);
    memcpy(answer, board, sizeof(board));
   

    // 随机移除一些数字，生成数独问题
    int numToRemove = rand() % 20 + 40; // 移除40到59个数字
    removeNumbers(numToRemove);
}

void removeNumbers(int numToRemove) {
    while (numToRemove > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (board[row][col] != 0) {
            board[row][col] = 0;
            numToRemove--;
        }
    }
}

