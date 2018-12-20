#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#define LEN 256
#define WIDTH 11
#define HEIGHT 11
#define SUCCESS 7
#define FAIL 4
#define oops(msg)       {perror(msg); exit(1);}
struct p_information
{
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
 
        int fd, port;
        int x,y;
        char end[1];
        int turn, winplayer;

        if(argc != 2)
        {
                printf("usage: ./clinet portnumber\n");
                exit(1);
        }

        port = atoi(argv[1]);

        fd = connect_to_server(port);
        if(fd == -1)
                exit(1);
  
        printf("connected to server\n please login for omokGo\n");
        login(fd);
        printf("your id is %s.",p_info.id);
        if( read(fd, &p_info.player_num,sizeof(int)) == -1)
                oops("read");
        printf("you are player%d\n",p_info.player_num);
        if(p_info.player_num ==1)
                p_info.com_player_num = 2;
        else if(p_info.player_num == 2)
                p_info.com_player_num =1;


        while(1)
        {
    
                if(p_info.player_num == 1)
                        player1(fd);
                else if(p_info.player_num == 2)
                        player2(fd);
      
                read(fd,&winplayer,sizeof(int));
                if(winplayer != 77){
                        printf("player%d win.\n", winplayer);
                        break;
                }
        }

        close(fd);
}
void player1(int fd)
{
        int x, y, r_x, r_y;
        printf("player %d turn (x,y) : ", p_info.player_num);
        scanf("%d %d",&x,&y);
		while(x < 0 || x > 10 || y < 0 || y > 10)
        {
			printf("out of range !!!\n");
			printf("player %d turn (x,y) : ",p_info.player_num);
			scanf("%d %d",&x,&y);
		}
        while(board[x][y] != 0)
        {
			printf("There is stone !!!\n");
        	printf("player %d turn (x,y) : ", p_info.player_num);
			scanf("%d %d",&x,&y);
		}
        write(fd, &x, sizeof(int));
        write(fd, &y, sizeof(int));
        putting(x,y,p_info.player_num);
        drawBoard();
        read(fd, &r_x, sizeof(int));
        read(fd, &r_y, sizeof(int));
        printf("player %d turn (x,y) : (%d, %d)\n", p_info.com_player_num,r_x,r_y);
        putting(r_x,r_y,p_info.com_player_num);
        drawBoard();
}
void player2(int fd)
{
        int x, y;
        read(fd, &x, sizeof(int));
        read(fd, &y, sizeof(int));
        printf("player %d turn (x,y) : (%d, %d)\n", p_info.com_player_num,x,y);
        putting(x,y,p_info.com_player_num);
        drawBoard();
        printf("player %d turn (x,y) : ", p_info.player_num);
        scanf("%d %d",&x,&y);
		while(x < 0 || x > 10 || y < 0 || y > 10)
        {
			printf("out of range !!!\n");
			printf("player %d turn (x,y) : ", p_info.player_num);
			scanf("%d %d", &x, &y);
		} 
		while(board[x][y] != 0)
        {
			printf("There is stone !!!\n");
        	printf("player %d turn (x,y) : ", p_info.player_num);
			scanf("%d %d",&x,&y);
		}
		write(fd, &x, sizeof(int));
        write(fd, &y, sizeof(int));
        putting(x, y, p_info.player_num);
        drawBoard(); 
}
void login(int fd)
{
        int new;
        char id[5];
        printf("please enter if you are new member 1,or 2 : ");
        scanf("%d",&new);
        write(fd,&new,sizeof(new));
        printf("please enter your id(id -> 4 letters) : ");
        scanf("%s",p_info.id);
        printf("%s\n",p_info.id);
        write(fd,p_info.id, BUFSIZ);
}
void drawBoard()
{
        int i, j;
        for(i = 0; i < WIDTH; i++)
        {
                for(j = 0; j < HEIGHT; j++)
                {
                        if(board[i][j] == 1) 
                        {
                                printf("○-");
                        }
                        else if(board[i][j] == 2)
                        {
                                printf("●-");
                        }
                        else if(board[i][j] == 0)
                        {
                                if(i == 0)
                                {
                                        if(j != 0 && j != HEIGHT-1) 
                                        {
                                                printf("┬-");
                                        }
                                }
                                else if(i == WIDTH-1)
                                {
                                        if(j != 0 && j != HEIGHT-1)
                                        {
                                                printf("┴-");
                                        }
                                }
                                if(j == 0)
                                {
                                        if(i == 0)
                                        {
                                                printf("┌-");
                                        }
                                        else if(i == WIDTH-1) 
                                        {
                                                printf("└-");
                                        }
                                        else 
                                                printf("├-");
                                }
                                else if(j == HEIGHT-1)
                                {
                                        if(i == 0)
                                        {
                                                printf("┐");
                                        }
                                        else if(i == WIDTH-1)
                                        {
                                                printf("┘");
                                        }
                                        else
                                        printf("┤");
                                }
                                if(i*j != 0 && i != WIDTH-1 && j != HEIGHT -1)
                                        printf("┼-");
                        }
                }
                printf("\n");
        }
}
void putting(int x, int y, int c)
{
        if(board[x][y] == 0)
        {
                board[x][y] = c;
        }
}
int connect_to_server(int port)
{
        int   client_socket;

        struct sockaddr_in   server_addr;


        client_socket  = socket( PF_INET, SOCK_STREAM, 0);
        if( client_socket == -1)
        {
                printf( "socket 생성 실패\n");
                exit(1);
        }

        memset( &server_addr, 0, sizeof( server_addr));
        server_addr.sin_family      = AF_INET;
        server_addr.sin_port        = htons(port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if(  connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) == -1  )
        {
                printf( "접속 실패\n");
                exit(1);
        }
        
        return client_socket;
}
