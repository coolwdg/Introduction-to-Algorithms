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
        placeShip(board, length); // ���·���ս��
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
        cout << "�ڷŲ��Ϸ��������°ڷ�" << endl;
        cin>>x>>y>>isVertical;
        placeShip(board,x, y, length, isVertical);

    }

       
}
bool attack(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    if (board[row][col] == 'S') {
        board[row][col] = 'X'; // ���Ϊ�ѻ���
        cout << "���У�" << endl;
        return true;
    }
    else if(board[row][col] == 'X'){
        cout << "��λ���ѱ�������" << endl;
        return false;
    }
    else
    {
        board[row][col] = 'O';
        cout << "δ����" << endl;
        return false;
    }
}
bool isGameOver(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 'S') {
                return false; // �ҵ�ս������Ϸδ����
            }
        }
    }
    return true; // û���ҵ�ս������Ϸ����
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
    srand(static_cast<unsigned int>(time(0))); // �����������

    initializeBoard(board1);
    initializeBoard(board2);

    placeShip(board1, 2); // ��������(2��)
    placeShip(board1, 3); // ����Ǳͧ(3��)
    placeShip(board1, 4); // ����ս�н�(4��)
    placeShip(board1, 5); // ���ú���ĸ��(5��)
    cout << "�����η�������(2��)��Ǳͧ(3��)��ս�н�(4��)������ĸ��(5��)�������������֣��ֱ��ʾ��ʼ����Ͱڷŷ�ʽ����1����ֱ����0��ˮƽ��" << endl;
    for (int i = 2; i < 6; i++)
    {   
        cin >> a >> b >> c;
		placeShip(board2, a, b, i, c);
    }
    cout<<"�Ҿ��������"<<endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout <<"." << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "�о��������"<< endl;
    cout << "����enter����ʼ��Ϸ" << endl;
    cin.get();
    cin.get();
    system("cls");
    int currentPlayer = 1;
    while (true)
    {
        int row, col;
       

        bool hit;
        if (currentPlayer == 1) {
            cout << "��Ļغϣ������빥�������꣺" << endl;
            cin >> row >> col;
            hit = attack(board1, row, col);
            printBoard(board1);
            cin.get();
            cin.get();
            system("cls");
        }
      
        else {
            if (lastHitRow != -1 && lastHitCol != -1) {
                // �����һ�ι���������ս������ô����ι���ʱ���ȿ�����Χ�ĸ���
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
                // �����һ�ι���û�л���ս������ô���ѡ��һ��λ�ý��й���
                row = rand() % BOARD_SIZE;
                col = rand() % BOARD_SIZE;
            }
            cout << "���ԵĻغϡ�����ѡ�񹥻�������Ϊ��" << row << ", " << col << endl;
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
            cout << "���Ի��ʤ����" << endl;
            cin.get();
            break;
        }
        if (isGameOver(board1))
        {
            cout << "����ʤ����" << endl;
            cin.get();
            break;
        }

        if (!hit) {
            currentPlayer = 3 - currentPlayer; // �л����
        }

    }
    
	
   


   
    return 0;
}
