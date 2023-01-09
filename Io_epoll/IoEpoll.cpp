#include "IoEpoll.h"

using namespace std;
#define MAXSIZE 1024

void Ioepoll(int &fd)
{
    struct epoll_event ev;
    /* 生成epoll专用的文件描述符 */
    int epollfd = epoll_create(10);
    /* 注册listen socket,for IN and LET */
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);

    int nfds, connfd, sockfd, nread;
    char recvbuf[MAXSIZE];
    struct sockaddr_in clientaddr;
    int nAddrclient = sizeof(clientaddr);
    
    /* begin */
    struct epoll_event events[20];
    while (true)
    {
        /* 等待epoll事件的发生 */
        nfds = epoll_wait(epollfd, events, 20, 500);
        /* 处理所发生的所有事件 */
        for (int i = 0; i < nfds; i++)
        {
            /* 如果是监听套接字 */
            if (events[i].data.fd == fd)
            {
                connfd = accept(fd, (struct sockaddr *)&clientaddr, (socklen_t *)&nAddrclient);
                if (connfd < 0)
                {
                    perror("accept");
                    return;
                }
                cout << "new connection: " << inet_ntoa(clientaddr.sin_addr) << endl;
                /* 注册 */
                ev.data.fd = connfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &ev);
            }
            else if (events[i].events & EPOLLIN)
            {
                if ((sockfd = events[i].data.fd) < 0)
                    continue;
                cout << "sockfd:" << sockfd << endl;
                if ((nread = recv(sockfd, recvbuf, sizeof(recvbuf), 0)) < 0)
                {
                    /* Connection reset by peer */
                    if (errno == ECONNRESET)
                    {
                        close(sockfd);
                        events[i].data.fd = -1;
                    }
                    else
                        perror("recv");
                    continue;
                }
                /* client close */
                else if (nread == 0)
                {
                    close(sockfd);
                    events[i].data.fd = -1;
                    continue;
                }
                if (nread < MAXSIZE - 2)
                    recvbuf[nread] = '\0';
                cout << "from " << inet_ntoa(clientaddr.sin_addr) << ": " << recvbuf << endl;
                memset(recvbuf, 0, sizeof(recvbuf));
                char sendbuf[1024] = "I'm Messi";
                send(sockfd, sendbuf, strlen(sendbuf), 0);
            }
        }
    }
}