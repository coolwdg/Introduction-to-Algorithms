#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY = '.';

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

bool canPlaceShip(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int length, bool isVertical) {
    if (isVertical) {
        for (int i = 0; i < length; i++) {
            if (row + i >= BOARD_SIZE || board[row + i][col] != EMPTY) {
                return false;
            }
        }
    }
    else {
        for (int i = 0; i < length; i++) {
            if (col + i >= BOARD_SIZE || board[row][col + i] != EMPTY) {
                return false;
            }
        }
    }
    return true;
}

void placeShip(char board[BOARD_SIZE][BOARD_SIZE], int length) {
    bool isVertical = rand() % 2 == 0;
    int row, col;
    if (isVertical) {
        row = rand() % (BOARD_SIZE - length + 1);
        col = rand() % BOARD_SIZE;
    }
    else {
        row = rand() % BOARD_SIZE;
        col = rand() % (BOARD_SIZE - length + 1);
    }

    if (canPlaceShip(board, row, col, length, isVertical)) {
        if (isVertical) {
            for (int i = 0; i < length; i++) {
                board[row + i][col] = 'S';
            }
        }
        else {
            for (int i = 0; i < length; i++) {
                board[row][col + i] = 'S';
            }
        }
    }
    else {
        placeShip(board, length); // 重新放置战舰
    }
}
void placeShip(char board[BOARD_SIZE][BOARD_SIZE], int x,int y,int length,int  isVertical) {
   
    int row=x, col=y;
   

    if (canPlaceShip(board, row, col, length, isVertical)) {
        if (isVertical) {
            for (int i = 0; i < length; i++) {
                board[row + i][col] = 'S';
            }
        }
        else {
            for (int i = 0; i < length; i++) {
                board[row][col + i] = 'S';
            }
        }
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    else {
        cout << "摆放不合法，请重新摆放" << endl;
        cin>>x>>y>>isVertical;
        placeShip(board,x, y, length, isVertical);

    }

       
}
bool attack(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    if (board[row][col] == 'S') {
        board[row][col] = 'X'; // 标记为已击中
        cout << "击中！" << endl;
        return true;
    }
    else if(board[row][col] == 'X'){
        cout << "该位置已被攻击过" << endl;
        return false;
    }
    else
    {
        board[row][col] = 'O';
        cout << "未击中" << endl;
        return false;
    }
}
bool isGameOver(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 'S') {
                return false; // 找到战舰，游戏未结束
            }
        }
    }
    return true; // 没有找到战舰，游戏结束
}
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j]!='S')
            cout << board[i][j] << " ";
            else
            {
                cout << "." << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    char board1[BOARD_SIZE][BOARD_SIZE];
    char board2[BOARD_SIZE][BOARD_SIZE];
    int lastHitRow = -1, lastHitCol = -1;
    int a, b,c;
    srand(static_cast<unsigned int>(time(0))); // 设置随机种子

    initializeBoard(board1);
    initializeBoard(board2);

    placeShip(board1, 2); // 放置驱逐舰(2格)
    placeShip(board1, 3); // 放置潜艇(3格)
    placeShip(board1, 4); // 放置战列舰(4格)
    placeShip(board1, 5); // 放置航空母舰(5格)
    cout << "请依次放置驱逐舰(2格)，潜艇(3格)，战列舰(4格)，航空母舰(5格)。输入三个数字，分别表示起始坐标和摆放方式（（1）垂直，（0）水平）" << endl;
    for (int i = 2; i < 6; i++)
    {   
        cin >> a >> b >> c;
		placeShip(board2, a, b, i, c);
    }
    cout<<"我军部署完毕"<<endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout <<"." << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "敌军部署完毕"<< endl;
    cout << "摁下enter键开始游戏" << endl;
    cin.get();
    cin.get();
    system("cls");
    int currentPlayer = 1;
    while (true)
    {
        int row, col;
       

        bool hit;
        if (currentPlayer == 1) {
            cout << "你的回合，请输入攻击的坐标：" << endl;
            cin >> row >> col;
            hit = attack(board1, row, col);
            printBoard(board1);
            cin.get();
            cin.get();
            system("cls");
        }
      
        else {
            if (lastHitRow != -1 && lastHitCol != -1) {
                // 如果上一次攻击击中了战舰，那么在这次攻击时优先考虑周围的格子
                int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
                int flag = 1;
                for (int i = 0; i < 4; i++) {
                    row = lastHitRow + directions[i][0];
                    col = lastHitCol + directions[i][1];
                    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board2[row][col] !='X' && board2[row][col] != 'O' ) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1)
                {
                    row = rand() % BOARD_SIZE;
                    col = rand() % BOARD_SIZE;
                }
            }
            else {
                // 如果上一次攻击没有击中战舰，那么随机选择一个位置进行攻击
                row = rand() % BOARD_SIZE;
                col = rand() % BOARD_SIZE;
            }
            cout << "电脑的回合。电脑选择攻击的坐标为：" << row << ", " << col << endl;
            hit = attack(board2, row, col);
            if (hit)
            {
                lastHitRow = row;
                lastHitCol = col;
            }
            else
            {
                lastHitRow = -1;
                lastHitCol = -1;
            }
            printBoard(board2);
            cin.get();
            system("cls");
        }
        if (isGameOver(board2))
        {
            cout << "电脑获得胜利！" << endl;
            cin.get();
            break;
        }
        if (isGameOver(board1))
        {
            cout << "你获得胜利！" << endl;
            cin.get();
            break;
        }

        if (!hit) {
            currentPlayer = 3 - currentPlayer; // 切换玩家
        }

    }
    
	
   


   
    return 0;
}
