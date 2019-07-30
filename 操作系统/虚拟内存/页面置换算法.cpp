#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
using namespace std;

#define Physical_block_number 3	                        //物理块数 
#define Visit_list_length 30                            //访问序列长度 
#define Page_number 5                                   //页面个数 
#define MAX 20000000									//定义一个较大数 

void OPT(int Visit_list[],int &Interruption_times,int &Substitution_times);
void FIFO(int Visit_list[],int &Interruption_times,int &Substitution_times);
void LRU(int Visit_list[],int &Interruption_times,int &Substitution_times);
bool Exist(int Physical_block[],int Visit);
void Print(int remind_physical_block[][Physical_block_number],int cnt);

int main() {
	int Visit_list[Visit_list_length];                  //访问序列 
	int Interruption_times = 0;                         //中断次数
	int Substitution_times = 0;                         //置换次数
	cout<<"访问序列：";
	for(int i=0;i<Visit_list_length;i++) {
		//随机生成页面访问序列
		Visit_list[i] = rand() % Page_number;
		cout<<Visit_list[i]<<" ";
	} 
	cout<<endl;
	OPT(Visit_list,Interruption_times,Substitution_times);
	printf("OPT算法缺页中断次数： %d        页面置换次数：%d        缺页率：%lf\n",Interruption_times,Substitution_times,(double)Interruption_times/(double)Visit_list_length);
	cout<<endl<<endl;
	FIFO(Visit_list,Interruption_times,Substitution_times);
	printf("FIFO算法缺页中断次数：%d        页面置换次数：%d       缺页率：%lf\n",Interruption_times,Substitution_times,(double)Interruption_times/(double)Visit_list_length);
	cout<<endl<<endl;
	LRU(Visit_list,Interruption_times,Substitution_times);
	printf("LRU算法缺页中断次数： %d        页面置换次数：%d       缺页率：%lf\n",Interruption_times,Substitution_times,(double)Interruption_times/(double)Visit_list_length);
	return 0; 
} 

void OPT(int Visit_list[],int &Interruption_times,int &Substitution_times) {
	int Physical_block[Physical_block_number] = {-1};   //物理块,-1表示为空 
	int remind_physical_block[Visit_list_length][Physical_block_number];    //记录物理块内容，用于输出置换过程 
	int Page_count[Physical_block_number];              //页面计数器，记录物理块中当前页面下一次出现距现在的时机 
	int p = 0;                                          //Physical_block下标，表示要被置换的物理块
	bool full = false;                                  //满标志，当物理块都被页面占据时full为true，反之为false 
	Substitution_times = 0;
	int cnt = 0;                                        //记录发生中断的次数 
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
				//当前物理块中没有需要访问的页面，需要置换
				bool found[Physical_block_number] = {false}; //若物理块中的页面已经在访问序列中找到了，则相应的found置为true，反之为false 
				for(int j=0;j<Physical_block_number;j++) {
					//寻找每个物理块中当前页面下一次出现的时机
					for(int k=i+1;k<Visit_list_length;k++) {
						if(Visit_list[k] == Physical_block[j] && !found[j]) {
							Page_count[j] = k;
							found[j] = true;
						} 
					}
				}
				//找到最晚需要访问的页面 
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
	int Physical_block[Physical_block_number] = {-1};   //物理块,-1表示为空
	int remind_physical_block[Visit_list_length][Physical_block_number];    //记录物理块内容，用于输出置换过程 
	int q = 0;
	int p = 0;                                          //物理块指针，物理块满后总是指向最先进入物理块的页面
	bool full = false;                                  //满标志，当物理块都被页面占据时full为true，反之为false
	int cnt = 0;                                        //记录发生中断的次数 
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
				//当前物理块中没有需要访问的页面，需要置换
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
	int Physical_block[Physical_block_number] = {-1};   //物理块,-1表示为空
	int remind_physical_block[Visit_list_length][Physical_block_number];    //记录物理块内容，用于输出置换过程 
	bool full = false;                                  //满标志，当物理块都被页面占据时full为true，反之为false
	int cnt = 0;                                        //记录发生中断的次数 
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
				//当前物理块中没有需要访问的页面，需要置换
				bool recent[Physical_block_number] = {false}; //用于标识最近访问的页面
				bool found[Physical_block_number] = {false};  //用于标识该物理块内的页面已经在页面访问序列中找到，找到为true，否则为false 
				int count = 0;                                //计数器，用于记录在页面请求序列中找到的最近最久未使用的页面数量 
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
						//找到最近最久未使用的页面，将其置换出去 
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
	//函数功能：判断当前物理块中是否有访问的页面。有则返回true，无需置换，否则返回false，需要置换
	for(int j=0;j<Physical_block_number;j++) {
		//当前物理块中有需要访问的页面，无需置换
		if(Visit == Physical_block[j]) return true;
	}
	return false;
}

void Print(int remind_physical_block[][Physical_block_number],int cnt) {
	//输出每次的页面置换情况 
	for(int i=0;i<Physical_block_number;i++) {
		for(int j=0;j<cnt;j++) {
			if(remind_physical_block[j][i]==-1) cout<<'N'<<"  "; 
			else cout<<remind_physical_block[j][i]<<"  ";
		}
		cout<<endl;
	}
	return;
}
