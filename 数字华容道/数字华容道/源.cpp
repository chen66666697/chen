#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<thread>		//���߳�
#define INUMBER 3		//3*3
#define SIDE_LENGTH 100		//�����С
#define MARGINS 10			//������
#define INITGR (INUMBER*SIDE_LENGTH+(INUMBER+1)*MARGINS)		//�������С
#define EXTRENDINITGR 170					//���������곤��
int a[INUMBER * INUMBER] = {0,1,2,3,4,5,6,7,8};			//ϴ���㷨��ѡȡ�����������жԻ�
int b[INUMBER][INUMBER] = { 0 };						//ʵ�ʲ���������
int flag2 = 0;  //��Ϸ״̬    0.δͨ��  1.ͨ��
int timeclock = 0;			//ʱ��洢
void createmap();			//�����ͼ����
void createnumber();			//���ִ��ң�����
void moveleft(int x, int y);		//�����ĸ������Ҷ�˵,�ƶ�
void moveright(int x, int y);
void movedown(int x, int y);
void moveup(int x, int y);
void ReadFile();				//��ȡ�ļ�
void WriteFile();				//д���ļ�
void keyboard();				//��������
void outtext1();				//�ж��Ƿ�ɹ�
void outtext2();				//�����Ч����
void Printtime();				//���̣߳����ʱ��
void outtext1()
{
	int temp = 0,flag=0;		//�ж�temp����������Ƿ�Ϊ0,�Լ����һ���Ƿ�Ϊ0
	for (int i = 0; i < INUMBER * INUMBER - 1; i++)
	{
		for (int j = i + 1; j < INUMBER * INUMBER; j++)
		{
			if (a[i] == 0) { break; }
			else if (a[j] == 0) { }
			else { if (a[i] > a[j])temp++; }
			if (a[INUMBER * INUMBER - 1] == 0)flag = 1;
		}
	}
	if (temp == 0 && flag == 1)			//��������������ɹ�
	{
		settextcolor(RED);
		settextstyle(40, 0, "����");
		int tw = textwidth("��ɹ���!!");
		int ty = textwidth("��ɹ���!!");
		outtextxy((INITGR / 2) - tw / 2, (INITGR / 2) - ty / 2, "��ɹ���!!");
		flag2 = 1;
	}
	//��ԭ������ɫ
	settextcolor(WHITE);
}
void outtext2()
{
	//����Ĳ���Ϊ��Ч����ʱ�����
	settextstyle(20, 0, "����");
	//settextcolor(RGB(255, 255, 255));
	int tw = textwidth("��Ч����!!");
	int ty = textheight("��Ч����!!");
	setfillcolor(WHITE);
	solidroundrect(INITGR + MARGINS, 2 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 100 + 2 * MARGINS, 10, 10);
	settextcolor(RED);
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw) / 2, 2 * MARGINS + (100 - ty) / 2, "��Ч����!!");
	//��ԭ��������
	settextcolor(WHITE);
}
void ReadFile()
{
	FILE* fp;
	int i = 0;
	char temp[100];
	fopen_s(&fp, "./game.txt", "r");
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
			sscanf_s(temp + 1, "%*s %d", &flag2);
			if (flag2 == 1)		//����������Ϸ�ɹ������¿�ʼ����Ϸ
			{
				createnumber();
				flag2 = 0;
				//��Ҫ�ر��ļ���ֹд��ʱ����
				fclose(fp);
				return;
			}

		}
		else if (temp[0] == '@')	//����ʱ��
		{
			sscanf_s(temp + 1, "%*s %d", &timeclock);
		}
		else
		{
			sscanf_s(temp, "%d %d %d", &b[i][0], &b[i][1], &b[i][2]);	//��ȡ������������
			i++;
		}
	}
	fclose(fp);
}
void WriteFile()
{
	FILE* fp;
	fopen_s(&fp, "game.txt", "w");
	if (fp == NULL)
	{
		//�ļ���ȡʧ��
		return;
	}
	fprintf(fp, "#flag2 %d\n", flag2); //д����Ϸ״̬
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d %d %d\n", b[i][0], b[i][1], b[i][2]);		//д����Ϸ����
	}
	fprintf(fp, "@timeclock %d", timeclock);  //д��ʱ��
	fclose(fp);		//�ر��ļ�
}
void menu()		//�˵���ѡ��Q��E
{
	//��ʾ����
	setfillcolor(RGB(238, 228, 218));
	solidroundrect((INITGR - 230) / 2, 43, (INITGR - 230) / 2 + 230, 43 + 100, 10, 10);
	solidroundrect((INITGR - 230) / 2, 43 + 43 + 100, (INITGR - 230) / 2 + 230, 43 + 43 + 100 + 100, 10, 10);
	settextstyle(30, 0, "����");
	settextcolor(RGB(245, 149, 99));
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("Q.����Ϸ");
	int ty1 = textheight("Q.����Ϸ");
	int tw2 = textwidth("E.������Ϸ");
	int ty2 = textheight("E.������Ϸ");
	outtextxy((INITGR - 230) / 2 + (230 - tw1) / 2, 43 + (100 - ty1) / 2, "Q.����Ϸ");
	outtextxy((INITGR - 230) / 2 + (230 - tw2) / 2, 43 + 43 + 100 + (100 - ty2) / 2, "E.������Ϸ");
}
void keyboard()
{
	int flag = 0, temp1 = 0, temp2 = 0;
	for (int i = 1; i <= INUMBER; i++)		//Ѱ��0��λ�ã��������������ֽ����������ƶ�
	{
		for (int j = 1; j <= INUMBER; j++)
		{
			if (b[i - 1][j - 1] == 0)
			{
				temp1 = i - 1;
				temp2 = j - 1;
				flag = 1;
			}
			if (flag == 1)
			{
				break;
			}
		}
		if (flag == 1)
		{
			break;
		}
	}
	switch (_getch())	//��getchar()��ͬ���ú�����ȡ�ַ������ûس���w,a,s,d,������˵��
	{
		case 'W':
		case 'w':
			moveup(temp1,temp2);
			createmap();
			break;

		case 'A':
		case 'a':
			moveleft(temp1, temp2);
			createmap();
			break;

		case 's':
		case 'S':
			movedown(temp1, temp2);
			createmap();
			break;

		case 'd':
		case 'D':
			moveright(temp1, temp2);
			createmap();
			break;
		case 'r':		//�����ļ���
		case 'R':
			WriteFile();
			break;
		default:
			break;
	}
}
void moveup(int x, int y)
{
	if (x < INUMBER - 1 && x >= 0)	//�����ƶ��������Ļ���ȴ���һ֡��ˢ��
	{
		b[x][y] = b[x + 1][y];
		b[x + 1][y] = 0;
		cleardevice();
		
	}
	else			//�����ƶ�����Ϊ��Ч����
	{
		outtext2();
	}

}
void movedown(int x, int y)
{
	if (x > 0 && x <= INUMBER - 1)		//�����ƶ��������Ļ���ȴ���һ֡��ˢ��
	{
		b[x][y] = b[x - 1][y];
		b[x - 1][y] = 0;
		cleardevice();
	}
	else
	{
		outtext2();			//�����ƶ�����Ϊ��Ч����
	}
}
void moveright(int x, int y)
{
	if (y > 0 && y <= INUMBER - 1)
	{
		b[x][y] = b[x][y - 1];
		b[x][y - 1] = 0;
		cleardevice();
	}
	else
	{
		outtext2();
	}
}
void moveleft(int x, int y)
{
	if (y < INUMBER - 1 && y >= 0)
	{
		b[x][y] = b[x][y + 1];
		b[x][y + 1] = 0;
		cleardevice();
	}
	else
	{
		outtext2();
	}
}
void createnumber()
{
	int temp = 0;
	int flag = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < INUMBER * INUMBER; i++)			//ϴ���㷨���̶�ϴ3*3��
	{
		int x = rand() % INUMBER * INUMBER;
		flag = a[x];
		a[x] = a[i];
		a[i] = flag;
	}
	while (1)
	{
		temp = 0;
		for (int i = 0; i < INUMBER * INUMBER-1; i++)
		{
			for (int j = i + 1; j < INUMBER * INUMBER; j++)
			{
				if (a[i] == 0) { break; }
				else if(a[j]==0){ }
				else { if(a[i] > a[j])temp++; }
			}
		}
		if (temp % 2 == 0 && temp != 0)		//�ж�������Ƿ�Ϊż��,ͬʱ����Բ�ӦΪ0��Ϊ��Ϳ��ܺ����׻�ʤ,����������ϴһ��
		{
			break;
		}
		else
		{
			int x = rand() % INUMBER * INUMBER;
			int y = rand() % INUMBER * INUMBER;
			flag = a[x];
			a[x] = a[y];
			a[y] = flag;

		}
	}	
	for (int i = 0; i < INUMBER * INUMBER; i++)			//����û���⣬д��b�У���Ҳ�벻����Ϊʲ����д�ˣ�����������
	{
		int x = i / 3;
		int y = i % 3;
		b[x][y] = a[i];
	}
}
void createmap()
{
	for (int i = 1; i <= INUMBER; i++)	//����3*3�ķ������
	{
		for (int j = 1; j <= INUMBER; j++)
		{
			a[(i - 1) * 3 + j - 1] = b[i - 1][j - 1];
			int x = (i - 1) * SIDE_LENGTH + i * MARGINS;
			int y = (j - 1) * SIDE_LENGTH + j * MARGINS;
			solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);		//Բ�Ǿ���
			char str[10] = " ";
			sprintf_s(str, "%d", b[j - 1][i - 1]);				//������ת��Ϊ�ַ���
			setbkmode(TRANSPARENT);				
			settextstyle(50, 0, "����");		
			int tw = textwidth(str);
			int th = textheight(str);
			int tx = (SIDE_LENGTH - tw) / 2;
			int ty = (SIDE_LENGTH - th) / 2;
			if (b[j - 1][i - 1] != 0)
			{
				setfillcolor(RGB(240,155,89));
				solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);
				outtextxy(x + tx, y + ty, str);
			}
			else
			{
				setfillcolor(RGB(240, 155, 89));
				solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);
			}
		}
	}
	//���ɸ�����
	setfillcolor(WHITE);
	solidroundrect(INITGR + MARGINS, 200 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 270 + 4 * MARGINS, 10, 10);//�������
	settextstyle(25, 0, "����");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("R.������Ϸ");
	int ty1 = textheight("R.������Ϸ");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw1) / 2, 200 + 4 * MARGINS + (70 - ty1) / 2, "R.������Ϸ");
	char str[10] = " ";
	sprintf_s(str, "%d:%d:%d", timeclock / 3600, (timeclock % 3600) / 60, timeclock % 60);  //��������
	//ʱ�������ʾ������ҲҪˢ��һ�Σ���ֹ������
	int tw2 = textwidth("ʱ��:");
	int ty2 = textheight("ʱ��:");
	int tw3 = textwidth("str");
	int ty3 = textheight("str");
	settextstyle(20, 0, "����");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	solidroundrect(INITGR + MARGINS, 100 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 180, 10, 10);  //ʱ�����
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 100 + 4 * MARGINS + (40 - ty2) / 2, "ʱ��:");
	settextstyle(25, 0, "����");
	outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw3) / 2, 140 + 4 * MARGINS + (40 - ty3) / 2, str);
	//��ԭ�������ã���Ȼ��һ���ÿ��ܽ�����ɫ��仯
	settextcolor(WHITE);
}
void Printtime()
{
	while (1) //��ѭ��������߳�һֱ����
	{
		Sleep(1000);	//�ӳ�һ��
		if (flag2 == 1)
		{
			return;
		}
		timeclock++;
		char str[10] = " ";
		sprintf_s(str, "%d:%d:%d", timeclock / 3600, (timeclock % 3600) / 60, timeclock % 60);  //��������
		//ʱ�������ʾ
		int tw2 = textwidth("ʱ��:");
		int ty2 = textheight("ʱ��:");
		int tw3 = textwidth("str");
		int ty3 = textheight("str");
		settextstyle(20, 0, "����");
		settextcolor(RED);
		setbkmode(TRANSPARENT);
		solidroundrect(INITGR + MARGINS, 100 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 180, 10, 10);//ʱ�����
		outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 100 + 4 * MARGINS + (40 - ty2) / 2, "ʱ��:");
		settextstyle(25, 0, "����");
		outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw3) / 2, 140 + 4 * MARGINS + (40 - ty3) / 2, str);
		//��ԭ�������ã���Ȼ��һ���ÿ��ܽ�����ɫ��仯
		settextcolor(WHITE);
	}
}
int main()
{
	//�˵��������
	initgraph(INITGR, INITGR);
	setbkcolor(RGB(187, 173, 160));
	cleardevice();
	menu();
	while (1)	//��ȡQ��E��ѡ������Ϸ���߼�����Ϸ
	{
		int in = 0;
		switch (_getch())
		{
		case 'q':
		case 'Q':
			in = 1;
			createnumber();
			createmap();
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
	//��Ϸ��ʼ��Ϸ�������
	initgraph(INITGR + EXTRENDINITGR, INITGR,1);
	setbkcolor(RGB(220, 155, 100));
	cleardevice();
	createmap();
	std::thread th(Printtime);		//std::�����򣬴����߳�
	th.detach();	//�����̲߳���ִ��
	while (1)
	{
		outtext1();
		keyboard();
	}
}