#include <iostream>
#include <stdlib.h>
using namespace std;

#define m 4 //��Դ������
#define n 5 //������Ŀ 
bool Security_Algorithms(int Available[],int Allocation[][m],int Need[][m],int Security_List[]);
void Print_Information(int Allocation[][m],int Need[][m],int Available[]);

int main() {
	int Available[m];           //������Դ������ÿһ��Ԫ�ش���һ������õ���Դ��Ŀ
	int Max[n][m];              //����������Max[i][j]=K��ʾ����i��Ҫ��j����Դ�������ĿΪK��
	int Allocation[n][m]={0};   //�������Allocation[i][j]=K��ʾ����i��ǰ�ѷֵõ�j����Դ����ĿΪK��
	int Need[n][m];             //�������Need[i][j]=K��ʾ����i����Ҫ��j����Դ��ĿΪK�� 
	int Request[m];             //������������ʾһ�����̶�m����Դ���������� 
	bool Finish[n]={false};     //��־������������ʾ�����Ƿ��Ѿ�ִ��
	int EXIT;
	for(int i=0;i<m;i++) {
		//������Դ������ʼ��
		Available[i] = rand()%67;
	}
	//��������ʼ�� 
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			Need[i][j] = rand()%38;
		}
	}
	Print_Information(Allocation,Need,Available);
	while(scanf("%d",&EXIT)) {
		int i,flag=0,minus=0;
		i = rand() % 5;
		for(int j=0;j<m;j++) {
			Request[j] = rand()%10;
			if(Request[j]==0) {
				flag++;
			}
			if(Request[j]<0) {
				minus = 1;
			}
		} 
		cout<<"���̱�ţ�"<<i+1<<'\t'<<"������Դ������";
		for(int j=0;j<m-1;j++) {
			cout<<Request[j]<<",";
		}
		cout<<Request[m-1]<<endl;
		if(i<0||i>n-1) {
			printf("���̱��ֻ����1-%d������\n",n);
			continue;
		}
		if(flag == m) {
			cout<<"������Դ�������в���ȫΪ0"<<endl;
			continue;
		}
		if(minus == 1) {
			cout<<"������Դ�������в��ܴ��ڸ���"<<endl;
			continue;
		}
		flag = 0;
		if(Finish[i]==true) {
			cout<<"�ý����Ѿ�ִ�н���"<<endl;
			continue;
		}
		for(int j=0;j<m;j++) {
			if(Request[j]>Need[i][j]) {
				//������Դ���ڽ���ִ����Ҫ��Դ������
				flag = 1;
				printf("��%d����Դ�����������ڽ���%d�������������\n",j+1,i+1);
				break;
			}
			if(Request[j]>Available[j]) {
				//��ǰ��Դ�������䣬�ý��̱���ȴ�
				flag = 2;
				printf("��%d����Դ�����������%d���ý��̱���ȴ�\n",j+1,i+1); 
				break;
			}
		}
		if(flag == 0) {
			//ϵͳ��̽�Ű���Դ������ý���
			for(int j=0;j<m;j++) {
				Available[j] = Available[j] - Request[j];
				Allocation[i][j] = Allocation[i][j] + Request[j];
				//Need[i][j] = Need[i][j] - Request[j];
			}
			int Security_List[n];
			if(Security_Algorithms(Available,Allocation,Need,Security_List)) {
				//���Եõ���ȫ����
				cout<<"��ȫ����Ϊ��";
				for(int j=0;j<n-1;j++) {
					cout<<Security_List[j]+1<<",";
				}
				cout<<Security_List[n-1]+1<<endl;
				for(int j=0;j<m;j++) {
					Need[i][j] = Need[i][j] - Request[j];
				}
				Print_Information(Allocation,Need,Available);
			}
			else {
				//���ܵõ���ȫ����
				printf("���ܷ��������%d�������Դ��������ᵼ������\n",i+1);
				Print_Information(Allocation,Need,Available);
				for(int j=0;j<m;j++) {
					Available[j] = Available[j] + Request[j];
					Allocation[i][j] = Allocation[i][j] - Request[j];
					//Need[i][j] = Need[i][j] + Request[j];
				} 
			}
			//����ִ������̵���Դ 
			for(int j=0;j<n;j++) {
				bool s=true;
				for(int k=0;k<m;k++) {
					if(Allocation[j][k]!=Need[j][k]) {
						s=false;
						break;
					}
				}
				if(s) {
					for(int k=0;k<m;k++) {
						Available[k] += Allocation[j][k];
						Allocation[j][k] = 0;
						Need[j][k] = 0;
					}
				}
			}
		}
	}
	return 0;
} 

bool Security_Algorithms(int Available[],int Allocation[][m],int Need[][m],int Security_List[]) {
	//�������ܣ���ȫ���㷨������ǰʱ�̿��Եõ����̵İ�ȫ�����򷵻�true�����򷵻�false
	int Work[m];                    //��ʾϵͳ���ṩ���̼������п�������Դ��Ŀ
	bool Finish[n]={false};         //��ʾ�����Ƿ��Ѿ�ִ�� 
	int count=0;                    //����������¼��ȫ������Ԫ�ظ���
	int cnt=0;                      //����������¼Ѱ�������н��̵Ĵ��� 
	
	for(int i=0;i<m;i++) {
		Work[i] = Available[i]; 
	}
	while(true) {   
		int i;
		bool flag = true;
		for(int j=0;j<n;j++) {
			//Ѱ��δִ�еĽ��� 
			flag = true; 
			for(int k=0;k<m;k++) {
				if(Need[j][k]>Work[k]+Allocation[j][k]) {
					//��ǰ������Դ�����޷�ִ�� 
					flag = false;
					break;
				}
			}
			if(!Finish[j] && flag) {
				i = j;
				break;
			}
			cnt++;
		} 
		if(Finish[i]==false && flag) {
			//�ҵ�δִ������Դ��������Ľ���
			Finish[i] = true;
			Security_List[count] = i; 
			count++;
			for(int j=0;j<m;j++) {
				Work[j] = Work[j] + Allocation[i][j];
			}
		}
		if(cnt==n) {
			if(count == n) {
				//�ҵ�һ����ȫ����
				return true;
			}
			else {
				//�����ڰ�ȫ����
				return false;
			}
		}
		cnt = 0;
	}
}
void Print_Information(int Allocation[][m],int Need[][m],int Available[]) {
	//��ӡϵͳ��Դ�������
	cout<<"***********************************************************"<<endl;
	cout<<"����"<<'\t'<<"Allocation"<<'\t'<<"Need"<<'\t'<<'\t'<<"Available"<<endl;
	for(int i=0;i<n;i++) {
		cout<<i+1<<'\t';
		for(int j=0;j<m-1;j++) {
			cout<<Allocation[i][j]<<",";
		}
		cout<<Allocation[i][m-1]<<"        "<<'\t';
		for(int j=0;j<m-1;j++) {
			cout<<Need[i][j]<<",";
		}
		cout<<Need[i][m-1]<<'\t';
		if(i==n/2) {
			for(int j=0;j<m-1;j++) {
				cout<<Available[j]<<",";
			}
			cout<<Available[m-1]<<endl;
		}
		else {
			cout<<endl;
		}
	}
	cout<<"***********************************************************"<<endl;
	return;
}
