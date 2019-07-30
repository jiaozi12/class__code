#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int flag;
void waiting() {
	while(flag!=0);
	//flag不为0时候进行等待 
}
void stop() {
	flag = 0;
	//中断等待 
}

int main() {
	int process_1,process_2;
	process_1 = fork();
	if(process_1 < 0) {
		printf("Child Process1 created failed\n");
		exit(-1);
	}
	else if(process_1 == 0) {
		flag = 1;
		signal(SIGUSR1,stop); //当捕捉到父进程传送过来的（kill）信号，继续执行 
		signal(SIGINT,SIG_IGN); //屏蔽键盘信号 
		signal(SIGQUIT,SIG_IGN); //屏蔽中断信号 
		waiting();
		lockf(1,1,0);
		printf("Child Process1 is killed by parent!\n");
		lockf(1,0,0);
		exit(0);
	}
	else {
		process_2 = fork();
		if(process_2 < 0) {
			printf("Child Process2 created failed\n");
			exit(-1);
		}
		else if(process_2 == 0) {
			flag = 1;
			signal(SIGUSR2,stop);//当捕捉到父进程传送过来的（kill）信号，继续执行
			signal(SIGINT,SIG_IGN);//屏蔽键盘信号
			signal(SIGQUIT,SIG_IGN);//屏蔽中断信号 
			waiting();
			lockf(1,1,0);
			printf("Child Process2 is killed by parent!\n");
			lockf(1,0,0);
			exit(0);
		}
		else {
			flag = 1;
			signal(SIGINT,stop); //父进程捕捉到来自键盘的中断信号，继续向下执行 
			waiting();
			kill(process_1,SIGUSR1); //向子进程process_1发送中断信号 
			wait(0);
			kill(process_2,SIGUSR2); //向子进程process_2发送中断信号 
			wait(0);
			printf("Parent Process is killed!\n");
			exit(0);
		}
	}
	return 0;
}
