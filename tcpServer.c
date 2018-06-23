#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

int main(){

	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int conexion;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024], buffer2[200];
	pid_t p_hijo;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error en la conexion \n");
		exit(1);
	}
	printf("Servidor Agregado.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error en union.\n");
		exit(1);
	}
	printf("Union a puerto %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("Escuchando....\n");
	}else{
		printf("Error al Escuchar.\n");
	}


	while(1){
		conexion = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(conexion < 0){
			exit(1);
		}
		printf("Conexion con = %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((p_hijo = fork()) == 0){
			close(sockfd);

			while(1){
				recv(conexion, buffer, 1024, 0);
				//------------------------------
				  //fgets(buffer2, 200, stdin);
				  //send(conexion, buffer2, 200, 0);
				  //bzero(buffer2, 200);
				  //recv(conexion, buffer2, 200, 0);
				  //printf("%s", buffer2);
				//------------------------------
				if(strcmp(buffer, ":exit") == 0){
					printf("Desconexion de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}else{
					printf("Cliente: %s\n", buffer);
					send(conexion, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
			}
		}

	}

	close(conexion);


	return 0;
}