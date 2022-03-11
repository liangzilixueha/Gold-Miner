#include <graphics.h>		
#include <conio.h>
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
int ab;//大力丸的个数
int bp(int aa)
{
	ab = aa;
	return ab;
}
int gift(int mark)
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
	loadimage(NULL,_T("./p/clear.png"),960,540);
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
				return mark;
			}

		}
		if (m.x > 100 && m.x < 100 + 37 && m.y>350 && m.y < 350 + 73 && m.mkLButton&&flag_1==0)
		{
			mark = mark - 1;
			
			flag_1 = 01;
		}
		if (m.x > 280 && m.x < 320 && m.y>380 && m.y < 420&& m.mkLButton&&flag_2==0)
		{
			mark = mark - 5;
			ab--;
			flag_2 = 1;
		}
		//Sleep(20);
		cleardevice();
		//FlushBatchDraw();
	}
}