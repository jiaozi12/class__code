#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

int main() {
	int process_1,process_2;
	process_1 = fork(); //�����̴����ӽ���1 
	if(process_1 == 0) {
		//�ӽ���1 
		printf("Process PID %d :c\n",getpid()); 
	}
	else {
		process_2 = fork(); //�����̴����ӽ���2 
		if(process_2 == 0) {
			//�ӽ���2 
			printf("Process PID %d :b\n",getpid()); 
		}
		else {
			//������ 
			printf("Process PID %d :a\n",getpid());
		}
	}
	return 0;
}


