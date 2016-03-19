


//NAME:           RAHUL KRISHNA DENDUKURI

#ifndef in_out_H
#define in_out_H

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<time.h>

ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t readline(int fd, void *vptr, size_t maxlen);


#endif
