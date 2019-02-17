

//通常希望把某个整形值传给线程,并让它返回某个整形值,一种方法是用long,因为它的大小和void指针相同,可以把它保存在void指针变量中
void* do_stuff(void* param)
{
	long thread_no = (long)param;
	printf("Thread number %ld\n", thread_no);
	return (void*)(thread_no + 1);
}


int main(int argc, char const *argv[])
{
	pthread_t threads[3];
	long t;
	for (t = 0; t < 3; t++) {
		pthread_create(&threads[t], NULL, do_stuff, (void *)t);
	}
	void* result;
	for (t = 0; t < 3; ++t)
	{
		pthread_join(threads[t], &result);
		printf("Thread %ld returned %ld\n", t, (long)result);
	}
	return 0;
}