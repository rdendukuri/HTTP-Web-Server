//wrapper.c
//NAME:           RAHUL KRISHNA DENDUKURI
#include "wrapper.h"

//Client Wrapper Functions


/**
* int w_close(int fd)
*
* The wrapper function for  close(int) fucntion used for closing the open sockets
*
* @param fd file descriptor

* @return zero on success.  On error, -1 is returned, and errno is set appropriately.
*
*
*****************************************************************************/
int w_close(int fd)
{
	int i;  
	errno = 0;
	if ( (i=close(fd)) < 0 )	
	{ 
		perror("close error"); 
		exit(1);
		}
	return i;
}
/**
* int w_shutdown(int fd,int mode)
*
* The wrapper function for  shutdown(int,int) fucntion used for closing only half of the sockets
*
* @param fd file descriptor

* @return zero on success.  On error, -1 is returned, and errno is set appropriately.
*
*
*****************************************************************************/
int w_shutdown(int fd,int mode)
{
        int i;
        errno = 0;
        if ( (i=shutdown(fd,mode)) < 0 )
        {
		 fprintf(stderr,"shutdown() error:%s\n",strerror(errno));

                exit(1);
                }
        return i;
}


/**
* 
*
* Wrapper function for  The  connect()  system  call that connects the socket referred to by the file descriptor sockfd to the address specified by addr.

*
* @param sockfd  type SOCK_DGRAM
* @param addr address
* @param addrlen specifies
       the size of addr 
*
* @return  If the connection or binding succeeds, zero is returned.  On error, -1 is returned, and errno is set appropriately.

*
*****************************************************************************/
//connects to the socket 
int w_connect(int sockfd,const struct sockaddr* addr, socklen_t addrlen)
{
	int n;
	errno = 0;
	if ( (n = connect(sockfd,addr, addrlen))< 0 ) //checking if connect succesfull
	{
		perror("connect error"); 
		exit(1);
		}
	return n;
} 

//to write to the stream
/**
*
* w_fputs() is a wrapper function for fputs() writes the string s to a stream, without its terminating null byte ('\0').
*
* @param s is a string
* @param stream is the file handler for the data

*
* @returns a nonnegative number on success, or EOF on error.

*
*****************************************************************************/
int w_fputs ( const char* s, FILE* stream )
{
	int i;
	errno = 0;
	if((i=fputs(s,stream)) == EOF)//check if display has reached EOF
	{		 
		perror("\nfputs error"); 
		exit(1);
		}
	return i;
}

char* w_fgets( char* s,int size, FILE* stream )
{
	char* i;//return value for fputs function
	errno = 0;//reset errno
	if((i=fgets(s,size,stream)) == NULL  )//check if anything is read
	{ 
		if(feof(stream))
			return NULL;  
		perror("\nfgets error"); 
		exit(1);
	}
	return i;
}
 
/**
This is a wrapper function for inet_pton() that converts the character string src into a network address structure in the af address family, then copies the network address structure to dst.
 The af argument must be either AF_INET or AF_INET6.
*
* @param af denotes the address family
* @param src character string that is passed for obtaining the peer address
* @param dst points to the network address structure
*
* @return  1  on  success  (network address was successfully converted).  0 is returned if src does not contain a character string representing a
       valid network address in the specified address family.  If af does not contain a valid address family, -1 is returned and errno is set to EAFNOSUPPORT.

*
*
*****************************************************************************/
//to convert presentation to network addressing
int w_inet_pton ( int af, const char* src, void* dst )
{
	int i;//return value for inet_pton function

	errno = 0;//reset errno
	if((i=inet_pton(af,src,dst)) == 0 )//checking validity of address
	{ 
		fprintf(stderr,"inet_pton error: Invalid address\n"); 
		exit(1);
	}
	else if(i < 0)
	{  
		perror("inet_pton error");
		exit(1);
	}
	return i;
}
 
/**
 This is the wrapper function for read() that  attempts to read up to count bytes from file descriptor fd into
       the buffer starting at buf.
*
* @param fd file descriptor
* @param buf points to the file buffer
* @param count
*
* @return On success, the number of bytes read is returned (zero indicates end of
       file), and the file position is advanced by this number.  It is not  an
       error  if  this  number  is smaller than the number of bytes requested;
       this may happen for example because fewer bytes are actually  available
       right  now  (maybe  because we were close to end-of-file, or because we
       are reading from a pipe, or from a terminal),  or  because  read()  was
       interrupted  by  a  signal.  On error, -1 is returned, and errno is set
       appropriately.  In this case, it is left unspecified whether  the  file
       position (if any) changes.
*****************************************************************************/
//to read from file
ssize_t w_read ( int fd, void* buf, size_t count )
{
	ssize_t n;//return value of read function 
	errno = 0;//reset the errno
	if( (n = read(fd,buf,count)) < 0 )//checking for read error
	{
		perror("read error"); 
		exit(1);
	}
	return n;
}

/**
* the wrapper function for socket() that  creates  an endpoint for communication and returns a descriptor
      
*
* @param domain  specifies a communication domain
* @param type for communication semantics
* @param protocol Denotes the protocol type
*
* @return On success, a file descriptor for  the  new  socket  is  returned.   On
       error, -1 is returned, and errno is set appropriately.

*****************************************************************************/
//to create a file with end to end connection
int w_socket ( int domain, int type, int protocol )
{
	int fd;//return value
	if((fd=socket(domain,type,protocol))<0)//check validity of socket
	{
		fprintf(stderr,"socket() error:%s\n",strerror(errno));
		exit(1);
	}
	return fd;
}

//Server wrapper functions

//accept
int w_accept ( int sockfd, struct sockaddr* addr, socklen_t* addrlen )
{
	int acpt;//to get the connection 
	errno = 0;//reset errno
	if( (acpt = accept(sockfd,addr,addrlen)) < 0)//accept error check
	{
		perror("accept error");
		exit(1);
		}
	return acpt;
}
 
/**
 this is the wrapper function for bind(),it assigns the
       address  specified  by  addr  to  the  socket  referred  to by the file
       descriptor sockfd.  addrlen  specifies  the  size,  in  bytes,  of  the
       address structure pointed to by addr.  Traditionally, this operation is
       called “assigning a name to a socket”.
*
* @param sockfd file descriptor
* @param addr points to the socket for sockfd
* @param addrlen length of the address structure
*
* @return On  success,  zero is returned.  On error, -1 is returned, and errno is
       set appropriately.
*****************************************************************************/
//to accept the connection
int w_bind ( int sockfd, const struct sockaddr *addr, socklen_t addrlen )
{
	int n;//to get the return value of bind function
	if((n = bind(sockfd,addr,addrlen))< 0)//checking bind error
	{
	  fprintf(stderr,"bind()error:%s\n",strerror(errno));
	  exit(1);
	}
	return n;
}
   /**
*
*  The wrapper function for listen() that marks  the  socket referred to by sockfd as a passive socket,
       that is, as a socket that will be used to  accept  incoming  connection
       requests using accept
*
* @param sockfd socket decsriptor
* @param backlog defines the maximum length to which the  queue  of
       pending  connections  for  sockfd  may  grow.
*
* @return On  success,  zero is returned.  On error, -1 is returned, and errno is
       set appropriately.

*
*****************************************************************************/
//Listens to the socket till an request arrives
int w_listen ( int sockfd, int backlog )
{
	int n;//to get the return value 
	errno = 0;//reset the errno
	if((n=listen(sockfd,backlog)) < 0)//listen error check
	{
		perror("listen failed");
		exit(1);
	}
	return n;
}
 
/**
The wrapper function for write utility allows you to communicate with other users, by copying lines from your terminal to theirs.
*
* @param fd file descriptor
* @param buf points to the buffer
* @param count
*
* @return This is where you describe the possible return values.
*
*****************************************************************************/
//to write the buffer to file descriptor
ssize_t w_write(int fd, const void* buf, size_t count)
{
	ssize_t n;
	errno = 0;
	if(( n = write(fd,buf,count))< 0)//check if write takes place
	{
		perror("write error");
		exit(1);
}
	return n;
}
 
/**
* A time() system call wrapper function .
* @param t points to the current time
*
* @return time measured in the format HH:MM:SS UTC
*
*****************************************************************************/
//gets time in seconds
time_t time(time_t * t)
{
	errno = 0;
	time_t tm;
	if((tm = time(t)) < 0)//validity of time
	{	
		perror("can't get time");
		exit(1);
	}
	return tm;
}

FILE* w_fopen(const char* fname,const char* mode){

	FILE *fp;
	 if((fp=fopen(fname,mode))==NULL)//look for file opening
	{
                 fprintf(stderr,"file not able to open : %s\n",strerror(errno));
		 exit(0);	
		}

return fp;


}




typedef void Sigfunc(int) ; // used in S i g a c t i o n f o r r e a d a b i l i t yi
/**
* A sigaction() system call wrapper function .
* @param signo points to the SIGNAL recieved from the operating system
* @param func is a pointer to the signal handling function passes to the fucntion.
* @return Sigfunc pointer  i.e a pointer to the signaml handler function.
*
*****************************************************************************/

Sigfunc *w_Sigaction ( int signo , Sigfunc *func ){

	struct sigaction NewAction ;
	struct sigaction OldAction ;

	 NewAction.sa_handler = func;
	 sigemptyset(&NewAction.sa_mask);
	 NewAction.sa_flags = 0;
	if(sigaction(signo , &NewAction , &OldAction)< 0)
	{//check for sigaction failure
		fprintf(stderr , "sigaction (%d ,... ) failed: %s \n" ,signo, strerror(errno));
		exit(1);
		 }
 // r e t u r n t h e o l d h a n dl e r in c a se c a l l e r wan ts t o know
	 return(OldAction.sa_handler);//returning old signal status
 }
 
/**
This funtion is used for trimming the \n characters at the end of the strings read from readline()
*
* @param str string reference that should be trimmined.
*
* @return void
*
*****************************************************************************/



void trim(char* str){
	int i=strlen(str)-1;
         while(i>=0 && isspace(str[i])){//remove \n character
                        str[i]='\0';
                        i--;
                }

	}
/**
The wrapper function for gethostbynamw() ayatwm call
*
* @param hostname pointer for the hostneme enered by the user
*
* @return pointer to the hostent structure
*
*****************************************************************************/

struct hostent* w_gethostbyname(const char *hostname){
	struct hostent *server = gethostbyname(hostname);
   	 if (server == NULL) {
       		 fprintf(stderr,"ERROR, no such host as %s\n", hostname);
      		  exit(0);
   	 }
	return server;

}


