#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<time.h>	
#include<math.h>
#include<thread>	//使用多线程
#define MARGINS 10 //方块之间的间隔
#define SIDE_LENGTH 95  //方块大小
#define INITGR (4*SIDE_LENGTH+5*MARGINS)	//主界面
#define NUMBER 4  //4*4
#define MOST_CREATE 2		//最大数量生成
#define EXTRENDINITGR 200		//扩张界面
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
	colorroundrect = RGB(205, 193, 180),//方块颜射
	colorback = RGB(187, 173, 160),//背景
};
Color arr[14] = { color0 ,color1 ,color2 ,color3,color4,color5,color6,color7,color8,color9,color10,color11,colorroundrect,colorback };
int a[NUMBER][NUMBER] = { 0 };	//方块数值存储
int flag2 = 1;		//游戏是否死亡	1,存活  0，死亡 
int timeclock = 0;  //时间
void gamedraw();		//图形界面绘制
int statenumber();		//随机生成一个数
void createnumber();	//处理生成数字数量及判断死亡
void keyboard();		//获取键盘输入及处理键盘命令
void moveup();			//一下都是处理数字，数字融合，上下左右不用我多说吧！
void movedown();
void moveleft();
void moveright();
void ReadFile();		//读取文件
void WriteFile();		//写入文件
void Printtime();		//多线程调用，显示时间
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
	switch (_getch())//该函数获取输入的一个字符，不用回车，不同与getchar();
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
	for (int i = 0; i < NUMBER; i++)		//获取已占位置，或者可以理解为还剩几个空位
	{
		for (int j = 0; j < NUMBER; j++)
		{
			if (a[i][j] != 0) { flag++; }	
		}
	}
	if (flag < NUMBER* NUMBER-1)
	{
		for (int i = 1; i <= MOST_CREATE;)	//如果有多余2个空，生成两个，循环跟while作用一样
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
	else if (flag == NUMBER * NUMBER - 1)	//如果有只有1个空，生成1个
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
	else if (flag == NUMBER * NUMBER )		//如果占满了，不生成数字，判断是否还能再合成
	{
		for (int i = 0; i < NUMBER-1; i++)
		{
			for (int j = 0; j < NUMBER-1; j++)
			{
				if (a[i][j] == a[i][j + 1] || a[i][j] == a[i + 1][j])
				{
					flag1= 1;   //检查12个方块
				}	
			}
			if (flag1 == 1)
			{
				break;
			}
		}
		for (int i = 3, j = 0; j < NUMBER - 1; j++)
		{
			if (a[j][i] == a[j + 1][i]) flag3 = 1;		//检查剩余方块
		}
		if ((flag1+flag3) == 0)		//都不能合成，那就GG
		{
			//cleardevice();
			settextcolor(RED);
			int tw = textwidth("你失败了!!");
			int ty = textheight("你失败了!!");
			outtextxy((INITGR / 2) - tw / 2, (INITGR / 2) - ty / 2, "你失败了!!");		//显示失败
			flag2 = 0;				//游戏置死亡
		}
	}
	
}
int statenumber()
{
	srand((unsigned)time(NULL) + clock());  //随机数种子
	int temp = rand() % 5;
	if (temp == 0||1||2 ) { return 2; }		//生成2的几率为75%
	else { return 4; }		//生成4的几率为25%
}
void gamedraw()
{
	for (int i = 1; i <= NUMBER; i++) //双循环,为每个数字绘制矩形框
	{
		for (int j = 1; j <= NUMBER; j++)
		{
			int x = (i - 1) * SIDE_LENGTH + i * MARGINS;
			int y = (j - 1) * SIDE_LENGTH + j * MARGINS;
			setfillcolor(arr[12]);
			solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);
			char str[10] = " ";
			sprintf_s(str, "%d",a[j - 1][i - 1]);	//将数字转换为str，方便显示
			setbkmode(TRANSPARENT);		//文字或数字背景删除
			settextstyle(50, 0, "黑体");	//设置字体格式
			int tw = textwidth(str);		//计算字符长度
			int th = textheight(str);		//计算字符宽度
			int tx = (SIDE_LENGTH - tw) / 2;	
			int ty = (SIDE_LENGTH - th) / 2;
			if (a[j - 1][i - 1] != 0)
			{
				int index = (int)log2((int)a[j - 1][i - 1]);
				COLORREF tcolor = arr[index];
				setfillcolor(tcolor);
				solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);		//绘制圆角矩形
				outtextxy(x + tx, y + ty, str);	//数字居中显示
			}
		}
	}
	//绘制和保存存档,目标等信息图形，时间显示在另一个线程
	setfillcolor(arr[12]);
	solidroundrect(INITGR, MARGINS, INITGR + EXTRENDINITGR-MARGINS, INITGR-MARGINS, 10, 10);//扩展总界面
	setfillcolor(arr[2]);
	solidroundrect(INITGR + MARGINS, 120 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 220 + 4 * MARGINS, 10, 10);//保存界面
	solidroundrect(INITGR + MARGINS, 240 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 340 + 4 * MARGINS, 10, 10);//目标：2048
	settextstyle(25, 0, "黑体");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("R.保存游戏");
	int ty1 = textheight("R.保存游戏");
	int tw2 = textwidth("目标:");
	int ty2 = textheight("目标:");
	int tw3 = textwidth("2048");
	int ty3 = textheight("2048");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw1) / 2, 120 + 4 * MARGINS + (100 - ty1) / 2, "R.保存游戏");
	settextstyle(30, 0, "黑体");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 240 + 4 * MARGINS + (50 - ty2) / 2, "目标:");
	settextstyle(40, 0, "黑体");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 240 + 4 * MARGINS+50 + (50 - ty2) / 2, "2048");
	//此处时间也要刷新显示，不然每次操作后，时间显示会被覆盖
	char str[10] = " ";
	sprintf_s(str, "%d:%d:%d", timeclock / 3600, (timeclock % 3600) / 60, timeclock % 60);
	int tw4 = textwidth("时间:");
	int ty4 = textheight("时间:");
	int tw5 = textwidth("str");
	int ty5 = textheight("str");
	settextstyle(30, 0, "黑体");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	solidroundrect(INITGR + MARGINS, 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 100, 10, 10);//时间界面
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw4) / 2, 4 * MARGINS + (50 - ty4) / 2, "时间:");
	settextstyle(40, 0, "黑体");
	outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw5) / 2, 50 + 4 * MARGINS + (50 - ty5) / 2, str);
	//还原字体设置
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
		//读取失败。
		return;
	}
	while (!feof(fp))		//处理字符
	{
		if (!fgets(temp, 100, fp))
			break;
		//跳过BOM头 即utf-8
		if (strstr(temp, "\xEF\xBB\xBF"))
		{
			strcpy_s(temp + 3, 20, temp);	//删除BOM头
		}
		if (temp[0] == '#')	//获取游戏状态
		{
			sscanf_s(temp+1, "%*s %d", &flag2);
			if (flag2 == 0)		//如果保存的游戏死亡，重新开时新游戏
			{
				createnumber();
				flag2 = 1;
				//都要关闭文件防止写入时干扰
				fclose(fp);
				return ;
			}
				
		}
		else if (temp[0] == '@')	//分离时间
		{
			sscanf_s(temp + 1, "%*s %d",&timeclock);
		}
		else
		{
			sscanf_s(temp, "%d %d %d %d", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);	//读取各个方块数据
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
	fprintf(fp, "#flag2 %d\n", flag2); //写入游戏状态
	for (int i = 0; i < 4; i++)
	{
		fprintf(fp, "%d %d %d %d\n", a[i][0], a[i][1], a[i][2], a[i][3]);		//写入游戏数据
	}
	fprintf(fp, "@timeclock %d", timeclock);  //写入时间
	fclose(fp);
}
void Printtime()
{
	while(1) //死循环让这个线程一直工作
	{
		Sleep(1000);	//延迟一秒
		if (flag2 == 0)
		{
			return;
		}
		timeclock++;
		char str[10] = " ";
		sprintf_s(str, "%d:%d:%d", timeclock/3600, (timeclock%3600)/60, timeclock%60);  //处理秒数
		//时间界面显示
		int tw1 = textwidth("时间:");
		int ty1 = textheight("时间:");
		int tw2 = textwidth("str");
		int ty2 = textheight("str");
		settextstyle(30, 0, "黑体");
		settextcolor(RED);
		setbkmode(TRANSPARENT);
		solidroundrect(INITGR + MARGINS, 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 100, 10, 10);//时间界面
		outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw1) / 2, 4 * MARGINS + (50 - ty1) / 2,"时间:");
		settextstyle(40, 0, "黑体");
		outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 50+4 * MARGINS + (50 - ty2) / 2, str);
		//还原字体设置
		settextcolor(WHITE);
	}
}
void menu()		//菜单，选择Q或E
{
	//显示界面
	setfillcolor(arr[1]);
	solidroundrect((INITGR-330)/2, 43, (INITGR - 330) / 2 +330, 43+100, 10, 10);
	solidroundrect((INITGR - 330) / 2, 43+43+100, (INITGR - 330) / 2 + 330, 43 +43+ 100+100, 10, 10);
	settextstyle(30, 0, "黑体");
	settextcolor(arr[3]);
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("Q.新游戏");
	int ty1 = textheight("Q.新游戏");
	int tw2 = textwidth("E.继续游戏");
	int ty2 = textheight("E.继续游戏");
	outtextxy((INITGR - 330) / 2 + (330 - tw1)/2, 43 + (100 - ty1 )/2, "Q.新游戏");
	outtextxy((INITGR - 330) / 2 + (330 - tw2 )/2, 43 +43+100+ (100 - ty2 )/2, "E.继续游戏");
}
int main()
{
	//easyx界面初始化
	initgraph(INITGR, INITGR);
	setbkcolor(arr[13]);
	cleardevice();
	menu();
	while (1)	//获取Q或E
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
	//重新绘制界面
	initgraph(INITGR + EXTRENDINITGR, INITGR, 1);
	setbkcolor(arr[13]);
	cleardevice();
	std::thread th(Printtime);		//std::作用域，创建线程
	th.detach();	//与主线程并发执行
	while (1) //主循环
	{
		if(flag2!=0)
		{
			gamedraw();	
		}
		keyboard();
	}
	closegraph();	//关闭图形库
	return 0;	
}