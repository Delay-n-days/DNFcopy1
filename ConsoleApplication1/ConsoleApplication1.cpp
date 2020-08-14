#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define LIMG 0
#define RIMG 80
#define NIMG 40
#define N 5//帧率8//越小动作越快
#define PixSpend 1//速度  越大相同时间内走的越远
#define T 10//周期 //越大走的越慢
int pximg = 0;
int Dtime = 0;
int imgNum = 318;
int imgL = 107;
static int lock = 0;
IMAGE  role;
IMAGE img;
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
struct Ship
{
	int x;
	int y;
	int img_x;
	int img_y;
	int img_ny;
	int dir;
}ship;
void PlayBGM()
{
	//打开音乐
	/*mciSendString("open ./res/Music0001.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM", 0, 0, 0);
	Sleep(8000);
	mciSendString("close BGM", 0, 0, 0);*/
}
void GameInit()
{
	ship = { 0,350,0,104 * 4,104 * 4 + 107,RIGHT };
	initgraph(640, 480);
	//setbkcolor(YELLOW);
	//cleardevice();
	loadimage(&img, "./res/Img0001.jpg");
	putimage(0, 0, &img);
	PlayBGM();
}
void DrawBackIMG(int x, int y)
{
	putimage(x, y, 40, 40, &img, x, y);
}
void KeyControl()
{

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) | GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			ship.y += PixSpend;
		}
		else {
			if (ship.dir == LEFT)
			{
				ship.img_ny = 104 * 3;
				ship.img_y = 104 * 2;

				Dtime++;
				if (Dtime > N)
				{
					Dtime = 0;
					ship.img_x -= 53;
				}
				if (ship.img_x == 0)ship.img_x = 477;
				ship.y += PixSpend;
				imgNum = 477;
				imgL = 104;
			}
			else if (ship.dir == RIGHT) {
				ship.img_ny = 104;
				ship.img_y = 0;
				Dtime++;
				if (Dtime > N)
				{
					Dtime = 0;
					ship.img_x -= 53;
				}
				if (ship.img_x == 0)ship.img_x = 477;
				ship.y += PixSpend;
				imgNum = 477;
				imgL = 104;
			}
			else {
				ship.y += PixSpend;
			}
		}

	}
	/*关于"与操作" 与 "或操作"讲解
	//第一步与操作，是遮罩图与背景彩色图进行颜色与操作
	//例：背景颜色1011，遮罩图人物部分（黑色）0000，背景部分白色：1111
	//与操作后
	//当前人物部分：1011&0000=0000黑色
	//当前背景部分：1011&1111=1011彩色
	//当前图像背景为彩色，人物为黑色
	//第二步操作，人物图与图像进行颜色或操作
	//例：人物图人物部分：1001 人物图背景部分黑色：0000
	//或操作后
	//当前人物部分：1001|0000=1001彩色
	//当前背景部分：0000|1011=1011彩色
	//两步操作后当前图像能正确显示人物和背景*/
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) | GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			ship.y -= PixSpend;
		}
		else {
			if (ship.dir == LEFT)
			{
				ship.img_ny = 104 * 3;
				ship.img_y = 104 * 2;

				Dtime++;
				if (Dtime > N)
				{
					Dtime = 0;
					ship.img_x -= 53;
				}
				if (ship.img_x == 0)ship.img_x = 477;
				ship.y -= PixSpend;
				imgNum = 477;
				imgL = 104;
			}
			else if (ship.dir == RIGHT) {
				ship.img_ny = 104;
				ship.img_y = 0;
				Dtime++;
				if (Dtime > N)
				{
					Dtime = 0;
					ship.img_x -= 53;
				}
				if (ship.img_x == 0)ship.img_x = 477;
				ship.y -= PixSpend;
				imgNum = 477;
				imgL = 104;
			}
			else {
				ship.y -= PixSpend;
			}
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		ship.dir = LEFT;
		ship.img_ny = 104 * 3;
		ship.img_y = 104 * 2;

		Dtime++;
		if (Dtime > N)
		{
			Dtime = 0;
			ship.img_x -= 53;
		}
		if (ship.img_x == 0)ship.img_x = 477;
		ship.x -= PixSpend;
		imgNum = 477;
		imgL = 104;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		ship.dir = RIGHT;
		ship.img_ny = 104;
		ship.img_y = 0;
		Dtime++;
		if (Dtime > N)
		{
			Dtime = 0;
			ship.img_x -= 53;
		}
		if (ship.img_x == 0)ship.img_x = 477;
		ship.x += PixSpend;
		imgNum = 477;
		imgL = 104;
	}
	if (ship.dir == RIGHT && !(GetAsyncKeyState(VK_DOWN) & 0x8000) && !(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_LEFT) & 0x8000) && !(GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
		ship.img_ny = 104 * 4 + 107;
		ship.img_y = 104 * 4;

		Dtime++;
		if (Dtime > N * 4)
		{
			Dtime = 0;
			ship.img_x += 53;
		}
		imgNum = 318;
		imgL = 107;
	}
	if (ship.dir == LEFT && !(GetAsyncKeyState(VK_DOWN) & 0x8000) && !(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_LEFT) & 0x8000) && !(GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
		ship.img_ny = 104 * 4 + 107 * 3;
		ship.img_y = 104 * 4 + 107 * 2;

		Dtime++;
		if (Dtime > N * 4)
		{
			Dtime = 0;
			ship.img_x += 53;
		}
		imgNum = 318;
		imgL = 107;
	}


}
void GameDraw()
{
	BeginBatchDraw();//后台画图 防止
	putimage(0, 0, &img);
	//cleardevice();
	putimage(ship.x, ship.y, 53, imgL, &role, ship.img_x % imgNum, ship.img_ny, SRCAND);
	putimage(ship.x, ship.y, 53, imgL, &role, ship.img_x % imgNum, ship.img_y, SRCPAINT);
	EndBatchDraw();
}
int main()
{

	loadimage(&role, "./res/0002.jpg");

	//initgraph(640, 480,SHOWCONSOLE);

	//fillcircle(320, 240, 50);
	//setbkcolor(YELLOW);
	//cleardevice();
	GameInit();
	while (1)
	{
		if (lock == 0)
		{

			KeyControl();
			lock = 1;
		}
		Sleep(T);
		lock = 0;
		GameDraw();
	}
	return 0;
}
