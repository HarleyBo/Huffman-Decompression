#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

// 哈夫曼树结点
struct HuffNode
{
	unsigned char ch;  //字节符
	long count;  //字节出现频度
	int parent; //父节点
	int lch;  //左孩子
	int rch;  //右孩子
	char bits[256]; // 哈夫曼编码
};
//文件结构体
struct weijiang
{
	int sum;
	int xunhao;
};

int DuXuWenJian(HuffNode hufftree[],string InFile)
{
	std::fstream infile;
	unsigned char ch;
	weijiang z[256] = { 0 };
	for (int k = 0; k < 256; k++)//初始化
		z[k].xunhao = k;
	infile.open(InFile); //打开文件
	if (!infile) 
	{
		std::cout << " 打开文件失败 " << std::endl
	}
	while (infile.get((char&)ch))//获取文件信息
	{
		for (int g = 0; g < 256; g++) 
		{
			if (ch == g) //统计字符频度
				z[g].sum++;
		}
	}
	for (int m = 0; m<256; m++)//冒泡排序
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)//频度从小到大排序
			{
				int temp1 = z[n].sum;
				z[n].sum = z[m].sum;
				z[m].sum = temp1;

				int temp2 = z[n].xunhao;
				z[n].xunhao = z[m].xunhao;
				z[m].xunhao = temp2;
			}
		}
	}
	for (int m = 0; m<256; m++)//冒泡排序
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)//序号排序
			{
				int temp2 = z[n].xunhao;
				z[n].xunhao = z[m].xunhao;
				z[m].xunhao = temp2;
			}
		}
	}
	int d = 0;//有效字节
	for (int j = 0; j < 256; j++)//去掉频度为0的字符
	{
		if (z[j].sum != 0)
		{
			hufftree[d].ch = z[j].xunhao;
			hufftree[d].count = z[j].sum;
			d++;
		}
	}
	infile.close();//关闭文件
	return d;//返回字符个数
}

// 选择最小和次小的两个结点，建立哈夫曼树调用
void select(HuffNode *huf_tree, int n, int *s1, int *s2)
{
	// 找最小结点
	unsigned int i;
	unsigned long min = LONG_MAX;
	for (i = 0; i < n; i++)
		if (huf_tree[i].parent == -1 && huf_tree[i].count < min)
		{
			min = huf_tree[i].count;
			*s1 = i;//记录下标
		}
	huf_tree[*s1].parent = 1;   // 标记此结点已被选中

	// 找次小结点
	min = LONG_MAX;
	for (i = 0; i < n; i++)
	{
		if (huf_tree[i].parent == -1 && huf_tree[i].count < min)
		{
			min = huf_tree[i].count;
			*s2 = i;
		}
	}
}

// 建立哈夫曼树
void creat(HuffNode *huf_tree, int n)
{
	int i;
	int s1, s2;
	for (i = n; i < 2*n-1; ++i)
	{
		select(huf_tree, i, &s1, &s2);		// 选择最小的两个结点
		huf_tree[s1].parent = i;            //原点双亲为i
		huf_tree[s2].parent = i;           
		huf_tree[i].lch = s1;               //新结点左子树是最小的s1
		huf_tree[i].rch = s2;               //新结点右子树是最小s2
		huf_tree[i].count = huf_tree[s1].count + huf_tree[s2].count;////新结点的权值
	}
}


// 生成哈夫曼编码
void creat_hmcode(HuffNode *huf_tree, int n)//生成哈夫曼编码
{
	int i;
	int cur, next, index;
	char code_tmp[256];		// 暂存编码，最多256个叶子，编码长度不超多255
	code_tmp[255] = '\0';

	for (i = 0; i < n; ++i)
	{
		index = 256 - 1;	// 编码临时空间初始化

		// 从叶子向根求编码
		for (cur = i, next = huf_tree[i].parent; next != -1; next = huf_tree[next].parent)
		{
			if (huf_tree[next].lch == cur)
				code_tmp[--index] = '0';	// 左‘0’
			else
				code_tmp[--index] = '1';	// 右‘1’

			cur = next;

		}
		strcpy(huf_tree[i].bits, &code_tmp[index]);     // 正向保存编码到树结点相应域 index是第一个
	}
}
