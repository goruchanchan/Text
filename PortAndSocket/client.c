#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
  struct sockaddr_in server;
  int sock;
  char buf[32];
  int n;

  /* ソケットの作成 */
  sock = socket(AF_INET, SOCK_STREAM,0);

  /* 接続先指定用の構造体の準備 */
  server.sin_family = AF_INET;//IPv4を利用する
  server.sin_port = htons(11111);
  server.sin_len = sizeof(server); /* Linuxでは不要 */

  /* 127.0.0.1はlocalhost */
  inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

  /* sockaddr_in構造体の長さを設定（Linuxでは不要）*/
  server.sin_len = sizeof(server);

  /* サーバに接続 */
  if(connect(sock, (struct sockaddr *)&server, sizeof(server))!=0)
  {
    perror("connect");
    return 1;
  }

  /* サーバからデータを受信 */
  memset(buf,0,sizeof(buf));
  n = read(sock,buf,sizeof(buf));

  printf("%d,%s\n",n,buf);

  /* socketの終了 */
  close(sock);

  return 0;
}
