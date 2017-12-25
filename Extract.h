#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include"Compress.h""
// 解压函数
int extract(HuffNode huf_tree[],  char *ifname, char *ofname)
{
	int i;
	char huozui;                          //文件后缀长度
	char tou[20];                         //文件后缀字符
	long flength;                         //文件总长度
	int n;                               //字符种类
	int node_num;                        //结点总数
	unsigned long writen_len = 0;		// 控制文件写入长度
	FILE *infile, *outfile;
	unsigned char code_temp;		// 暂存8bits编码
	unsigned int root;		// 保存根节点索引，供匹配编码使用

	infile = fopen(ifname, "rb");		// 以二进制方式打开压缩文件
	// 判断输入文件是否存在
	if (infile == NULL)
		return -1;

	//读取文件后缀名长度
	fread(&huozui, sizeof(char),1,infile);
	//字符转数字
	int huozui_du = huozui - '0';
	//读取文件后缀字符
	fread(&tou, sizeof(char), huozui_du, infile); //读取文件后缀字符
	fread(&flength, sizeof(long), 1, infile);    //读取文件总长度
	fread(&n, sizeof(int), 1, infile);          //读取字符种类

	node_num = 2 * n - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数 
		
	// 初始化后
	for (int a = 0; a < 512; a++)    
	{
		huf_tree[a].parent = -1;
		huf_tree[a].ch = NULL;
		huf_tree[a].count = -1;
		huf_tree[a].lch = -1;
		huf_tree[a].rch = -1;
	}

	// 读取压缩文件前端的字符及对应权重，用于重建哈夫曼树
	for (i = 0; i < n; i++)
	{
		fread((char *)&huf_tree[i].ch, sizeof(unsigned char), 1, infile);		// 读入字符
		fread((char *)&huf_tree[i].count, sizeof(long), 1, infile);	// 读入字符对应权重
	}

	creat(huf_tree, n);//构建哈夫曼仿真指针孩子父亲表示法
	creat_hmcode(huf_tree, n);//生成哈夫曼编码


	//printf("\n");
	//for (int d = 0; d < 2 * n - 1; d++)//仅供测试
	//{
	//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, huf_tree[d].ch, huf_tree[d].count, huf_tree[d].parent, huf_tree[d].lch, huf_tree[d].rch);  /* 用于测试 */

	//	for (int f = 0; huf_tree[d].bits[f] == '0' || huf_tree[d].bits[f] == '1'; f++)
	//		printf("%c", huf_tree[d].bits[f]);
	//	printf("\n");
	//}

	strncat(ofname, tou, huozui_du);

	outfile = fopen(ofname, "wb");		// 打开压缩后将生成的文件
	root = node_num - 1;                //根结点的下标
	while (1)
	{
		fread(&code_temp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码

		// 处理读取的一个字符长度的编码（通常为8位）
		for (i = 0; i < 8; i++)
		{
			// 由根向下直至叶节点正向匹配编码对应字符（逆向）
			if (code_temp & 128)//128是1000 0000   按位与就是编码缓存的最高位是否为1
				root = huf_tree[root].rch;//为1，root=右子树
			else
				root = huf_tree[root].lch;//为0，root=左子树

			if (root < n)//0到n-1的左右子树为-1
			{
				fwrite(&huf_tree[root].ch, sizeof(unsigned char), 1, outfile);
				writen_len++;//已编译字符加一
				if (writen_len == flength) break;		// 控制文件长度，跳出内层循环
				root = node_num - 1;        // 复位为根索引，匹配下一个字符
			}
			code_temp <<= 1;		// 将编码缓存的下一位移到最高位，提供匹配
		}
		if (writen_len == flength) break;		// 控制文件长度，跳出外层循环
	}

   //关闭文件
	fclose(infile);
	fclose(outfile);
	return 1;
}//extract()