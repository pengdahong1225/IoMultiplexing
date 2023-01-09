#include "IoSelect.h"

using namespace std;
int conn_amount;

void IoSelect(int &fd)
{
    int newfd;
    string sendBuf;

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);
    int maxsockfd = fd;
    conn_amount = 0;
    cout << "maxfd = " << maxsockfd << endl;
    while (true)
    {
        fd_set tempSet;
        tempSet = readSet;
        int ret = select(maxsockfd + 1, &tempSet, nullptr, nullptr, nullptr);
        if (ret == 0)
            continue;
        else if (ret == -1)
        {
            perror("select");
            cout << "select error" << endl;
            break;
        }
        cout << "ret = " << ret << endl;
        /*check every fd in the set*/
        for (int i = 0; i <= maxsockfd; i++)
        {
            if (FD_ISSET(i, &tempSet))
            {
                if (i == fd)
                {
                    struct sockaddr_in remoteAddr;
                    int nAddrlen = sizeof(remoteAddr);
                    newfd = accept(fd, (struct sockaddr*)&remoteAddr,(socklen_t*)&nAddrlen);
                    if (conn_amount < FD_SETSIZE)
                    {
                        FD_SET(newfd, &readSet);
                        cout << "New Connection: " << inet_ntoa(remoteAddr.sin_addr) << endl;
                        //cout << "New Connection: " << newfd << endl;
                        maxsockfd = (newfd > fd ? newfd : fd);
                        cout << "maxfd = " << maxsockfd << endl;
                        conn_amount++;
                        sendBuf = "Welcome my home";
                        send(newfd,sendBuf.c_str(),sendBuf.size(),0);
                    }
                    else
                    {
                        cout << "max connections arrive, exit" << endl;
                        break;
                    }
                }
                else
                {
                    char recvBuf[1024];
                    int recvBytes = recv(i, recvBuf, sizeof(recvBuf), 0);
                    if (recvBytes < 0)
                    {
                        perror("recv");
                        cout << "recv error" << endl;
                        FD_CLR(i, &readSet);
                        close(i);
                        break;
                    }
                    else if (recvBytes == 0)
                    {
                        cout << "client(" << i << ") "
                             << "is closed!" << endl;
                        FD_CLR(i, &readSet);
                        close(i);
                        break;
                    }
                    else
                    {
                        cout << "from " << i << " :" << recvBuf << endl;
                        sendBuf = "Messi";
                        send(i, sendBuf.c_str(), sendBuf.size(), 0);
                    }
                }
            }
        }
    }
}