/*

6
��̶��ѧ ��ɳ����ѧ ʯ��ׯѧԺ �ӱ���ҵ��ѧ ���ϴ�ѧ ���ϴ�ѧ 
3
���� ��ѩ �ļ�
2
���� ƹ���� 
-1
2 3 4 5 1
-1
1 3 5 6 4
-1
2 3 4 5 6
-1
1 4 5 2 3
0
2 3 4

*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#define MAXSIZE 50
using namespace std;
struct School_score {
	//����ѧУ��Ϣ 
	int Index;//ѧУ��� 
	string School_name;//ѧУ���� 
	int man_SumScore;//��ѧУ����������� 
	int woman_SumScore;//��ѧУ��Ů������� 
	int sum_Score;//��ѧУ���ܻ��� 
};
struct school {
	//ѧУ��Ϣ���� 
	School_score School_Score[MAXSIZE];
	int School_number;//�μ��˶����ѧУ���� 
};
struct Event {
	//����������Ŀ��Ϣ 
	int Index;//������Ŀ��� 
	string Event_name;//��Ŀ���� 
	int School_Index[8];//����Ŀ��ѧУ�ı�� 
};
struct Event_information {
	//������Ŀ���� 
	Event Event_man[MAXSIZE];
	int Event_man_number;//�������������
	Event Event_woman[MAXSIZE];
	int Event_woman_number;//Ů����������� 
};

void Get_man_event_score(Event_information &s,school &t);//���������������Ŀ��ǰ������ǰ�����ĳɼ� 
void Get_woman_event_score(Event_information &s,school &t);//����Ů���������Ŀ��ǰ������ǰ�����ĳɼ�
bool Judge_is_illegal_cin(Event_information s);//�ж��Ƿ��зǷ����� ,���޷Ƿ����룬�򷵻�true 
void Print_all_result(Event_information s,school t);//��ѧУ��Ż����ơ�ѧУ�ܷ֡���Ů�����ܷ���������� 
void Search_with_school(Event_information s,school e,int t);//��ѧУ��Ų�ѯ��ѧУ����Ŀ�����
void Search_with_event(Event_information s,school e,int t);//����Ŀ��Ų�ѯȡ��ǰ����ǰ���ѧУ 
bool cmp2(School_score a,School_score b);//�ȽϺ�����ʹSchool_score���ݰ�School_name�������� 
bool cmp3(School_score a,School_score b);//�ȽϺ�����ʹSchool_score���ݰ������ֽܷ�������
bool cmp4(School_score a,School_score b);//�ȽϺ�����ʹSchool_score���ݰ��������ֽܷ�������
bool cmp5(School_score a,School_score b);//�ȽϺ�����ʹSchool_score���ݰ�Ů�����ֽܷ�������

int main() {
	school School;
	Event_information Event_Information;
	cout<<"����μ��˶����ѧУ������";
	cin>>School.School_number;
	if(School.School_number<=0) {
		cout<<"����μ��˶����ѧУ�����Ƿ�������"<<endl;
		return 0;
	}
	cout<<"����μ��˶����ѧУ���ƣ�";
	for(int i=1;i<=School.School_number;i++) {
		School.School_Score[i].Index=i;
		cin>>School.School_Score[i].School_name;
	} 
	cout<<"�������������������";
	cin>>Event_Information.Event_man_number;
	if(Event_Information.Event_man_number<=0) {
		cout<<"������������������Ƿ�"<<endl;
		return 0; 
	}
	cout<<"����������������ƣ�";
	for(int i=1;i<=Event_Information.Event_man_number;i++) {
		Event_Information.Event_man[i].Index=i;
		cin>>Event_Information.Event_man[i].Event_name;
	}
	cout<<"����Ů�������������";
	cin>>Event_Information.Event_woman_number;
	if(Event_Information.Event_woman_number<=0) {
		cout<<"����Ů������������Ƿ�"<<endl;
		return 0;
	}
	cout<<"����Ů����������ƣ�";
	for(int i=1;i<=Event_Information.Event_woman_number;i++) {
		Event_Information.Event_woman[i].Index=i;
		cin>>Event_Information.Event_woman[i].Event_name;
	}
	cout<<"������������Ŀ�ɼ���"<<endl;
	Get_man_event_score(Event_Information,School);
	cout<<"����Ů������Ŀ�ɼ���"<<endl;
	Get_woman_event_score(Event_Information,School);
	cout<<endl; 
	if(!Judge_is_illegal_cin(Event_Information)) {
		cout<<"�Ƿ�"; 
		return 0;
	}
	int w=0;
	while(w!=-1) {
		cout<<endl<<"����Ҫִ�еĹ��ܣ�"<<endl;
		cout<<"1.��ѧУ��Ż����ơ�ѧУ�ܷ֡���Ů�����ܷ����������"<<endl;
		cout<<"2.��ѧУ��Ų�ѯ����Ŀ�����" <<endl;
		cout<<"3.����Ŀ��Ų�ѯȡ��ǰ����ǰ���ѧУ"<<endl;
		cout<<"����-1��������"<<endl;
		cin>>w;
		if(w==1) {
			Print_all_result(Event_Information,School);
		}
		else if(w==2) {
			cout<<"����Ҫ��ѯ��ѧУ��ţ�";
			int m;
			cin>>m; 
			Search_with_school(Event_Information,School,m);
		}
		else if(w==3) {
			cout<<"����Ҫ��ѯ����Ŀ��ţ�";
			int m;
			cin>>m;
			Search_with_event(Event_Information,School,m);
		}
		else {
			if(w!=-1)
			cout<<"���빦�������Ч������"<<endl;
		}
	}
}

 void Get_man_event_score(Event_information &s,school &t) {
 	//���������Ŀ��ǰ������ǰ�����ĳɼ�
 	for(int i=1;i<=s.Event_man_number;i++) {
 		cout<<"��Ŀ"<<i<<"����ȡǰ3������0����ȡǰ5������-1����";
		int three_or_five,length=0;
		cin>>three_or_five;
		if(three_or_five==0) {
			cout<<"��Ŀ"<<i<<"ǰ3��ѧУ��ţ�";
			length=3;
		}
		if(three_or_five==-1) {
			cout<<"��Ŀ"<<i<<"ǰ5��ѧУ��ţ�";
			length=5;
		}
		for(int j=1;j<=length;j++) {
			cin>>s.Event_man[i].School_Index[j];
			if(s.Event_man[i].School_Index[j]<=0) {
				cout<<"������Ŀ"<<i<<"��ѧУ������ݷǷ�������"<<endl;
				return; 
			}
			if(three_or_five==0) {
				//������ȡǰ����������Ϊ5��3��2 
				if(j==1) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=5;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=5;
				}
				else if(j==2) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=3;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=3;
				}
				else if(j==3) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=2;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=2;
					s.Event_man[i].School_Index[j+1]=-1;
				}
			}
			if(three_or_five==-1) {
				//������ȡǰ����������Ϊ7��5��3��2��1 
				if(j==1) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=7;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=7;
				}
				else if(j==2) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=5;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=5;
				}
				else if(j==3) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=3;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=3;
				}
				else if(j==4) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=2;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=2;
				}
				else if(j==5) {
					t.School_Score[s.Event_man[i].School_Index[j]].sum_Score+=1;
					t.School_Score[s.Event_man[i].School_Index[j]].man_SumScore+=1;
					s.Event_man[i].School_Index[j+1]=-1;
				}
			}
		}
 	}
 }
 
 void Get_woman_event_score(Event_information &s,school &t) {
 	//���������Ŀ��ǰ������ǰ�����ĳɼ�
 	for(int i=1;i<=s.Event_woman_number;i++) {
 		cout<<"��Ŀ"<<i+s.Event_man_number<<"����ȡǰ3������0����ȡǰ5������-1����";
		int three_or_five,length=0;
		cin>>three_or_five;
		if(three_or_five==0) {
			cout<<"��Ŀ"<<i+s.Event_man_number<<"ǰ3��ѧУ��ţ�";
			length=3;
		}
		if(three_or_five==-1) {
			cout<<"��Ŀ"<<i+s.Event_man_number<<"ǰ5��ѧУ��ţ�";
			length=5;
		}
		for(int j=1;j<=length;j++) {
			cin>>s.Event_woman[i].School_Index[j];
			if(s.Event_woman[i].School_Index[j]<=0) {
				cout<<"������Ŀ"<<i+s.Event_man_number<<"��ѧУ������ݷǷ�������"<<endl;
				return; 
			}
			if(three_or_five==0) {
				//Ů����ȡǰ����������Ϊ5��3��2 
				if(j==1) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=5;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=5;
				}
				else if(j==2) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=3;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=3;
				}
				else if(j==3) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=2;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=2;
					s.Event_woman[i].School_Index[j+1]=-1;
				}
			}
			if(three_or_five==-1) {
				//Ů����ȡǰ����������Ϊ7��5��3��2��1 
				if(j==1) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=7;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=7;
				}
				else if(j==2) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=5;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=5;
				}
				else if(j==3) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=3;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=3;
				}
				else if(j==4) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=2;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=2;
				}
				else if(j==5) {
					t.School_Score[s.Event_woman[i].School_Index[j]].sum_Score+=1;
					t.School_Score[s.Event_woman[i].School_Index[j]].woman_SumScore+=1;
					s.Event_woman[i].School_Index[j+1]=-1;
				}
			}
		}
 	}
 }
 
 bool Judge_is_illegal_cin(Event_information s) {
 	//�ж��Ƿ��зǷ�����,���޷Ƿ����룬�򷵻�true 
 	if(s.Event_man_number<=0) {
 		cout<<"��������Ŀ��������Ƿ�������"<<endl;
 		return false;
 	}
 	if(s.Event_woman_number<=0) {
 		cout<<"Ů������Ŀ��������Ƿ�������"<<endl;
 		return false;
 	}
 	return true;
 }
 
void Print_all_result(Event_information s,school t) {
	//��ѧУ��Ż����ơ�ѧУ�ܷ֡���Ů�����ܷ����������
	vector<School_score>array;
	for(int i=1;i<=t.School_number;i++) {
		array.push_back(t.School_Score[i]);
	}
	cout<<"�����������׼��1��ѧУ�������2��ѧУ��������3��ѧУ�ֽܷ���4���������ֽܷ���5��Ů�����ֽܷ���-1�˳�����"<<endl;
	int way=0;
	while(way!=-1) {
		cin>>way;
		if(way==1) {
			//��ѧУ������� 
			ofstream outFile;
    		outFile.open("�����������ѧУ�������.txt",ios::out);
			if(outFile) {
				outFile<<"���"<<'\t'<<"ѧУ���"<<'\t'<<"ѧУ����"<<'\t'<<"�ܷ�"<<'\t'<<"�������ܷ�"<<'\t'<<"Ů�����ܷ�"<<endl;
				for(int i=1;i<=t.School_number;i++) {
					outFile<<i<<'\t'<<"   "<<t.School_Score[i].Index<<'\t'<<'\t'<<t.School_Score[i].School_name<<'\t'<<" "<<t.School_Score[i].sum_Score<<'\t';
					outFile<<"    "<<t.School_Score[i].man_SumScore<<'\t'<<'\t'<<"    "<<t.School_Score[i].woman_SumScore<<endl;
				}
			}
			outFile.close();
			cout<<"���ڡ������������ѧУ�������.txt���ļ��в鿴���"<<endl; 
		}
		else if(way==2) {
			//��ѧУ�������� 
			sort(array.begin(),array.end(),cmp2);
			ofstream outFile;
			outFile.open("�����������ѧУ��������.txt",ios::out);
			if(outFile) {
				outFile<<"���"<<'\t'<<"ѧУ����"<<'\t'<<"ѧУ���"<<'\t'<<"�ܷ�"<<'\t'<<"�������ܷ�"<<'\t'<<"Ů�����ܷ�"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<" "<<array[i].sum_Score<<'\t';
					outFile<<"    "<<array[i].man_SumScore<<'\t'<<'\t'<<"    "<<array[i].woman_SumScore<<endl;
				}
			}
			outFile.close();
			cout<<"���ڡ������������ѧУ��������.txt���ļ��в鿴���"<<endl;
		}
		else if(way==3) {
			//��ѧУ�ֽܷ��� 
			sort(array.begin(),array.end(),cmp3);
			ofstream outFile;
			outFile.open("�����������ѧУ�ֽܷ���.txt",ios::out);
			if(outFile) {
				outFile<<"���"<<'\t'<<"ѧУ����"<<'\t'<<"ѧУ���"<<'\t'<<"�ܷ�"<<'\t'<<"�������ܷ�"<<'\t'<<"Ů�����ܷ�"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<" "<<array[i].sum_Score<<'\t';
					outFile<<"    "<<array[i].man_SumScore<<'\t'<<'\t'<<"    "<<array[i].woman_SumScore<<endl;
				}
			}
			outFile.close();
			cout<<"���ڡ������������ѧУ�ֽܷ���.txt���ļ��в鿴���"<<endl;
		}
		else if(way==4) {
			//���������ֽܷ��� 
			sort(array.begin(),array.end(),cmp4);
			ofstream outFile;
			outFile.open("������������������ֽܷ���.txt",ios::out);
			if(outFile) {
				outFile<<"���"<<'\t'<<"ѧУ����"<<'\t'<<"ѧУ���"<<'\t'<<"�������ܷ�"<<'\t'<<"Ů�����ܷ�"<<'\t'<<"�����ܷ�"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<"    "<<array[i].man_SumScore<<'\t';
					outFile<<'\t'<<"    "<<array[i].woman_SumScore<<'\t'<<'\t'<<"   "<<array[i].sum_Score<<endl;
				}
			}
			outFile.close();
			cout<<"���ڡ�������������������ֽܷ���.txt���ļ��в鿴���"<<endl;
		}
		else if(way==5) {
			//��Ů�����ֽܷ��� 
			sort(array.begin(),array.end(),cmp5);
			ofstream outFile;
			outFile.open("�����������Ů�����ֽܷ���.txt",ios::out);
			if(outFile) {
				outFile<<"���"<<'\t'<<"ѧУ����"<<'\t'<<"ѧУ���"<<'\t'<<"Ů�����ܷ�"<<'\t'<<"�������ܷ�"<<'\t'<<"�����ܷ�"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<"    "<<array[i].woman_SumScore<<'\t';
					outFile<<'\t'<<"    "<<array[i].man_SumScore<<'\t'<<'\t'<<"   "<<array[i].sum_Score<<endl;
				}
			}
			outFile.close();
			cout<<"���ڡ������������Ů�����ֽܷ���.txt���ļ��в鿴���"<<endl;
		}
	}
}

void Search_with_school(Event_information s,school e,int t) {
	//��ѧУ��Ų�ѯ��ѧУ����Ŀ�����
	if(t<=0||t>e.School_number) {
		cout<<"����ѧУ��ŷǷ�������"<<endl;
		return;
	}
	ofstream outFile;
	outFile.open("��ѯ����ѧУ��Ų�ѯ����Ŀ�����.txt",ios::out);
	if(outFile) {
		for(int i=1;i<=e.School_number;i++) {
			if(e.School_Score[i].Index==t) {
				outFile<<"ѧУ��ţ�"<<t<<",  ѧУ���ƣ�"<<e.School_Score[i].School_name<<"      �����"<<endl;
			}
		}
		for(int i=1;i<=s.Event_man_number;i++) {
			for(int j=1;s.Event_man[i].School_Index[j]!=-1;j++) {
				if(s.Event_man[i].School_Index[j]==t) {
					outFile<<"����Ŀ��ţ�"<<s.Event_man[i].Index<<"  "<<"����Ŀ���ƣ�"<<s.Event_man[i].Event_name<<"����������Ŀ��"<<endl; 
				}
			}
		}
		for(int i=1;i<=s.Event_woman_number;i++) {
			for(int j=1;s.Event_woman[i].School_Index[j]!=-1;j++) {
				if(s.Event_woman[i].School_Index[j]==t) {
					outFile<<"����Ŀ��ţ�"<<s.Event_woman[i].Index+s.Event_man_number<<"  "<<"����Ŀ���ƣ�"<<s.Event_woman[i].Event_name<<"��Ů������Ŀ��"<<endl; 
				}
			}
		}
		cout<<"���ڡ���ѯ����ѧУ��Ų�ѯ����Ŀ�����.txt���ļ��в鿴���"<<endl;
	}
}

void Search_with_event(Event_information s,school e,int t) {
	//����Ŀ��Ų�ѯȡ��ǰ����ǰ���ѧУ
	if(t<=0||t>s.Event_man_number+s.Event_woman_number) {
			cout<<"������Ŀ��ŷǷ�������"<<endl;
			return;
		} 
	ofstream outFile;
	outFile.open("��ѯ������Ŀ��Ų�ѯȡ��ǰ����ǰ���ѧУ��.txt",ios::out);
	if(outFile) {
		if(t>0&&t<=s.Event_man_number) {
			outFile<<"��Ŀ���Ϊ"<<t<<"��ѧУ�������������Ŀ��"<<s.Event_man[t].Event_name<<"��"<<endl;  
			int cnt=1;
			for(int i=1;s.Event_man[t].School_Index[i]!=-1;i++) {
				outFile<<"��"<<cnt<<"����  "<<"ѧУ��ţ�"<<s.Event_man[t].School_Index[i]<<'\t'<<"ѧУ���ƣ�"<<e.School_Score[s.Event_man[t].School_Index[i]].School_name<<endl;
				cnt++;
			}
		}
		else if(t>s.Event_man_number&&t<=s.Event_man_number+s.Event_woman_number){
			t-=s.Event_man_number;
			outFile<<"��Ŀ���Ϊ"<<t<<"��ѧУ�������Ů����Ŀ��"<<s.Event_woman[t].Event_name<<"��"<<endl;
			int cnt=1;
			for(int i=1;s.Event_woman[t].School_Index[i]!=-1;i++) {
				outFile<<"��"<<cnt<<"����  "<<"ѧУ��ţ�"<<s.Event_woman[t].School_Index[i]<<'\t'<<"ѧУ���ƣ�"<<e.School_Score[s.Event_woman[t].School_Index[i]].School_name<<endl;
				cnt++;
			}
		}
		cout<<"���ڡ���ѯ������Ŀ��Ų�ѯȡ��ǰ����ǰ���ѧУ��.txt���ļ��в鿴���"<<endl;
	}
}

bool cmp2(School_score a,School_score b) {
	//�ȽϺ�����ʹSchool_score���ݰ�ѧУ������������
	return a.School_name<b.School_name;
}

bool cmp3(School_score a,School_score b) {
	//�ȽϺ�����ʹSchool_score���ݰ������ֽܷ�������
	return a.sum_Score>b.sum_Score;
}

bool cmp4(School_score a,School_score b) {
	//�ȽϺ�����ʹSchool_score���ݰ��������ֽܷ�������
	return a.man_SumScore>b.man_SumScore;
}

bool cmp5(School_score a,School_score b) {
	//�ȽϺ�����ʹSchool_score���ݰ�Ů�����ֽܷ�������
	return a.woman_SumScore>b.woman_SumScore;
}
