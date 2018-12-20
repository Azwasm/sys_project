void login(int fd){

        int new;
        char id[5];

        printf("please enter if you are new member 1,or 2 : ");
        scanf("%d" ,&new );
        write(fd , &new , sizeof(new));
        printf("please enter your id(id -> 4 letters) : ");
        scanf("%s" , p_info.id);
        printf("%s\n" , p_info.id );
        write(fd,p_info.id , BUFSIZ);
}

void putting(int x, int y, int c)
{
        if(board[x][y]==0)
        {
                board[x][y]=c;
        }
}