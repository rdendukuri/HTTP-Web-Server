//wrapper.h
//NAME:           RAHUL KRISHNA DENDUKURI
//ZID:              Z1749863
//Assignment 5
//Due Date :04/28/2015
//CSCI 631 section -1
#ifndef wrapper_H
#define wrapper_H
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<ctype.h>
#include<sys/socket.h>
#include<string.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<time.h>
#include<signal.h>
//#define MAXLINE  4096
//#define LISTENQ 10
#include <netinet/in.h>
#include <netdb.h>
#include "netdb.h"

#define MAXLINE  4096
#define LISTENQ 10
 


typedef void Sigfunc(int); 
struct hostent* w_gethostbyname(const char *hostname);
int w_inet_pton(int af,const char *src,void *dst);
int w_connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
int w_socket(int domain, int type, int protocol);
ssize_t w_read(int fd,void *buf,size_t count);
int w_fputs(const char *s,FILE *stream);
int w_close(int fd);
int w_bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
int w_accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
ssize_t w_write(int fd,const void *buf,size_t count);
int w_listen(int sockfd, int backlog);
char* w_fgets( char* s,int size, FILE* stream );
FILE* w_fopen(const char*,const char*);
Sigfunc *w_Sigaction ( int signo , Sigfunc *func );
void trim(char* str);
int w_shutdown(int fd,int mode);
#endif
