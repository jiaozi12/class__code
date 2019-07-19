#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int id[21830],problem_id[21830],weigui[21830],i,j=23,shuruid,N,L,r=0;
char ac_time[21830][30],kaishishijian[30],jiesushijian[30],filename1[30],filename2[30],filename4[30];

void shurushuju()
{
    FILE *fp=fopen("F:\\c2017.txt","r");//打开F:\\c2017.txt文件
    j=23;
    for(i=0; i<615; i++)//读取id从1到9的用户数据，并储存
    {
        fseek(fp,j,SEEK_SET);
        fscanf(fp,"%d",&id[i]);
        fseek(fp,j+1,SEEK_SET);
        fscanf(fp,"%d",&problem_id[i]);
        fseek(fp,j+7,SEEK_SET);
        fgets(ac_time[i],20,fp);
        j+=28;
    }
    for(i=614; i<7831; i++)//读取id从10到99的用户数据，并储存
    {
        fseek(fp,j,SEEK_SET);
        fscanf(fp,"%d",&id[i]);
        fseek(fp,j+3,SEEK_SET);
        fscanf(fp,"%d",&problem_id[i]);
        fseek(fp,j+8,SEEK_SET);
        fgets(ac_time[i],20,fp);
        j+=29;
    }
    for(i=7831; i<21826; i++)//读取id从100到300的用户数据，并储存
    {
        fseek(fp,j,SEEK_SET);
        fscanf(fp,"%d",&id[i]);
        fseek(fp,j+4,SEEK_SET);
        fscanf(fp,"%d",&problem_id[i]);
        fseek(fp,j+9,SEEK_SET);
        fgets(ac_time[i],20,fp);
        j+=30;
    }
    fclose(fp);//关闭文件
    return;
}


void gongnengyi()
{
    printf("功能一:接收用户输入的参数,输出文件名,过题数N,寻找在间隔时长内,过题数大于和等于N的用户,并输出到指定的文件中\n");//打印指定内容
    int st,sy;
    printf("请输入执行功能一的次数:");
    scanf("%d",&st);//输入st
    getchar();
    if(st!=0)//判断st是否等于0
    {
        printf("请输入储存数据的文件名:");
        gets(filename1);
        FILE *fp1=fopen(filename1,"w");
        for(sy=0; sy<st; sy++)//sy<st？，循环
        {
            printf("请输入查询开始时间(时间格式按照例如2017-10-10 18:52:49的格式):");//输入及打印指定内容
            gets(kaishishijian);
            printf("请输入查询结束时间(时间格式按照例如2017-10-10 18:52:49的格式):");
            gets(jiesushijian);
            printf("请输入过题数N:");
            scanf("%d",&N);
            getchar();
            L=timezhuanhuan(kaishishijian,jiesushijian);
            fprintf(fp1,"ID           开始时间                结束时间           时长L    题数N\n");
            int a,b[100],c=0,d=0,e;
            for(a=0; a<i; a++)//a=0，以a<i为循环条件的循环
            {
                //进行功能1的操作，判断是否有学生在规定时间内提交了满足要求的题目数量。如有，清楚该学生的存在不良行为的提交记录
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
    return;//结束
}
void gongnenger()
{
    int a;//开始
    printf("请输入功能二中数据存储的文件名:");//打印并输入指定内容，打开相应文件
    gets(filename2);
    FILE *fp2=fopen(filename2,"w");
    for(a=0; a<i; a++)//a=0，a<i，a++
    {
        if(problem_id[a]!=0)//执行功能2的功能，判断指定数据是否满足条件，若满足则输出指定数据到指定文件
        {
            fprintf(fp2,"%d\t        %d\t           %s\n",id[a],problem_id[a],ac_time[a]);
        }
    }
    fclose(fp2);//关闭文件
    return;//结束
}
void gongnengsan()
{
    printf("请输入储存成绩的文件名:");//打印并输入指定内容，打开相应文件
    gets(filename4);
    FILE *fp4=fopen(filename4,"w");
    fprintf(fp4,"排名\tid\t积分\t  成绩\t  是否存在不良行为\n");
    int paiming[301]= {0},chengji[301]= {0},paiming2[301],a,b,c,d,e,f,g;
    char time[301][30]= {0},temp[30];
    double jifen[301]= {0},p;
    for(a=0; a<i; a++)//a=0，循环条件为a<i，
    {
        if(problem_id[a]!=0)//判断是否符合条件，若符合执行赋值语句，并将数据储存到指定位置
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
    for(g=0; g<300; g++)//g=0，g<300，
    {
        if(jifen[g+1]>sum)//判断是否符合条件，若符合，执行相应的语句
        {
            sum=jifen[g+1];
        }
    }
    for(g=0; g<300; g++)//g=0,g<300
    {
        paiming2[g]=g+1;//判断是否符合条件，若符合，执行相应的语句
    }
    for(g=0; g<300; g++)//g=0,g<300
    {
        for(d=g+1; d<300; d++)
        {
            if(jifen[g]<jifen[d])//判断是否符合条件，若符合，执行相应的语句
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
        for(f=0;f<r;f++)//判断是否符合条件，若符合，执行相应的语句
        {
            if(paiming2[g]==weigui[f])
            {
                fprintf(fp4,"%d\t%d\t%.2f\t  %d\t          存在\n",g+1,paiming2[g],jifen[g],chengji[g]);
                d=2;
                break;
            }
        }
        if(d==1)
        {
            fprintf(fp4,"%d\t%d\t%.2f\t  %d\t         不存在\n",g+1,paiming2[g],jifen[g],chengji[g]);
        }
    }
    fclose(fp4);//关闭文件
    return;//结束
}

int suanchengji(double s,double t)
{
    double a,b,c;//开始
    int d;
    a=1+(s-t)/t;//赋值语句
    b=100+log(a)*10;
    c=b;
    d=(int)c;
    if((b-d)<0.5)//根据条件，判断返回值
    {
        return d;
    }
    else
    {
        return d+1;
    }//结束
}

int timezhuanhuan(char s[30],char t[30])
{
    char *ch1,*ch2;//开始，定义指针
    int year1,month1,day1,hour1,minute1,m,n,year2,month2,day2,hour2,minute2,a=31,b=31;
    ch1=s;//指针初始化
    year1=atoi(ch1);//执行9条赋值语句
    ch1+=5;
    month1=atoi(ch1);
    ch1+=3;
    day1=atoi(ch1);
    ch1+=3;
    hour1=atoi(ch1);
    ch1+=3;
    minute1=atoi(ch1);
    ch2=t;//指针初始化
    year2=atoi(ch2);//执行9条赋值语句
    ch2+=5;
    month2=atoi(ch2);
    ch2+=3;
    day2=atoi(ch2);
    ch2+=3;
    hour2=atoi(ch2);
    ch2+=3;
    minute2=atoi(ch2);
    if(month1==2)//4条判断语句，并执行符合判断条件的赋值语句
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
    m=year1*365*24*60+month1*a*24*60+day1*24*60+hour1*60+minute1;//按照给定的公式，计算m和n的值
    n=year2*365*24*60+month2*b*24*60+day2*24*60+hour2*60+minute2;
    return n-m;//返回 n-m，结束
}

int main()
{
    shurushuju();
    gongnengyi();
    gongnenger();
    gongnengsan();
    return 0;
}
