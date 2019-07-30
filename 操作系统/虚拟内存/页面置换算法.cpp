#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
using namespace std;

#define Physical_block_number 3	                        //������� 
#define Visit_list_length 30                            //�������г��� 
#define Page_number 5                                   //ҳ����� 
#define MAX 20000000									//����һ���ϴ��� 

void OPT(int Visit_list[],int &Interruption_times,int &Substitution_times);
void FIFO(int Visit_list[],int &Interruption_times,int &Substitution_times);
void LRU(int Visit_list[],int &Interruption_times,int &Substitution_times);
bool Exist(int Physical_block[],int Visit);
void Print(int remind_physical_block[][Physical_block_number],int cnt);

int main() {
	int Visit_list[Visit_list_length];                  //�������� 
	int Interruption_times = 0;                         //�жϴ���
	int Substitution_times = 0;                         //�û�����
	cout<<"�������У�";
	for(int i=0;i<Visit_list_length;i++) {
		//�������ҳ���������
		Visit_list[i] = rand() % Page_number;
		cout<<Visit_list[i]<<" ";
	} 
	cout<<endl;
	OPT(Visit_list,Interruption_times,Substitution_times);
	printf("OPT�㷨ȱҳ�жϴ����� %d        ҳ���û�������%d        ȱҳ�ʣ�%lf\n",Interruption_times,Substitution_times,(double)Interruption_times/(double)Visit_list_length);
	cout<<endl<<endl;
	FIFO(Visit_list,Interruption_times,Substitution_times);
	printf("FIFO�㷨ȱҳ�жϴ�����%d        ҳ���û�������%d       ȱҳ�ʣ�%lf\n",Interruption_times,Substitution_times,(double)Interruption_times/(double)Visit_list_length);
	cout<<endl<<endl;
	LRU(Visit_list,Interruption_times,Substitution_times);
	printf("LRU�㷨ȱҳ�жϴ����� %d        ҳ���û�������%d       ȱҳ�ʣ�%lf\n",Interruption_times,Substitution_times,(double)Interruption_times/(double)Visit_list_length);
	return 0; 
} 

void OPT(int Visit_list[],int &Interruption_times,int &Substitution_times) {
	int Physical_block[Physical_block_number] = {-1};   //�����,-1��ʾΪ�� 
	int remind_physical_block[Visit_list_length][Physical_block_number];    //��¼��������ݣ���������û����� 
	int Page_count[Physical_block_number];              //ҳ�����������¼������е�ǰҳ����һ�γ��־����ڵ�ʱ�� 
	int p = 0;                                          //Physical_block�±꣬��ʾҪ���û��������
	bool full = false;                                  //����־��������鶼��ҳ��ռ��ʱfullΪtrue����֮Ϊfalse 
	Substitution_times = 0;
	int cnt = 0;                                        //��¼�����жϵĴ��� 
	memset(remind_physical_block,-1,sizeof(remind_physical_block));
	for(int i=0;i<Visit_list_length;i++) {
		if(!full && !Exist(Physical_block,Visit_list[i])) {
			Physical_block[p] = Visit_list[i];
			remind_physical_block[cnt][p] =  Visit_list[i];
			p++;
			cnt++;
			for(int j=0;j<Physical_block_number;j++) remind_physical_block[cnt][j] = remind_physical_block[cnt-1][j];
			if(p == Physical_block_number) full = true;
		}
		else if(full) {
			for(int j=0;j<Physical_block_number;j++)  Page_count[j] = MAX + j;
			if(!Exist(Physical_block,Visit_list[i])) {
				//��ǰ�������û����Ҫ���ʵ�ҳ�棬��Ҫ�û�
				bool found[Physical_block_number] = {false}; //��������е�ҳ���Ѿ��ڷ����������ҵ��ˣ�����Ӧ��found��Ϊtrue����֮Ϊfalse 
				for(int j=0;j<Physical_block_number;j++) {
					//Ѱ��ÿ��������е�ǰҳ����һ�γ��ֵ�ʱ��
					for(int k=i+1;k<Visit_list_length;k++) {
						if(Visit_list[k] == Physical_block[j] && !found[j]) {
							Page_count[j] = k;
							found[j] = true;
						} 
					}
				}
				//�ҵ�������Ҫ���ʵ�ҳ�� 
				int max = Page_count[0],index = 0;
				for(int j=1;j<Physical_block_number;j++) {
					if(max < Page_count[j]) {
						max = Page_count[j];
						index = j;
					}
				}
				Physical_block[index] = Visit_list[i]; 
				remind_physical_block[cnt][index] =  Visit_list[i];
				cnt++;
				for(int j=0;j<Physical_block_number;j++) remind_physical_block[cnt][j] = remind_physical_block[cnt-1][j];
				Substitution_times++;
			} 
		}
		else ; 
	}
	Print(remind_physical_block,cnt);
	Interruption_times = Substitution_times + Physical_block_number;
	return;
}

void FIFO(int Visit_list[],int &Interruption_times,int &Substitution_times) {
	int Physical_block[Physical_block_number] = {-1};   //�����,-1��ʾΪ��
	int remind_physical_block[Visit_list_length][Physical_block_number];    //��¼��������ݣ���������û����� 
	int q = 0;
	int p = 0;                                          //�����ָ�룬�������������ָ�����Ƚ���������ҳ��
	bool full = false;                                  //����־��������鶼��ҳ��ռ��ʱfullΪtrue����֮Ϊfalse
	int cnt = 0;                                        //��¼�����жϵĴ��� 
	Substitution_times = 0;
	memset(remind_physical_block,-1,sizeof(remind_physical_block));
	for(int i=0;i<Visit_list_length;i++) {
		if(!full && !Exist(Physical_block,Visit_list[i])) {
			Physical_block[q] = Visit_list[i];
			remind_physical_block[cnt][q] =  Visit_list[i];
			cnt++;
			for(int j=0;j<Physical_block_number;j++) remind_physical_block[cnt][j] = remind_physical_block[cnt-1][j];
			q++;
			if(q == Physical_block_number) full = true;
		}
		else if(full) {
			if(!Exist(Physical_block,Visit_list[i])) {
				//��ǰ�������û����Ҫ���ʵ�ҳ�棬��Ҫ�û�
				Physical_block[p] = Visit_list[i];
				remind_physical_block[cnt][p] =  Visit_list[i];
				p++;
				cnt++;
				for(int j=0;j<Physical_block_number;j++) remind_physical_block[cnt][j] = remind_physical_block[cnt-1][j];
				p = p % Physical_block_number;
				Substitution_times++;
			}
		}
		else ;
	}
	Print(remind_physical_block,cnt); 
	Interruption_times = Substitution_times + Physical_block_number;
	return;
}

void LRU(int Visit_list[],int &Interruption_times,int &Substitution_times) {
	int Physical_block[Physical_block_number] = {-1};   //�����,-1��ʾΪ��
	int remind_physical_block[Visit_list_length][Physical_block_number];    //��¼��������ݣ���������û����� 
	bool full = false;                                  //����־��������鶼��ҳ��ռ��ʱfullΪtrue����֮Ϊfalse
	int cnt = 0;                                        //��¼�����жϵĴ��� 
	Substitution_times = 0;
	int q = 0;
	memset(remind_physical_block,-1,sizeof(remind_physical_block));
	for(int i=0;i<Visit_list_length;i++) {
		if(!full && !Exist(Physical_block,Visit_list[i])) {
			Physical_block[q] = Visit_list[i];
			remind_physical_block[cnt][q] =  Visit_list[i];
			cnt++;
			for(int j=0;j<Physical_block_number;j++) remind_physical_block[cnt][j] = remind_physical_block[cnt-1][j];
			q++;
			if(q == Physical_block_number) full = true;
		}
		else if(full){
			if(!Exist(Physical_block,Visit_list[i])) {
				//��ǰ�������û����Ҫ���ʵ�ҳ�棬��Ҫ�û�
				bool recent[Physical_block_number] = {false}; //���ڱ�ʶ������ʵ�ҳ��
				bool found[Physical_block_number] = {false};  //���ڱ�ʶ��������ڵ�ҳ���Ѿ���ҳ������������ҵ����ҵ�Ϊtrue������Ϊfalse 
				int count = 0;                                //�����������ڼ�¼��ҳ�������������ҵ���������δʹ�õ�ҳ������ 
				for(int j=i-1;j>=0;j--) {
					for(int k=0;k<Physical_block_number;k++) {
						if(Visit_list[j] == Physical_block[k] && !found[k]) {
							recent[k] = true;
							found[k] = true;
							count++;
						}
					}
					if(count == Physical_block_number - 1) break;
				} 
				for(int j=0;j<Physical_block_number;j++) {
					if(!recent[j]) {
						//�ҵ�������δʹ�õ�ҳ�棬�����û���ȥ 
						Physical_block[j] = Visit_list[i];
						remind_physical_block[cnt][j] =  Visit_list[i];
						cnt++;
						for(int j=0;j<Physical_block_number;j++) remind_physical_block[cnt][j] = remind_physical_block[cnt-1][j];
						Substitution_times++;
						break;
					}
				}
			}
		}
		else ;
	}
	Print(remind_physical_block,cnt);
	Interruption_times = Substitution_times + Physical_block_number;
	return;
}

bool Exist(int Physical_block[],int Visit) {
	//�������ܣ��жϵ�ǰ��������Ƿ��з��ʵ�ҳ�档���򷵻�true�������û������򷵻�false����Ҫ�û�
	for(int j=0;j<Physical_block_number;j++) {
		//��ǰ�����������Ҫ���ʵ�ҳ�棬�����û�
		if(Visit == Physical_block[j]) return true;
	}
	return false;
}

void Print(int remind_physical_block[][Physical_block_number],int cnt) {
	//���ÿ�ε�ҳ���û���� 
	for(int i=0;i<Physical_block_number;i++) {
		for(int j=0;j<cnt;j++) {
			if(remind_physical_block[j][i]==-1) cout<<'N'<<"  "; 
			else cout<<remind_physical_block[j][i]<<"  ";
		}
		cout<<endl;
	}
	return;
}
