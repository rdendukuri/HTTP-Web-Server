#include "http.h"
#include "wrapper.h"
#include "in_out.h"
static int getn;
static int headc;
//char* st="HTTP/1.1 200 OK";
//
void writehead(int sock,char* head,char*content){
    writen(sock,head,strlen(head));
                writen(sock,"\r",1);
                writen(sock,"\n",1);
                writen(sock,content,strlen(content));
                 writen(sock,"\r",1);
                writen(sock,"\n",1);

                writen(sock,"Connection: close",17);
                 writen(sock,"\r",1);
                writen(sock,"\n",1);
                 writen(sock,"\r",1);
                writen(sock,"\n",1);

}
static void doIllegalRequestType(int sock)
{
writehead(sock,"HTTP/1.0 404 Not Found","Content-Type: text/plain");
 writen(sock,"\r",1);
writen(sock,"\n",1);
 writen(sock,"Error:Query",11);
}


/**
****************************************************************/
static void doHttpGet(int sock, char *root)
{
	getn++;
  //      alarm(5);
	char s[MAXLINE];
        // read the request header lines
	if(strcmp(root,"docs/")==0){
		   writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/html");
		  char buffer[MAXLINE]="<HTML>\r\n<body>\r\n<h1>hello world</h1>\r\n</body>\r\n</HTML>\r\n";
		w_write(sock,buffer,strlen(buffer));   

                  writen(sock,"\r",1);
                writen(sock,"\n",1);



		}
	else if(strcmp(root,"docs/status")==0)
	{


		writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/plain");

		sprintf(s,"GET reguests:%d",getn);
		  writen(sock,s,strlen(s));
                  writen(sock,"\r",1);
                writen(sock,"\n",1);
		 sprintf(s,"Head reguests:%d",headc);
                writen(sock,s,strlen(s));

                  writen(sock,"\r",1);
                writen(sock,"\n",1);


		


		}
	else
	{
		
	
		char buffer[MAXLINE];
		char* m="r";
		if(strstr(root,".gif")){
			 writehead(sock,"HTTP/1.1 200 OK","Content-Type: image/gif");
				m="rb";
		}
		else if(strstr(root,".jpg"))
			 writehead(sock,"HTTP/1.1 200 OK","Content-Type: image/jpg");
		else if(strstr(root,".jpeg"))
			 writehead(sock,"HTTP/1.1 200 OK","Content-Type: image/jpeg");
		  else if(strstr(root,".txt"))
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/plain");
		  else if(strstr(root,".html"))
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/html");
		  else 
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/plain");

		FILE*  fp=fopen(root,m);




		if(fp==NULL)
			doIllegalRequestType(sock);
		else
		{	 while(!ferror(fp)) 
			{ 
    			int  n = fread(buffer, 1, MAXLINE, fp); 
		     	if (0 == n) break;


			 writen(sock,buffer,n);
        
	
	
				} 
               		
		}
		
          }

}

/**
****************************************************************/
static void doHttpHead(int sock, char *root)
{


	
        headc++;

        if(strcmp(root,"docs/")==0){
                   writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/html");

                }
        else if(strcmp(root,"docs/status")==0)
        {


                writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/plain");
      
     
	}

	else
	{

		    if(strstr(root,".gif"))
			{
	                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: image/gif");
//                                m="rb";
                	}
                	else if(strstr(root,".jpg"))
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: image/jpg");
                	else if(strstr(root,".jpeg"))
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: image/jpeg");
                  	else if(strstr(root,".txt"))
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/plain");
                  	else if(strstr(root,".html"))
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/html");
                  	else
                         writehead(sock,"HTTP/1.1 200 OK","Content-Type: text/plain");


		}
}

/**
****************************************************************/



/**
* This is intendewd to be called from doServ() after it calls
* fork() to create a child process to handle an HTTP client
* socket.
*
* @param sock The client socket connection.
* @param root The directory name where the web server files are.
****************************************************************/
 void doHTTPQuery(int sock, char root[MAXLINE])
{



//	fprintf(stderr,"HTTPQuery\n");
        char buffer[MAXLINE];
	char temp[MAXLINE]="\0";
	char b2[MAXLINE];
//        alarm(5);
	strcpy(b2,root);
	readline(sock,buffer,MAXLINE);
	
	
		strcpy(root,b2);

        // read the request header lines
          
        trim(buffer);


	int i=0;


	while(i<strlen(buffer)-1 && !isspace(buffer[i])){



		temp[i]=buffer[i];
		i++;
	


		}


	// determine what type of request was received
 

	if (strcmp(temp,"GET")==0)
	{


		int i=4;
		int j=0;
		char a[MAXLINE];

		while(!isspace(buffer[i]) && i<strlen(buffer)-1)
		{	
			a[j++]=buffer[i];
			i++;


			}
		if(strstr(a,"/../") || strstr(a,"/.."))
			{
			 doIllegalRequestType(sock);

			return;
			}

		j=0;
		for(i=strlen(root);j<strlen(a);j++)
			root[i++]=a[j];


		doHttpGet(sock, root);

		}
	else if ((strcmp(temp,"HEAD"))==0)
		doHttpHead(sock, root);
	else
		doIllegalRequestType(sock);


	

}

