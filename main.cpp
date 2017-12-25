#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Extract.h"
using namespace std;

int main()
{

	int n;//有效字节
	HuffNode hufftree[512];//最多511个结点
	for (int a = 0; a < 512; a++)
	{
		hufftree[a].parent = -1;
		hufftree[a].ch = NULL;
		hufftree[a].count = -1;
		hufftree[a].lch = -1;
		hufftree[a].rch = -1;
	}


	while (1)
	{
		int opt, flag = 0;		// 每次进入循环都要初始化flag为0
		char ifname[256]; 
		char ofname[256];		// 保存输入输出文件名
		printf(" =======================================\n");
		cout << "        ***Huffman文件压缩***" << endl;
		printf(" =======================================\n");
		printf("            ※  1：压缩              \n");
		printf("            ※  2：解压              \n");
		printf("            ※  3：退出              \n");
		printf("         ※ 请输入您的操作：         \n");
		scanf("%d", &opt);

		if (opt == 3)
			exit(1);
		else
		{
			printf("请输入操作的文件名：");
			fflush(stdin);		// 清空标准输入流，防止干扰gets函数读取文件名
			gets(ifname);
			printf("请输入生成的文件名：");
			fflush(stdin);
			gets(ofname);
			
		}
		switch (opt)
		{
		case 1:
		{
			//求文件总字节长度
			FILE *file;
			file = fopen(ifname, "r");
			fseek(file, SEEK_SET, SEEK_END);
			long flength = ftell(file);
			fclose(file);


			n = DuXuWenJian(hufftree, ifname);//读取文件，并按字节频率排序，返回有效字节（频率不为0）
			creat(hufftree, n);//构建哈夫曼仿真指针孩子父亲表示法

			creat_hmcode(hufftree, n);//生成哈夫曼编码

			//for (int d = 0; d < 2 * n - 1; d++)//仅供测试
			//{
			//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, hufftree[d].ch, hufftree[d].count, hufftree[d].parent, hufftree[d].lch, hufftree[d].rch);  /* 用于测试 */

			//	for (int f = 0; hufftree[d].bits[f] == '0' || hufftree[d].bits[f] == '1'; f++)
			//		printf("%c", hufftree[d].bits[f]);
			//	printf("\n");
			//}

			flag = compress(hufftree, n, flength, ifname, ofname);	// 压缩，返回值用于判断是否文件名不存在
			if (flag != -1)
			{
				cout << "\n……客官稍等," << ifname << "正在压缩中……\n";
				cout << "……来了客官," << ofname << "压缩完毕……\n";
			}
			break;
		}
		case 2:
		{
			flag = extract(hufftree, ifname, ofname);		// 解压，返回值用于判断是否文件名不存在
			
			if (flag != -1)
			{
				cout << "\n……客官稍等," << ifname << "正在解压中……\n";
				cout << "……来了客官," << ofname << "解压完毕……\n";
			}
			break;
		}


		if (flag == -1)
			printf("\nSorry ,您输入的文件\"%s\"不存在\n", ifname);		// 如果标志为‘-1’则输入文件不存在
		else
			printf("\n操作完成！\n");		// 操作完成
		system("pause");
		system("CLS");
		}

		return 0;

	}


}