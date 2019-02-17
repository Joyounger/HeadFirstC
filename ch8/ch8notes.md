
/usr/local/inlcude一般用来放第三方库的头文件
/usr/inlcude一般用来放os的头文件



在多个C项目中共享头文件的方法:
1 把头文件放在标准目录中
2 include使用完整路径名
3 用完整路径 告诉编译器去哪找头文件
gcc -I/my_header_files ...

共享.o目标文件
1 用完整路径 告诉编译器去哪找.o目标文件
2 创建.o目标文件存档(.a格式:current ar archive)

可以用nm命令查看.a的内容,nm命令列出了存档中保存文件的名字


用存档命令ar创建存档:
ar会在存档中保存一批目标文件:
ar -rcs libhfsecurity.a(要创建的文件名) encrypt.o checksum.o
-r如果.a存在就更新它.
-c创建时不显示反馈信息
-s要在.a文件开头建立索引

所有.a文件名都是libXXX.a.  存档是静态库,所以要以lib开头

在库目录下保存.a:
1 把.a放在标砖目录中.如/usr/local/lib, 这里专门放本地自定义库
使用时这种情况可以用-l开关编译代码:
gcc test.c -lhfsecurity.a -o test
如果需要使用多个存档,可以设置多个-l选项.
2 把.a放在自定义目录
gcc test.c -L/my_lib -lhfsecurity -o test
用-L告诉编译器去自定义目录找.a



ar命令的存档格式在不同平台间差别不大,但存档中目标代码的格式在不同os中天差地别
at -t filename 会列出存档中的目标文件
.a不会像可执行文件那样把目标文件链接在一起,.a中的目标文件以独立文件形式保存在.a中
可以从.a中提取.o:
ar -x libhfsecurity.a encrypt.o



动态库:
动态库相比静态库,多了元信息.它是带有元信息的可重定位目标文件,os需要用这些信息把库连接到文件.
动态库由一个或多个.o文件创建,核心是一段目标代码
1 先创建目标文件
假设hfcal.h头文件在/includes中
gcc -I/includes -fPIC -c hfcal.c -o hfcal.o
-fPIC表示创建位置无关代码.有的os和cpu要用位置无关代码创建库,这样它们才能在运行时决定把代码加载到存储器的哪个位置.
事实上大多数os中都不需要加这个选择.
位置无关代码:就是无论计算机把它加载到存储器哪个位置都可以运行的代码.包括win在内的一些os在加载动态库时会使用一种叫存储器映射技术,也就是说所有代码其实都是位置无关的
2 
                        C:\hfcal.dll          win
gcc -shared hfcal.o -o  /libs/libhfcal.dll.a   win上的cygwin
                        /libs/libhfcal.so      unix
                        /libs/libhfcal.dylib   mac


-shared告诉gcc把.o转化为动态库.编译器创建动态库时会把库的名字保存在文件中.假设在linux中创建了一个叫libhfcal.so的库,那么libhfcal.so文件会记住它的库名叫hfcal.
也就是说一旦用某个名字编译了库,就不能再修改文件名了.如想重命名库就必须用新名字重新编译一次.

3 一旦创建了动态库,就可以像静态库那样使用它:
gcc -I/include -c ell.c -o ell.o
gcc ell.o -L/libs -lhfcal -o ell
尽管使用的命令和静态存档一模一样,但两者的编译的方式不同.因为库是动态的,
所以编译器不会在可执行文件中包含库代码,而是插入一段用来查找库的"占位符"代码,并在运行时链接库.

运行时:
mac:动态库的完整路径保存在可执行文件中
linux:linux和大部分unix中编译器只记录libhfcal,so库的文件名,而不会包含路径名.也就时说如果不把hfcal库保存到标准目录,程序就找不到它.(这是一种设计上的选择.如果不保存路径名,程序就可以使用不同版本的库,当需要开发新的库时,这种设计的好处就特别明显).
为解决这个问题,linux会检查保存在LD_LIBRARY_PATH中的附加目录.
因此只要把库目录添加到LD_LIBRARY_PATH中并export它.(如果动态库已经在标准目录中就不需要)


如果不同的程序使用相同的动态库,动态库会加载一次还是多次?
这取决于os.有的os会为每个进程加载一个动态库,有的则会共享动态库以节省存储器.






