#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

void IoSelect(int &fd);