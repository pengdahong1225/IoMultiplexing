#include "IoEpoll.h"

void Sock_Init(int &fd)
{
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("192.168.111.128");//localhost
    sin.sin_port = htons(9000);
    if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        return;
    }
}
int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    Sock_Init(listenfd);
    if (listen(listenfd, 5) == -1)
    {
        perror("listen");
        exit(0);
    }
    Ioepoll(listenfd);
    close(listenfd);
    return 0;
}