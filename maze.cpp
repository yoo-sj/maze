#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <windows.h>

#define MAX_STACK_SIZE 100  // ������ ũ��
#define MAZE_SIZE 10  // �̷�ũ�� 
typedef struct  StackObjectRec // ���ÿ� ������ ��ġ����  // ����ü�� ���ÿ�����Ʈ ���� StackObject���� �Ѱ��� r��c�� ���� �ٴ´�. �ڽİ��� ����
{
    short r;  // row 
    short c; // col 
}
StackObject;

StackObject  stack[MAX_STACK_SIZE]; // ����(�迭�� 100��)  //StackObject�� ���� stack[100] <- ����ü�� 100���� ����
int  top = -1;  //������ ��ġ // ������ ������� 
StackObject here = { 1,0 }, entry = { 1,0 }; // ������ġ�� �Ա�  // hered�� entry�� r�� 1���ְ� c�� 0�� �ֽ��ϴ�.�� ǥ��

char maze[MAZE_SIZE][MAZE_SIZE] =  // ĳ������ ������ maze[10][10]�� �����ϰ� �Ʒ��� ���� �ʱ�ȭ
{     // �̷� ��(10x10) : 1�� ��, 0�� ��, �Ա� E, �ⱸ X 
 {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
 {'E', '0', '1', '0', '0', '0', '1', '0', '0', 'X'},
 {'1', '0', '1', '0', '1', '0', '1', '0', '1', '1'},
 {'1', '0', '1', '0', '1', '0', '1', '0', '1', '1'},
 {'1', '0', '0', '0', '1', '0', '1', '0', '1', '1'},
 {'1', '1', '1', '1', '1', '0', '1', '0', '1', '1'},
 {'1', '1', '1', '1', '1', '0', '1', '0', '1', '1'},
 {'1', '0', '0', '0', '0', '0', '1', '0', '1', '1'},
 {'1', '0', '1', '1', '1', '0', '0', '0', '1', '1'},
 {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};


int isEmpty()
{
    return (top == -1); // ������ ����ִ��� Ȯ��[���� ���� Ȯ��]
}

int isFull()  // top ���� 99 .������ �� ������. �迭�� 0���� ���ϱ� 99���� �� 100��
{
    return (top == (MAX_STACK_SIZE - 1));  // ������ �� á���� �˻� 
}
void push(StackObject item) // ���ÿ� ������ �߰�
{
    if (isFull())  // ������ Ǯ�̸� �ƹ��͵� �����ʰ�
    {    }
    else stack[++top] = item;  // ���ÿ� ��ġ ���� / ������ ������ top�� 1����(�����߿�)��Ű�� ������Ų���� �������� �߰�
}

StackObject pop() // ���ÿ��� �������� ������
{
    if (isEmpty()) // ������ ��������� �ƹ��͵� ���� �ʰ�
    {    }
    else return stack[top--];  // ���ÿ��� �������� ���´��� top���� -1��Ŵ
}


void pushLoc(int r, int c)
{
    if (r < 0 || c < 0) return;  // r�̳� c�� ���� 0���� ������ �� �Ʒ��� �������� �ʰ� �Լ��� ���� ����
    if (maze[r][c] != '1' && maze[r][c] != '.') // maze[r][c]�� 1�� �ƴϰ�  maze[r][c]�� . �̾ƴ� ��� ������ �����ϸ�
    {
        StackObject tmp;  // �ӽ÷� ���� ����ü�� �ϳ� ����
        tmp.r = r;  // �ӽ� ����ü r�� c�� ���� r,c�� ����
        tmp.c = c;
        push(tmp);  // ���ÿ� �߰�
    }
}

void printMaze(char m[MAZE_SIZE][MAZE_SIZE])// ������ �����ߴ� maze �� m[][]�� �����ؼ�
{
    int r, c;

    for (r = 0; r < MAZE_SIZE; r++)
    {
        for (c = 0; c < MAZE_SIZE; c++)
        {
            if (c == here.c && r == here.r) // 1) c,r�� ���� here.c, here.r�� ��� ������
                printf("m "); // m�� ����ϰ�
            else  // 1)�� �ƴѰ��߿�
            {
                if (m[r][c] == 0) printf("0 "); // 2) m[r][c]�� 0�̸� 0�� ����ϰ�
                else printf("%c ", m[r][c]);  // 2)�� �ƴϸ� m[r][c]�� ������ �״�� ���
            }
        }
        printf("\n"); // ���پ� ���� ���� �ٲ�
    }
    printf("\n\n");   // ��Ʈ������ �� ���� ������ ���
    system("cls");  // ȭ�� �����
}

void main()
{
    int r, c;
    here = entry; //���� ��ġ, �Ա� // entry�� here�� ����
    printMaze(maze);  // �̷����
   

    while (maze[here.r][here.c] != 'X') // ���� ��ġ�� �ⱸ('x')�� �ƴҶ� ���� �ݺ�  // maze[here.r][here.c]�� ���� X�� �ƴϸ� ��� ����
    {
        printMaze(maze); //  maze�� ���
        r = here.r; //���� ��ġ ���� // r�� c�� ����  here.r�� here.c�� ����
        c = here.c;
        maze[r][c] = '.';  //���� ��ġ �湮 ǥ�� 
        pushLoc(r - 1, c); //�� // pushLoc(r-1,c) ȣ��
        pushLoc(r + 1, c); //��
        pushLoc(r, c - 1); //��
        pushLoc(r, c + 1); //��

        if (isEmpty())  // ������ ���������
        {
            printf("����\n"); // ���
            return;
        }
        else   // �ƴϸ�
            here = pop();  // ���ÿ��� �ϳ� ���� // ���ÿ��� �ϳ� �׸��� ������ here�� ����
        printMaze(maze); // �̷� ���
        
            }
    printf("����\n");  // ���� ���
}