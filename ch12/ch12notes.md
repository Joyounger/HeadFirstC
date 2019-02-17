
创建进程要花时间:如果想要执行的任务才用几十毫秒,每次都创建进程就很低效
进程共享数据不方便:如果子进程想把数据传回父进程,就需要借助管道之类


如何创建线程:使用多线程库
最流行的是POSIX线程库,也称pthread


互斥锁有时也叫锁,是把代码变为线程安全最简单的方法.
创建互斥锁:
pthread_mutex_t a_lock = PTHREAD_MUTEX_INITIALIZER;
互斥锁必须对所有可能冲突的线程可见,也就说它必须是一个全局变量
PTHREAD_MUTEX_INITIALIZER实际上是一个宏,当编译器看到它,就会插入创建互斥锁的代码

pthread_mutex_lock(&a_lock);
// 含有共享数据的代码从这里开始
...
// 结束
pthread_mutex_unlock(&a_lock);



