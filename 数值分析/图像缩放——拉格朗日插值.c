#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef  unsigned char  uint8;
typedef  unsigned short uint16;
typedef  unsigned int   uint32;

#pragma  pack(1)
typedef struct{ 
    //文件头 
    uint16 bfType;         // BM
    uint32 bfSize;         //文件大小
    uint16 bfReserved1;    //未使用，全0 
    uint16 bfReserved2;    //未使用，全0 
    uint32 bfOffBits;      //文件头偏移量，灰度图54+1024，彩色图像54 

    //信息头 
    uint32 biSize;         //信息头大小
    uint32 biWidth;        //图像宽度
    uint32 biHeight;       //图像高度
    uint16 biPlanes;       
    uint16 biBitCount;     //每个相素点的位数，8（灰度图像），24（彩色图像） 
    uint32 biCompression;
    uint32 biSizeImage;    //图像尺寸（灰度图像[biWidth/4]*4*biHeight）,(彩色图像[bi]) 
    uint32 biXPelsPerMeter;
    uint32 biYPelsPerMeter;
    uint32 biClrUsed;      //灰度256，彩色0 
    uint32 biClrImportant;
}BMP_HEADER;

void Lagrange(uint16 bpp,uint8 data[],uint8 y[],uint32 source_Width,uint32 source_Height,uint32 target_Width,uint32 target_Height,uint32 num_SamplePoint,uint32 stride_Source);
BMP_HEADER get_Image(char image_Name[],uint8 data[]);
void write_Image(char image_Name[],uint8 y[],BMP_HEADER header,int target_Width,int target_Height);
void print_BMPHEADER(BMP_HEADER header);

int main() {
	BMP_HEADER header;
	int fd = -1;
	char image_Name[256];
	static uint8 data[2048*2048*30],y[2048*2048*30];
	uint32 target_Width = 0,target_Height = 0,num_SamplePoint = 0,stride_Source = 0;
	while(1) {
		printf("**********************************************************************\n"); 
		printf("请输入待缩放的图片名(输入0结束程序)：");
		//输入要缩放的图像名
		scanf("%s",image_Name);
		if(strcmp(image_Name,"0") == 0) {
			//结束 
			return 0;
		}
		printf("请指定目标图像尺寸(宽度、高度)：");
		//输入目标图像尺寸
		scanf("%d%d",&target_Width,&target_Height);
		printf("请指定插值所需样本点数：");
		//输入插值所需样本点数 
		scanf("%d",&num_SamplePoint);
		//读取待缩放图片 
		header = get_Image(image_Name,data);
		//计算待缩放图像每行的元素个数 
		stride_Source = header.biSizeImage / header.biHeight;
		//进行拉格朗日插值 
		Lagrange(header.biBitCount,data,y,header.biWidth,header.biHeight,target_Width,target_Height,num_SamplePoint,stride_Source);
		//将处理好的图像数据保存 
		write_Image(image_Name,y,header,target_Width,target_Height);
	}
}


void Lagrange(uint16 bpp,uint8 data[],uint8 y[],uint32 source_Width,uint32 source_Height,uint32 target_Width,uint32 target_Height,uint32 num_SamplePoint,uint32 stride_Source) {
	//bpp表示图像类型（8为灰度图，24为彩色图像）
	//data用来存储像素信息
	//source_Width,source_Height,target_Width,target_Height分别表示源图像宽度，源图像高度，目标图像宽度，目标图像高度
	//num_SamplePoint表示插值所需样本点数，stride_Source表示像素矩阵的列数 
	if(bpp == 8) {
		//处理灰度图
		int i = 0,j = 0,stride_target = (target_Width+3)/4*4,p = 0;
		for(i=0;i<target_Height;i++) {
			static int set[2048*2048*10] = {0};
            static double g[2048*2048*10] = {0.0};
			for(j=0;j<stride_target;j++) {
				//对每个像素点进行拉格朗日插值 
				g[j] = g[0] + (double)j*(double)(stride_Source-1)/(double)(stride_target-1);
				int floor;
				//求距离该点最近的指定个数的样本点数组下标 
				if(num_SamplePoint%2==0) {
					floor = (int)g[j];
					floor -= (num_SamplePoint-2)/2;
				}
				else {
					floor = round(g[j]);
					floor -= (num_SamplePoint-1)/2;
				}
				for(p=0;p<num_SamplePoint;p++) {
					set[p] = floor;
					floor++;
				}
				double temp = 0;
				int flag = 0;
				for(p=0;p<num_SamplePoint;p++) {
					double l = 1.0;
					int q = 0;
					//计算拉格朗日插值因子 
					for(q=0;q<num_SamplePoint;q++) {
						double a=set[q],b=set[p];
						if(a!=b) {
							l = l * (g[j]-a)/(b-a);
					    }
					}
					double a=source_Height,b=target_Height;
					double c = (double)i * (double)(a - 1) / (double)(b - 1);
					int index = round(c);
					if(set[p] < 0) {
						set[p] = 0 - set[p];
						flag = 1;
					}
					index = index * stride_Source + set[p];
					//插值求和 
					temp += l*(double)data[index];
					if(flag==1) {
						set[p] = 0 - set[p];
						flag = 0;
					}
				}
				//保存插值结果 
				y[i*stride_target+j] = (uint8)temp;
		    }
		} 
	}
	else if(bpp == 24) {
		//处理彩色图片
		int i = 0,j = 0,stride_target = (target_Width*3+3)/4*4,p = 0,k = 0;
		for(i=0;i<target_Height;i++) {
			for(k=0;k<3;k++) {
				static int set[2048*2048*4] = {0};
            	static double g[2048*2048*4] = {0.0};
            	static uint8 fictitious_y[2048*2048*4] = {0};
            	//提取出一行中相同颜色的像素点（RGB） 
            	for(j=0;j<stride_Source;j++) {
            		double c = (double)i * (double)(source_Height - 1) / (double)(target_Height - 1);
            		int index = round(c);
            		fictitious_y[j] = data[index*stride_Source+3*j+k];
				}
				for(j=0;j<stride_target/3;j++) {
					//对每个像素点进行拉格朗日插值 
					g[j] = g[0] + (double)j*(double)(stride_Source/3-1)/(double)(stride_target/3-1);
					int floor;
					//求距离该点最近的指定个数的样本点数组下标 
					if(num_SamplePoint%2==0) {
						floor = (int)g[j];
						floor -= (num_SamplePoint-2)/2;
					}
					else {
						floor = round(g[j]);
						floor -= (num_SamplePoint-1)/2;
					}
					for(p=0;p<num_SamplePoint;p++) {
						set[p] = floor;
						floor = floor + 1;
					}
					double temp = 0;
					int flag = 0;
					for(p=0;p<num_SamplePoint;p++) {
						double l = 1.0;
						int q = 0;
						//计算拉格朗日插值因子 
						for(q=0;q<num_SamplePoint;q++) {
							double a=set[q],b=set[p];
							if(a!=b) {
								l = l * (g[j]-a)/(b-a);
					    	}
						}
						if(set[p] < 0) {
							set[p] = 0 - set[p];
							flag = 1;
						}
						//插值求和 
						temp += l*(double)fictitious_y[set[p]];
						if(flag==1) {
							set[p] = 0 - set[p];
							flag = 0;
						}
					}
					//保存插值结果 
					y[i*stride_target+j*3+k] = (uint8)temp;
				}
			}
		} 
	}
	else {
		//返回错误信息 
		perror("Wrong type of image.");
	}
} 

BMP_HEADER get_Image(char image_Name[],uint8 data[]) {
	int fd = open(image_Name, O_RDONLY | O_BINARY);
	BMP_HEADER header;
	if(fd == -1) {
		; 
	}
	else {
		//读取图像文件头和信息头 
		read(fd, &header, sizeof(BMP_HEADER));
		printf("********************************源图像********************************\n"); 
		//输出文件头、信息头数据 
		print_BMPHEADER(header);
		//跳过调色板部分 
		lseek(fd, header.bfOffBits, SEEK_SET);
		//读取图像数据部分 
        read(fd, data, header.biSizeImage);
  	    close(fd);
  	    //返回图像文件头和信息头数据 
  	    return header;
	}
}

void write_Image(char image_Name[],uint8 y[],BMP_HEADER header,int target_Width,int target_Height) {
	char fName[256],temp[16];
	//确定要写的文件名 
	strcpy(fName,"");
    strncat(fName,image_Name,strlen(image_Name)-4);
    itoa(target_Width,temp,10);
    strcat(temp,"x");
    strcat(fName,temp);
    itoa(target_Height,temp,10);
    strcat(fName,temp);
    strcat(fName,".bmp");
	int fd = open(fName, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);
    if(fd < 0 ) {
    	;
	}
	//写文件头和信息头 
	uint16 bpp = header.biBitCount;
	uint32 compression = header.biCompression;
    memset(&header, 0, sizeof(BMP_HEADER));
    header.bfType = 'M'*256 + 'B';
    header.bfOffBits = sizeof(BMP_HEADER) + ((bpp==8)?1024:0);
    header.biSize = 40;
    header.biWidth = target_Width;
    header.biHeight = target_Height;
    header.biPlanes = 1;
    header.biBitCount = bpp;
    header.biCompression = compression;
    header.biSizeImage = (bpp==8)?((target_Width+3)/4*4*target_Height):((target_Width*3+3)/4*4*target_Height);
    header.bfSize = header.bfOffBits + header.biSizeImage;
    header.biClrUsed = (bpp==8)?256:0;
    write(fd, &header, sizeof(BMP_HEADER));
    //写文件调色板数据 
    if(bpp == 8) {
    	uint8 clrPal[256*4];
    	int i = 0;
    	for(i=0; i<256; i++) {
    		clrPal[4*i] = clrPal[4*i+1] = clrPal[4*i+2] = i;
            clrPal[4*i+3] = 0;
        }
        write(fd, clrPal, 256*4);
	}
	//写图像数据部分 
	write(fd, y, header.biSizeImage);
    close(fd);
    printf("********************************目标图像********************************\n"); 
    //输出写的文件头和信息头数据 
    print_BMPHEADER(header);
    //结束 
    return; 
}

void print_BMPHEADER(BMP_HEADER header) {
	//输出BMP_HEADER信息 
	printf(" bfType          : %c%c\n", header.bfType%256,header.bfType/256 );
    printf(" bfSize          : %d  \n", header.bfSize          );
    printf(" bfReserved1     : %d  \n", header.bfReserved1     );
    printf(" bfReserved2     : %d  \n", header.bfReserved2     );
    printf(" bfOffBits       : %d\n\n", header.bfOffBits       );
    printf(" biSize          : %d  \n", header.biSize          );
    printf(" biWidth         : %d  \n", header.biWidth         );
    printf(" biHeight        : %d  \n", header.biHeight        );
    printf(" biPlanes        : %d  \n", header.biPlanes        );
    printf(" biBitCount      : %d  \n", header.biBitCount      );
    printf(" biCompression   : %d  \n", header.biCompression   );
    printf(" biSizeImage     : %d  \n", header.biSizeImage     );
    printf(" biXPelsPerMeter : %d  \n", header.biXPelsPerMeter );
    printf(" biYPelsPerMeter : %d  \n", header.biYPelsPerMeter );
    printf(" biClrUsed       : %d  \n", header.biClrUsed       );
    printf(" biClrImportant  : %d  \n", header.biClrImportant  );
    printf("\n");
    //输出完毕 
    return;
}
