//user.c
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv){
	int fd, n, nbytes, nwritten, nread;
	struct sockaddr_in addr;
	struct hostent *hostptr;
	char *ptr, buffer[128];
	
	
	char *username = argv[1];
	char *SMBname;
	int SMBport;
	int NG = 0;
	
	if (argc == 4) {
	
		if (!strcmp(argv[2], "-n")) {
			SMBname = argv[3];
			SMBport = 5800 + NG;
		}
		else if (!strcmp(argv[2], "-p")) {
			SMBport = atoi(argv[3]);
			SMBname = "localhost";
		}
	
	} else if(argc == 6) {

		SMBname = argv[3];
		SMBport = atoi(argv[5]);
	
	} else if (argc == 2) {
		SMBname = "localhost";
		SMBport = 58000+NG;
	}
	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1)
		exit(1);
		
	hostptr = gethostbyname(SMBname);
		
	memset((void*)&addr, (int)'\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ((struct in_addr*)(hostptr->h_addr_list[0]))->s_addr;
	addr.sin_port = htons(SMBport);
	
	n = connect(fd,(struct sockaddr*)&addr, sizeof(addr));
	if(n == -1)
		exit(1);
	
	ptr = strcpy(buffer, "ping");
	nbytes = 4;
	
	nwritten = write(fd, ptr, nbytes);
	if(nwritten == -1)
		exit(1);
		
	nread = read(fd, buffer, 128);
	
	puts(buffer);
	
	close(fd);
	exit(0);
}
