void login(int fd , int s_num){

        int new;
        char buf[BUFSIZ],id[5];

        if(read(fd , &new , sizeof(new))==-1)
                oops("read");
        if(read(fd,p_info[s_num].id , BUFSIZ)==-1)
                 oops("read id");
        printf("login id : %s\n" , p_info[s_num].id);
    
}

int putting(int x, int y, int c)
{
        if(board[x][y]==0)
        {
                board[x][y]=c;
        }
}