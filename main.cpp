#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#include <fstream>

int main()
{
	std::cout << "Server started" << std::endl;
	// ソケットを作成。返り値はint.通信のための端点を作成する。
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		std::cout << "create socket failed!" << std::endl;
	}

	// ソケットに対して、ポートなどの情報を設定する。構造体に入れる。
	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(49100);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// バインド!
	int status = bind(sockfd,(const sockaddr *)&sock_addr,sizeof(sock_addr));
	std::cout << status << std::endl;
	listen(sockfd, 1);

	unsigned int len = sizeof(sock_addr);
	int s = accept(sockfd, (struct sockaddr *)&sock_addr,&len);

	// パケットを受け取る。
	char buf[1024*1024];
	std::cout << "count" + len << std::endl;
	int recv_status = recv(s, buf, sizeof(buf)-1, 0);
	std::cout << recv_status << std::endl;
	std::cout << buf << std::endl;
	close(sockfd);

	// 送られてきた内容をテキストファイルに書き込む。
	std::ofstream writing_file;
	std::string filename = "sample2.txt";
	writing_file.open(filename, std::ios::out);
	std::string writing_text = buf;
	writing_file << writing_text << std::endl;
	writing_file.close();
}