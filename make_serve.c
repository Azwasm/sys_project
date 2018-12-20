#include <unistd.h>
#include <netinet/in.h>


int make_server_socket(int port)
{
        struct sockaddr_in servaddr;
        int sockfd;

        if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("Socket is Error !");
                return -1;
        }

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 )
        {
                perror("Bind is Error !");
                return -1;
        }

        listen(sockfd, 2);

        return sockfd;
}