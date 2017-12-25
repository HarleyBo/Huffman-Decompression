#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Extract.h"
using namespace std;

int main()
{

	int n;//��Ч�ֽ�
	HuffNode hufftree[512];//���511�����
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
		int opt, flag = 0;		// ÿ�ν���ѭ����Ҫ��ʼ��flagΪ0
		char ifname[256]; 
		char ofname[256];		// ������������ļ���
		printf(" =======================================\n");
		cout << "        ***Huffman�ļ�ѹ��***" << endl;
		printf(" =======================================\n");
		printf("            ��  1��ѹ��              \n");
		printf("            ��  2����ѹ              \n");
		printf("            ��  3���˳�              \n");
		printf("         �� ���������Ĳ�����         \n");
		scanf("%d", &opt);

		if (opt == 3)
			exit(1);
		else
		{
			printf("������������ļ�����");
			fflush(stdin);		// ��ձ�׼����������ֹ����gets������ȡ�ļ���
			gets(ifname);
			printf("���������ɵ��ļ�����");
			fflush(stdin);
			gets(ofname);
			
		}
		switch (opt)
		{
		case 1:
		{
			//���ļ����ֽڳ���
			FILE *file;
			file = fopen(ifname, "r");
			fseek(file, SEEK_SET, SEEK_END);
			long flength = ftell(file);
			fclose(file);


			n = DuXuWenJian(hufftree, ifname);//��ȡ�ļ��������ֽ�Ƶ�����򣬷�����Ч�ֽڣ�Ƶ�ʲ�Ϊ0��
			creat(hufftree, n);//��������������ָ�뺢�Ӹ��ױ�ʾ��

			creat_hmcode(hufftree, n);//���ɹ���������

			//for (int d = 0; d < 2 * n - 1; d++)//��������
			//{
			//	printf("%4d: %4u,   %9d,  %9d,   %9d,  %9d       ", d, hufftree[d].ch, hufftree[d].count, hufftree[d].parent, hufftree[d].lch, hufftree[d].rch);  /* ���ڲ��� */

			//	for (int f = 0; hufftree[d].bits[f] == '0' || hufftree[d].bits[f] == '1'; f++)
			//		printf("%c", hufftree[d].bits[f]);
			//	printf("\n");
			//}

			flag = compress(hufftree, n, flength, ifname, ofname);	// ѹ��������ֵ�����ж��Ƿ��ļ���������
			if (flag != -1)
			{
				cout << "\n�����͹��Ե�," << ifname << "����ѹ���С���\n";
				cout << "�������˿͹�," << ofname << "ѹ����ϡ���\n";
			}
			break;
		}
		case 2:
		{
			flag = extract(hufftree, ifname, ofname);		// ��ѹ������ֵ�����ж��Ƿ��ļ���������
			
			if (flag != -1)
			{
				cout << "\n�����͹��Ե�," << ifname << "���ڽ�ѹ�С���\n";
				cout << "�������˿͹�," << ofname << "��ѹ��ϡ���\n";
			}
			break;
		}


		if (flag == -1)
			printf("\nSorry ,��������ļ�\"%s\"������\n", ifname);		// �����־Ϊ��-1���������ļ�������
		else
			printf("\n������ɣ�\n");		// �������
		system("pause");
		system("CLS");
		}

		return 0;

	}


}