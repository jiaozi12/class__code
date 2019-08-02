/*

6
湘潭大学 长沙理工大学 石家庄学院 河北工业大学 湖南大学 中南大学 
3
篮球 滑雪 蹦极
2
足球 乒乓球 
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
	//单个学校信息 
	int Index;//学校编号 
	string School_name;//学校名字 
	int man_SumScore;//该学校的男团体积分 
	int woman_SumScore;//该学校的女团体积分 
	int sum_Score;//该学校的总积分 
};
struct school {
	//学校信息汇总 
	School_score School_Score[MAXSIZE];
	int School_number;//参加运动会的学校数量 
};
struct Event {
	//单个比赛项目信息 
	int Index;//比赛项目编号 
	string Event_name;//项目名字 
	int School_Index[8];//该项目获奖学校的编号 
};
struct Event_information {
	//比赛项目汇总 
	Event Event_man[MAXSIZE];
	int Event_man_number;//男子组比赛数量
	Event Event_woman[MAXSIZE];
	int Event_woman_number;//女子组比赛数量 
};

void Get_man_event_score(Event_information &s,school &t);//输入男子组各个项目的前三名或前五名的成绩 
void Get_woman_event_score(Event_information &s,school &t);//输入女子组各个项目的前三名或前五名的成绩
bool Judge_is_illegal_cin(Event_information s);//判断是否有非法输入 ,若无非法输入，则返回true 
void Print_all_result(Event_information s,school t);//按学校编号或名称、学校总分、男女团体总分输出排序结果 
void Search_with_school(Event_information s,school e,int t);//按学校编号查询该学校获奖项目的情况
void Search_with_event(Event_information s,school e,int t);//按项目编号查询取得前三或前五的学校 
bool cmp2(School_score a,School_score b);//比较函数，使School_score数据按School_name升序排序 
bool cmp3(School_score a,School_score b);//比较函数，使School_score数据按团体总分降序排序
bool cmp4(School_score a,School_score b);//比较函数，使School_score数据按男团体总分降序排序
bool cmp5(School_score a,School_score b);//比较函数，使School_score数据按女团体总分降序排序

int main() {
	school School;
	Event_information Event_Information;
	cout<<"输入参加运动会的学校数量：";
	cin>>School.School_number;
	if(School.School_number<=0) {
		cout<<"输入参加运动会的学校数量非法！！！"<<endl;
		return 0;
	}
	cout<<"输入参加运动会的学校名称：";
	for(int i=1;i<=School.School_number;i++) {
		School.School_Score[i].Index=i;
		cin>>School.School_Score[i].School_name;
	} 
	cout<<"输入男子组比赛数量：";
	cin>>Event_Information.Event_man_number;
	if(Event_Information.Event_man_number<=0) {
		cout<<"输入男子组比赛数量非法"<<endl;
		return 0; 
	}
	cout<<"输入男子组比赛名称：";
	for(int i=1;i<=Event_Information.Event_man_number;i++) {
		Event_Information.Event_man[i].Index=i;
		cin>>Event_Information.Event_man[i].Event_name;
	}
	cout<<"输入女子组比赛数量：";
	cin>>Event_Information.Event_woman_number;
	if(Event_Information.Event_woman_number<=0) {
		cout<<"输入女子组比赛数量非法"<<endl;
		return 0;
	}
	cout<<"输入女子组比赛名称：";
	for(int i=1;i<=Event_Information.Event_woman_number;i++) {
		Event_Information.Event_woman[i].Index=i;
		cin>>Event_Information.Event_woman[i].Event_name;
	}
	cout<<"输入男子组项目成绩："<<endl;
	Get_man_event_score(Event_Information,School);
	cout<<"输入女子组项目成绩："<<endl;
	Get_woman_event_score(Event_Information,School);
	cout<<endl; 
	if(!Judge_is_illegal_cin(Event_Information)) {
		cout<<"非法"; 
		return 0;
	}
	int w=0;
	while(w!=-1) {
		cout<<endl<<"输入要执行的功能："<<endl;
		cout<<"1.按学校编号或名称、学校总分、男女团体总分输出排序结果"<<endl;
		cout<<"2.按学校编号查询获奖项目的情况" <<endl;
		cout<<"3.按项目编号查询取得前三或前五的学校"<<endl;
		cout<<"输入-1结束程序"<<endl;
		cin>>w;
		if(w==1) {
			Print_all_result(Event_Information,School);
		}
		else if(w==2) {
			cout<<"输入要查询的学校编号：";
			int m;
			cin>>m; 
			Search_with_school(Event_Information,School,m);
		}
		else if(w==3) {
			cout<<"输入要查询的项目编号：";
			int m;
			cin>>m;
			Search_with_event(Event_Information,School,m);
		}
		else {
			if(w!=-1)
			cout<<"输入功能序号无效！！！"<<endl;
		}
	}
}

 void Get_man_event_score(Event_information &s,school &t) {
 	//输入各个项目的前三名或前五名的成绩
 	for(int i=1;i<=s.Event_man_number;i++) {
 		cout<<"项目"<<i<<"（若取前3名输入0，若取前5名输入-1）：";
		int three_or_five,length=0;
		cin>>three_or_five;
		if(three_or_five==0) {
			cout<<"项目"<<i<<"前3名学校编号：";
			length=3;
		}
		if(three_or_five==-1) {
			cout<<"项目"<<i<<"前5名学校编号：";
			length=5;
		}
		for(int j=1;j<=length;j++) {
			cin>>s.Event_man[i].School_Index[j];
			if(s.Event_man[i].School_Index[j]<=0) {
				cout<<"输入项目"<<i<<"的学校编号数据非法！！！"<<endl;
				return; 
			}
			if(three_or_five==0) {
				//男子组取前三名，积分为5，3，2 
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
				//男子组取前五名，积分为7，5，3，2，1 
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
 	//输入各个项目的前三名或前五名的成绩
 	for(int i=1;i<=s.Event_woman_number;i++) {
 		cout<<"项目"<<i+s.Event_man_number<<"（若取前3名输入0，若取前5名输入-1）：";
		int three_or_five,length=0;
		cin>>three_or_five;
		if(three_or_five==0) {
			cout<<"项目"<<i+s.Event_man_number<<"前3名学校编号：";
			length=3;
		}
		if(three_or_five==-1) {
			cout<<"项目"<<i+s.Event_man_number<<"前5名学校编号：";
			length=5;
		}
		for(int j=1;j<=length;j++) {
			cin>>s.Event_woman[i].School_Index[j];
			if(s.Event_woman[i].School_Index[j]<=0) {
				cout<<"输入项目"<<i+s.Event_man_number<<"的学校编号数据非法！！！"<<endl;
				return; 
			}
			if(three_or_five==0) {
				//女子组取前三名，积分为5，3，2 
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
				//女子组取前五名，积分为7，5，3，2，1 
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
 	//判断是否有非法输入,若无非法输入，则返回true 
 	if(s.Event_man_number<=0) {
 		cout<<"男子组项目数量输入非法！！！"<<endl;
 		return false;
 	}
 	if(s.Event_woman_number<=0) {
 		cout<<"女子组项目数量输入非法！！！"<<endl;
 		return false;
 	}
 	return true;
 }
 
void Print_all_result(Event_information s,school t) {
	//按学校编号或名称、学校总分、男女团体总分输出排序结果
	vector<School_score>array;
	for(int i=1;i<=t.School_number;i++) {
		array.push_back(t.School_Score[i]);
	}
	cout<<"请输入排序标准（1按学校编号升序，2按学校名称升序，3按学校总分降序，4按男团体总分降序，5按女团体总分降序，-1退出）："<<endl;
	int way=0;
	while(way!=-1) {
		cin>>way;
		if(way==1) {
			//按学校编号升序 
			ofstream outFile;
    		outFile.open("排序输出（按学校编号升序）.txt",ios::out);
			if(outFile) {
				outFile<<"序号"<<'\t'<<"学校编号"<<'\t'<<"学校名称"<<'\t'<<"总分"<<'\t'<<"男团体总分"<<'\t'<<"女团体总分"<<endl;
				for(int i=1;i<=t.School_number;i++) {
					outFile<<i<<'\t'<<"   "<<t.School_Score[i].Index<<'\t'<<'\t'<<t.School_Score[i].School_name<<'\t'<<" "<<t.School_Score[i].sum_Score<<'\t';
					outFile<<"    "<<t.School_Score[i].man_SumScore<<'\t'<<'\t'<<"    "<<t.School_Score[i].woman_SumScore<<endl;
				}
			}
			outFile.close();
			cout<<"请在《排序输出（按学校编号升序）.txt》文件中查看结果"<<endl; 
		}
		else if(way==2) {
			//按学校名称升序 
			sort(array.begin(),array.end(),cmp2);
			ofstream outFile;
			outFile.open("排序输出（按学校名称升序）.txt",ios::out);
			if(outFile) {
				outFile<<"序号"<<'\t'<<"学校名称"<<'\t'<<"学校编号"<<'\t'<<"总分"<<'\t'<<"男团体总分"<<'\t'<<"女团体总分"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<" "<<array[i].sum_Score<<'\t';
					outFile<<"    "<<array[i].man_SumScore<<'\t'<<'\t'<<"    "<<array[i].woman_SumScore<<endl;
				}
			}
			outFile.close();
			cout<<"请在《排序输出（按学校名称升序）.txt》文件中查看结果"<<endl;
		}
		else if(way==3) {
			//按学校总分降序 
			sort(array.begin(),array.end(),cmp3);
			ofstream outFile;
			outFile.open("排序输出（按学校总分降序）.txt",ios::out);
			if(outFile) {
				outFile<<"序号"<<'\t'<<"学校名称"<<'\t'<<"学校编号"<<'\t'<<"总分"<<'\t'<<"男团体总分"<<'\t'<<"女团体总分"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<" "<<array[i].sum_Score<<'\t';
					outFile<<"    "<<array[i].man_SumScore<<'\t'<<'\t'<<"    "<<array[i].woman_SumScore<<endl;
				}
			}
			outFile.close();
			cout<<"请在《排序输出（按学校总分降序）.txt》文件中查看结果"<<endl;
		}
		else if(way==4) {
			//按男团体总分降序 
			sort(array.begin(),array.end(),cmp4);
			ofstream outFile;
			outFile.open("排序输出（按男团体总分降序）.txt",ios::out);
			if(outFile) {
				outFile<<"序号"<<'\t'<<"学校名称"<<'\t'<<"学校编号"<<'\t'<<"男团体总分"<<'\t'<<"女团体总分"<<'\t'<<"团体总分"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<"    "<<array[i].man_SumScore<<'\t';
					outFile<<'\t'<<"    "<<array[i].woman_SumScore<<'\t'<<'\t'<<"   "<<array[i].sum_Score<<endl;
				}
			}
			outFile.close();
			cout<<"请在《排序输出（按男团体总分降序）.txt》文件中查看结果"<<endl;
		}
		else if(way==5) {
			//按女团体总分降序 
			sort(array.begin(),array.end(),cmp5);
			ofstream outFile;
			outFile.open("排序输出（按女团体总分降序）.txt",ios::out);
			if(outFile) {
				outFile<<"序号"<<'\t'<<"学校名称"<<'\t'<<"学校编号"<<'\t'<<"女团体总分"<<'\t'<<"男团体总分"<<'\t'<<"团体总分"<<endl;
				for(int i=0;i<t.School_number;i++) {
					outFile<<i+1<<'\t'<<array[i].School_name<<'\t'<<"    "<<array[i].Index<<'\t'<<'\t'<<"    "<<array[i].woman_SumScore<<'\t';
					outFile<<'\t'<<"    "<<array[i].man_SumScore<<'\t'<<'\t'<<"   "<<array[i].sum_Score<<endl;
				}
			}
			outFile.close();
			cout<<"请在《排序输出（按女团体总分降序）.txt》文件中查看结果"<<endl;
		}
	}
}

void Search_with_school(Event_information s,school e,int t) {
	//按学校编号查询该学校获奖项目的情况
	if(t<=0||t>e.School_number) {
		cout<<"输入学校编号非法！！！"<<endl;
		return;
	}
	ofstream outFile;
	outFile.open("查询（按学校编号查询获奖项目情况）.txt",ios::out);
	if(outFile) {
		for(int i=1;i<=e.School_number;i++) {
			if(e.School_Score[i].Index==t) {
				outFile<<"学校编号："<<t<<",  学校名称："<<e.School_Score[i].School_name<<"      获奖情况"<<endl;
			}
		}
		for(int i=1;i<=s.Event_man_number;i++) {
			for(int j=1;s.Event_man[i].School_Index[j]!=-1;j++) {
				if(s.Event_man[i].School_Index[j]==t) {
					outFile<<"获奖项目编号："<<s.Event_man[i].Index<<"  "<<"获奖项目名称："<<s.Event_man[i].Event_name<<"（男子组项目）"<<endl; 
				}
			}
		}
		for(int i=1;i<=s.Event_woman_number;i++) {
			for(int j=1;s.Event_woman[i].School_Index[j]!=-1;j++) {
				if(s.Event_woman[i].School_Index[j]==t) {
					outFile<<"获奖项目编号："<<s.Event_woman[i].Index+s.Event_man_number<<"  "<<"获奖项目名称："<<s.Event_woman[i].Event_name<<"（女子组项目）"<<endl; 
				}
			}
		}
		cout<<"请在《查询（按学校编号查询获奖项目情况）.txt》文件中查看结果"<<endl;
	}
}

void Search_with_event(Event_information s,school e,int t) {
	//按项目编号查询取得前三或前五的学校
	if(t<=0||t>s.Event_man_number+s.Event_woman_number) {
			cout<<"输入项目编号非法！！！"<<endl;
			return;
		} 
	ofstream outFile;
	outFile.open("查询（按项目编号查询取得前三或前五的学校）.txt",ios::out);
	if(outFile) {
		if(t>0&&t<=s.Event_man_number) {
			outFile<<"项目编号为"<<t<<"的学校获奖情况（男子项目："<<s.Event_man[t].Event_name<<"）"<<endl;  
			int cnt=1;
			for(int i=1;s.Event_man[t].School_Index[i]!=-1;i++) {
				outFile<<"第"<<cnt<<"名：  "<<"学校编号："<<s.Event_man[t].School_Index[i]<<'\t'<<"学校名称："<<e.School_Score[s.Event_man[t].School_Index[i]].School_name<<endl;
				cnt++;
			}
		}
		else if(t>s.Event_man_number&&t<=s.Event_man_number+s.Event_woman_number){
			t-=s.Event_man_number;
			outFile<<"项目编号为"<<t<<"的学校获奖情况（女子项目："<<s.Event_woman[t].Event_name<<"）"<<endl;
			int cnt=1;
			for(int i=1;s.Event_woman[t].School_Index[i]!=-1;i++) {
				outFile<<"第"<<cnt<<"名：  "<<"学校编号："<<s.Event_woman[t].School_Index[i]<<'\t'<<"学校名称："<<e.School_Score[s.Event_woman[t].School_Index[i]].School_name<<endl;
				cnt++;
			}
		}
		cout<<"请在《查询（按项目编号查询取得前三或前五的学校）.txt》文件中查看结果"<<endl;
	}
}

bool cmp2(School_score a,School_score b) {
	//比较函数，使School_score数据按学校名称升序排序
	return a.School_name<b.School_name;
}

bool cmp3(School_score a,School_score b) {
	//比较函数，使School_score数据按团体总分降序排序
	return a.sum_Score>b.sum_Score;
}

bool cmp4(School_score a,School_score b) {
	//比较函数，使School_score数据按男团体总分降序排序
	return a.man_SumScore>b.man_SumScore;
}

bool cmp5(School_score a,School_score b) {
	//比较函数，使School_score数据按女团体总分降序排序
	return a.woman_SumScore>b.woman_SumScore;
}
