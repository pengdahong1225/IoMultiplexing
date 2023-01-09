#include"IoSelect.h"

void SocketInit(int &fd)
{
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("192.168.111.128");
    sin.sin_port = htons(8080);
    if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("bind");
        exit(0);
    }
}

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SocketInit(listenfd);
    if (listen(listenfd, 5) < 0) //第二个参数规定了内核应该为相应套接字排队的最大连接个数
    {
        perror("listen");
        exit(0);
    }
    /*Begin select*/
    IoSelect(listenfd);
    close(listenfd);
    return 0;
}