#include <stdlio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

// gcc argument.c -lpthread -o argument

void error(char* msg)
{
	fprintf(stderr, "%s: %s\n", msg, stderror(errno));
	exit(1);  //使用exit系统调用必须包含 stdlib.h
}


void* does_not(void *a)
{
	int i = 0;
	for (i = 0; i < 5; i++) {
		sleep(i);
		puts("Does not!");
	}

	return NULL;
}

void* does_too(void *a)
{
	int i = 0;
	for (i = 0; i < 5; i++) {
		sleep(i);
		puts("Does too!");
	}

	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t t0; //保存线程所有信息的数据结构
	pthread_t t1;
	if(pthread_create(&t0, NULL, does_not, NULL) == -1) {
		error("无法创建线程t0")
	}
	if(pthread_create(&t1, NULL, does_too, NULL) == -1) {
		error("无法创建线程t1")
	}
	//如果程序运行完这段代码就结束了,则线程也会随之灭亡

    void* result; // does_not, does_too函数返回的void指针会保存在这里
    if(pthread_join(t0, &result) == -1) // pthread_join会等待线程结束,接收线程函数的返回值.
    	error("无法收回线程t0")
    if(pthread_join(t1, &result) == -1)
    	error("无法收回线程t1")



	return 0;
}

