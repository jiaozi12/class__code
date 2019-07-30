#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

#define Length 1024
#define MAX 2147483647

struct Status_Table {
	int Start_Address;
	int Size;
};

struct Apple_Tuple {
	int Task_Id;
	int Task_Size;
	int Start_Time;
	int Task_Runtime;
	int Start_Address;
};

bool cmp(Status_Table a,Status_Table b) {
	if(a.Start_Address<=b.Start_Address) return true;
	else return false;
}
bool Application_Memory(Status_Table Unallocated[],Status_Table Allocated[],Apple_Tuple &tuple,int &Unallocated_Size,int &Allocated_Size);
void Release_Memory(Status_Table Unallocated[],Status_Table Allocated[],Apple_Tuple tuple[],int &Unallocated_Size,int &Allocated_Size,int time,int tuple_Size);

int main() {
	Status_Table Unallocated[Length];				//δ�ַ���״̬�� 
	Status_Table Allocated[Length];					//�ѷַ���״̬�� 
	int Memory[Length];								//����Ϊ1024��һά���飬����ģ���ڴ档1��ʾռ�ã�0��ʾδʹ�� 
	Apple_Tuple tuple[Length];
	int Unallocated_Size=1,Allocated_Size=0,tuple_Size=0,start_time=clock()/CLK_TCK,now;
	Unallocated[0].Start_Address = 1;
	Unallocated[0].Size = Length;
	for(int i=0;;) {
		cin>>tuple[i].Task_Id>>tuple[i].Task_Size>>tuple[i].Task_Runtime;
		now = clock()/CLK_TCK-start_time;
		tuple[i].Start_Time = now;
		if(tuple[i].Task_Size > Length) {
			cout<<"�ڴ���û�з���Ҫ��Ŀ��з���"<<endl;
			continue;
		}
		Release_Memory(Unallocated,Allocated,tuple,Unallocated_Size,Allocated_Size,now,tuple_Size);
		if(Application_Memory(Unallocated,Allocated,tuple[i],Unallocated_Size,Allocated_Size) == true) {tuple_Size++; i++;}
	}
}

bool Application_Memory(Status_Table Unallocated[],Status_Table Allocated[],Apple_Tuple &tuple,int &Unallocated_Size,int &Allocated_Size) {
	for(int i=0;i<Unallocated_Size;i++) {
		if(Unallocated[i].Size==tuple.Task_Size) {
			//��δ����״̬�����ҵ�һ����С���õķ��� 
			Allocated[Allocated_Size].Start_Address = tuple.Start_Address = Unallocated[i].Start_Address;
			Allocated[Allocated_Size].Size = Unallocated[i].Size;
			Allocated_Size++;
			sort(Allocated,Allocated+Allocated_Size,cmp);
			for(int j=i;j<Unallocated_Size;j++) {
				Unallocated[j] =  Unallocated[j+1];
			}
			Unallocated_Size--;
			cout<<"��ҵ"<<tuple.Task_Id<<"�����ڴ�ɹ�"<<endl; 
			return true;
		}
		else if(Unallocated[i].Size>tuple.Task_Size) {
			//��δ����״̬�����ҵ�һ����������ķ���
			Allocated[Allocated_Size].Start_Address = tuple.Start_Address = Unallocated[i].Start_Address;
			Allocated[Allocated_Size].Size = tuple.Task_Size;
			Allocated_Size++;
			sort(Allocated,Allocated+Allocated_Size,cmp);
			Unallocated[i].Start_Address +=  tuple.Task_Size;
			Unallocated[i].Size -= tuple.Task_Size;
			cout<<"��ҵ"<<tuple.Task_Id<<"�����ڴ�ɹ�"<<endl;
			return true;
		}
		else {
			;
		}
	}
	cout<<"�ڴ���û�з���Ҫ��Ŀ��з���"<<endl;
	return false;
}
void Release_Memory(Status_Table Unallocated[],Status_Table Allocated[],Apple_Tuple tuple[],int &Unallocated_Size,int &Allocated_Size,int time,int tuple_Size) {
	for(int i=0;i<tuple_Size;i++) {
		if((time-tuple[i].Start_Time)>=tuple[i].Task_Runtime) {
			//����ҵִ�����
			tuple[i].Start_Time = tuple[i].Task_Runtime = MAX;
			int flag = 0;
			if(tuple[i].Start_Address == 1) {
				//λ���ڴ���ǰ�����ҵִ����� 
				if(Allocated[1].Start_Address==tuple[i].Start_Address+tuple[i].Task_Size) {
					Unallocated[Unallocated_Size].Start_Address = tuple[i].Start_Address;
					Unallocated[Unallocated_Size].Size = tuple[i].Task_Size;
					Unallocated_Size++;
					cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
				}  
				else {
					Unallocated[0].Start_Address = tuple[i].Start_Address;
					Unallocated[0].Size += tuple[i].Task_Size;
					cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
				}
				goto L;
			}
			if(tuple[i].Start_Address+tuple[i].Task_Size==Length) {
				if(Unallocated[Unallocated_Size-1].Start_Address+Unallocated[Unallocated_Size-1].Size==tuple[i].Start_Address) {
					//����-��ҵ
					Unallocated[Unallocated_Size-1].Size += tuple[i].Task_Size;
					cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
				}
				else{
					//��ҵ-��ҵ
					Unallocated[Unallocated_Size].Start_Address = tuple[i].Start_Address;
					Unallocated[Unallocated_Size].Size = tuple[i].Task_Size;
					Unallocated_Size++;
					cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
				}
				sort(Unallocated,Unallocated+Unallocated_Size,cmp);
				goto L;
			}
			for(int j=0;j<Unallocated_Size;j++) {
				if(Unallocated[j].Start_Address+Unallocated[j].Size == tuple[i].Start_Address) {
					if(tuple[i].Start_Address+tuple[i].Task_Size==Unallocated[j+1].Start_Address) {
						//����-��ҵ-����
						Unallocated[j].Size += tuple[i].Task_Size + Unallocated[j+1].Size;
						for(int k=j+1;k<Unallocated_Size-1;k++) {
							Unallocated[j]=Unallocated[j+1];
						} 
						Unallocated_Size--;
						cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
					}
					else {
						//����-��ҵ-��ҵ
						Unallocated[j].Size += tuple[i].Task_Size;
						cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
					}
					flag = 1;
					break;
				}
			} 
			sort(Unallocated,Unallocated+Unallocated_Size,cmp);
			if(!flag) {
				for(int j=0;j<Allocated_Size;j++) {
					if(Allocated[j].Start_Address+Allocated[j].Size==tuple[i].Start_Address) {
						if(tuple[i].Start_Address+tuple[i].Task_Size==Allocated[j+1].Start_Address) {
							//��ҵ-��ҵ-��ҵ
							Unallocated[Unallocated_Size-1].Start_Address = tuple[i].Start_Address;
							Unallocated[Unallocated_Size-1].Size = tuple[i].Task_Size;
							Unallocated_Size++;
							cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
						}
						else {
							//��ҵ-��ҵ-����
							for(int k=0;k<Unallocated_Size;k++) {
								if(Unallocated[k].Start_Address == tuple[i].Start_Address+tuple[i].Task_Size) {
									Unallocated[k].Start_Address -= tuple[i].Task_Size;
									Unallocated[k].Size += tuple[k].Task_Size;
								}
							}
							cout<<"�ͷ���ҵ"<<tuple[i].Task_Id<<"ռ�õ��ڴ�ռ�"<<endl;
						}
					}
				}
			}
L:			sort(Unallocated,Unallocated+Unallocated_Size,cmp);
			for(int j=0;j<Allocated_Size;j++) {
				if(Allocated[j].Start_Address == tuple[i].Start_Address) {
					for(int k=j;k<Allocated_Size;k++) Allocated[k] = Allocated[k+1];
					Allocated_Size--;
					break;
				}
			}
		}
	}
}
