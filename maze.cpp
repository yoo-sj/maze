#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <windows.h>

#define MAX_STACK_SIZE 100  // 스택의 크기
#define MAZE_SIZE 10  // 미로크기 
typedef struct  StackObjectRec // 스택에 저장할 위치정보  // 구조체로 스택오브젝트 정의 StackObject변수 한개당 r과c가 따라 붙는다. 자식같은 개념
{
    short r;  // row 
    short c; // col 
}
StackObject;

StackObject  stack[MAX_STACK_SIZE]; // 스택(배열로 100개)  //StackObject형 변수 stack[100] <- 구조체가 100개가 생성
int  top = -1;  //스택의 위치 // 스택이 비어있음 
StackObject here = { 1,0 }, entry = { 1,0 }; // 현재위치와 입구  // hered와 entry의 r에 1을넣고 c에 0을 넣습니다.을 표시

char maze[MAZE_SIZE][MAZE_SIZE] =  // 캐릭터형 변수를 maze[10][10]을 선언하고 아래와 같이 초기화
{     // 미로 맵(10x10) : 1은 벽, 0은 길, 입구 E, 출구 X 
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
    return (top == -1); // 스택이 비어있는지 확인[여유 공간 확인]
}

int isFull()  // top 값이 99 .스택이 꽉 차있음. 배열은 0부터 세니까 99까지 딱 100개
{
    return (top == (MAX_STACK_SIZE - 1));  // 스택이 꽉 찼는지 검사 
}
void push(StackObject item) // 스택에 아이템 추가
{
    if (isFull())  // 스택이 풀이면 아무것도 하지않고
    {    }
    else stack[++top] = item;  // 스택에 위치 저장 / 공간이 있으면 top을 1증가(순서중요)시키고 증가시킨곳에 아이템을 추가
}

StackObject pop() // 스택에서 아이템을 빼오기
{
    if (isEmpty()) // 스택이 비어있으면 아무것도 하지 않고
    {    }
    else return stack[top--];  // 스택에서 아이템을 빼온다음 top값을 -1시킴
}


void pushLoc(int r, int c)
{
    if (r < 0 || c < 0) return;  // r이나 c의 값이 0보다 작으면 이 아래를 실행하지 않고 함수를 빠져 나감
    if (maze[r][c] != '1' && maze[r][c] != '.') // maze[r][c]가 1이 아니고  maze[r][c]가 . 이아닌 모든 조건을 만족하면
    {
        StackObject tmp;  // 임시로 위의 구조체를 하나 선언
        tmp.r = r;  // 임시 구조체 r과 c에 각각 r,c를 대입
        tmp.c = c;
        push(tmp);  // 스택에 추가
    }
}

void printMaze(char m[MAZE_SIZE][MAZE_SIZE])// 위에서 선언했던 maze 를 m[][]에 전달해서
{
    int r, c;

    for (r = 0; r < MAZE_SIZE; r++)
    {
        for (c = 0; c < MAZE_SIZE; c++)
        {
            if (c == here.c && r == here.r) // 1) c,r이 각각 here.c, here.r과 모두 같으면
                printf("m "); // m을 기록하고
            else  // 1)이 아닌것중에
            {
                if (m[r][c] == 0) printf("0 "); // 2) m[r][c]가 0이면 0을 기록하고
                else printf("%c ", m[r][c]);  // 2)도 아니면 m[r][c]의 내용을 그대로 기록
            }
        }
        printf("\n"); // 한줄씩 쓰고 줄을 바꿈
    }
    printf("\n\n");   // 매트릭스를 다 쓰고 두줄을 띄움
    system("cls");  // 화면 지우기
}

void main()
{
    int r, c;
    here = entry; //시작 위치, 입구 // entry를 here에 대입
    printMaze(maze);  // 미로출력
   

    while (maze[here.r][here.c] != 'X') // 현재 위치가 출구('x')가 아닐때 까지 반복  // maze[here.r][here.c]의 값이 X가 아니면 계속 실행
    {
        printMaze(maze); //  maze를 출력
        r = here.r; //현재 위치 저장 // r과 c에 각각  here.r과 here.c를 대입
        c = here.c;
        maze[r][c] = '.';  //현재 위치 방문 표시 
        pushLoc(r - 1, c); //상 // pushLoc(r-1,c) 호출
        pushLoc(r + 1, c); //하
        pushLoc(r, c - 1); //좌
        pushLoc(r, c + 1); //우

        if (isEmpty())  // 스택이 비어있으면
        {
            printf("실패\n"); // 출력
            return;
        }
        else   // 아니면
            here = pop();  // 스택에서 하나 꺼냄 // 스택에서 하나 항목을 가져와 here에 대입
        printMaze(maze); // 미로 출력
        
            }
    printf("성공\n");  // 성공 출력
}