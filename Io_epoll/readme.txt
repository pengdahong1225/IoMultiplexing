https://blog.csdn.net/Ineffable__/article/details/125920309

/* 创建一个epoll的句柄，size用来告诉内核需要监听的数目一共有多大,只要>0即可。当创建好epoll句柄后，
它就是会占用一个fd值，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。*/
int epoll_create(int size);

/*将需要监视的socket添加到epfd中 and 事件注册*/
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event); 
op: EPOLL_CTL_ADD
    EPOLL_CTL_MOD
    EPOLL_CTL_DEL
    
/*等待事件的到来，如果检测到事件，就将所有就绪的事件从内核事件表中复制到它的第二个参数events指向的数组*/
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);


struct epoll_event 结构如下：
    typedef union epoll_data
    {
        void        *ptr;
        int          fd;
        __uint32_t   u32;
        __uint64_t   u64;
    } epoll_data_t;

    struct epoll_event 
    {
        __uint32_t events; /* Epoll events */
        epoll_data_t data; /* User data variable */
    };

    events:
    EPOLLIN     //表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
    EPOLLOUT    //表示对应的文件描述符可以写；
    EPOLLPRI    //表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
    EPOLLERR    //表示对应的文件描述符发生错误；
    EPOLLHUP    //表示对应的文件描述符被挂断；
    EPOLLET     //将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
    EPOLLONESHOT//只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里。

