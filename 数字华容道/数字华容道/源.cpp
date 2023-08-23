#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<thread>		//多线程
#define INUMBER 3		//3*3
#define SIDE_LENGTH 100		//方块大小
#define MARGINS 10			//方块间隔
#define INITGR (INUMBER*SIDE_LENGTH+(INUMBER+1)*MARGINS)		//主界面大小
#define EXTRENDINITGR 170					//副界面延申长度
int a[INUMBER * INUMBER] = {0,1,2,3,4,5,6,7,8};			//洗牌算法，选取其中两个进行对换
int b[INUMBER][INUMBER] = { 0 };						//实际操作的数组
int flag2 = 0;  //游戏状态    0.未通关  1.通关
int timeclock = 0;			//时间存储
void createmap();			//方块地图创建
void createnumber();			//数字打乱，生成
void moveleft(int x, int y);		//以下四个不用我多说,移动
void moveright(int x, int y);
void movedown(int x, int y);
void moveup(int x, int y);
void ReadFile();				//读取文件
void WriteFile();				//写入文件
void keyboard();				//键盘输入
void outtext1();				//判断是否成功
void outtext2();				//输出无效操作
void Printtime();				//多线程，输出时间
void outtext1()
{
	int temp = 0,flag=0;		//判断temp逆序对数量是否为0,以及最后一个是否为0
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
	if (temp == 0 && flag == 1)			//都满足条件，则成功
	{
		settextcolor(RED);
		settextstyle(40, 0, "黑体");
		int tw = textwidth("你成功了!!");
		int ty = textwidth("你成功了!!");
		outtextxy((INITGR / 2) - tw / 2, (INITGR / 2) - ty / 2, "你成功了!!");
		flag2 = 1;
	}
	//还原字体颜色
	settextcolor(WHITE);
}
void outtext2()
{
	//输入的操作为无效操作时，输出
	settextstyle(20, 0, "黑体");
	//settextcolor(RGB(255, 255, 255));
	int tw = textwidth("无效操作!!");
	int ty = textheight("无效操作!!");
	setfillcolor(WHITE);
	solidroundrect(INITGR + MARGINS, 2 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 100 + 2 * MARGINS, 10, 10);
	settextcolor(RED);
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw) / 2, 2 * MARGINS + (100 - ty) / 2, "无效操作!!");
	//还原字体设置
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
			sscanf_s(temp + 1, "%*s %d", &flag2);
			if (flag2 == 1)		//如果保存的游戏成功，重新开始新游戏
			{
				createnumber();
				flag2 = 0;
				//都要关闭文件防止写入时干扰
				fclose(fp);
				return;
			}

		}
		else if (temp[0] == '@')	//分离时间
		{
			sscanf_s(temp + 1, "%*s %d", &timeclock);
		}
		else
		{
			sscanf_s(temp, "%d %d %d", &b[i][0], &b[i][1], &b[i][2]);	//读取各个方块数据
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
		//文件读取失败
		return;
	}
	fprintf(fp, "#flag2 %d\n", flag2); //写入游戏状态
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d %d %d\n", b[i][0], b[i][1], b[i][2]);		//写入游戏数据
	}
	fprintf(fp, "@timeclock %d", timeclock);  //写入时间
	fclose(fp);		//关闭文件
}
void menu()		//菜单，选择Q或E
{
	//显示界面
	setfillcolor(RGB(238, 228, 218));
	solidroundrect((INITGR - 230) / 2, 43, (INITGR - 230) / 2 + 230, 43 + 100, 10, 10);
	solidroundrect((INITGR - 230) / 2, 43 + 43 + 100, (INITGR - 230) / 2 + 230, 43 + 43 + 100 + 100, 10, 10);
	settextstyle(30, 0, "黑体");
	settextcolor(RGB(245, 149, 99));
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("Q.新游戏");
	int ty1 = textheight("Q.新游戏");
	int tw2 = textwidth("E.继续游戏");
	int ty2 = textheight("E.继续游戏");
	outtextxy((INITGR - 230) / 2 + (230 - tw1) / 2, 43 + (100 - ty1) / 2, "Q.新游戏");
	outtextxy((INITGR - 230) / 2 + (230 - tw2) / 2, 43 + 43 + 100 + (100 - ty2) / 2, "E.继续游戏");
}
void keyboard()
{
	int flag = 0, temp1 = 0, temp2 = 0;
	for (int i = 1; i <= INUMBER; i++)		//寻找0的位置，方便与其他数字交换，产生移动
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
	switch (_getch())	//与getchar()不同，该函数获取字符不需用回车，w,a,s,d,不用我说吧
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
		case 'r':		//保存文件键
		case 'R':
			WriteFile();
			break;
		default:
			break;
	}
}
void moveup(int x, int y)
{
	if (x < INUMBER - 1 && x >= 0)	//可以移动则清除屏幕，等待下一帧的刷新
	{
		b[x][y] = b[x + 1][y];
		b[x + 1][y] = 0;
		cleardevice();
		
	}
	else			//不能移动则视为无效操作
	{
		outtext2();
	}

}
void movedown(int x, int y)
{
	if (x > 0 && x <= INUMBER - 1)		//可以移动则清除屏幕，等待下一帧的刷新
	{
		b[x][y] = b[x - 1][y];
		b[x - 1][y] = 0;
		cleardevice();
	}
	else
	{
		outtext2();			//不能移动则视为无效操作
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
	for (int i = 0; i < INUMBER * INUMBER; i++)			//洗牌算法，固定洗3*3次
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
		if (temp % 2 == 0 && temp != 0)		//判断逆序对是否为偶数,同时逆序对不应为0，为零就可能很容易获胜,不和条件再洗一次
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
	for (int i = 0; i < INUMBER * INUMBER; i++)			//生成没问题，写入b中，我也想不起来为什这样写了，（哈哈）。
	{
		int x = i / 3;
		int y = i % 3;
		b[x][y] = a[i];
	}
}
void createmap()
{
	for (int i = 1; i <= INUMBER; i++)	//生成3*3的方块矩阵
	{
		for (int j = 1; j <= INUMBER; j++)
		{
			a[(i - 1) * 3 + j - 1] = b[i - 1][j - 1];
			int x = (i - 1) * SIDE_LENGTH + i * MARGINS;
			int y = (j - 1) * SIDE_LENGTH + j * MARGINS;
			solidroundrect(x, y, x + SIDE_LENGTH, y + SIDE_LENGTH, 10, 10);		//圆角矩形
			char str[10] = " ";
			sprintf_s(str, "%d", b[j - 1][i - 1]);				//将数字转换为字符串
			setbkmode(TRANSPARENT);				
			settextstyle(50, 0, "黑体");		
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
	//生成副界面
	setfillcolor(WHITE);
	solidroundrect(INITGR + MARGINS, 200 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 270 + 4 * MARGINS, 10, 10);//保存界面
	settextstyle(25, 0, "黑体");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	int tw1 = textwidth("R.保存游戏");
	int ty1 = textheight("R.保存游戏");
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw1) / 2, 200 + 4 * MARGINS + (70 - ty1) / 2, "R.保存游戏");
	char str[10] = " ";
	sprintf_s(str, "%d:%d:%d", timeclock / 3600, (timeclock % 3600) / 60, timeclock % 60);  //处理秒数
	//时间界面显示，这里也要刷新一次，防止被覆盖
	int tw2 = textwidth("时间:");
	int ty2 = textheight("时间:");
	int tw3 = textwidth("str");
	int ty3 = textheight("str");
	settextstyle(20, 0, "黑体");
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	solidroundrect(INITGR + MARGINS, 100 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 180, 10, 10);  //时间界面
	outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 100 + 4 * MARGINS + (40 - ty2) / 2, "时间:");
	settextstyle(25, 0, "黑体");
	outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw3) / 2, 140 + 4 * MARGINS + (40 - ty3) / 2, str);
	//还原字体设置，不然下一次用可能界面颜色会变化
	settextcolor(WHITE);
}
void Printtime()
{
	while (1) //死循环让这个线程一直工作
	{
		Sleep(1000);	//延迟一秒
		if (flag2 == 1)
		{
			return;
		}
		timeclock++;
		char str[10] = " ";
		sprintf_s(str, "%d:%d:%d", timeclock / 3600, (timeclock % 3600) / 60, timeclock % 60);  //处理秒数
		//时间界面显示
		int tw2 = textwidth("时间:");
		int ty2 = textheight("时间:");
		int tw3 = textwidth("str");
		int ty3 = textheight("str");
		settextstyle(20, 0, "黑体");
		settextcolor(RED);
		setbkmode(TRANSPARENT);
		solidroundrect(INITGR + MARGINS, 100 + 4 * MARGINS, INITGR + EXTRENDINITGR - 2 * MARGINS, 4 * MARGINS + 180, 10, 10);//时间界面
		outtextxy(INITGR + MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw2) / 2, 100 + 4 * MARGINS + (40 - ty2) / 2, "时间:");
		settextstyle(25, 0, "黑体");
		outtextxy(INITGR - MARGINS + (EXTRENDINITGR - 3 * MARGINS - tw3) / 2, 140 + 4 * MARGINS + (40 - ty3) / 2, str);
		//还原字体设置，不然下一次用可能界面颜色会变化
		settextcolor(WHITE);
	}
}
int main()
{
	//菜单界面绘制
	initgraph(INITGR, INITGR);
	setbkcolor(RGB(187, 173, 160));
	cleardevice();
	menu();
	while (1)	//获取Q或E，选择新游戏或者继续游戏
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
	//游戏开始游戏界面绘制
	initgraph(INITGR + EXTRENDINITGR, INITGR,1);
	setbkcolor(RGB(220, 155, 100));
	cleardevice();
	createmap();
	std::thread th(Printtime);		//std::作用域，创建线程
	th.detach();	//与主线程并发执行
	while (1)
	{
		outtext1();
		keyboard();
	}
}