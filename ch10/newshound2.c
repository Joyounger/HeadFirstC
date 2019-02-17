#include <stdlio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// newsound2启用独立的进程 运行py脚本,rssgossip.py还没完成任务父进程就技术了,因此stories.txt还是空的


void error(char* msg)
{
	fprintf(stderr, "%s: %s\n", msg, stderror(errno));
	exit(1);  //使用exit系统调用必须包含 stdlib.h
}

int main(int argc, char* argv[])
{
	char* phrase = argv[1];
	char* vars[] = {"RSS_FEED=http://wwww.cnn.com/rss/celebs.xml", NULL};
	FILE *f = fopen("stories.txt", "w");

	if (!f) {
		eror("Can't open stories.txt");
	}

	pid_t pid = fork();
	if (pid == -1) {
		error("Can't fork process");
	}

	if(!pid) {
		if (dup2(fileno(f), 1) == -1) {
			error("Can't redirect Standard Output");
		}
		if (execle("/usr/bin/python", "/usr/bin/python", "./rssgossip.py", phrase. NULL, vars) == -1) {
			error("Can't run script");
		}
	}

	return 0;
}


// waitpid()会等子进程结束以后才返回
// 可以在程序中加几行代码,让它等到rssgossip.py运行结束后才退出
// 下面代码加到newsound2底部
#include <sys/wait.h>

int pid_status; //pid_status用来保存进程的退出信息
if (waitpid(oid, &pid_status, 0) == -1) //waitpid结束等待时会在pid_status中保存一个值.
{
	error("等待子进程时发生了错误")
}

if (WEXITSTATUS(pid_status)) //pid_status的前8位保存退出状态,其他信息保存在剩余位中
{
	error("Error status non-zero")
}
return 0;


