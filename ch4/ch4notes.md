
浮点数前也可以用long
只有C99和C11支持long long


异或加密是以重很简单的加密方法,它将文本中的每个字符与某个值进行异或,虽然异或加密
很不安全,但易于操作,而且加解密使用同一段代码.
```cpp
void encrypt(char* message)
{
	char c;
	while (*message) {
		*message = *message ^31
		message++;
	}
}
```

makefile会调用底层os的命令,所以不能在其他os使用