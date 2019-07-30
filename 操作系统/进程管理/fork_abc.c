#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

int main() {
	int process_1,process_2;
	process_1 = fork(); //父进程创建子进程1 
	if(process_1 == 0) {
		//子进程1 
		printf("Process PID %d :c\n",getpid()); 
	}
	else {
		process_2 = fork(); //父进程创建子进程2 
		if(process_2 == 0) {
			//子进程2 
			printf("Process PID %d :b\n",getpid()); 
		}
		else {
			//父进程 
			printf("Process PID %d :a\n",getpid());
		}
	}
	return 0;
}


