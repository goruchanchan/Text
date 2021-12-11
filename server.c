#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

int main(void)
{
  struct sockaddr_in addr,client;
  socklen_t len;
  int sock0,sock1,sock2;

  /* ソケットの作成 */
  sock0 = socket(AF_INET, SOCK_STREAM,0);

  /*** ソケットの設定 ***/

  /* 接続先指定用の構造体の準備 */
  addr.sin_family = AF_INET;//IPv4を利用する
  addr.sin_port = htons(11111);
  
  addr.sin_addr.s_addr = INADDR_ANY; /* 任意のインタフェースを指定 */
  addr.sin_len = sizeof(addr); /* Linuxでは不要 */

  bind(sock0, (struct sockaddr *)&addr,sizeof(addr));/* ソケットをインタフェースとポートに割り付け */

  listen(sock0,5);/* TCPクライアントからの接続要求を待てる状態にする */

  /* TCPクライアントからの接続要求を待ち受ける（１回目） */
  len = sizeof(client);
  sock1 = accept(sock0,(struct sockaddr *)&client,& len);

  write(sock1, "HELLO", 6);/* ６文字送信('H','E','L','L','O','\0') */
  close(sock1); /* TCPセッション１の終了 */

  /* TCPクライアントからの接続要求を待ち受ける（１回目） */
  len = sizeof(client);
  sock2 = accept(sock0,(struct sockaddr *)&client,& len);

  write(sock2, "HOGE", 5);/* 5文字送信('H','O','G','E','\0') */
  close(sock2); /* TCPセッション2の終了 */

  /* socketの終了 */
  close(sock0);

  return 0;
}
