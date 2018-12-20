#include <stdio.h>

#define WIDTH 11 //width size
#define HEIGHT 11 //height size

int board[WIDTH][HEIGHT];


void drawBoard()
{
    int i, j ;
    for(i = 0 ; i < WIDTH ; i ++ )
    {
        for( j = 0 ; j <HEIGHT ; j++ )
        {
            if (board[i][j] == 1 )
                printf("○-");//player1's
            else if(board[i][j] == 2 )
                printf("●-");//player2's
            else if(board[i][j] == 0 )
            {
                if(i == 0)
                {
                    if( j != 0 && j != HEIGHT-1 )
                        printf("┬-");
                    else if ( i == WIDTH -1 )
                        if(j!=0 && j!= HEIGHT-1)  
                            printf("┴-");
                    if(j == 0){
                            if(i==0) 
                                printf("┌-"); //(0,0)
                            else if(i==WIDTH-1) 
                                printf("└-");
                            else printf("├-");
                    }
                    else if(j== HEIGHT-1){
                            if(i==0)
                                printf("┐");
                            else if(i==WIDTH-1) 
                                printf("┘");
                            else printf("┤");
                    }
                    if(i*j!=0&&i!=WIDTH-1&& j!=HEIGHT -1)printf("┼-");              
                }
            }
        }
    }
}
