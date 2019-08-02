#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#define MAXSIZE 100
#define people_number 10
using namespace std;

struct People {
	string name;
	string Student_ID;
	string Dormitory_Index;
	string key;
};


void Read_file(People people[]);//读取学生信息文件中的数据
void Sort(People people[],int);//排序（按姓名、学号、房号）
void Search(People people[]);//查询，按姓名、学号、房号查询 
void QSort(People people[],int ,int);//快速排序
int Partition(People people[],int low,int high);//交换数组people中子数组low~high的内容

int main() {
	//此程序测试数据有10组数据
	People people[MAXSIZE];
	Read_file(people);
	Search(people);
	return 0;
}

void Read_file(People people[]) {
	//读取学生信息文件中的数据
	ifstream inFile("学生信息.txt",ios::in);
	if(!inFile) {
		cout<<"读取学生信息.txt失败"<<endl;
		return;
	}
	else {
		string lineStr;
		int i=1;
		getline(inFile,lineStr);
		while(getline(inFile, lineStr)) {
        	// 按,分隔
        	stringstream ss(lineStr);
        	string str;
        	getline(ss, str, ',');
        	people[i].Student_ID=str;
        	getline(ss, str, ',');
        	people[i].name=str;
        	getline(ss, str, ',');
        	people[i].Dormitory_Index=str;
        	i++;
		}
	}
	inFile.close();
	return;
}

void Sort(People people[],int Sort_way) {
	//排序（按姓名、学号、房号）
	if(Sort_way==1) {
		ofstream outFile("name_up.txt",ios::in);
		if(!outFile) {
			cout<<"打开name_up.txt文件失败"<<endl;
			return;
		}
		else {
			outFile<<"学号"<<'\t'<<'\t'<<"姓名"<<'\t'<<"宿舍"<<endl;
			for(int i=1;i<=people_number;i++) {
				people[i].key=people[i].name;
			}
			QSort(people,1,people_number);
			for(int i=1;i<=people_number;i++) {
				outFile<<people[i].Student_ID<<'\t'<<people[i].name<<'\t'<<people[i].Dormitory_Index<<endl;
			}
		}
		outFile.close();
	}
	if(Sort_way==2) {
		ofstream outFile("Student_ID_up.txt",ios::in);
		if(!outFile) {
			cout<<"打开Student_ID_up.txt文件失败"<<endl;
			return;
		}
		else {
			outFile<<"学号"<<'\t'<<'\t'<<"姓名"<<'\t'<<"宿舍"<<endl;
			for(int i=1;i<=people_number;i++) {
				people[i].key=people[i].Student_ID;
			}
			QSort(people,1,people_number);
			for(int i=1;i<=people_number;i++) {
				outFile<<people[i].Student_ID<<'\t'<<people[i].name<<'\t'<<people[i].Dormitory_Index<<endl;
			}
		}
		outFile.close();
	}
	if(Sort_way==3) {
		ofstream outFile("Dormitory_Index_up.txt",ios::in);
		if(!outFile) {
			cout<<"Dormitory_Index_up.txt文件失败"<<endl;
			return;
		}
		else {
			outFile<<"学号"<<'\t'<<'\t'<<"姓名"<<'\t'<<"宿舍"<<endl;
			for(int i=1;i<=people_number;i++) {
				people[i].key=people[i].Dormitory_Index;
			}
			QSort(people,1,people_number);
			for(int i=1;i<=people_number;i++) {
				outFile<<people[i].Student_ID<<'\t'<<people[i].name<<'\t'<<people[i].Dormitory_Index<<endl;
			}
		}
		outFile.close();
	}
}

void Search(People people[]) {
	//查询，按姓名、学号、房号查询 
	cout<<"输入查询标准"<<endl;
	cout<<"1按姓名查询"<<endl;
	cout<<"2按学号查询"<<endl;
	cout<<"3按房号查询"<<endl;
	cout<<"-1结束程序"<<endl;
	int Search_way=0;
	while(true) {
		cin>>Search_way;
		if(Search_way==-1) {
			return;
		}
		Sort(people,Search_way);
		cout<<"输入查询关键字：";
		string key;
		cin>>key;
		int low=1,high=people_number,mid;
		bool sign=false;
		while(low<high) {
			if(key==people[people_number].key) {
				cout<<"学号"<<'\t'<<'\t'<<"姓名"<<'\t'<<'\t'<<"宿舍号"<<endl;
				cout<<people[people_number].Student_ID<<'\t'<<people[people_number].name<<'\t'<<'\t'<<people[people_number].Dormitory_Index<<endl;
				sign=true;
				break; 
			}
			if(key==people[1].key) {
				cout<<"学号"<<'\t'<<'\t'<<"姓名"<<'\t'<<'\t'<<"宿舍号"<<endl;
				cout<<people[1].Student_ID<<'\t'<<people[1].name<<'\t'<<'\t'<<people[1].Dormitory_Index<<endl;
				sign=true;
				break; 
			}
			if(low==high-1&&key!=people[high].key) {
				break;
			}
			mid=(low+high)/2;
			if(key<people[mid].key) {
				high=mid;
			}
			if(key>people[mid].key) {
				low=mid;
			}
			if(key==people[mid].key) {
				cout<<"学号"<<'\t'<<'\t'<<"姓名"<<'\t'<<'\t'<<"宿舍号"<<endl;
				cout<<people[mid].Student_ID<<'\t'<<people[mid].name<<'\t'<<'\t'<<people[mid].Dormitory_Index<<endl;
				sign=true;
				break;
			}
		}
		if(!sign) {
			cout<<"未找到，请核对关键字是否正确"<<endl;
		}
	}
} 

void QSort(People people[],int low,int high) {
	//快速排序
	if(low<high) {
		int pivotloc=Partition(people,low,high);
		QSort(people,low,pivotloc-1);
		QSort(people,pivotloc+1,high);
	}
}

int Partition(People people[],int low,int high)  {
	//交换数组people中子数组low~high的内容
	people[0]=people[low];
	string pivotkey=people[low].key;
	while(low<high) {
		while(low<high&&people[high].key>=pivotkey) --high;
		people[low]=people[high];
		while(low<high&&people[low].key<=pivotkey) ++low;
		people[high]=people[low];
	}
	people[low]=people[0];
	return low;
}

