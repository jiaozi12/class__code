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


void Read_file(People people[]);//��ȡѧ����Ϣ�ļ��е�����
void Sort(People people[],int);//���򣨰�������ѧ�š����ţ�
void Search(People people[]);//��ѯ����������ѧ�š����Ų�ѯ 
void QSort(People people[],int ,int);//��������
int Partition(People people[],int low,int high);//��������people��������low~high������

int main() {
	//�˳������������10������
	People people[MAXSIZE];
	Read_file(people);
	Search(people);
	return 0;
}

void Read_file(People people[]) {
	//��ȡѧ����Ϣ�ļ��е�����
	ifstream inFile("ѧ����Ϣ.txt",ios::in);
	if(!inFile) {
		cout<<"��ȡѧ����Ϣ.txtʧ��"<<endl;
		return;
	}
	else {
		string lineStr;
		int i=1;
		getline(inFile,lineStr);
		while(getline(inFile, lineStr)) {
        	// ��,�ָ�
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
	//���򣨰�������ѧ�š����ţ�
	if(Sort_way==1) {
		ofstream outFile("name_up.txt",ios::in);
		if(!outFile) {
			cout<<"��name_up.txt�ļ�ʧ��"<<endl;
			return;
		}
		else {
			outFile<<"ѧ��"<<'\t'<<'\t'<<"����"<<'\t'<<"����"<<endl;
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
			cout<<"��Student_ID_up.txt�ļ�ʧ��"<<endl;
			return;
		}
		else {
			outFile<<"ѧ��"<<'\t'<<'\t'<<"����"<<'\t'<<"����"<<endl;
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
			cout<<"Dormitory_Index_up.txt�ļ�ʧ��"<<endl;
			return;
		}
		else {
			outFile<<"ѧ��"<<'\t'<<'\t'<<"����"<<'\t'<<"����"<<endl;
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
	//��ѯ����������ѧ�š����Ų�ѯ 
	cout<<"�����ѯ��׼"<<endl;
	cout<<"1��������ѯ"<<endl;
	cout<<"2��ѧ�Ų�ѯ"<<endl;
	cout<<"3�����Ų�ѯ"<<endl;
	cout<<"-1��������"<<endl;
	int Search_way=0;
	while(true) {
		cin>>Search_way;
		if(Search_way==-1) {
			return;
		}
		Sort(people,Search_way);
		cout<<"�����ѯ�ؼ��֣�";
		string key;
		cin>>key;
		int low=1,high=people_number,mid;
		bool sign=false;
		while(low<high) {
			if(key==people[people_number].key) {
				cout<<"ѧ��"<<'\t'<<'\t'<<"����"<<'\t'<<'\t'<<"�����"<<endl;
				cout<<people[people_number].Student_ID<<'\t'<<people[people_number].name<<'\t'<<'\t'<<people[people_number].Dormitory_Index<<endl;
				sign=true;
				break; 
			}
			if(key==people[1].key) {
				cout<<"ѧ��"<<'\t'<<'\t'<<"����"<<'\t'<<'\t'<<"�����"<<endl;
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
				cout<<"ѧ��"<<'\t'<<'\t'<<"����"<<'\t'<<'\t'<<"�����"<<endl;
				cout<<people[mid].Student_ID<<'\t'<<people[mid].name<<'\t'<<'\t'<<people[mid].Dormitory_Index<<endl;
				sign=true;
				break;
			}
		}
		if(!sign) {
			cout<<"δ�ҵ�����˶Թؼ����Ƿ���ȷ"<<endl;
		}
	}
} 

void QSort(People people[],int low,int high) {
	//��������
	if(low<high) {
		int pivotloc=Partition(people,low,high);
		QSort(people,low,pivotloc-1);
		QSort(people,pivotloc+1,high);
	}
}

int Partition(People people[],int low,int high)  {
	//��������people��������low~high������
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

