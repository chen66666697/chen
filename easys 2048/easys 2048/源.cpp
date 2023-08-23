#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<time.h>	
#include<math.h>
#include<thread>	//ʹ�ö��߳�
#define MARGINS 10 //����֮��ļ��
#define SIDE_LENGTH 95  //�����С
#define INITGR (4*SIDE_LENGTH+5*MARGINS)	//������
#define NUMBER 4  //4*4
#define MOST_CREATE 2		//�����������
#define EXTRENDINITGR 200		//���Ž���
enum Color
{
	color0 = RGB(205, 193, 180),//0
	color1 = RGB(238, 228, 218),//2
	color2 = RGB(237, 224, 200),//4
	color3 = RGB(242, 177, 121),//8
	color4 = RGB(245, 149, 99),//16
	color5 = RGB(246, 124, 95),//32
	color6 = RGB(246, 94, 59),//64
	color7 = RGB(242, 177, 121),//128
	color8 = RGB(237, 204, 97),//256
	color9 = RGB(255, 0, 128),//512
	color10 = RGB(145, 0, 72),//1024
	color11 = RGB(242, 17, 158),//2048
	colorroundrect = RGB(205, 193, 180),//��������
	colorback = RGB(187, 173, 160),//����
};
Color arr[14] = { color0 ,color1 ,color2 ,color3,color4,color5,color6,color7,color8,color9,color10,color11,colorroundrect,colorback };
int a[NUMBER][NUMBER] = { 0 };	//������ֵ�洢
int flag2 = 1;		//��Ϸ�Ƿ�����	1,���  0������ 
int timeclock = 0;  //ʱ��
void gamedraw();		//ͼ�ν������
int statenumber();		//�������һ����
void createnumber();	//�������������������ж�����
void keyboard();		//��ȡ�������뼰�����������
void moveup();			//һ�¶��Ǵ������֣������ںϣ��������Ҳ����Ҷ�˵�ɣ�
void movedown();
void moveleft();
void moveright();
void ReadFile();		//��ȡ�ļ�
void WriteFile();		//д���ļ�
void Printtime();		//���̵߳��ã���ʾʱ��
void moveright()
{
	for (int i = 0; i < NUMBER; i++)
	{
		int temp = NUMBER-1;
		for (int j = NUMBER-2; j>=0; j--)
		{
			if (a[i][j] != 0)
			{
				if (a[i][temp] == 0)
				{
					a[i][temp] = a[i][j];
					a[i][j] = 0;
				}
				else if (a[i][temp] == a[i][j])
				{
					a[i][temp] += a[i][j];
					a[i][j] = 0;
					temp--;
				}
				else
				{
					a[i][temp -1] = a[i][j];
					if (temp -1 != j)
					{
						a[i][j] = 0;
					}
					temp--;
				}
			}
		}
	}
}
void moveleft()
{
	for (int i = 0; i<NUMBER; i++)
	{
		int temp = 0;
		for (int j = 1 ;j < NUMBER; j++)
		{
			if (a[i][j] != 0)
			{
				if (a[i][temp] == 0)
				{
					a[i][temp] = a[i][j];
					a[i][j] = 0;
				}
				else if (a[i][temp] == a[i][j])
				{
					a[i][temp] += a[i][j];
					a[i][j] = 0;
					temp++;
				}
				else
				{
					a[i][temp + 1] = a[i][j];
					if (temp + 1 != j)
					{
						a[i][j] = 0;
					}
					temp++;
				}
			}
		}
	}
}
void movedown()
	{
		for (int i = 0; i <NUMBER; i++)
		{
			int temp = NUMBER-1;
			for (int j = NUMBER - 2; j >= 0; j--)
			{
				if (a[j][i] != 0)
				{
					if (a[temp][i] == 0)
					{
						a[temp][i] = a[j][i];
						a[j][i] = 0;
					}
					else if (a[temp][i] == a[j][i])
					{
						a[temp][i] += a[j][i];
						a[j][i] = 0;
						temp--;
					}
					else
					{
						a[temp -1][i] = a[j][i];
						if (temp -1 != j)
						{
							a[j][i] = 0;
						}
						temp--;
					}
				}
			}
		}
	}
void keyboard()
{
	switch (_getch())//�ú�����ȡ�����һ���ַ������ûس�����ͬ��getchar();
	{
		case 'w':
		case 'W':
			moveup();
			createnumber();
			break;
		case 's':
		case 'S':
			movedown();
			createnumber();
			break;
		case 'a':
		case 'A':
			moveleft();
			createnumber();
			break;
		case 'd':
		case 'D':
			moveright();
			createnumber();
			break;
		case 'r':
		case 'R':
			WriteFile();
		default:
			break;
	}
}
void moveup()
{
	for (int i = 0; i < NUMBER; i++)
	{
		int temp = 0;
		for (int j = 1; j < NUMBER; j++)
		{
			if (a[j][i] != 0)
			{
				if (a[temp][i] == 0)
				{
					a[temp][i] = a[j][i];
					a[j][i] = 0;
				}
				else if (a[temp][i] == a[j][i])
				{
					a[temp][i] += a[j][i];
					a[j][i] = 0;
					temp++;
				}
				else
				{
					a[temp + 1][i] = a[j][i];
					if (temp + 1 != j)
					{
						a[j][i] = 0;
					}
					temp++;
				}
			}
		}
	}
}
void createnumber()
{
	int flag = 0;
	int flag1 = 0,flag3=0;
	char str[] = "";
	for (int i = 0; i < NUMBER; i++)		//��ȡ��ռλ�ã����߿������Ϊ��ʣ������λ
	{
		for (int j = 0; j < NUMBER; j++)
		{
			if (a[i][j] != 0) { flag++; }	
		}
	}
	if (flag < NUMBER* NUMBER-1)
	{
		for (int i = 1; i <= MOST_CREATE;)	//����ж���2���գ�����������ѭ����while����һ��
		{
			int b = rand() % NUMBER;
			int c = rand() % NUMBER;
			if (a[b][c] == 0)
			{
				a[b][c] = statenumber();
				i++;
			}
		}
	}
	else if (flag == NUMBER * NUMBER - 1)	//�����ֻ��1���գ�����1��
	{
		while (1)
		{
			int b = rand() % NUMBER;
			int c = rand() % NUMBER;
			if (a[b][c] == 0)
			{
				a[b][c] = statenumber();
				break;
			}
		}
	}
	else if (flag == NUMBER * NUMBER )		//���ռ���ˣ����������֣��ж��Ƿ����ٺϳ�
	{
		for (int i = 0; i < NUMBER-1; i++)
		{
			for (int j = 0; j < NUMBER-1; j++)
			{
				if (a[i][j] == a[i][j + 1] || a[i][j] == a[i + 1][j])
				{
					flag1= 1;   //���12������
				}	
			}
			if (flag1 == 1)
			{
				break;
			}
		}
		for (int i = 3, j = 0; j < NUMBER - 1; j++)
		{
			if (a[j][i] == a[j + 1][i]) flag3 = 1;		//���ʣ�෽��
		}
		if ((flag1+flag3) == 0)		//�����ܺϳɣ��Ǿ�GG
		{
			//cleardevice();
			settextcolor(RED);
			int tw = textwidth("��ʧ����!!");
			int ty = textheight("��ʧ����!!");
			outtextxy((INITGR / 2) - tw / 2, (INITGR / 2) - ty / 2, "��ʧ����!!");		//��ʾʧ��
			flag2 = 0;				//��Ϸ������
		}
	}
	
}
int statenumber()
{
	srand((unsigned)time(NULL) + clock());  //���������
	int temp = rand() % 5;
	if (temp == 0||1||2 ) { return 2; }		//����2�ļ���Ϊ75%
	else { return 4; }		//����4�ļ���Ϊ25%
}
void gamedraw()
{
	for (int i = 1; i <= NUMBER; i++) //˫ѭ��,Ϊÿ�����ֻ��ƾ��ο�
	{
		for (int j = 1; j <= NUMBER; j++)
		{
			int x = (i - 1) * SIDE_LENGTH + i * MARGINS;
			int y = (j - 1) * SIDE_LENGTH + j * MARGINS;
			setfillcolor(arr[12]);
			solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);
			char str[10] = " ";
			sprintf_s(str, "%d",a[j - 1][i - 1]);	//������ת��Ϊstr��������ʾ
			setbkmode(TRANSPARENT);		//���ֻ����ֱ���ɾ��
			settextstyle(50, 0, "����");	//���������ʽ
			int tw = textwidth(str);		//�����ַ�����
			int th = textheight(str);		//�����ַ����
			int tx = (SIDE_LENGTH - tw) / 2;	
			int ty = (SIDE_LENGTH - th) / 2;
			if (a[j - 1][i - 1] != 0)
			{
				int index = (int)log2((int)a[j - 1][i - 1]);
				COLORREF tcolor = arr[index];
				setfillcolor(tcolor);
				solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);		//����Բ�Ǿ���
				outtextxy(x + tx, y + ty, str);	//���־�����ʾ
			}
		}
	}
	//���ƺͱ���浵,Ŀ�����Ϣͼ�Σ�ʱ����ʾ����һ���߳�
	setfillcolor(arr[12]);
	solidroundrect(INITGR, MARGINS, INITGR + EXTRENDINITGR-MARGINS, INITGR-MARGINS, 10, 10);//��չ�ܽ���
	setfillcolor(arr[2]);
	solidroundrect(INITGR + MARGINS, 120 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 220 + 4 * MARGINS, 10, 10);//�������
	solidroundrect(INITGR + MARGINS, 240 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 340 + 4 * MARGINS, 10, 10);//Ŀ�꣺2048
	settextstyle(25, 0, "����");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("R.������Ϸ");
	int ty1 = textheight("R.������Ϸ");
	int tw2 = textwidth("Ŀ��:");
	int ty2 = textheight("Ŀ��:");
	int tw3 = textwidth("2048");
	int ty3 = textheight("2048");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw1) / 2, 120 + 4 * MARGINS + (100 - ty1) / 2, "R.������Ϸ");
	settextstyle(30, 0, "����");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 240 + 4 * MARGINS + (50 - ty2) / 2, "Ŀ��:");
	settextstyle(40, 0, "����");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 240 + 4 * MARGINS+50 + (50 - ty2) / 2, "2048");
	//�˴�ʱ��ҲҪˢ����ʾ����Ȼÿ�β�����ʱ����ʾ�ᱻ����
	char str[10] = " ";
	sprintf_s(str, "%d:%d:%d", timeclock / 3600, (timeclock % 3600) / 60, timeclock % 60);
	int tw4 = textwidth("ʱ��:");
	int ty4 = textheight("ʱ��:");
	int tw5 = textwidth("str");
	int ty5 = textheight("str");
	settextstyle(30, 0, "����");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	solidroundrect(INITGR + MARGINS, 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 100, 10, 10);//ʱ�����
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw4) / 2, 4 * MARGINS + (50 - ty4) / 2, "ʱ��:");
	settextstyle(40, 0, "����");
	outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw5) / 2, 50 + 4 * MARGINS + (50 - ty5) / 2, str);
	//��ԭ��������
	settextcolor(WHITE);
}
void ReadFile()
{
	FILE* fp;
	int i = 0;
	char temp[100];
	fopen_s(&fp,"./game.txt", "r");
	if (!fp)
	{
		//��ȡʧ�ܡ�
		return;
	}
	while (!feof(fp))		//�����ַ�
	{
		if (!fgets(temp, 100, fp))
			break;
		//����BOMͷ ��utf-8
		if (strstr(temp, "\xEF\xBB\xBF"))
		{
			strcpy_s(temp + 3, 20, temp);	//ɾ��BOMͷ
		}
		if (temp[0] == '#')	//��ȡ��Ϸ״̬
		{
			sscanf_s(temp+1, "%*s %d", &flag2);
			if (flag2 == 0)		//����������Ϸ���������¿�ʱ����Ϸ
			{
				createnumber();
				flag2 = 1;
				//��Ҫ�ر��ļ���ֹд��ʱ����
				fclose(fp);
				return ;
			}
				
		}
		else if (temp[0] == '@')	//����ʱ��
		{
			sscanf_s(temp + 1, "%*s %d",&timeclock);
		}
		else
		{
			sscanf_s(temp, "%d %d %d %d", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);	//��ȡ������������
			i++;
		}
	}
	fclose(fp);
}
void WriteFile()
{
	FILE *fp;
	fopen_s(&fp, "game.txt", "w");
	if (fp == NULL)
	{
		return;
	}
	fprintf(fp, "#flag2 %d\n", flag2); //д����Ϸ״̬
	for (int i = 0; i < 4; i++)
	{
		fprintf(fp, "%d %d %d %d\n", a[i][0], a[i][1], a[i][2], a[i][3]);		//д����Ϸ����
	}
	fprintf(fp, "@timeclock %d", timeclock);  //д��ʱ��
	fclose(fp);
}
void Printtime()
{
	while(1) //��ѭ��������߳�һֱ����
	{
		Sleep(1000);	//�ӳ�һ��
		if (flag2 == 0)
		{
			return;
		}
		timeclock++;
		char str[10] = " ";
		sprintf_s(str, "%d:%d:%d", timeclock/3600, (timeclock%3600)/60, timeclock%60);  //��������
		//ʱ�������ʾ
		int tw1 = textwidth("ʱ��:");
		int ty1 = textheight("ʱ��:");
		int tw2 = textwidth("str");
		int ty2 = textheight("str");
		settextstyle(30, 0, "����");
		settextcolor(RED);
		setbkmode(TRANSPARENT);
		solidroundrect(INITGR + MARGINS, 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 100, 10, 10);//ʱ�����
		outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw1) / 2, 4 * MARGINS + (50 - ty1) / 2,"ʱ��:");
		settextstyle(40, 0, "����");
		outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 50+4 * MARGINS + (50 - ty2) / 2, str);
		//��ԭ��������
		settextcolor(WHITE);
	}
}
void menu()		//�˵���ѡ��Q��E
{
	//��ʾ����
	setfillcolor(arr[1]);
	solidroundrect((INITGR-330)/2, 43, (INITGR - 330) / 2 +330, 43+100, 10, 10);
	solidroundrect((INITGR - 330) / 2, 43+43+100, (INITGR - 330) / 2 + 330, 43 +43+ 100+100, 10, 10);
	settextstyle(30, 0, "����");
	settextcolor(arr[3]);
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("Q.����Ϸ");
	int ty1 = textheight("Q.����Ϸ");
	int tw2 = textwidth("E.������Ϸ");
	int ty2 = textheight("E.������Ϸ");
	outtextxy((INITGR - 330) / 2 + (330 - tw1)/2, 43 + (100 - ty1 )/2, "Q.����Ϸ");
	outtextxy((INITGR - 330) / 2 + (330 - tw2 )/2, 43 +43+100+ (100 - ty2 )/2, "E.������Ϸ");
}
int main()
{
	//easyx�����ʼ��
	initgraph(INITGR, INITGR);
	setbkcolor(arr[13]);
	cleardevice();
	menu();
	while (1)	//��ȡQ��E
	{
		int in=0;
		switch (_getch())
		{
			case 'q':
			case 'Q':
				in = 1;
				createnumber();
				break;
			case 'e':
			case 'E':
				in = 1;
				ReadFile();
				break;
			default:
				break;
		}
		if (in == 1)break;
	}
	//���»��ƽ���
	initgraph(INITGR + EXTRENDINITGR, INITGR, 1);
	setbkcolor(arr[13]);
	cleardevice();
	std::thread th(Printtime);		//std::�����򣬴����߳�
	th.detach();	//�����̲߳���ִ��
	while (1) //��ѭ��
	{
		if(flag2!=0)
		{
			gamedraw();	
		}
		keyboard();
	}
	closegraph();	//�ر�ͼ�ο�
	return 0;	
}