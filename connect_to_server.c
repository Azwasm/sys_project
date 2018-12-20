#include <unistd.h>
#include <netinet/in.h>


int connet_to_server(int port)
{
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket( PF_INET, SOCK_STREAM, 0 );
    if( client_socket == -1 )
    {
        printf("Socket is Error.\n");
        eixt(1);
    }
    memset( &server_addr, 0, sizeof( server_addr));
    server_addr.sin_family     = AF_INET;
    server_addr.sin_port       = htons(port);
    server_addr.sin_addr.s_addr= inet_addr( "127.0.0.1");

    if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
    {
        printf( "Connting is Error.\n");
        exit( 1);
    }
        
    return client_socket;
}