#include <graphics.h>		
#include <conio.h>
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#define pignum 10
#define b_goldnum 5
//#include "gift.h"
#pragma comment(lib,"Winmm.lib")//播放音乐？？
#define pi 3.1415926
int num_bp=1;//大力丸的个数
IMAGE a;//隔板
IMAGE BG;//背景
IMAGE b[4];//人物的图片
IMAGE b_gold[2];
IMAGE bkd[2];
int bkdnum = 1;//炸弹的数量
IMAGE powerman;
int b_gold_x[b_goldnum];
int b_gold_y[b_goldnum];
IMAGE s_gold[2];
int s_gold_x = rand() % 200 + 300;
int s_gold_y = rand() % 200 + 300;
IMAGE dia[2];
int dia_x = rand() % 200 + 300;
int dia_y = rand() % 200 + 300;
double angle = 0;//钩子的角度
double len = 50;//钩子摇动的半径
double o = pi / 90;
int hit = 0;//绳子是否处于抓捕状态
int len_speed = 10;//绳子伸长的速度
int count = 0;//时间计时器；存在于exit中
char s[] = "剩下的时间：";
int game_time = 1;//游戏的次数
int power = 0;//力量的存在;
struct pig {
IMAGE pig[2];
int if1 = 0;
int x=0;
int y=0;
int speed=10;
}p[pignum];
IMAGE hook[2];
int mark = 0;
IMAGE gameover;
int textbox = 0;//判断是否有对话框了，不然间隔时间太短同时会有许多的对话框
void gift()
{
	MOUSEMSG m;
	IMAGE bakudan[2];
	IMAGE shop;
	int flag_1 = 0;
	loadimage(&bakudan[0], _T("./p/bakudan.bmp"));
	loadimage(&bakudan[1], _T("./p/bakudan_mask.bmp"));
	int flag_2 = 0;
	Sleep(1000);
	initgraph(960, 540);
	loadimage(NULL, _T("./p/clear.png"), 960, 540);
	Sleep(2000);
	loadimage(&shop, _T("./p/shop.png"), 960, 540);
	TCHAR s[] = _T("大炮仗");
	while (1)
	{
		putimage(0, 0, &shop);
		if (flag_1 == 0)
		{
			putimage(100, 350, &bakudan[1], NOTSRCERASE);
			putimage(100, 350, &bakudan[0], SRCINVERT);
			outtextxy(150, 400, s);
		}
		if (flag_2 == 0)
		{
			setfillcolor(BLUE);
			fillcircle(300, 400, 20);
			TCHAR ss[] = _T("伸腿瞪眼丸");
			outtextxy(350, 400, ss);
		}

		char num[20];
		setbkmode(TRANSPARENT);
		sprintf(num, "%d", mark);
		outtextxy(0, 50, "金钱＄:");
		outtextxy(70, 50, num);


		m = GetMouseMsg();
		if (m.x > 618 + 100 && m.x < 730 + 150 && m.y>90 && m.y < 135)
		{
			if (m.mkLButton)
			{
				break;
			}

		}
		if (m.x > 100 && m.x < 100 + 37 && m.y>350 && m.y < 350 + 73 && m.mkLButton && flag_1 == 0 )
		{
			textbox = 1;
			Sleep(100);
		}
		if (textbox != 0)
		{
			int result = MessageBox(NULL, TEXT("你确定要购买炸弹吗？这将花费您30元"), TEXT("确认按钮"), MB_ICONINFORMATION | MB_YESNO);
			switch (result)/*注意！使用Unicode应用TEXT包围字串*/
			{
			case IDYES: {
				MessageBox(NULL, TEXT("感谢您的购买"), TEXT("感谢信"), MB_OK);
				mark = mark - 30;
				bkdnum++;
				flag_1 = 0;
				textbox = 0;
				break;
			}
			case IDNO:MessageBox(NULL, TEXT("没有钱就不要乱买了啊！！！"), TEXT("抱怨信"), MB_OK); textbox = 0; break;
			}
			
			
		}
		if (m.x > 280 && m.x < 320 && m.y>380 && m.y < 420 && m.mkLButton && flag_2 == 0)
		{
			Sleep(100);
			int result = MessageBox(NULL, TEXT("你确定要购买大力丸吗？这将花费您30元"), TEXT("确认按钮"), MB_ICONINFORMATION | MB_YESNO);
			switch (result)/*注意！使用Unicode应用TEXT包围字串*/
			{
			case IDYES: {
				MessageBox(NULL, TEXT("感谢您的购买"), TEXT("感谢信"), MB_OK);
				mark = mark - 5;
				num_bp++;
				flag_2 = 0;
				break;
			}
			case IDNO:MessageBox(NULL, TEXT("没有钱就不要乱买了啊！！！"), TEXT("抱怨信"), MB_OK); break;
			}

			
		}
		//Sleep(1);
		cleardevice();
		//FlushBatchDraw();
	}
}
void start()
{
	IMAGE a;
	IMAGE b;
	MOUSEMSG m;
	initgraph(640, 480);
	loadimage(NULL, _T("./p/start.png"));
	loadimage(&a, _T("./p/startbottom1.png"));
	loadimage(&b, _T("./p/startbottom2.png"));
	mciSendString("open ./s/bgm.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play mymusic", NULL, 0, NULL);
	while (1)
	{
		m = GetMouseMsg();
		 if (m.x > 100 && m.x < 246 && m.y>100 && m.y < 184)
			putimage(100, 100, &b);
		else
			putimage(100, 100, &a);
		 if (m.mkLButton && m.x > 100 && m.x < 246 && m.y>100 && m.y < 184)
		 {
			 
			 mciSendString("stop mymusic", NULL, 0, NULL);
			 mciSendString("close mymusic", NULL, 0, NULL);
			 break;
		 }
	}
	
	closegraph();
}
void load()
{
	initgraph(960, 540);
	loadimage(&BG, _T("./p/level-background-1.jpg"));	
	loadimage(&a, _T("./p/brick.png"));
	loadimage(&b[1], _T("./p/char1.jpg"));//人
	loadimage(&b[0], _T("./p/char1_mask.jpg"));//遮罩
	loadimage(&b_gold[0], _T("./p/big_gold_mask.png"));
	loadimage(&b_gold[1], _T("./p/big_gold.png"));
	loadimage(&s_gold[0], _T("./p/small_gold.bmp_mask.bmp"));
	loadimage(&s_gold[1], _T("./p/small_gold.bmp"));
	loadimage(&dia[1], _T("./p/diamond.png"));
	loadimage(&dia[0], _T("./p/diamond_mask.png"));
	loadimage(&hook[0], _T("./p/hook_mask.bmp"));
	loadimage(&hook[1], _T("./p/hook.bmp"));
	loadimage(&gameover, _T("./p/gameover.jpg"),960,540);
	loadimage(&powerman, _T("./p/powerman.jpg"), 50, 50);
	loadimage(&bkd[0], _T("./p/bkd_mask.png"), 350, 350);
    loadimage(&bkd[1], _T("./p/bkd.png"), 350, 350);
	for (int i = 0; i < pignum; i++)
	{
	loadimage(&p[i].pig[0], _T("./p/pig_mask.png"),30,30);
	loadimage(&p[i].pig[1], _T("./p/pig.png"),30,30);
	}
	for (int i = 0; i < pignum; i++)
	{
		p[i].y = rand()%300+200;
		p[i].x = rand() % 950;;
	}
	for (int i = 0; i < b_goldnum; i++)
	{
		b_gold_x[i] = rand() % 200 + 300;
		b_gold_y[i] = rand() % 200 + 300;
	}
}

void show()
{
	
	putimage(0,0,&BG);
	for (int i = 0; i <= 12; i++)
	{
		putimage(i * 80, 69, &a);
	}
	putimage(480, 0, &b[0],NOTSRCERASE);//先遮罩，再人
	putimage(480, 0, &b[1],SRCINVERT);
	setcolor(BLACK);
	line(500, 68, 500 + len * sin(angle), 69 + len * cos(angle));
	angle = angle + o;
	if (fabs(angle) > pi / 3)
	{
		o= -o;
		if (angle > 0)
			angle = pi / 3;
		else
			angle = -pi / 3;
	}
	for (int i = 0; i < game_time*3; i++)
	{
	putimage(p[i].x, p[i].y, &p[i].pig[0],NOTSRCERASE);
	putimage(p[i].x, p[i].y, &p[i].pig[1],SRCINVERT);
	p[i].x += p[i].speed;
	if (p[i].x > 930)
	{
		p[i].x = 929;
		p[i].speed = -p[i].speed;
	}
	if (p[i].x < 1)
	{
		p[i].x = 1;
		p[i].speed = -p[i].speed;
	}
	}
	
	for (int i = 0; i < b_goldnum; i++)
	{
		putimage(b_gold_x[i], b_gold_y[i], &b_gold[0], NOTSRCERASE);
	putimage(b_gold_x[i], b_gold_y[i], &b_gold[1], SRCINVERT);

	}
	
	putimage(dia_x, dia_y, &dia[0], NOTSRCERASE);
	putimage(dia_x, dia_y, &dia[1], SRCINVERT);
	
	putimage(500 + len * sin(angle)-17.5, 69 + len * cos(angle), &hook[0], NOTSRCERASE);
	putimage(500 + len * sin(angle)-17.5, 69 + len * cos(angle), &hook[1], SRCINVERT);
	//putimage(s_gold_x, s_gold_y, &s_gold[0], NOTSRCERASE);
	putimage(s_gold_x, s_gold_y, &s_gold[1]/*, SRCINVERT*/);
	setbkmode(TRANSPARENT);
	char num[20];//得分
	char cou[20];//计时器
	
	outtextxy(730, 38, "当前你拥有大力丸:");
	char num_bpp[20];//游戏局数所需要的分数
	sprintf(num_bpp, "%d", num_bp);
	outtextxy(880, 38, num_bpp);
    
	outtextxy(730, 55, "当前你拥有大炮仗:");
	char bkdnumm[20];//游戏局数所需要的分数
	sprintf(bkdnumm, "%d", bkdnum);
	outtextxy(880, 55, bkdnumm);
	
	outtextxy(0, 30, "目标分数:");
	char game_timee[20];//游戏局数所需要的分数
	sprintf(game_timee, "%d", 30 + game_time * 20);
	outtextxy(80, 30, game_timee);
	
	sprintf(num, "%d", mark);
	outtextxy(0, 50, "金钱＄:"); 
	sprintf(cou, "%d", 70-count/20-game_time*10);
	outtextxy(55, 50, num);//分数在这
	outtextxy(730, 20, s);
	outtextxy(830, 20, cou);

	if (power == 1)
		putimage(560, 10, &powerman);
	
	Sleep(50);
}
int b_gold_if[b_goldnum] = {0};//是否被逮住,1被抓住
int s_gold_if = 0;
int dia_if=0;
void grab()
{//xy_gold是判定的范围

	bool xy_b_gold[b_goldnum];
	for (int i = 0; i < b_goldnum; i++)
	{
		xy_b_gold[i]= (500 + len * sin(angle) > b_gold_x[i]) && (500 + len * sin(angle) < b_gold_x[i] + 52) && (69 + len * cos(angle) > b_gold_y[i]) && (69 + len * cos(angle) < b_gold_y[i] + 52);
	}
	for (int i = 0; i < b_goldnum; i++)
	{
		if (xy_b_gold[i])
		{
			b_gold_if[i] = 1;
			if (power == 0)
			{


				len_speed = 3;//大黄金重一点
			}
			else
			{
				len_speed = 50;
			}
			len_speed = -len_speed;
		}
		if (b_gold_if[i] == 1)
		{
			b_gold_x[i] = 500 + len * sin(angle);
			b_gold_y[i] = 69 + len * cos(angle);
		}
		if (b_gold_if[i] == 1 && len == 50)
		{
			b_gold_x[i] = rand() % 950;
			b_gold_y[i] = rand() % 170 + 360;
			b_gold_if[i] = 0;
			mark = mark + 50;
			len_speed = 10;
		}//到达终点再次生成
	}
    
	bool xy_dia = (500 + len * sin(angle) > dia_x) && (500 + len * sin(angle) < dia_x + 52) && (69 + len * cos(angle) > dia_y) && (69 + len * cos(angle) < dia_y + 52);
	if (xy_dia)
	{
		dia_if = 1;
		len_speed = -len_speed;
	}
	if (dia_if == 1)
	{
		dia_x = 500 + len * sin(angle);
		dia_y = 69 + len * cos(angle);
	}
	if (dia_if == 1 && len == 50)
	{
		dia_x = rand() % 950;
		dia_y = rand() % 170 + 360;
		dia_if = 0;
		mark = mark + 10;
		len_speed = 10;
	}//到达终点再次生成
	//int t3 = 500 + len * sin(angle) - s_gold_x;
	bool xy_s_gold = (500 + len * sin(angle) > s_gold_x) && (500 + len * sin(angle) < s_gold_x + 52) && (69 + len * cos(angle) > s_gold_y) && (69 + len * cos(angle) < s_gold_y + 52);
	if (xy_s_gold)
	{

		s_gold_if = 1;
		len_speed = -len_speed;
	}
	if (s_gold_if == 1)
	{
		s_gold_x = 500 + len * sin(angle);
		//s_gold_x = 500 + len * sin(angle) - t3;
		s_gold_y = 69 + len * cos(angle);
	}
	if (s_gold_if == 1 && len == 50)
	{
		s_gold_x = rand() % 950;
		s_gold_y = rand() % 170 + 360;
		s_gold_if = 0;
		mark = mark + 20;
		len_speed = 10;
	}//到达终点再次生成
	bool xy_pig[pignum];
	for(int i=0;i<game_time*3;i++)
		xy_pig[i] = (500 + len * sin(angle) > p[i].x-5) && (500 + len * sin(angle) < p[i].x + 35) && (69 + len * cos(angle) > p[i].y-5) && (69 + len * cos(angle) < p[i].y + 35);
		//xy_pig[i] = (500 + len * sin(angle) > p[i].x) && (500 + len * sin(angle) < p[i].x + 30) && (69 + len * cos(angle) > p[i].y) && (69 + len * cos(angle) < p[i].y + 52);
	for (int i = 0; i < game_time*3; i++)
	{
	 	
	if (xy_pig[i])
	{
		p[i].if1 = 1;
		len_speed = -fabs(len_speed);
	}
	if (p[i].if1 == 1)
	{
		p[i].x = 500 + len * sin(angle);
		p[i].y = 69 + len * cos(angle);
	}
	if (p[i].if1 == 1 && len == 50)
	{
		p[i].x = rand()%950;
		p[i].y = rand()%300+200;
		p[i].if1 = 0;
		mark = mark + 1;
		len_speed = 10;
	}//到达终点再次生成*/

	}
}
void out()
{
	if (power == 1)
	{
		if (len_speed > 0)
			len_speed = 50;
		else len_speed = -50;
	}
	if (o == 0&&hit==1)
		len = len + len_speed;//按下空格键升绳子的伸长
	if (500 + len * sin(angle) > 960 || 500 + len * sin(angle) < 1)
	{
		if(len_speed>0)
		len_speed = -len_speed;
	}//左右边界回弹
	if (69 + len * cos(angle) > 540)
	{
		if (len_speed > 0)
		len_speed = -len_speed;
	}//下边界回弹
	if (len <= 50 && hit == 1)
	{
		hit = 0;
		len = 50;
		o = pi / 90;
		len_speed = 10;
		power = 0;
		//len_speed = -len_speed;
	}//防止回弹过度
	//下面是物体的相关//
	if (mark >=30+game_time*20)

	{
		mciSendString("close dig", NULL, 0, NULL);
		gift();
		for (int i = 0; i < b_goldnum; i++)
		{
			b_gold_x[i] = rand() % 950;
			b_gold_y[i] = rand() % 170 + 360;
			p[i].x = rand() % 950;
			p[i].y = rand() % 300 + 200;
			s_gold_x = rand() % 950;
			s_gold_y = rand() % 170 + 360;
			dia_x = rand() % 950;
			dia_y = rand() % 170 + 360;
		}

		game_time = game_time + 1;
		count = 0;
	}
	
}
void in()
{
	if (_kbhit())
	{
		char input;
		input = _getch();
		if (input == ' ' && hit ==0)
		{
			o = 0;
			hit = 1;
			mciSendString("open ./s/dig.mp3 alias dig", NULL, 0, NULL);
			mciSendString("play dig repeat", NULL, 0, NULL);
			
			line(500, 68, 500 + len * sin(angle), 69 + len * cos(angle));
		}
		if (num_bp > 0)
		{
			if (input == 'w'&&power==0&&len_speed>0)
		    {
			len_speed = 50;
			power = 1;
			num_bp--;
		    }

		}
		
		if (input == 'q'&&bkdnum>=1)
		{
			hit = 0;
			len = 50;
			if (o > 0)
				o = pi / 90;
			else
				o = -pi / 90;
			//len_speed = 10;
			bkdnum--;
			putimage(500 + len * sin(angle)-175, 69 + len * cos(angle)-175, &bkd[0], NOTSRCERASE);//先遮罩，再人
			putimage(500 + len * sin(angle)-175, 69 + len * cos(angle)-175, &bkd[1], SRCINVERT);
		}
		
	}
	if (hit!=1)
		{
			mciSendString("close dig", NULL, 0, NULL);
		}
}
void exit()//退出的函数
{
	count = count + 1;
	if (70 - count / 20 - game_time * 10 <= 0)
	{
		char a[] = "时间已尽";

			settextstyle(100, 0, _T("Consolas"));
			outtextxy(350, 200, a);
		Sleep(2000);
		putimage(0, 0, &gameover);
		Sleep(2000);
		exit(0);
	}
}
int main()
{
	start();
	srand((unsigned)time(NULL));
	load();
	while (1)
	{
		exit();
		show();
		out();
		in();
		grab();
		FlushBatchDraw();
	}
}