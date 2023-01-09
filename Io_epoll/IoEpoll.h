#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <string>

void Ioepoll(int &fd);