/*************************************************************************************
                                UDP UNIX socket
************************************************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include<errno.h>
#include<stdio.h>

int main()
{


char buf[100] = {0};
struct sockaddr_un cli_addr = {0};
int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
if(-1 == sockfd)
{
  perror("socket creation:");
  return -1;
}

struct sockaddr_un serv_addr = {0};
serv_addr.sun_family = AF_UNIX;
strncpy(serv_addr.sun_path, "socket_name1", sizeof(serv_addr.sun_path)- 1);

unlink("socket_name1");
if(-1 == bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_un)))
{
  perror("socket bind:");
  return -1;
}

#if 0
/* You cannot listen in udp server socket
*/
/* Listen marks the socket as a passive socket. It means this sockfd
   will be used to keep on listening for the client connections. 
*/
if(-1 == listen(sockfd,10 ))
{
  perror("socket listen:");
  return -1;
}
#endif

socklen_t len = sizeof(struct sockaddr_un);
if(-1 == recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&cli_addr, &len))
{
  perror("recvfrom:");
}
printf("\n %d \n", cli_addr.sun_family);
printf("\n %d \n", len);
printf("\n %s \n", cli_addr.sun_path);
printf("\n %s \n", buf);

if(-1 == sendto(sockfd, "sneha", 6, 0, (const struct sockaddr *)&cli_addr, len))
{
  perror("sendto:");
  return -1;
}

}
