# http-web-server - Let's understand http deeply

## Fundamental CS knowledge involved in here

### Application Layer
- For "End user", sitting at the higher level in OSI(Open Systems Interconnection) 7 Layer MOdel
- ex) HTTP, FTP, IRC, SSH, DNS
### Transport Layer
- For "End-to-End" connection, lower level than Application Layer
- ex) TCP, UDP
### TCP
- connection-based, full-duplex(bi-directional), reliable
- less efficient than sharing a single connection to many requests in close succession
- HTTP, HTTPs, FTP, SMTP, Telnet run on top of TCP
- 3-way handshake(`syn`, `syn-ack`, `ack`) to create aa socket connection between the two endpoints[sockets] (here, the server and the client)
### UDP
- Better in handling many requests in close succession than TCP
- Not reliable (Delivery is not guaranteed) + no resending
- Datagram based protocol
- No overhead in opening a connection (no 3 way handshake)
- Good for broadcast and multicast
- No sequencing; order is not guaranteed at this level
- DNS, DHCP, TFTP run on top of this
### Socket
- For "End-to-End" connection and transporting, we need to set up a socket.
- sockets are endpoint "instance" defined by `IP address` and a `Port` number
- There can only be one listener socket for a given address/port combination
- Sequencing; in-order at this level
- Resending(part of the guarantee) of those lost packets
### Port
- VIrtualized identifier
- like a zipcode
### HTTP
- HypterText Transfer Protocol, underlying protocl of World Wide Web
- Developed by Tim Berners-Lee and his team
- Versions (covering only some of them):
  - HTTP/1.1 The standardized protocol
    - reuses a connection (saves resource being used in opening a connection)
    - TCP/IP
    - if using HTTPS, then it uses TLS to encrpy HTTP requests and response (the data now would be not human-readable)
  - HTTP/2
    - binary protocol rathern than text -> light-weight and so faster
    - multiplexed protocol - parallel requests can be handled over the same connection
    - allows a server to populate data in a client cache
    - TCP/TLS(TLS over TCP/IP) for security (encription and guaranteeing the authenticity of the messages exchanged between the server and client)
    - No need HTTPs, HTTP2 is implemented for TLS(HTTPS) connections
### TLS(SSL almost same, just a improvement of SSL)
- Trnasport Layer Security, protocol for implementing cryptography on the web
- Provides a secure enhancement ot the standard TCP/IP sockets protocol
- is sitting between Application Layer and Transport Layer

<br>

## General Workflow of HTTP Server set-up
### 1. Create a socket using TCP connection for the server 
### 2. Define the port and address and bind the socket to that
### 3. Let the socket listen
### 4. Handle those request you listened
### 5. Send back a response to that request
### 6. Loop step `4~6`


# Reference & Sources
https://www.geeksforgeeks.org/differences-between-tcp-and-udp/ <br>
https://ruslanspivak.com/lsbaws-part1/ <br>
https://pubs.opengroup.org/onlinepubs/7908799/xns/socket.html <br>
https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/ <br>
https://www.ibm.com/docs/en/sdk-java-technology/7?topic=provider-tls-protocol-overview <br>
