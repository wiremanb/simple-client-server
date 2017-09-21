#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	bool quit = false, clientConnected = false;
	char buffer[1024] = {0};
	int fd, sock, clientNumber = 0, port = 8080, addrlen = sizeof(address);;
	struct sockaddr_in address;

	std::cout << "[*] Server starting..." << std::endl;

	// Create server socket and set it up as a TCP connection
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "[!] Error creating socket." << std::endl;
        return EXIT_FAILURE;
    }
    
    // Setup the sockaddr_in struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
     
    // Bind the struct to the socket
    if (bind(fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        std::cout << "[!] Failed to bind to address." << std::endl;
        return EXIT_FAILURE;
    }

    // Listen on this socket and queue 10 connections
    if (listen(fd, 10) < 0)
    {
        std::cout << "[!] Listening failed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "[*] Server is listening for clients." << std::endl;

    // While not quitting...
    while(!quit)
    {
    	// No client is connected
    	if(!clientConnected)
    	{
    		// Setup a client socket when a client connects
	    	if ((sock = accept(fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
	    	{
	        	std::cout << "[!] Server failed to accept." << std::endl;
	        	return EXIT_FAILURE;
	    	}
	    	std::cout << "[*] Client " << ++clientNumber << " has connected." << std::endl;
	    	clientConnected = true;
		}


		// Read messages from the clients
    	size_t rBytes = recv(sock, buffer, 1024, 0);
    	if(rBytes == 0)
    	{
    		close(sock);
    		clientConnected = false;
    		memset(buffer, 0, sizeof(buffer));
    		std::cout << "[*] Client " << clientNumber << " has disconnected." << std::endl;
    	}
    	else
    	{
    		std::cout << "[*] Client " << clientNumber << ": " << buffer << std::endl;
    		send(sock, buffer, sizeof(buffer), 0);
    	}
	}
	close(fd);
	return 0;
}