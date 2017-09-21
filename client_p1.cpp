#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	bool quit = false;
	struct sockaddr_in address;
    int sock = 0, port = 8080;
    struct sockaddr_in serv_addr;
    std::string msg = "";

	if(argc < 2)
		std::cout << "[!] Missing input. Suggested use: ./client_p1 <server ip>" << std::endl;
	
	else
	{

	    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	    {
	        std::cout << "[!] Error creating socket." << std::endl;
        	return EXIT_FAILURE;
	    }
	  
	    memset(&serv_addr, '0', sizeof(serv_addr));
	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(port);

	    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) 
	    {
	        std::cout << "[!] Invalid address." << std::endl;
        	return EXIT_FAILURE;
	    }
	  
	    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	    {
	        std::cout << "[!] Connection failed." << std::endl;
        	return EXIT_FAILURE;
	    }

	    while(!quit)
	    {
	    	std::cout << "Client >> " << std::flush;
	    	msg = ""; 
	    	std::getline(std::cin, msg);
	    	msg.append("\0");
	    	if(msg == "quit")
	    		quit = true;
    		else
    			send(sock, msg.c_str(), msg.length(), 0);
		}
		send(sock, 0, 0, 0);
	}
	return 0;
}