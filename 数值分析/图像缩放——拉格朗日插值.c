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
    //�ļ�ͷ 
    uint16 bfType;         // BM
    uint32 bfSize;         //�ļ���С
    uint16 bfReserved1;    //δʹ�ã�ȫ0 
    uint16 bfReserved2;    //δʹ�ã�ȫ0 
    uint32 bfOffBits;      //�ļ�ͷƫ�������Ҷ�ͼ54+1024����ɫͼ��54 

    //��Ϣͷ 
    uint32 biSize;         //��Ϣͷ��С
    uint32 biWidth;        //ͼ����
    uint32 biHeight;       //ͼ��߶�
    uint16 biPlanes;       
    uint16 biBitCount;     //ÿ�����ص��λ����8���Ҷ�ͼ�񣩣�24����ɫͼ�� 
    uint32 biCompression;
    uint32 biSizeImage;    //ͼ��ߴ磨�Ҷ�ͼ��[biWidth/4]*4*biHeight��,(��ɫͼ��[bi]) 
    uint32 biXPelsPerMeter;
    uint32 biYPelsPerMeter;
    uint32 biClrUsed;      //�Ҷ�256����ɫ0 
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
		printf("����������ŵ�ͼƬ��(����0��������)��");
		//����Ҫ���ŵ�ͼ����
		scanf("%s",image_Name);
		if(strcmp(image_Name,"0") == 0) {
			//���� 
			return 0;
		}
		printf("��ָ��Ŀ��ͼ��ߴ�(��ȡ��߶�)��");
		//����Ŀ��ͼ��ߴ�
		scanf("%d%d",&target_Width,&target_Height);
		printf("��ָ����ֵ��������������");
		//�����ֵ������������ 
		scanf("%d",&num_SamplePoint);
		//��ȡ������ͼƬ 
		header = get_Image(image_Name,data);
		//���������ͼ��ÿ�е�Ԫ�ظ��� 
		stride_Source = header.biSizeImage / header.biHeight;
		//�����������ղ�ֵ 
		Lagrange(header.biBitCount,data,y,header.biWidth,header.biHeight,target_Width,target_Height,num_SamplePoint,stride_Source);
		//������õ�ͼ�����ݱ��� 
		write_Image(image_Name,y,header,target_Width,target_Height);
	}
}


void Lagrange(uint16 bpp,uint8 data[],uint8 y[],uint32 source_Width,uint32 source_Height,uint32 target_Width,uint32 target_Height,uint32 num_SamplePoint,uint32 stride_Source) {
	//bpp��ʾͼ�����ͣ�8Ϊ�Ҷ�ͼ��24Ϊ��ɫͼ��
	//data�����洢������Ϣ
	//source_Width,source_Height,target_Width,target_Height�ֱ��ʾԴͼ���ȣ�Դͼ��߶ȣ�Ŀ��ͼ���ȣ�Ŀ��ͼ��߶�
	//num_SamplePoint��ʾ��ֵ��������������stride_Source��ʾ���ؾ�������� 
	if(bpp == 8) {
		//����Ҷ�ͼ
		int i = 0,j = 0,stride_target = (target_Width+3)/4*4,p = 0;
		for(i=0;i<target_Height;i++) {
			static int set[2048*2048*10] = {0};
            static double g[2048*2048*10] = {0.0};
			for(j=0;j<stride_target;j++) {
				//��ÿ�����ص�����������ղ�ֵ 
				g[j] = g[0] + (double)j*(double)(stride_Source-1)/(double)(stride_target-1);
				int floor;
				//�����õ������ָ�������������������±� 
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
					//�����������ղ�ֵ���� 
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
					//��ֵ��� 
					temp += l*(double)data[index];
					if(flag==1) {
						set[p] = 0 - set[p];
						flag = 0;
					}
				}
				//�����ֵ��� 
				y[i*stride_target+j] = (uint8)temp;
		    }
		} 
	}
	else if(bpp == 24) {
		//�����ɫͼƬ
		int i = 0,j = 0,stride_target = (target_Width*3+3)/4*4,p = 0,k = 0;
		for(i=0;i<target_Height;i++) {
			for(k=0;k<3;k++) {
				static int set[2048*2048*4] = {0};
            	static double g[2048*2048*4] = {0.0};
            	static uint8 fictitious_y[2048*2048*4] = {0};
            	//��ȡ��һ������ͬ��ɫ�����ص㣨RGB�� 
            	for(j=0;j<stride_Source;j++) {
            		double c = (double)i * (double)(source_Height - 1) / (double)(target_Height - 1);
            		int index = round(c);
            		fictitious_y[j] = data[index*stride_Source+3*j+k];
				}
				for(j=0;j<stride_target/3;j++) {
					//��ÿ�����ص�����������ղ�ֵ 
					g[j] = g[0] + (double)j*(double)(stride_Source/3-1)/(double)(stride_target/3-1);
					int floor;
					//�����õ������ָ�������������������±� 
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
						//�����������ղ�ֵ���� 
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
						//��ֵ��� 
						temp += l*(double)fictitious_y[set[p]];
						if(flag==1) {
							set[p] = 0 - set[p];
							flag = 0;
						}
					}
					//�����ֵ��� 
					y[i*stride_target+j*3+k] = (uint8)temp;
				}
			}
		} 
	}
	else {
		//���ش�����Ϣ 
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
		//��ȡͼ���ļ�ͷ����Ϣͷ 
		read(fd, &header, sizeof(BMP_HEADER));
		printf("********************************Դͼ��********************************\n"); 
		//����ļ�ͷ����Ϣͷ���� 
		print_BMPHEADER(header);
		//������ɫ�岿�� 
		lseek(fd, header.bfOffBits, SEEK_SET);
		//��ȡͼ�����ݲ��� 
        read(fd, data, header.biSizeImage);
  	    close(fd);
  	    //����ͼ���ļ�ͷ����Ϣͷ���� 
  	    return header;
	}
}

void write_Image(char image_Name[],uint8 y[],BMP_HEADER header,int target_Width,int target_Height) {
	char fName[256],temp[16];
	//ȷ��Ҫд���ļ��� 
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
	//д�ļ�ͷ����Ϣͷ 
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
    //д�ļ���ɫ������ 
    if(bpp == 8) {
    	uint8 clrPal[256*4];
    	int i = 0;
    	for(i=0; i<256; i++) {
    		clrPal[4*i] = clrPal[4*i+1] = clrPal[4*i+2] = i;
            clrPal[4*i+3] = 0;
        }
        write(fd, clrPal, 256*4);
	}
	//дͼ�����ݲ��� 
	write(fd, y, header.biSizeImage);
    close(fd);
    printf("********************************Ŀ��ͼ��********************************\n"); 
    //���д���ļ�ͷ����Ϣͷ���� 
    print_BMPHEADER(header);
    //���� 
    return; 
}

void print_BMPHEADER(BMP_HEADER header) {
	//���BMP_HEADER��Ϣ 
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
    //������ 
    return;
}
