//
//  main.cpp
//  http-server
//
//  Created by Jason on 7/27/21.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    /*
     HTTP is "Application Layer Protocol"
     TCP is "Transport Layer" in 7 layers of the
     OSI(Open Systems Interconnection) Model
     
     Application Layer is for End User Laer
     HTTP, FTP, IRC, SSH, DNS
     
     Transport Layer is for End-to-End connection
     TCP, UDP
     */
    
    /*
     TCP, since it is connection-based, is more reliable than UDP while is less
     efficient than sharing a singple connection to many requests in
     close succession
     However, http looks for reliablity therefore it uses TCP runs top of it
     */
    
    /*
     For End-to-End connection and transporting, we need to set up socket
     Sockets are endpoint instance defined by IP address and a Port number
     (port is a virtualized identifier - treat it as ZipCode)
     And there can only be one listenr socket for a given address/port combination
     Since TCP connection is defined by two endpoints a.k.a sockets,
     there would be socket in server side and client side
     
     And 3-way handshake happens (syn, syn-ack, ack) when creating a
     socket connection between the two endpoint (here server and client)
     */
    
    // 1. Create socket for the server (need to define the port and bind the socket to the port)

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int server_socket_file_descripter;
    server_socket_file_descripter = socket(AF_INET, SOCK_STREAM, 0);
    // socket(communication domain, type of socket, protocol)
    // AF_INET - Internet address
    // SOCK_STREAM - "sequenced", "reliable", "bidrectional" conection-mode == TCP
    // SOCK_DGRAM - datagrams, connectionless-mode, unreliable, fixed max length --> UDP
    // If protocol argument is non-zero, it must specify a protocol that is supported by address famil
    // https://pubs.opengroup.org/onlinepubs/7908799/xns/socket.html
    if(server_socket_file_descripter == 0){//Failed to create a socket
        perror("create a scoket failed\n");
        exit(EXIT_FAILURE); // equivalent to 1
    }
    
    //bind socket to the port you define
    int opt = 1;
    // setsockopt(socket, level, option_name, option_value, option_len)
    // option - to set options at the socket level, specify the level argument as SOL_Socket
    // to set other leves, supply the appropriate protocol number for
    // the protocol controlling option. EX) to indicate an option to be interpreted by TCP
    // set level to the protocol number of TCP as defined in the <netinet/in.h> header
    // Below option allows us to reuse address and port, prevents error such as
    // "address already in use"
    if(setsockopt(server_socket_file_descripter, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
        // non-zero is failure in binding
        perror("setsockopt failed\n");
        exit(EXIT_FAILURE);
    } // This is sort of initializing socket instance we created
    
    // bind to a certain address and port(8000)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8000);
    if(bind(server_socket_file_descripter, (struct sockaddr *) &address, sizeof(address)) < 0){
        perror("bind socket failed");
        exit(EXIT_FAILURE);
    }
    
    // 2. Let it listen and receive
    while(listen(server_socket_file_descripter,3) >= 0){
        // 0 is success OW -1 is returend
        int client_socket = accept(server_socket_file_descripter, (struct sockaddr *) &address, (socklen_t*)&addrlen);
        if ( client_socket < 0){
            perror("accept client socket failed");
            exit(EXIT_FAILURE);
        }
        char buffer[1024] = {0}; // zero value
        read(client_socket, buffer, 1024);
        
        // 3. Handler - (if catches request from client in listen) handle properly
        printf("packet received from client : %s\n", buffer);
        char * server_resp = "Server receive success";
        send(client_socket, server_resp, strlen(server_resp), 0);
        close(client_socket);
    }
    perror("listen failed");
    exit(EXIT_FAILURE);
}
