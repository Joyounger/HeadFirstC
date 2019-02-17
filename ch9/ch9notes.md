﻿
调用system时,os必须解释命令字符串,然后决定运行哪些程序和怎样运行,但这容易出错.
要解决这个问题必须消除歧义,明确告诉os想运行哪个程序,这就是exec函数的好处

exec()通过运行其他程序来替换当前进程,新进程启动后pid和老程序一样
exec()的版本可分为两组:
1 列表函数:execl,execlp,execle
列表函数以参数列表形式接收命令行参数:
程序:第一个参数告诉exec将运行什么程序.对execl或execle,是程序的完整路径名.对execlp是命令名字,execlp会根据它去查找程序.
命令行参数:需要一次列出想使用的命令行参数,第一个命令行参数必须是程序名,因此列表版exec的前两个参数是相同字符串
NULL:要在最后一个命令行参数后加上NULL
环境变量(如果有的话):如果调用了以...e结尾的exec函数,还可以传递环境变量数组,
2 数组函数:execv,execvp,execve
如果已经把命令行参数保存在了数组中,这个版本用起来更容易:
execv("/home/flynn/clu", my_args); //参数需要保存在字符串数组my_args中
execvp("clu", my_args);


传递环境变量:
c程序可以用getenv系统调用读取环境变量
用命令行参数和环境变量运行程序:
```cpp
// 可以用字符串数组的形式创建一组环境变量,数组最后一项必须是NULL
// 环境变量的格式是"变量名=值"
char *my_env[] = {"JUICE=peach and apple", NULL};
execle("diner_info", "diner_info", "4", NULL, my_env); //my env里放的是环境变量
```


exec是程序中最后一行代码:exec用过运行新程序来替换当前程序,原来的程序会立刻终止


为了让fork进程变快,os使用了很多技巧.os不会真的复制父进程的数据,而是让父子进程共享数据.
但如果os发现子进程要修改存储器,就会为它复制一份.这种技术称为"写时复制"(copy-on-write)
