#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>

#include<stdio.h>
#include<errno.h>

int main()
{

struct sockaddr_un cli_addr = {0};

int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
if(-1 == sockfd)
{
  perror("socket creation:");
  return -1;
}

struct sockaddr_un serv_addr;
memset(&serv_addr, 0, sizeof(struct sockaddr_un));

serv_addr.sun_family = AF_UNIX;
strncpy(serv_addr.sun_path, "socket_name1", sizeof(serv_addr.sun_path)- 1);

char buf[100] = "JAI HANUMAN :) ANJANEYA";
socklen_t len =  sizeof(struct sockaddr_un);



/************************************************************************ Needed for bidirectional *************************************************************/
/*  if you dint bind the socket to a client address,
    then recvfrom in server.c will not receive the client address
    in recvfrom() API. This bind API in the client side is requited 
    for bidirectional use case.  
*/
struct sockaddr_un addr; //this is cli address
memset(&addr, 0, sizeof(struct sockaddr_un));
addr.sun_family = AF_UNIX;
strncpy(addr.sun_path, "socket_client", sizeof(addr.sun_path)- 1);
unlink("socket_client");
if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
{
  perror("bind");
}
/************************************************************************ Needed for bidirectional *************************************************************/

// You cannot use send/read because it doesnot know to which address it should send
//if u wish to use send and recv call instead of sendto and recvfrom in client.c, then u need to use connect system call.
//connect(sockfd, &serv_addr, len);
if(-1 == sendto(sockfd, buf, 100, 0,(const struct sockaddr *)&serv_addr, len))
{
  perror("write:");
  return -1;
}


if(-1 == recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&serv_addr, &len))
{
  perror("recvfrom:");
}
printf(" printing: %s", buf);

return 0;

}
