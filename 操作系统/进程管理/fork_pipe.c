#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
int flag;
void stop() {
	flag = 0;
}
void waiting() {
	while(flag) {
		;
	}
}

int main() {
	int process_1,process_2;
	int fd[2];
	char Parent_Message[64],Child_Message[64];
	pipe(fd); //�����ܵ� 
	process_1 = fork();
	if(process_1 < 0) {
		printf("Child Process1 created failed\n");
		exit(-1);
	}
	else if(process_1 == 0) {
		//�ӽ���1��ܵ�д���� 
		flag = 1;
		signal(SIGUSR1,stop);
		//signal(SIGQUIT,SIG_IGN);
		waiting();
		lockf(fd[1],1,0);
		sprintf(Child_Message,"Child 1 is sending a message!");
		write(fd[1],Child_Message,sizeof(Child_Message));
		lockf(fd[1],0,0);
		exit(0);
	}
	else {
		process_2 = fork();
		if(process_2 < 0) {
			printf("Child Process2 created failed\n");
			exit(-1);
		}
		else if(process_2 == 0) {
			//�ӽ���2��ܵ�д���� 
			flag = 1;
			signal(SIGUSR2,stop);
			//signal(SIGINT,SIG_IGN);
			waiting();
			sleep(1);
			lockf(fd[1],1,0);
			sprintf(Child_Message,"Child 2 is sending a message!");
			write(fd[1],Child_Message,sizeof(Child_Message));
			lockf(fd[1],0,0);
			exit(0);
		}
		else {
			kill(process_1,SIGUSR1);
			wait(0); //�ȴ��ӽ���1���� 
			read(fd[0],Parent_Message,sizeof(Parent_Message)); //�����̴ӹܵ��ж��ӽ���1������ 
			printf("%s\n",Parent_Message);
			kill(process_2,SIGUSR2);
			wait(0);
			read(fd[0],Parent_Message,sizeof(Parent_Message));//�����̴ӹܵ��ж��ӽ���2������ 
			printf("%s\n",Parent_Message);
			exit(0);
		}
	}
	return 0;
}
