//serv.c
//NAME:           RAHUL KRISHNA DENDUKURI




#include "wrapper.h"
#include "serv.h"
#include "in_out.h"
#include "http.h"

typedef void Sigfunc(int);
void sig_chld(int);
/**
* int doServ(uint16_t port)
*
* The is function is for server side socket connection 
* @param uint16_t port       port number for server connection
* @return integer
*
*
*****************************************************************************/
int doServ(uint16_t port){
	int listenfd,connfd;/*for socket file descriptor and connection descriptor*/
/*	struct linger s;
	 s.l_onoff = 1;
         s.l_linger = 10;*/
	
	pid_t childpid;//child process ID
	socklen_t clilen;
	char root[MAXLINE]="docs";
	struct sockaddr_in cliaddr,servaddr;//to store server details
	listenfd=socket(AF_INET,SOCK_STREAM,0);//connect to a socket
	bzero(&servaddr,sizeof(servaddr)); //set server address structure to 0
	servaddr.sin_family=AF_INET;//uses IPV4
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);//ready for listening for connections
	servaddr.sin_port=htons(port);/*set port to Book SERVER*/
	w_bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); //bind the port to the socket
	w_listen(listenfd,LISTENQ);//listen for connections
        Sigfunc *old=w_Sigaction(SIGCHLD ,sig_chld);
	while(1)
	{
		clilen=sizeof(cliaddr);
		if((connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&clilen))<0){//if connect problem
		     if(errno == EINTR || errno == ECONNABORTED )//check for interrupts and aborts
			continue;
		 else
                	fprintf(stderr,"accept error:%s",strerror(errno));
			}	
	if((childpid= fork())==0){

		w_Sigaction(SIGCHLD ,old);
		w_close(listenfd);

//		setsockopt(connfd,SOL_SOCKET,SO_LINGER, &s, sizeof(s));

		doHTTPQuery(connfd,root);
 		w_close(connfd);
		exit(0);
		}
	 w_close(connfd);
		}				
	}


/**
* void sig_chld(int signo)
*
* The is function is for signal handlinf when a SIGHLD signal recieved
* @param int signo       Signal number corresponding to SIGCHLD
* @return void
*
*
*****************************************************************************/
void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0);

	return;
}
