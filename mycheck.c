#include <stdio.h>
#include <stdlib.h>
#define N 16

int chessboard[N][N]={0};
int whoseturn=0;

void PrintChessBoard();
void InitGame();
void PlayChess();
int Judge(int,int,int);
void PlayChess();

int main()
{
    InitGame();
    while(1)
    {
        whoseturn++;
        PlayChess();
    }
    return 0;
}

void PrintChessBoard()
{
    int i;
    int j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(i==0)
                printf("%3d",j);
            else if(j==0)
                printf("%3d",i);
            else if(chessboard[i][j]==1)
                printf("  X");
            else if(chessboard[i][j]==2)
                printf("  O");
            else
                printf("  *");
        }
        printf("\n");
    }
}

void InitGame()
{
    char c;
    printf("Welcome to gobang,please enter Y to start:");
    c=getchar();
    if(c!='Y')
        exit(0);

    system("clear");
    PrintChessBoard();

}

int Judge(int x,int y,int whoseturn)
{
    int i;
    int j;
    int t=2-whoseturn%2;

    for(i=x-4,j=y;i<=x;i++)
    {
        if (i >= 1 && i <= N - 4 &&\
            t == chessboard[i][j] &&\
            t == chessboard[i + 1][j] &&\
            t == chessboard[i + 2][j] && \
            t == chessboard[i + 3][j] && \
            t == chessboard[i + 4][j])
        return 1;
    }

    for(i=x,j=y-4;j<=y;j++)
    {
        if (j >= 1 && j <= N - 4 &&\
            t == chessboard[i][j] &&\
            t == chessboard[i][j+1] &&\
            t == chessboard[i][j+2] && \
            t == chessboard[i][j+3] && \
            t == chessboard[i][j+4])
        return 1;
    }

    for(i=x-4,j=y+4;i<=x,j<=y;i++,j++)
    {
        if (i >= 1 && i <= N - 4 &&\
            t == chessboard[i][j] &&\
            t == chessboard[i + 1][j-1] &&\
            t == chessboard[i + 2][j-2] && \
            t == chessboard[i + 3][j-3] && \
            t == chessboard[i + 4][j-4])
        return 1;
    }

    for(i=x-4,j=y-4;i<=x,j<=y;i++,j++)
    {
        if (i >= 1 && i <= N - 4 &&\
            t == chessboard[i][j] &&\
            t == chessboard[i + 1][j+1] &&\
            t == chessboard[i + 2][j+2] && \
            t == chessboard[i + 3][j+3] && \
            t == chessboard[i + 4][j+4])
        return 1;
    }
    return 0;
}

void PlayChess()
{
    int i=0,j=0,winner=0;
    if(1==whoseturn%2)
    {
        printf("Please enter the player 1:");
        scanf("%d %d",&i,&j);

        while(chessboard[i][j]!=0)
        {
            printf("Please try again!:");
            scanf("%d %d",&i,&j);
        }
        chessboard[i][j]=1;
    }
    else
    {
        printf("Please enter the player 2:");
        scanf("%d %d",&i,&j);
        while(chessboard[i][j]!=0)
        {
            printf("Please try again!:");
            scanf("%d %d",&i,&j);
        }
        chessboard[i][j]=2;
    }

    system("clear");
    PrintChessBoard();
    if(Judge(i,j,whoseturn))
    {
        if(1==whoseturn%2)
        {
            printf("player 1 is win!\n");
            exit(0);
        }
        else
        {
            printf("player 2 is win!\n");
            exit(0);
        }
    }
}


