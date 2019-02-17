
int main(int argc, char const *argv[])
{
	char* advice[] = {
		"Take smaller bites\r\n",
		"go for the tight jeans. No they do NOT make you look fat.\r\n",
		"One word: inappropriate\r\n",
		"Just for today, be honest. Tell your boss what you *really* think\r\n",
		"You might want to rethink that haircut\r\n"
	};
	int listener_d = socket(PF_INET. SOCK_STREAM, 0);

	struct sockaddr name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(listener_d, (struct sockaddr *)&name, sizeof(name));
	listen(listener_d, 10); //最多可以有10个客户端同时尝试连接服务器,它们不会立刻得到相应,但可以排队等待,而第11个客户端会被告知服务器太忙
	puts("Waiting for connection");
	while(1) {
		struct sockaddr_storage client_addr;
		unsigned int address_size = sizeof(client_addr);
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size); //一旦绑定玩端口,设置完监听队列,唯一可以做的就是等待.
		char* msg = advice[rand() % 5];

		send(connect_d, msg, strlen(msg), 0);
		close(connect_d);
	}


	return 0;
}




