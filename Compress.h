#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include"HuffmanTree.h""
// 压缩函数
int compress(HuffNode huf_tree[], int n,long flength, char *ifname, char *ofname)
{
	FILE * inFile = fopen(ifname, "rb");//打开要压缩文件
	FILE * outFile = fopen(ofname, "wb");//打开压缩后文件

	unsigned char temp='\0';            //8bit临时的变量

	char buffer[256] = "\0";           //缓存流

	char tou[20];                     //文件后缀名字符数组
	int z = 0;
	int strLen = strlen(ifname);//文件后缀名长度
	for (int g = strLen - 1; g>0; g--)//获取文件后缀名（从后面获取）
	{
		if (ifname[g] == '.')//获取文件后缀名最后一个“.”
		{
			for (int k = g; k< strLen; k++)
			{
				z++;
				tou[z] = ifname[k];

			}
		}
	}

	tou[0] = z + '0';//获取文件后缀名长度(转成字符)
	fwrite((char *)&tou, sizeof(char), z + 1, outFile);//存文件头部
	fwrite(&flength, sizeof(long), 1, outFile);//存总长度
	fwrite(&n, sizeof(int), 1, outFile);//存字符的种类

	for (int i = 0; i < n; i++) {//存每个编号对应的字符,权重
		fwrite(&huf_tree[i].ch, sizeof(unsigned char), 1, outFile);
		fwrite(&huf_tree[i].count, sizeof(long), 1, outFile);
		/*for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)
		{
			fwrite(&huf_tree[i].bits[f], sizeof(char), 1, outFile);
		}*/
	}
	

	while (fread(&temp, sizeof(unsigned char), 1, inFile))//文件不为空
	{
		for (int i = 0; i <n; i++)//找对应字符
		{
			if (temp == huf_tree[i].ch)
			{
				for (int f = 0; huf_tree[i].bits[f] == '0' || huf_tree[i].bits[f] == '1'; f++)//过滤掉非0非1的编码（数组带来的弊端）
				{
					strncat(buffer,&huf_tree[i].bits[f],1);//给缓存流赋值
				}
			}
				
		}
		while (strlen(buffer) >= 8)//缓存流大于等于8个bits进入循环 
		{
			temp = 0;
			for (int i = 0; i < 8; i++)//每8个bits循环一次
			{
				temp = temp << 1;//左移1
				if (buffer[i] == '1')//如果是为1，就按位为1
				{
					temp = temp | 0x01;//在不影响其他位的情况下，最后位置1
				}
			}
			fwrite(&temp, sizeof(unsigned char), 1, outFile);//写入文件
			strcpy(buffer, buffer + 8);//将写入文件的bits删除
		}
	}
	int m = strlen(buffer);//将剩余不足为8的bits的个数给l
	if (m) {
		temp = 0;
		for (int i = 0; i < m; i++)
		{
			temp = temp << 1;//移动1
			if (buffer[i] == '1')//如果是为1，就按位为1
			{
				temp = temp | 0x01;
			}
			
		}
		temp <<= 8 - m;// // 将编码字段从尾部移到字节的高位
	    fwrite(&temp, sizeof(unsigned char), 1, outFile);//写入最后一个
	}

	fclose(inFile);
	fclose(outFile);


	/*std::fstream infile;
	unsigned char ch;
	infile.open(ofname);
	if (!infile)
	{
		std::cout << " 打开文件失败 " << std::endl;

	}

	while (infile.get((char&)ch))
	{
		printf("%c，", ch);
	}*/

	
   return 1;
}//compress
