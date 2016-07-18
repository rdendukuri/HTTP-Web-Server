# HTTP-Web-Server

This web server will accept and process HEAD and GET transactions from a web browser using the HTTP/1.0 protocol. The HTTP protocol is implemented over UNIX with a TCP concurrent sever which listens for connections forks to create child sever process that handles the client request .The sever looks for the HTTP requests and provides the response with proper header format to client viz. web browser in this case.

Usage :

 Server Side:
  After building the contents on your unix box , run the executable as follows in cwd
  
    $ http_server [port number]
    
  Client side(Any web brownser):
  
    In the address bar , type the address of the machine,port number on which your server program is listening for connections.
     
         <IP address or dns name of your machine>:[port number]/index.html
   
      
    
    _
