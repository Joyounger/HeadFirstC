
函数名是L-value, 在存储器中不分配变量

C中没有函数类型
一旦声明了函数指针变量,就可以像其他变量一样使用它:
返回类型 (* 指针变量)(参数类型)



创建函数指针数组:
```cpp
void (*replies[])(response) = { dump, second_chance, marriage };

int main()
{
	response r[] = {
		{"Mike", DUMP}, {"Luis", SECOND_CHANCE},
		{"Matt", SECOND_CHANCE}, {"Wialliam", MARRIAGE}
	};
	int i;
	for (i = 0; i < 4; i++) {
		(replies[r[i].type])(r[i]) // 
	}
}
```

如果需要在程序中多次调用回复函数,当决定添加新的回复类型和函数时,只需要把它加到数组中即可:
enum response_type {DUMP, SECOND_CHANCE, MARRIAGE, LAW_SUIT};
void (*replies[])(response) = {dump, second_chance, marriage, law_suit};
可变参数
```cpp
#include <stdarg.h>

void print_ints(int args, ...) //c中函数后面的省略号表示还有更多参数
{
	va_list ap;  //创建va_list va_list用来保存传给函数的其他参数
	va_start(ap, args); // 说明可变参数从哪开始,需要把最后一个普通参数的名字告诉c
	int i;
	for (i = 0; i < args; i++) { // 逐一读取可变参数: 参数现在全保存在va_list中,可以用va_arg读取. va_arg接收va_list和要读取参数的类型
		printf("argument: %i\n", va_arg(ap, int));
	}
	va_end(ap); //最后销毁va_list
}

print_ints(3, 79, 101, 32);
```
不能只使用可变参数,至少需要一个普通参数.
如果从va_arg中读取比传给函数更多的参数,后者以double或其他类型读取, 都会发生不确定的错误.
