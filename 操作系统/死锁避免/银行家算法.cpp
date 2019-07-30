#include <iostream>
#include <stdlib.h>
using namespace std;

#define m 4 //资源种类数
#define n 5 //进程数目 
bool Security_Algorithms(int Available[],int Allocation[][m],int Need[][m],int Security_List[]);
void Print_Information(int Allocation[][m],int Need[][m],int Available[]);

int main() {
	int Available[m];           //可用资源向量，每一个元素代表一类可利用的资源数目
	int Max[n][m];              //最大需求矩阵，Max[i][j]=K表示进程i需要第j类资源的最大数目为K个
	int Allocation[n][m]={0};   //分配矩阵，Allocation[i][j]=K表示进程i当前已分得第j类资源的数目为K个
	int Need[n][m];             //需求矩阵，Need[i][j]=K表示进程i还需要第j类资源数目为K个 
	int Request[m];             //请求向量，表示一个进程对m类资源的请求数量 
	bool Finish[n]={false};     //标志向量，用来表示进程是否已经执行
	int EXIT;
	for(int i=0;i<m;i++) {
		//可用资源向量初始化
		Available[i] = rand()%67;
	}
	//需求矩阵初始化 
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
		cout<<"进程编号："<<i+1<<'\t'<<"请求资源向量：";
		for(int j=0;j<m-1;j++) {
			cout<<Request[j]<<",";
		}
		cout<<Request[m-1]<<endl;
		if(i<0||i>n-1) {
			printf("进程编号只能是1-%d的整数\n",n);
			continue;
		}
		if(flag == m) {
			cout<<"进程资源请求序列不能全为0"<<endl;
			continue;
		}
		if(minus == 1) {
			cout<<"进程资源请求序列不能存在负数"<<endl;
			continue;
		}
		flag = 0;
		if(Finish[i]==true) {
			cout<<"该进程已经执行结束"<<endl;
			continue;
		}
		for(int j=0;j<m;j++) {
			if(Request[j]>Need[i][j]) {
				//请求资源大于进程执行需要资源，出错
				flag = 1;
				printf("第%d类资源请求数量大于进程%d对其的需求数量\n",j+1,i+1);
				break;
			}
			if(Request[j]>Available[j]) {
				//当前资源不够分配，该进程必须等待
				flag = 2;
				printf("第%d类资源不够满足进程%d，该进程必须等待\n",j+1,i+1); 
				break;
			}
		}
		if(flag == 0) {
			//系统试探着把资源分配给该进程
			for(int j=0;j<m;j++) {
				Available[j] = Available[j] - Request[j];
				Allocation[i][j] = Allocation[i][j] + Request[j];
				//Need[i][j] = Need[i][j] - Request[j];
			}
			int Security_List[n];
			if(Security_Algorithms(Available,Allocation,Need,Security_List)) {
				//可以得到安全序列
				cout<<"安全序列为：";
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
				//不能得到安全序列
				printf("不能分配给进程%d请求的资源，若分配会导致死锁\n",i+1);
				Print_Information(Allocation,Need,Available);
				for(int j=0;j<m;j++) {
					Available[j] = Available[j] + Request[j];
					Allocation[i][j] = Allocation[i][j] - Request[j];
					//Need[i][j] = Need[i][j] + Request[j];
				} 
			}
			//回收执行完进程的资源 
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
	//函数功能：安全性算法。若当前时刻可以得到进程的安全序列则返回true，否则返回false
	int Work[m];                    //表示系统可提供进程继续运行可利用资源数目
	bool Finish[n]={false};         //表示进程是否已经执行 
	int count=0;                    //计数器，记录安全序列中元素个数
	int cnt=0;                      //计数器，记录寻找能运行进程的次数 
	
	for(int i=0;i<m;i++) {
		Work[i] = Available[i]; 
	}
	while(true) {   
		int i;
		bool flag = true;
		for(int j=0;j<n;j++) {
			//寻找未执行的进程 
			flag = true; 
			for(int k=0;k<m;k++) {
				if(Need[j][k]>Work[k]+Allocation[j][k]) {
					//当前进程资源不够无法执行 
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
			//找到未执行且资源满足需求的进程
			Finish[i] = true;
			Security_List[count] = i; 
			count++;
			for(int j=0;j<m;j++) {
				Work[j] = Work[j] + Allocation[i][j];
			}
		}
		if(cnt==n) {
			if(count == n) {
				//找到一条安全序列
				return true;
			}
			else {
				//不存在安全序列
				return false;
			}
		}
		cnt = 0;
	}
}
void Print_Information(int Allocation[][m],int Need[][m],int Available[]) {
	//打印系统资源分配情况
	cout<<"***********************************************************"<<endl;
	cout<<"进程"<<'\t'<<"Allocation"<<'\t'<<"Need"<<'\t'<<'\t'<<"Available"<<endl;
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
