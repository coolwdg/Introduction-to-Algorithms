#include <stdio.h>
#include <malloc.h>
#include <chrono>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace std::chrono;

int a[9][9] = { 0 };
int board[9][9] = { 0 };
int answer[9][9];
void solve(int row, int col);
bool isExist(int row, int col, int num);
void generateSudoku();
void removeNumbers(int numToRemove);

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
typedef struct DLX_node//节点定义
{
    struct DLX_node* up;
    struct DLX_node* down;
    struct DLX_node* left;
    struct DLX_node* right;
    int is_head;
    int index;
}d_node, * pd_node;
int row = 0;
struct node_heap
{
    int cul_value;
    int position_index;
};
pd_node head;
pd_node* p_head;
pd_node stack[81];
int stack_index = 0;
struct node_heap mutual_index[324];
int current_heap_number = 323;
int available_column = 323;
int position_index[324];
#define shift_base 0x80000000

void insert_row(int i, int j, int value)//进行行插入的函数，用来组成网格
{
    pd_node temp_node_one, temp_node_two, temp_node_three, temp_node_four;
    int current_index;
    current_index = 81 * i + 9 * j + value - 1;
    temp_node_one = (pd_node)malloc(sizeof(struct DLX_node));
    temp_node_two = (pd_node)malloc(sizeof(struct DLX_node));
    temp_node_three = (pd_node)malloc(sizeof(struct DLX_node));
    temp_node_four = (pd_node)malloc(sizeof(struct DLX_node));
    temp_node_one->right = temp_node_two;
    temp_node_two->right = temp_node_three;
    temp_node_three->right = temp_node_four;
    temp_node_four->right = temp_node_one;
    temp_node_one->left = temp_node_four;
    temp_node_two->left = temp_node_one;
    temp_node_three->left = temp_node_two;
    temp_node_four->left = temp_node_three;
    temp_node_one->is_head = 0;
    temp_node_two->is_head = 0;
    temp_node_three->is_head = 0;
    temp_node_four->is_head = 0;
    temp_node_one->down = p_head[i * 9 + value - 1];
    temp_node_one->up = temp_node_one->down->up;
    temp_node_one->up->down = temp_node_one;
    temp_node_one->down->up = temp_node_one;
    mutual_index[i * 9 + value - 1].cul_value += 1;
    temp_node_two->down = p_head[j * 9 + value - 1 + 81];
    temp_node_two->up = temp_node_two->down->up;
    temp_node_two->up->down = temp_node_two;
    temp_node_two->down->up = temp_node_two;
    mutual_index[j * 9 + value + 81 - 1].cul_value += 1;
    temp_node_three->down = p_head[162 + ((i / 3) * 3 + j / 3) * 9 + value - 1];
    temp_node_three->up = temp_node_three->down->up;
    temp_node_three->up->down = temp_node_three;
    temp_node_three->down->up = temp_node_three;
    mutual_index[162 + ((i / 3) * 3 + j / 3) * 9 + value - 1].cul_value += 1;
    temp_node_four->down = p_head[243 + i * 9 + j];
    temp_node_four->up = temp_node_four->down->up;
    temp_node_four->up->down = temp_node_four;
    temp_node_four->down->up = temp_node_four;
    mutual_index[243 + i * 9 + j].cul_value += 1;
    temp_node_one->index = temp_node_two->index = temp_node_three->index = temp_node_four->index = current_index;
    row++;
}
void swap_heap(int index_one, int index_two)//交换在堆中的两个元素的值，及相关数据索引
{
    int intermidate_one, intermidate_two;
    intermidate_one = mutual_index[index_one].cul_value;
    intermidate_two = mutual_index[index_one].position_index;
    mutual_index[index_one].cul_value = mutual_index[index_two].cul_value;
    mutual_index[index_one].position_index = mutual_index[index_two].position_index;
    mutual_index[index_two].cul_value = intermidate_one;
    mutual_index[index_two].position_index = intermidate_two;
    position_index[mutual_index[index_two].position_index] = index_two;
    position_index[mutual_index[index_one].position_index] = index_one;

}
void heap_initial()//初始化堆
{
    int k, i = 0;
    int current_min;
    for (i = (current_heap_number - 1) / 2; i >= 0; i--)
    {
        k = i;
        while (2 * k + 1 <= current_heap_number)
        {
            current_min = mutual_index[k].cul_value;
            current_min = current_min < mutual_index[2 * k + 1].cul_value ? current_min : mutual_index[2 * k + 1].cul_value;
            if (2 * k + 2 <= current_heap_number)
            {
                current_min = current_min < mutual_index[2 * k + 2].cul_value ? current_min : mutual_index[2 * k + 2].cul_value;
            }
            if (current_min == mutual_index[k].cul_value)
            {
                break;
            }
            else
            {
                if (current_min == mutual_index[2 * k + 1].cul_value)
                {
                    swap_heap(k, 2 * k + 1);
                    k = 2 * k + 1;
                }
                else
                {
                    swap_heap(k, 2 * k + 2);
                    k = 2 * k + 2;
                }
            }
        }
    }
}
void creat_dlx_sudoku(int input_matrix[9][9])//利用矩阵来建立十字网格
{
    int i, j, k;
    unsigned int row_position[9];
    unsigned int column_position[9];
    unsigned int small_position[9];
    unsigned int optional_value;
    pd_node temp_swap_node;
    for (i = 0; i < 324; i++)
    {
        mutual_index[i].cul_value = 0;
        mutual_index[i].position_index = i;
        position_index[i] = i;
    }
    for (i = 0; i < 9; i++)
    {
        row_position[i] = 0;
        column_position[i] = 0;
        small_position[i] = 0;
    }
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (input_matrix[i][j] != 0)
            {
                row_position[i] = row_position[i] | (shift_base >> (input_matrix[i][j] - 1));
                column_position[j] = column_position[j] | (shift_base >> (input_matrix[i][j] - 1));
                small_position[(i / 3) * 3 + j / 3] = small_position[(i / 3) * 3 + j / 3] | (shift_base >> (input_matrix[i][j] - 1));
            }
        }
    }
    p_head = (pd_node*)malloc(324 * sizeof(struct DLX_node*));
    for (i = 0; i < 324; i++)
    {
        p_head[i] = (pd_node)malloc(sizeof(struct DLX_node));
        p_head[i]->up = p_head[i];
        p_head[i]->down = p_head[i];
        p_head[i]->is_head = 1;
    }
    for (i = 0; i < 324; i++)
    {
        p_head[i]->right = p_head[(i + 1) % 324];
        p_head[i]->left = p_head[(i + 323) % 324];
    }
    temp_swap_node = (pd_node)malloc(sizeof(struct DLX_node));
    temp_swap_node->down = temp_swap_node->up = temp_swap_node;
    temp_swap_node->is_head = 1;
    temp_swap_node->left = p_head[323];
    temp_swap_node->right = p_head[0];
    p_head[323]->right = temp_swap_node;
    p_head[0]->left = temp_swap_node;
    head = temp_swap_node;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (input_matrix[i][j] != 0)
            {
                insert_row(i, j, input_matrix[i][j]);
            }
            else
            {
                optional_value = row_position[i] | column_position[j] | small_position[(i / 3) * 3 + j / 3];
                optional_value = ~optional_value;
                for (k = 0; k < 9; k++)
                {
                    if (((shift_base >> k) & optional_value))
                    {
                        insert_row(i, j, k + 1);
                    }
                    else
                    {
                        //do nothing
                    }
                }
            }
        }
    }
    heap_initial();
}

void delete_minimal()//删除堆中最小的元素
{
    int k;
    int current_min;
    if (current_heap_number != 0)
    {
        swap_heap(0, current_heap_number);//交换最高元素与最低元素
        current_heap_number--;//然后将堆的大小进行缩减
        k = 0;
        while (2 * k + 1 <= current_heap_number)//然后，下面便是一些维护性的工作，用来维护最小堆
        {
            current_min = mutual_index[k].cul_value;
            current_min = current_min < mutual_index[2 * k + 1].cul_value ? current_min : mutual_index[2 * k + 1].cul_value;
            if (2 * k + 2 <= current_heap_number)
            {
                current_min = current_min < mutual_index[2 * k + 2].cul_value ? current_min : mutual_index[2 * k + 2].cul_value;
            }
            if (current_min == mutual_index[k].cul_value)
            {
                return;
            }
            else
            {
                if (current_min == mutual_index[2 * k + 1].cul_value)
                {
                    swap_heap(k, 2 * k + 1);
                    k = 2 * k + 1;
                }
                else
                {
                    swap_heap(k, 2 * k + 2);
                    k = 2 * k + 2;
                }
            }
        }
    }
    else//如果只剩下一个元素，那就不需要进行交换，直接将堆元素的个数降低一
    {
        current_heap_number = -1;
    }

}
void heap_renew(int target_position, int new_value)//对于第target_position列，进行度数更新
{
    int heap_target_position, k, current_min;
    heap_target_position = position_index[target_position];//这个是这一列在堆中所在的位置
    k = heap_target_position;
    if (new_value < mutual_index[k].cul_value)//如果值是减少的，就直接进行赋值，然后维护堆的性质
    {
        mutual_index[k].cul_value = new_value;
        while (k > 0 && (mutual_index[(k - 1) / 2].cul_value > mutual_index[k].cul_value))//维护堆
        {
            swap_heap((k - 1) / 2, k);
            k = (k - 1) / 2;
        }
        if (new_value == 0)//如果是赋值为0，则从堆中进行删除，因为我们每次操纵一个元素，所以最多会有一个元素为0，所以肯定是最小值。
        {
            delete_minimal();
        }
    }
    else//对于值增大的情况
    {
        mutual_index[k].cul_value = new_value;
        if (new_value == 1)//如果新的值是1，则把这个元素重新加入堆中
        {
            current_heap_number++;//扩大堆的范围，我们可以证明重新加入堆中的元素一定是排在堆的末尾，当然条件是删除与插入的顺序是对应相反的
            while (k > 0 && (mutual_index[(k - 1) / 2].cul_value > mutual_index[k].cul_value))//由于新的值是1，所以不可能比上一个数大
            {
                swap_heap((k - 1) / 2, k);
                k = (k - 1) / 2;
            }
        }
        else//如果不是1，说明已经在堆中，所以不需要扩大堆的范围，直接赋值之后进行维护堆结构就行
        {
            while (2 * k + 1 <= current_heap_number)
            {
                current_min = mutual_index[k].cul_value;
                current_min = current_min < mutual_index[2 * k + 1].cul_value ? current_min : mutual_index[2 * k + 1].cul_value;
                if (2 * k + 2 <= current_heap_number)
                {
                    current_min = current_min < mutual_index[2 * k + 2].cul_value ? current_min : mutual_index[2 * k + 2].cul_value;
                }
                if (current_min == mutual_index[k].cul_value)
                {
                    break;
                }
                else
                {
                    if (current_min == mutual_index[2 * k + 1].cul_value)
                    {
                        swap_heap(k, 2 * k + 1);
                        k = 2 * k + 1;
                    }
                    else
                    {
                        swap_heap(k, 2 * k + 2);
                        k = 2 * k + 2;
                    }
                }
            }
        }
    }
}
void node_heap_decrease(pd_node current_node)//对于一个点进行她所在的行的删除，因为一行中一定有四个元素，所以有四列，我们对这四列的度数都进行减少1
{
    int i, j, k;
    k = current_node->index % 9;
    j = (current_node->index / 9) % 9;
    i = (current_node->index / 81) % 9;
    heap_renew(i * 9 + k, mutual_index[position_index[i * 9 + k]].cul_value - 1);
    heap_renew(81 + j * 9 + k, mutual_index[position_index[81 + j * 9 + k]].cul_value - 1);
    heap_renew(162 + ((i / 3) * 3 + j / 3) * 9 + k, mutual_index[position_index[162 + ((i / 3) * 3 + j / 3) * 9 + k]].cul_value - 1);
    heap_renew(243 + i * 9 + j, mutual_index[position_index[243 + i * 9 + j]].cul_value - 1);
}
void node_heap_increase(pd_node current_node)//增加与减少的顺序是刚好相反的
{
    int i, j, k;
    k = current_node->index % 9;
    j = (current_node->index / 9) % 9;
    i = (current_node->index / 81) % 9;
    heap_renew(243 + i * 9 + j, mutual_index[position_index[243 + i * 9 + j]].cul_value + 1);
    heap_renew(162 + ((i / 3) * 3 + j / 3) * 9 + k, mutual_index[position_index[162 + ((i / 3) * 3 + j / 3) * 9 + k]].cul_value + 1);
    heap_renew(81 + j * 9 + k, mutual_index[position_index[81 + j * 9 + k]].cul_value + 1);
    heap_renew(i * 9 + k, mutual_index[position_index[i * 9 + k]].cul_value + 1);
}
void in_stack(pd_node target_to_stack)
{
    pd_node temp_node_one, temp_node_two, temp_node_three, temp_node_four;
    temp_node_one = target_to_stack->left;//在删除的时候，从当前点的左边开始
    while (temp_node_one != target_to_stack)//从左进行遍历
    {
        temp_node_three = temp_node_one->down;//每遇到一个节点，就往下开始遍历
        while (temp_node_three != temp_node_one)
        {
            if (temp_node_three->is_head != 1)//如果遇到的点不是头部节点，则当前行摘除
            {
                temp_node_four = temp_node_three->right;//在删除行的过程中，我们采取的是从右往左删
                while (temp_node_four != temp_node_three)//从右往左的每一个节点，将他的上下关系摘除，注意第一个点是不能删除的，因为我们需要将他们连接起来。
                {
                    temp_node_four->up->down = temp_node_four->down;
                    temp_node_four->down->up = temp_node_four->up;
                    temp_node_four = temp_node_four->right;
                }
                node_heap_decrease(temp_node_three);//对这一行所占据的三列进行降低度数操作，每一个降低一度
            }
            else//对于是头节点的情况，我们将头节点与两边摘下来，而且对于头节点，我们不需要进行度数操作
            {
                temp_node_three->left->right = temp_node_three->right;
                temp_node_three->right->left = temp_node_three->left;
            }
            temp_node_three = temp_node_three->down;//继续往下遍历
        }
        temp_node_one = temp_node_one->left;
    }
    temp_node_three = temp_node_one->down;//然后对与当前列相交的行的进行删除
    while (temp_node_three != temp_node_one)
    {
        if (temp_node_three->is_head != 1)
        {
            temp_node_four = temp_node_three->right;
            while (temp_node_four != temp_node_three)
            {
                temp_node_four->up->down = temp_node_four->down;
                temp_node_four->down->up = temp_node_four->up;
                temp_node_four = temp_node_four->right;
            }
            node_heap_decrease(temp_node_three);
        }
        else
        {
            temp_node_three->left->right = temp_node_three->right;
            temp_node_three->right->left = temp_node_three->left;
        }
        temp_node_three = temp_node_three->down;
    }
    node_heap_decrease(target_to_stack);//最后对当前行进行删除
    stack[stack_index++] = target_to_stack;//然后才是入栈
    available_column -= 4;
}
void out_stack()//出栈的顺序与入栈的顺序是刚好对称相反的
{
    pd_node temp_node_one, temp_node_two, temp_node_three, temp_node_four;
    pd_node target_node;
    available_column += 4;
    temp_node_one = target_node = stack[stack_index - 1];
    temp_node_three = temp_node_one->up;
    node_heap_increase(temp_node_one);
    while (temp_node_three != temp_node_one)//先考虑当前列
    {
        if (temp_node_three->is_head == 1)
        {
            temp_node_three->right->left = temp_node_three;
            temp_node_three->left->right = temp_node_three;
        }
        else
        {
            temp_node_four = temp_node_three->left;
            while (temp_node_four != temp_node_three)
            {
                temp_node_four->up->down = temp_node_four;
                temp_node_four->down->up = temp_node_four;
                temp_node_four = temp_node_four->left;
            }
            node_heap_increase(temp_node_three);
        }
        temp_node_three = temp_node_three->up;
    }
    temp_node_one = target_node->right;
    while (temp_node_one != target_node)
    {
        temp_node_three = temp_node_one->up;
        while (temp_node_three != temp_node_one)
        {
            if (temp_node_three->is_head == 1)
            {
                temp_node_three->right->left = temp_node_three;
                temp_node_three->left->right = temp_node_three;
            }
            else
            {
                temp_node_four = temp_node_three->left;
                while (temp_node_four != temp_node_three)
                {
                    temp_node_four->up->down = temp_node_four;
                    temp_node_four->down->up = temp_node_four;
                    temp_node_four = temp_node_four->left;
                }
                node_heap_increase(temp_node_three);
            }
            temp_node_three = temp_node_three->up;
        }
        temp_node_one = temp_node_one->right;
    }
    stack_index--;
}
void print_result()//打印出结果
{
    int out[9][9] = { 0 };
    int i, j, k, current_index;
    int m, n;
    for (m = 0; m < stack_index; m++)
    {
        current_index = stack[m]->index;
        k = current_index % 9;
        current_index /= 9;
        j = current_index % 9;
        current_index /= 9;
        i = current_index;
        out[i][j] = k + 1;
    }
    printf("***********************\n");
    for (m = 0; m < 9; m++)
    {
        for (n = 0; n < 9; n++)
        {
            printf("%d ", out[m][n] | a[m][n]);
        }
        printf("\n");
    }
}
int find_next()//用来找下一个可以入栈的元素，如果无法入栈或者已经找到了解，则返回并进行回溯操作
{
    int target_position;
    pd_node temp_node_one;
    if (available_column == current_heap_number)
    {
        if (available_column == -1)
        {
            return 2;
        }
        else
        {
            target_position = mutual_index[0].position_index;
            temp_node_one = p_head[target_position];
            temp_node_one = temp_node_one->down;
            in_stack(temp_node_one);
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
void seek_sudoku()
{
    int find_result = 0;
    pd_node temp_node_one;
    while (1)
    {
        find_result = find_next();
        if (!find_result)//如果无法入栈且目前没有找到解，则出栈
        {
            temp_node_one = stack[stack_index - 1];
            out_stack();
            temp_node_one = temp_node_one->down;
            while ((temp_node_one->is_head))//如果当前元素是当前列头节点，则递归出栈
            {
                if (stack_index == 0)//如果栈空，则所有的搜索空间已经搜索完全 返回
                {
                    return;
                }
                else
                {
                    temp_node_one = stack[stack_index - 1];
                    out_stack();
                    temp_node_one = temp_node_one->down;
                }
            }
            in_stack(temp_node_one);//将所选元素入栈
        }
        else
        {
            if (find_result / 2)//如果已经找到结果，则返回，事实上我们可以更改这个逻辑来应对有多个解的情况，并把它全部打印
            {
                return;
            }
        }
    }
}
int main()
{
    int x[100];
    int y[100];
    for (int i = 0; i < 100; i++)
    {
    
        generateSudoku();
        /*for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j] << " ";
                a[i][j] = board[i][j];
            }
            cout << endl;
        }*/

        auto start = high_resolution_clock::now();
        creat_dlx_sudoku(a);
        seek_sudoku();
        auto stop = high_resolution_clock::now();
        //print_result();
        auto duration = duration_cast<microseconds>(stop - start);
       // printf("%d mscond passed in dancing links\n", duration.count());
        x[i] = duration.count();
        start = high_resolution_clock::now();
        solve(0, 0);
        stop = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop - start);

        //printf("%d mscond passed in our method\n", duration1.count());
        y[i] = duration1.count();

    }
    int maxX = *std::max_element(x, x + 100);
    int maxY = *std::max_element(y, y + 100);
    int minX = *std::min_element(x, x + 100);
    int minY = *std::min_element(y, y + 100);

    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(800, 600), "Line Chart");

    // 设置坐标轴
    int xAxisLength = 700; // x 轴长度
    int yAxisLength = 400; // y 轴长度
    sf::Vertex xAxis[] =
    {
        sf::Vertex(sf::Vector2f(100, 500)), // 起点
        sf::Vertex(sf::Vector2f(100 + xAxisLength, 500))  // 终点
    };
    sf::Vertex yAxis[] =
    {
        sf::Vertex(sf::Vector2f(100, 500)), // 起点
        sf::Vertex(sf::Vector2f(100, 500 - std::max(maxY, 0)))   // 终点
    };

    // 创建折线图
    sf::VertexArray line(sf::LinesStrip, 100);
    for (int i = 0; i < 100; ++i)
    {
        float xPos = 100 + xAxisLength * (i / 100.0f); // 计算 x 坐标
        float yPos = 500 - yAxisLength * ((x[i] - minY) / static_cast<float>(maxY - minY)); // 计算 y 坐标
        line[i].position = sf::Vector2f(xPos, yPos);
        line[i].color = sf::Color::Red; // 设置颜色为红色
    }

    // 创建另一条折线图
    sf::VertexArray line2(sf::LinesStrip, 100);
    for (int i = 0; i < 100; ++i)
    {
        float xPos = 100 + xAxisLength * (i / 100.0f); // 计算 x 坐标
        float yPos = 500 - yAxisLength * ((y[i] - minY) / static_cast<float>(maxY - minY)); // 计算 y 坐标
        line2[i].position = sf::Vector2f(xPos, yPos);
        line2[i].color = sf::Color::Blue; // 设置颜色为蓝色
    }

    // 循环绘制
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // 绘制坐标轴
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);

        // 绘制折线图
        window.draw(line);
        window.draw(line2);

        window.display();
    }

}