#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

// �����������
struct HuffNode
{
	unsigned char ch;  //�ֽڷ�
	long count;  //�ֽڳ���Ƶ��
	int parent; //���ڵ�
	int lch;  //����
	int rch;  //�Һ���
	char bits[256]; // ����������
};
//�ļ��ṹ��
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

	for (int k = 0; k < 256; k++)
		z[k].xunhao = k;

	infile.open(InFile);
	if (!infile)
	{
		std::cout << " ���ļ�ʧ�� " << std::endl;

	}

	while (infile.get((char&)ch))
	{
		for (int g = 0; g < 256; g++)
		{
			if (ch == g)
				z[g].sum++;
		}
	}

	for (int m = 0; m<256; m++)
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)
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
	for (int m = 0; m<256; m++)
	{
		for (int n = m + 1; n <= 255; n++)
		{
			if (z[n].sum <= z[m].sum)
			{
				int temp2 = z[n].xunhao;
				z[n].xunhao = z[m].xunhao;
				z[m].xunhao = temp2;
			}
		}

	}
	int d = 0;//��Ч�ֽ�
	for (int j = 0; j < 256; j++)
	{
		if (z[j].sum != 0)
		{
			hufftree[d].ch = z[j].xunhao;
			hufftree[d].count = z[j].sum;
			d++;
		}
	}
	infile.close();
	return d;
}

// ѡ����С�ʹ�С��������㣬����������������
void select(HuffNode *huf_tree, int n, int *s1, int *s2)
{
	// ����С���
	unsigned int i;
	unsigned long min = LONG_MAX;
	for (i = 0; i < n; i++)
		if (huf_tree[i].parent == -1 && huf_tree[i].count < min)
		{
			min = huf_tree[i].count;
			*s1 = i;//��¼�±�
		}
	huf_tree[*s1].parent = 1;   // ��Ǵ˽���ѱ�ѡ��

	// �Ҵ�С���
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

// ������������
void creat(HuffNode *huf_tree, int n)
{
	int i;
	int s1, s2;
	for (i = n; i < 2*n-1; ++i)
	{
		select(huf_tree, i, &s1, &s2);		// ѡ����С���������
		huf_tree[s1].parent = i;            //ԭ��˫��Ϊi
		huf_tree[s2].parent = i;           
		huf_tree[i].lch = s1;               //�½������������С��s1
		huf_tree[i].rch = s2;               //�½������������Сs2
		huf_tree[i].count = huf_tree[s1].count + huf_tree[s2].count;////�½���Ȩֵ
	}
}


// ���ɹ���������
void creat_hmcode(HuffNode *huf_tree, int n)//���ɹ���������
{
	int i;
	int cur, next, index;
	char code_tmp[256];		// �ݴ���룬���256��Ҷ�ӣ����볤�Ȳ�����255
	code_tmp[255] = '\0';

	for (i = 0; i < n; ++i)
	{
		index = 256 - 1;	// ������ʱ�ռ��ʼ��

		// ��Ҷ����������
		for (cur = i, next = huf_tree[i].parent; next != -1; next = huf_tree[next].parent)
		{
			if (huf_tree[next].lch == cur)
				code_tmp[--index] = '0';	// ��0��
			else
				code_tmp[--index] = '1';	// �ҡ�1��

			cur = next;

		}
		strcpy(huf_tree[i].bits, &code_tmp[index]);     // ���򱣴���뵽�������Ӧ�� index�ǵ�һ��
	}
}