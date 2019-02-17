
操作系统控制数据如何进出标准输入,标准输出.如果在命令提示符或终端运行程序,os会把所有键盘输入都发送到标准输入.默认情况下,如果os从标准输出中读到数据,就发送到显示器.
scanf和printf并不知道数据从哪里来,也不知道数据要到哪里去,它们只管从stdin读数据,向stdout写数据.
os使用stdin,stdout与程序交互的一个很好的原因是:这样就可以重定向stdin,stdout,让程序从键盘以外的地方读数据,往显示器以外的地方写数据,例如文件.

os创建进程时除了创建stdin,stdout,还会创建stderr.和stdout一样,stderr会默认发到显示器
创建标准错误的初衷是为了区普通输出和错误消息
printf是fprintf的特例.fprintf可以决定将文本发送到哪里.scanf()就是用fscanf(stdin, ...)实现的 scanf和fscanf的关系同理
不能打印stdin


设计小工具的原则:
1 从stdin读取数据
2 在stdout显示数据
3 处理文本数据,而不是二进制格式

os会管理管道的细节
两个独立的程序用管道连接以后就可以看成一个程序,可以重定向它的stdin和stdout:
(./bermuda | ./geo2json) < spook.csv > output.json

两个程序用管道相连后会同时运行,第一个程序一发出数据,第二个马上就可以处理.
当用管道连接多个进程时,<把文件内容发送到流水线中第一个进程的stdin,>捕获流水线中最后一个进程的stdout

```cpp
// ./rocket_to -e 4 -a Brasilia Tokyo London
while ((ch) = getopt(argc, argv, "ae:")) != EOF)
{
	switch(ch) {
		case
	}

}
// 选项必须在命令行参数之前出现
argc -= optind; //为了让程序读取命令行参数,需要调整一下argc和argc,跳过所有选项.然后argv会指向选项后的第一个命令行参数
argv += optind; // 最后argv数组变成这样: argv[0]--Brasilia argv[1]--Tokyo argv[2]--London

```

如何在参数中使用负数:可以用--隔开参数和选项,getopt看到--就会停止读取选项,程序会把后面的内容当成普通的命令行参数读取.

