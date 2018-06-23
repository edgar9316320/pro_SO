all : tcpServer tcpClient

CPPFLAGS = -g -I.

tcpServer : tcpServer.c
	cc -g -I. tcpServer.c -o tcpServer

tcpClient : tcpClient.c
	cc -g -I. tcpClient.c -o tcpClient

clean :
	rm tcpClient tcpServer
