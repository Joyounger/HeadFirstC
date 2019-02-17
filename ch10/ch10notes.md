

重定向进程的输出,相当于改变进程发送数据的方向


进程会把文件描述符和对应的数据流保存在描述符表中

描述符表的一列是文件描述符号,另一列是它们对应的数据流.虽然名字叫文件描述符,但他们不一定连接硬盘上的某个文件,
也有可能连接键盘,屏幕,文件指针或网络.

描述符表的前3项万年不变:0号标准输入,1号标准输出,2号标准错误.其他项要么为空,要么连接进程打开的数据流.比如程序在打开文件进行读写时,就会占用其中一项


所有向标准输出发送数据的函数会先查看描述符表,看1号描述符指向哪条数据流,然后再把数据写到这条数据流中.printf便是如此


每打开一个文件,os都会在描述符表中新注册一项.假设你打开了某个文件,os会遍历描述符表寻找空项,把新文件注册在其中.
可根据文件指针知道对应的描述符:fileno()函数
每次打开文件都会使用描述符表中的一项,但如果想修改已经注册过的数据流,比如想让3号描述符重新指向其他数据流,可以用dup2()
假设在4号描述符中注册了A.mp3文件,dup2(4, 3)就能同时把它连接到3号描述符.虽然A.mp3只有一个,与它相连的数据流也只有一条,但这条数据流同时注册在了文件描述符3和4中


如何重用错误代码:
```cpp
pid_t pid = fork();
if (pid == -1) {
	fprintf(stderr, "无法运行脚本: %s\n", strerror(errno));
}


// 把处理代码放到一个单独的error函数中,然后把return语句换成exit系统调用
void error(char* msg)
{
	fprintf(stderr, "%s: %s\n", msg, stderror(errno));
	exit(1);  //使用exit系统调用必须包含 stdlib.h
}

//
pid_t pid = fork();
if (pid == -1) {
	error("无法克隆进程");
}

```


调用exit时不用检查返回值,exit是唯一没有返回值而且不会失败的函数

描述符表多大:0-255号

unix上除了stdout,打开/dev/tty文件也可以把数据直接发送到屏幕

可以用waitpid等待任何进程,不限于子进程



###### 用管道连接进程
在命令行用管道连接两条命令时,实际把它们当成了父子进程来连接
pytho rssgossip.py -u 'pajama death' | grep 'http'
grep命令是rssgossip.py的父进程
1 命令行创建了父进程
2 父进程在子进程中克隆出了rssgossip.py脚本
3 父进程用管道把子进程的输出连接到了自己的输入
4 父进程运行了grep命令


管道是否是文件取决于os创建操作系统的方式,通常用pipe创建的管道都不是文件
可以创建基于文件的管道,它们通常叫有名管道或FIFO文件.因为基于文件的管道有名字,所以两个进程只要知道管道的名字也能用它来通信,即使非父子进程
用mkfifo系统调用创建有名管道:http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/FIFO-Special-Files.html

如果不用文件实现管道,通常用存储器,数据写到存储器中的某个位置,然后再从另一个位置读取.
如果试图读取空的管道,程序会等待管道中出现东西
父进程如何知道子进程什么时候结束:子进程结束时,管道会关闭.
完全可以反向连接管道,让2数据从父进程发送到子进程
管道不能双向通信, 但可以创建两个管道,一个从父进程连接到子进程,一个从子进程链接到父进程j




 捕捉信号然后运行自己的代码:sigcation
 进程收到信号后会停止手头一切工作来处理信号
 sigcation是一个结构体,有一个函数指针
 struct sigcation actio;
 action.sa_handler = diedie; //想在收到信号时调用的函数,称为处理器
 sigemptyset(&action.sa_mask); // 用掩码过滤sigcation要处理的信号,通常会用一个空的掩码
 action.sa_flags = 0; // 一些附加标志位

处理器函数必须接收整形参数(信号是整形值)
void diedie(int sig)
{
 // 处理器函数中使用stdout,stdin要小心,之所以会有信号就是程序中发生了故障
}
多个信号可以公用一个处理器,处理器的实现应该短而快.

创建sigcation以后要用sigcation()注册:
sigcation(signal_no, &new_action, &old_action);
signal_no:要处理的信号,一般传SIGINT或SIGQUIT
new_action:要注册的sigcation的地址

int catch_signal(int sig, void (*handler)(int))
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction(sig, &action, NULL);

}
信号 | 引起的原因
SIGINT 进程被中断
SIGQUIT 有人要求停止进程,并把存储器中的内容保存到核心转储文件
SIGFPE 浮点错误
SIGTRAP 调试人员询问进程执行到了哪里
SIGSEGV 进程企图访问非法存储器地址
SIGWINCH 终端窗口的大小发生改变
SIGTERM 有人要求内核终止进程
SIGPIPE 进程在向一个没有人读的管道写数据

如果中断信号的处理器不调用exit,程序不会结束

即使程序中有一个错误导致进程对任何其他信号都视而不见,还是能用kill -KILL结束该进程. SIGSTOP也无法忽略,它可以用来暂停进程


想让程序向自己发送信号,用raise().通常会在自定义的信号处理函数中使用raise,这样程序能在接收到低级别的信号时引发高级别的信号.这叫信号升级

有时进程需要产生自己的信号,如闹钟信号SIGALARM,通常由进程的间隔定时器创建.间隔定时器就像一台闹钟:可以定一个时间,其间程序就会去做其他事情:
进程在收到SIGALARM后默认是结束进程
catch_signal(SIGALARM, pour_coffee);
alarm(120); // 计时器会在后台运行,120s以后定时器发出SIGALARM信号
do_important_busy_work(); //期间代码做其他事
SIGALARM可实现多任务,如果需要每隔几秒运行一个任务,或者想限制花费在某个任务上的时间,就可以用SIGALARM让程序打断自己
同时使用alarm和sleep会发生冲突


还原默认的信号处理器:
signal.h中有一个符号SIG_DFL,代表以默认方式处理信号
catch_signal(SIGTERM, SIG_DFL);
还可以用SIG_IGN让进程忽略某个信号


可以把alarm的参数定在几分之一秒,但很复杂,需要用另一个函数setitimer,它可以把进程间隔计时器的单位设为几分之一秒:http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Setting-an-Alarm.html

一个进程只有一个定时器:定时器由内核管理,如果一个进程有很多定时器内核会变得很慢.
每次调用alarm都会重置定时器.就是如如果把闹钟调到10秒,过一会又把它设为10分钟,那么闹钟信号19分钟后才会触发,第一个10s计时就失效了

如果两个信号发送间隔时间很短,程序就不会按顺序接收,os会先发送它认为更重要的信号

linux和mac中如果一个信号在很短时间发送了两次,内核只会发送其中的一个

