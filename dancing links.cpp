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
        // ������Һ�ѡ����˳��
        random_shuffle(candidates.begin(), candidates.end());
        // ���γ���ÿ����ѡ����
        for (int num : candidates) {
            board[row][col] = num;
            solve(nextRow, nextCol);
            if (board[8][8] != 0) {
                return;
            }
        }
        // ������к�ѡ���ֶ����Թ����޷��������������
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
    // ʹ�õ�ǰʱ����Ϊ�����������������������
    srand(static_cast<unsigned int>(time(nullptr)));

    // ����һ��������������Ŀ
    solve(0, 0);
    memcpy(answer, board, sizeof(board));


    // ����Ƴ�һЩ���֣�������������
    int numToRemove = rand() % 20 + 40; // �Ƴ�40��59������
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
typedef struct DLX_node//�ڵ㶨��
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

void insert_row(int i, int j, int value)//�����в���ĺ����������������
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
void swap_heap(int index_one, int index_two)//�����ڶ��е�����Ԫ�ص�ֵ���������������
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
void heap_initial()//��ʼ����
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
void creat_dlx_sudoku(int input_matrix[9][9])//���þ���������ʮ������
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

void delete_minimal()//ɾ��������С��Ԫ��
{
    int k;
    int current_min;
    if (current_heap_number != 0)
    {
        swap_heap(0, current_heap_number);//�������Ԫ�������Ԫ��
        current_heap_number--;//Ȼ�󽫶ѵĴ�С��������
        k = 0;
        while (2 * k + 1 <= current_heap_number)//Ȼ���������һЩά���ԵĹ���������ά����С��
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
    else//���ֻʣ��һ��Ԫ�أ��ǾͲ���Ҫ���н�����ֱ�ӽ���Ԫ�صĸ�������һ
    {
        current_heap_number = -1;
    }

}
void heap_renew(int target_position, int new_value)//���ڵ�target_position�У����ж�������
{
    int heap_target_position, k, current_min;
    heap_target_position = position_index[target_position];//�������һ���ڶ������ڵ�λ��
    k = heap_target_position;
    if (new_value < mutual_index[k].cul_value)//���ֵ�Ǽ��ٵģ���ֱ�ӽ��и�ֵ��Ȼ��ά���ѵ�����
    {
        mutual_index[k].cul_value = new_value;
        while (k > 0 && (mutual_index[(k - 1) / 2].cul_value > mutual_index[k].cul_value))//ά����
        {
            swap_heap((k - 1) / 2, k);
            k = (k - 1) / 2;
        }
        if (new_value == 0)//����Ǹ�ֵΪ0����Ӷ��н���ɾ������Ϊ����ÿ�β���һ��Ԫ�أ�����������һ��Ԫ��Ϊ0�����Կ϶�����Сֵ��
        {
            delete_minimal();
        }
    }
    else//����ֵ��������
    {
        mutual_index[k].cul_value = new_value;
        if (new_value == 1)//����µ�ֵ��1��������Ԫ�����¼������
        {
            current_heap_number++;//����ѵķ�Χ�����ǿ���֤�����¼�����е�Ԫ��һ�������ڶѵ�ĩβ����Ȼ������ɾ��������˳���Ƕ�Ӧ�෴��
            while (k > 0 && (mutual_index[(k - 1) / 2].cul_value > mutual_index[k].cul_value))//�����µ�ֵ��1�����Բ����ܱ���һ������
            {
                swap_heap((k - 1) / 2, k);
                k = (k - 1) / 2;
            }
        }
        else//�������1��˵���Ѿ��ڶ��У����Բ���Ҫ����ѵķ�Χ��ֱ�Ӹ�ֵ֮�����ά���ѽṹ����
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
void node_heap_decrease(pd_node current_node)//����һ������������ڵ��е�ɾ������Ϊһ����һ�����ĸ�Ԫ�أ����������У����Ƕ������еĶ��������м���1
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
void node_heap_increase(pd_node current_node)//��������ٵ�˳���Ǹպ��෴��
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
    temp_node_one = target_to_stack->left;//��ɾ����ʱ�򣬴ӵ�ǰ�����߿�ʼ
    while (temp_node_one != target_to_stack)//������б���
    {
        temp_node_three = temp_node_one->down;//ÿ����һ���ڵ㣬�����¿�ʼ����
        while (temp_node_three != temp_node_one)
        {
            if (temp_node_three->is_head != 1)//��������ĵ㲻��ͷ���ڵ㣬��ǰ��ժ��
            {
                temp_node_four = temp_node_three->right;//��ɾ���еĹ����У����ǲ�ȡ���Ǵ�������ɾ
                while (temp_node_four != temp_node_three)//���������ÿһ���ڵ㣬���������¹�ϵժ����ע���һ�����ǲ���ɾ���ģ���Ϊ������Ҫ����������������
                {
                    temp_node_four->up->down = temp_node_four->down;
                    temp_node_four->down->up = temp_node_four->up;
                    temp_node_four = temp_node_four->right;
                }
                node_heap_decrease(temp_node_three);//����һ����ռ�ݵ����н��н��Ͷ���������ÿһ������һ��
            }
            else//������ͷ�ڵ����������ǽ�ͷ�ڵ�������ժ���������Ҷ���ͷ�ڵ㣬���ǲ���Ҫ���ж�������
            {
                temp_node_three->left->right = temp_node_three->right;
                temp_node_three->right->left = temp_node_three->left;
            }
            temp_node_three = temp_node_three->down;//�������±���
        }
        temp_node_one = temp_node_one->left;
    }
    temp_node_three = temp_node_one->down;//Ȼ����뵱ǰ���ཻ���еĽ���ɾ��
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
    node_heap_decrease(target_to_stack);//���Ե�ǰ�н���ɾ��
    stack[stack_index++] = target_to_stack;//Ȼ�������ջ
    available_column -= 4;
}
void out_stack()//��ջ��˳������ջ��˳���ǸպöԳ��෴��
{
    pd_node temp_node_one, temp_node_two, temp_node_three, temp_node_four;
    pd_node target_node;
    available_column += 4;
    temp_node_one = target_node = stack[stack_index - 1];
    temp_node_three = temp_node_one->up;
    node_heap_increase(temp_node_one);
    while (temp_node_three != temp_node_one)//�ȿ��ǵ�ǰ��
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
void print_result()//��ӡ�����
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
int find_next()//��������һ��������ջ��Ԫ�أ�����޷���ջ�����Ѿ��ҵ��˽⣬�򷵻ز����л��ݲ���
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
        if (!find_result)//����޷���ջ��Ŀǰû���ҵ��⣬���ջ
        {
            temp_node_one = stack[stack_index - 1];
            out_stack();
            temp_node_one = temp_node_one->down;
            while ((temp_node_one->is_head))//�����ǰԪ���ǵ�ǰ��ͷ�ڵ㣬��ݹ��ջ
            {
                if (stack_index == 0)//���ջ�գ������е������ռ��Ѿ�������ȫ ����
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
            in_stack(temp_node_one);//����ѡԪ����ջ
        }
        else
        {
            if (find_result / 2)//����Ѿ��ҵ�������򷵻أ���ʵ�����ǿ��Ը�������߼���Ӧ���ж����������������ȫ����ӡ
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

    // ��������
    sf::RenderWindow window(sf::VideoMode(800, 600), "Line Chart");

    // ����������
    int xAxisLength = 700; // x �᳤��
    int yAxisLength = 400; // y �᳤��
    sf::Vertex xAxis[] =
    {
        sf::Vertex(sf::Vector2f(100, 500)), // ���
        sf::Vertex(sf::Vector2f(100 + xAxisLength, 500))  // �յ�
    };
    sf::Vertex yAxis[] =
    {
        sf::Vertex(sf::Vector2f(100, 500)), // ���
        sf::Vertex(sf::Vector2f(100, 500 - std::max(maxY, 0)))   // �յ�
    };

    // ��������ͼ
    sf::VertexArray line(sf::LinesStrip, 100);
    for (int i = 0; i < 100; ++i)
    {
        float xPos = 100 + xAxisLength * (i / 100.0f); // ���� x ����
        float yPos = 500 - yAxisLength * ((x[i] - minY) / static_cast<float>(maxY - minY)); // ���� y ����
        line[i].position = sf::Vector2f(xPos, yPos);
        line[i].color = sf::Color::Red; // ������ɫΪ��ɫ
    }

    // ������һ������ͼ
    sf::VertexArray line2(sf::LinesStrip, 100);
    for (int i = 0; i < 100; ++i)
    {
        float xPos = 100 + xAxisLength * (i / 100.0f); // ���� x ����
        float yPos = 500 - yAxisLength * ((y[i] - minY) / static_cast<float>(maxY - minY)); // ���� y ����
        line2[i].position = sf::Vector2f(xPos, yPos);
        line2[i].color = sf::Color::Blue; // ������ɫΪ��ɫ
    }

    // ѭ������
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // ����������
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);

        // ��������ͼ
        window.draw(line);
        window.draw(line2);

        window.display();
    }

}