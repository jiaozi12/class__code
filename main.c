#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int id[21830],problem_id[21830],weigui[21830],i,j=23,shuruid,N,L,r=0;
char ac_time[21830][30],kaishishijian[30],jiesushijian[30],filename1[30],filename2[30],filename4[30];

void shurushuju()
{
    FILE *fp=fopen("F:\\c2017.txt","r");//��F:\\c2017.txt�ļ�
    j=23;
    for(i=0; i<615; i++)//��ȡid��1��9���û����ݣ�������
    {
        fseek(fp,j,SEEK_SET);
        fscanf(fp,"%d",&id[i]);
        fseek(fp,j+1,SEEK_SET);
        fscanf(fp,"%d",&problem_id[i]);
        fseek(fp,j+7,SEEK_SET);
        fgets(ac_time[i],20,fp);
        j+=28;
    }
    for(i=614; i<7831; i++)//��ȡid��10��99���û����ݣ�������
    {
        fseek(fp,j,SEEK_SET);
        fscanf(fp,"%d",&id[i]);
        fseek(fp,j+3,SEEK_SET);
        fscanf(fp,"%d",&problem_id[i]);
        fseek(fp,j+8,SEEK_SET);
        fgets(ac_time[i],20,fp);
        j+=29;
    }
    for(i=7831; i<21826; i++)//��ȡid��100��300���û����ݣ�������
    {
        fseek(fp,j,SEEK_SET);
        fscanf(fp,"%d",&id[i]);
        fseek(fp,j+4,SEEK_SET);
        fscanf(fp,"%d",&problem_id[i]);
        fseek(fp,j+9,SEEK_SET);
        fgets(ac_time[i],20,fp);
        j+=30;
    }
    fclose(fp);//�ر��ļ�
    return;
}


void gongnengyi()
{
    printf("����һ:�����û�����Ĳ���,����ļ���,������N,Ѱ���ڼ��ʱ����,���������ں͵���N���û�,�������ָ�����ļ���\n");//��ӡָ������
    int st,sy;
    printf("������ִ�й���һ�Ĵ���:");
    scanf("%d",&st);//����st
    getchar();
    if(st!=0)//�ж�st�Ƿ����0
    {
        printf("�����봢�����ݵ��ļ���:");
        gets(filename1);
        FILE *fp1=fopen(filename1,"w");
        for(sy=0; sy<st; sy++)//sy<st����ѭ��
        {
            printf("�������ѯ��ʼʱ��(ʱ���ʽ��������2017-10-10 18:52:49�ĸ�ʽ):");//���뼰��ӡָ������
            gets(kaishishijian);
            printf("�������ѯ����ʱ��(ʱ���ʽ��������2017-10-10 18:52:49�ĸ�ʽ):");
            gets(jiesushijian);
            printf("�����������N:");
            scanf("%d",&N);
            getchar();
            L=timezhuanhuan(kaishishijian,jiesushijian);
            fprintf(fp1,"ID           ��ʼʱ��                ����ʱ��           ʱ��L    ����N\n");
            int a,b[100],c=0,d=0,e;
            for(a=0; a<i; a++)//a=0����a<iΪѭ��������ѭ��
            {
                //���й���1�Ĳ������ж��Ƿ���ѧ���ڹ涨ʱ�����ύ������Ҫ�����Ŀ���������У������ѧ���Ĵ��ڲ�����Ϊ���ύ��¼
                if(strcmp(kaishishijian,ac_time[a])<=0&&strcmp(jiesushijian,ac_time[a])>=0)
                {
                    c=0;
                    b[c]=a;
                    c++;
                    for(; id[a]==id[a+1]; a++)
                    {
                        if(strcmp(kaishishijian,ac_time[a])<=0&&strcmp(jiesushijian,ac_time[a])>=0)
                        {
                            b[c]=a;
                            c++;
                        }
                    }
                    if(c>=N)
                    {
                        fprintf(fp1,"%d\t  %s\t %s\t %d\t %d\n",id[a],kaishishijian,jiesushijian,L,N);
                        for(d=0; d<c; d++)
                        {
                            e=b[d];
                            if(problem_id[e]!=0)
                            {
                                fprintf(fp1,"          %d\t       %s\n",problem_id[e],ac_time[e]);
                                problem_id[e]=0;
                                weigui[r]=id[e];
                                r++;
                            }
                        }
                    }
                }
            }
        }
        fclose(fp1);
    }
    return;//����
}
void gongnenger()
{
    int a;//��ʼ
    printf("�����빦�ܶ������ݴ洢���ļ���:");//��ӡ������ָ�����ݣ�����Ӧ�ļ�
    gets(filename2);
    FILE *fp2=fopen(filename2,"w");
    for(a=0; a<i; a++)//a=0��a<i��a++
    {
        if(problem_id[a]!=0)//ִ�й���2�Ĺ��ܣ��ж�ָ�������Ƿ����������������������ָ�����ݵ�ָ���ļ�
        {
            fprintf(fp2,"%d\t        %d\t           %s\n",id[a],problem_id[a],ac_time[a]);
        }
    }
    fclose(fp2);//�ر��ļ�
    return;//����
}
void gongnengsan()
{
    printf("�����봢��ɼ����ļ���:");//��ӡ������ָ�����ݣ�����Ӧ�ļ�
    gets(filename4);
    FILE *fp4=fopen(filename4,"w");
    fprintf(fp4,"����\tid\t����\t  �ɼ�\t  �Ƿ���ڲ�����Ϊ\n");
    int paiming[301]= {0},chengji[301]= {0},paiming2[301],a,b,c,d,e,f,g;
    char time[301][30]= {0},temp[30];
    double jifen[301]= {0},p;
    for(a=0; a<i; a++)//a=0��ѭ������Ϊa<i��
    {
        if(problem_id[a]!=0)//�ж��Ƿ����������������ִ�и�ֵ��䣬�������ݴ��浽ָ��λ��
        {
            b=0;
            paiming[b]=id[a];
            strcpy(time[b],ac_time[a]);
            b++;
            for(c=a+1; c<i; c++)
            {
                if(problem_id[a]==problem_id[c])
                {
                    paiming[b]=id[c];
                    strcpy(time[b],ac_time[c]);
                    b++;
                    problem_id[c]=0;
                }
            }
            for(d=0; d<b; d++)
            {
                for(e=d+1; e<b; e++)
                {
                    if(strcmp(time[d],time[e])>0)
                    {
                        strcpy(temp,time[d]);
                        strcpy(time[d],time[e]);
                        strcpy(time[e],temp);
                        f=paiming[d];
                        paiming[d]=paiming[e];
                        paiming[e]=f;
                    }
                }
            }
            for(g=0; g<300; g++)
            {
                if(paiming[g]!=0)
                {
                    if(g<12)
                    {
                        d=paiming[g]-1;
                        jifen[d]+=32;
                    }
                    else if(g>=12&&g<24)
                    {
                        d=paiming[g]-1;
                        jifen[d]+=16;
                    }
                    else if(g>=24&&g<48)
                    {
                        d=paiming[g]-1;
                        jifen[d]+=8;
                    }
                    else if(g>=48&&g<96)
                    {
                        d=paiming[g]-1;
                        jifen[d]+=4;
                    }
                    else if(g>=96&&g<192)
                    {
                        d=paiming[g]-1;
                        jifen[d]+=2;
                    }
                    else
                    {
                        d=paiming[g]-1;
                        jifen[d]+=1;
                    }
                }
            }
        }
    }
    double sum;
    sum=jifen[0];
    for(g=0; g<300; g++)//g=0��g<300��
    {
        if(jifen[g+1]>sum)//�ж��Ƿ���������������ϣ�ִ����Ӧ�����
        {
            sum=jifen[g+1];
        }
    }
    for(g=0; g<300; g++)//g=0,g<300
    {
        paiming2[g]=g+1;//�ж��Ƿ���������������ϣ�ִ����Ӧ�����
    }
    for(g=0; g<300; g++)//g=0,g<300
    {
        for(d=g+1; d<300; d++)
        {
            if(jifen[g]<jifen[d])//�ж��Ƿ���������������ϣ�ִ����Ӧ�����
            {
                f=paiming2[g];
                paiming2[g]=paiming2[d];
                paiming2[d]=f;
                p=jifen[g];
                jifen[g]=jifen[d];
                jifen[d]=p;
                f=chengji[g];
                chengji[g]=chengji[d];
                chengji[d]=f;
            }
        }
    }
    for(g=0; g<300; g++)//g=0,g<300
    {
        chengji[g]=suanchengji(jifen[g],sum);
        d=1;
        for(f=0;f<r;f++)//�ж��Ƿ���������������ϣ�ִ����Ӧ�����
        {
            if(paiming2[g]==weigui[f])
            {
                fprintf(fp4,"%d\t%d\t%.2f\t  %d\t          ����\n",g+1,paiming2[g],jifen[g],chengji[g]);
                d=2;
                break;
            }
        }
        if(d==1)
        {
            fprintf(fp4,"%d\t%d\t%.2f\t  %d\t         ������\n",g+1,paiming2[g],jifen[g],chengji[g]);
        }
    }
    fclose(fp4);//�ر��ļ�
    return;//����
}

int suanchengji(double s,double t)
{
    double a,b,c;//��ʼ
    int d;
    a=1+(s-t)/t;//��ֵ���
    b=100+log(a)*10;
    c=b;
    d=(int)c;
    if((b-d)<0.5)//�����������жϷ���ֵ
    {
        return d;
    }
    else
    {
        return d+1;
    }//����
}

int timezhuanhuan(char s[30],char t[30])
{
    char *ch1,*ch2;//��ʼ������ָ��
    int year1,month1,day1,hour1,minute1,m,n,year2,month2,day2,hour2,minute2,a=31,b=31;
    ch1=s;//ָ���ʼ��
    year1=atoi(ch1);//ִ��9����ֵ���
    ch1+=5;
    month1=atoi(ch1);
    ch1+=3;
    day1=atoi(ch1);
    ch1+=3;
    hour1=atoi(ch1);
    ch1+=3;
    minute1=atoi(ch1);
    ch2=t;//ָ���ʼ��
    year2=atoi(ch2);//ִ��9����ֵ���
    ch2+=5;
    month2=atoi(ch2);
    ch2+=3;
    day2=atoi(ch2);
    ch2+=3;
    hour2=atoi(ch2);
    ch2+=3;
    minute2=atoi(ch2);
    if(month1==2)//4���ж���䣬��ִ�з����ж������ĸ�ֵ���
    {
        a=28;
    }
    if(month1==4||month1==6||month1==9||month1==11)
    {
        a=30;
    }
    if(month2==2)
    {
        b=28;
    }
    if(month2==4||month2==6||month2==9||month2==11)
    {
        b=30;
    }
    m=year1*365*24*60+month1*a*24*60+day1*24*60+hour1*60+minute1;//���ո����Ĺ�ʽ������m��n��ֵ
    n=year2*365*24*60+month2*b*24*60+day2*24*60+hour2*60+minute2;
    return n-m;//���� n-m������
}

int main()
{
    shurushuju();
    gongnengyi();
    gongnenger();
    gongnengsan();
    return 0;
}
