
如果一个结构包含一个链向同种结构的链接,那么这个结构就被称为递归结构

递归结构中需要包含一个相同类型的指针,C的语法不允许用typedef别名来声明它,因此必须为结构起一个名字.


strdup()函数可以把字符串复制到堆上.strdup计算出字符串长度,然后调用malloc在堆上分配相应的空间.
也就是说strdup总是在堆上创建空间,所以要记得用free释放
```cpp
island* create(char* name)
{
	island *i = malloc(sizeof(island));
	i->name = strdup(name);
}

void release(island *start)
{
	island *i = start;
	island *next = NULL;
	for (; i != NULLl i = next) {
		next = i->nexxt;
		free(i->name); //需要释放用strdup创建的name字符串
		free(i); // 如果先释放了island,就再也找不到name去释放了
	}
}
```


valgrind通过伪造malloc可以监控分配在堆上的数据.当程序想分配堆时,valgrind将会拦截你对mallo和free的调用,然后运行自己的malloc和free.
valgrind的malloc会记录调用它的是哪段代码和分配了哪段存储器.