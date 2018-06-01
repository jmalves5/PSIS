#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>

#include "library.h"


int main(){

	struct sockaddr_un server_addr;
	struct sockaddr_un client_addr;
	int nbytes;
	int sock_fd=0;



	//Create and fill client address
	printf(" socket created \n");
	client_addr.sun_family = AF_UNIX;

	//Create and fill clipboard server address
	printf(" socket with adress \n");
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, CLIPBOARD_SOCKET);

	//Create socket
	sock_fd=clipboard_connect(server_addr);

	
	char * m=malloc(1000*sizeof(char));
	void * buff=malloc(1000*sizeof(char));

	strcpy(m, "Message in a bottle");
	clipboard_copy(sock_fd, 8, m, (strlen(m)+1)*sizeof(char));
	
    nbytes=0;
	
	//Send to clipboard something
	while(nbytes!=-1){
		nbytes=clipboard_paste(sock_fd, 6, (char *)buff, MAXSIZE);
		sleep(2);
	}

	close(sock_fd);
	free(m);
	free(buff);
	exit(0);
}
