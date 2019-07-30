#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h>

int main() {
	int process_1,process_2;
	process_1 = fork();
	if(process_1 == 0) {
		int i;
		lockf(1,1,0); //对标准输出stdout进行互斥访问 
		for(i=0;i<100;i++) {
			printf("Process PID %d :I am the son %d\n",getpid(),i);
		}
		lockf(1,0,0);
	}
	else {
		process_2 = fork();
		if(process_2 == 0) {
			int j;
			lockf(1,1,0);
			for(j=0;j<100;j++) {
				printf("Process PID %d :I am the daughter %d\n",getpid(),j);
			}
			lockf(1,0,0);
		}
		else {
			printf("Process PID %d :I am the parent\n",getpid());
		}
	}
	return 0;
}
