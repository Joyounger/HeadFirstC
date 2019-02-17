
###### 数集类型的大小

可以使用limits.h中的宏,宏的名字取自数据类型,INT,SHRT,LONG,CHAR,FLT,DBL
可以在后面加上_MAX或_MIN.如果想查看更具体的数据类型,还可以加上前缀U(代表unsigned),S(signed)或L(long)


###### C的自动化测试框架
AceUnit
shunit2:如果写的是命令行工具,shunit2允许创建shell脚本来测试



###### gcc

-Ofast : 会打开最高级别的优化
-Wall:因为一些历史原因,-Wall其实并不会显示所有的警告.
如果想显示所有警告必须加上-Wextra:-Wall -Wextra
如果需要遵循严格的编译,可以使用-Werror,表示把警告当错误,只要有一个警告就失败


###### 参考资料
实用C语言编程 Steve Oualline,列出了一些实用的C开发细节
C专家编程 Peter an der Linden
C语言参开手册 Samuel P. Harbison

C标准
pubs.opengroup.org/onlinepubs/9699919799/
www.cprogramming.com
www.crasseux.com/books/ctutorial
www.cppreference.com
