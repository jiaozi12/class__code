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
	//flag��Ϊ0ʱ����еȴ� 
}
void stop() {
	flag = 0;
	//�жϵȴ� 
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
		signal(SIGUSR1,stop); //����׽�������̴��͹����ģ�kill���źţ�����ִ�� 
		signal(SIGINT,SIG_IGN); //���μ����ź� 
		signal(SIGQUIT,SIG_IGN); //�����ж��ź� 
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
			signal(SIGUSR2,stop);//����׽�������̴��͹����ģ�kill���źţ�����ִ��
			signal(SIGINT,SIG_IGN);//���μ����ź�
			signal(SIGQUIT,SIG_IGN);//�����ж��ź� 
			waiting();
			lockf(1,1,0);
			printf("Child Process2 is killed by parent!\n");
			lockf(1,0,0);
			exit(0);
		}
		else {
			flag = 1;
			signal(SIGINT,stop); //�����̲�׽�����Լ��̵��ж��źţ���������ִ�� 
			waiting();
			kill(process_1,SIGUSR1); //���ӽ���process_1�����ж��ź� 
			wait(0);
			kill(process_2,SIGUSR2); //���ӽ���process_2�����ж��ź� 
			wait(0);
			printf("Parent Process is killed!\n");
			exit(0);
		}
	}
	return 0;
}
