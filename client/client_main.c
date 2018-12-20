#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#define LEN 256
#define WIDTH 11 //width size
#define HEIGHT 11 //height size
#define SUCCESS 7
#define FAIL 4
#define oops(msg)       {perror(msg); exit(1);}
struct p_information{
        char id[5];
        int win_record,recent_time;
        int player_num, com_player_num;
};
void login(int fd);
void drawBoard();
void putting(int x, int y, int c);
void player1(int fd);
void player2(int fd);
struct  p_information p_info;
int board[WIDTH][HEIGHT];
int connect_to_server(int port);
int main(int argc, char *argv[])
{
        //client
        int fd,port = atoi(argv[1]);
        //program
        int x,y;
        char end[1];
        int turn, winplayer;
        fd = connect_to_server(port);
        if(fd == -1)
                exit(1);
        //login
        printf("connected to server\n please login for omokGo\n");
        login(fd);
        printf("your id is %s.",p_info.id);
        if(read(fd,&p_info.player_num,sizeof(int))==-1)
                oops("read");
        printf("you are player%d\n",p_info.player_num);
        if(p_info.player_num ==1)
                p_info.com_player_num = 2;
        else if(p_info.player_num == 2)
                p_info.com_player_num =1;

        //what to do
        while(1)
		{
                //whose turn
                if(p_info.player_num == 1)
                        player1(fd);
                else if(p_info.player_num == 2)
                        player2(fd);
                //add
                read(fd,&winplayer,sizeof(int));
                if(winplayer !=77){
                        printf("player%d win.\n",winplayer);
                        break;
                }
        }
        //close socket
        close(fd);
}