//ϵͳ������
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
//////////////////////////////������ �궨����� //////////////////////////////

#define       WIDE              640            //��Ļ���
#define       HIGH              480            //��Ļ�߶�

#define  UP    72
#define  DOWN  80
#define  LEFT  75
#define  RIGHT 77
#define  SPACE 32

/////////////////////////////������  ȫ�ֱ���  //////////////////////////////

IMAGE       menu1, menu2, menu3, set, help, end, door1, door2, door3;                                                               //�˵�����
IMAGE       back1, back2, back3, img1, img2, man1, man2, wall1, wall2, wall3, box1, box2, flower1, flower2, boom1, boom2, xianshi1, yincang1, xianshi2, yincang2, xianshi3, yincang3;               //��Ϸ��������   

//////////////////////////////���������ݽṹ����//////////////////////////////

//�û���Ϣ
typedef struct users {
	char       name[20];                        //�û���
	int        num = 5;                         //��������
	int        score = 0;                          //�û��÷�
	//struct     users* next;
}USER;

//������Ϣ
typedef struct Tool {
	int        x, y;                           //����
	int        flag;                           //��orը�� 0 �� 1 ը��
	struct     Tool* next;
}tool;

typedef struct {
	int x;
	int y;
}People;
//////////////////////////////������  ��������  //////////////////////////////

void        LoadImg();                                                                            //����ͼƬ
void        Startmenu(USER& user);                                                                //���ؿ�ʼ�˵�����
void        Mainmenu(USER& user);                                                                          //������Ϸ�˵�����
int         checkButton(int mouseX, int mouseY);                                                    //����Ƿ��ڰ�ť��
void        Initgame(USER& user, int gamemode);                                                            //��ʼ���Թ�����
void        InGame(USER& user, int a[10][10], tool*& head, int gamemode, People people);                                               //������Ϸ
void        Display(People people);                                                                //��������
void        Remember(USER user, int a[10][10], tool* head, int gamemode, People people);             //�浵
void        score(USER user);                                                                       //���û���Ϣ
void        Read(USER& user);                                                                       //����              

void        Mode1(USER& user, int a[10][10], tool*& head, People people);
void        Mode2(USER& user, int a[10][10], tool*& head, People people);
void        Mode3(USER& user, int a[10][10], tool*& head, People people);


int main()
{
	USER user;                                     //�����û�
	//MOUSEMSG mmsg;                                 //�����Ϣ����
	int mouseX = 0, mouseY = 0;                    //�������
	//int flag = 0;                                  // 0 ��ʼ�˵� 1 ��Ϸ�˵� 2 ��ȡ��Ϸ�˵� 3 ��Ϸ����
	initgraph(WIDE, HIGH);                         //��ʼ������

	SetWindowText(GetHWnd(), "�Թ�������:-)");     //���ô��ڱ���
	LoadImg();                                     //����ͼƬ
	putimage(0, 0, &menu1);
	//BeginBatchDraw();                              //����˫���壬��ֹ����
	//�ڴ˴����ϳ�ʼ������
	srand((unsigned)time(NULL));
	mciSendString("open image\\BGM.mp3 alias bgm", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
	/*while (true)
	{
		while (true)
		{


		}
		//InGame(user,flag,mouseX,mouseY);
		if (flag == 0 || flag == 1)
			Drawmenu(user, mouseX, mouseY);                                 //���ƽ���
		else break;


		//FlushBatchDraw();
	}*/

	Startmenu(user);
	//Initgame(user);

	//EndBatchDraw();
	closegraph();
	return 0;

}

void LoadImg()
{
	loadimage(&menu1, "image\\1.png");
	loadimage(&menu2, "image\\2.png");
	loadimage(&menu3, "image\\3.png");
	loadimage(&back1, "image\\4.png");
	loadimage(&wall1, "image\\5.jpg");
	loadimage(&man1, "image\\man1.jpg");
	loadimage(&man2, "image\\man2.jpg");
	loadimage(&box1, "image\\6.jpg");
	loadimage(&box2, "image\\7.jpg");
	loadimage(&boom1, "image\\8.jpg");
	loadimage(&boom2, "image\\9.jpg");
	loadimage(&flower1, "image\\10.jpg");
	loadimage(&flower2, "image\\11.jpg");
	loadimage(&set, "image\\12.jpg", 460, 200);
	loadimage(&help, "image\\13.jpg");
	loadimage(&end, "image\\14.jpg");
	//loadimage(&door, "image\\15.jpg");
	loadimage(&back2, "image\\16.png");
	loadimage(&back3, "image\\17.png");
	loadimage(&wall2, "image\\18.png");
	loadimage(&wall3, "image\\19.png");
	loadimage(&door1, "image\\door1.jpg");
	loadimage(&door2, "image\\door2.jpg");
	loadimage(&door3, "image\\door3.jpg");
	loadimage(&xianshi1, "image\\xianshi1.jpg");
	loadimage(&xianshi2, "image\\xianshi2.jpg");
	loadimage(&xianshi3, "image\\xianshi3.jpg");
	loadimage(&yincang1, "image\\yincang1.jpg");
	loadimage(&yincang2, "image\\yincang2.jpg");
	loadimage(&yincang3, "image\\yincang3.jpg");
}

void Startmenu(USER& user)
{
	MOUSEMSG mmsg;
	char numb[15];
	int flag = 0;
	int i = 1;
	while (i)                                                                   //�ڿ�ʼ�˵�����ʱ
	{
		if (MouseHit())
		{
			mmsg = GetMouseMsg();
			if (mmsg.x > 264 && mmsg.x < 376 && mmsg.y >253 && mmsg.y < 284)      //��ʼ��Ϸ��ť
			{
				if (WM_LBUTTONDOWN == mmsg.uMsg)
				{
					putimage(0, 0, &menu2);
					flag = 1;
				}
				else if (WM_LBUTTONUP == mmsg.uMsg && flag == 1)
				{
					flag = 2;
					i = 0;
				}
			}
			if (mmsg.x > 264 && mmsg.x < 376 && mmsg.y >319 && mmsg.y < 349)       //��ȡ��Ϸ��ť
			{
				if (WM_LBUTTONDOWN == mmsg.uMsg)
				{
					putimage(0, 0, &menu3);
					flag = 3;
				}
				else if (WM_LBUTTONUP == mmsg.uMsg && flag == 3)
				{
					flag = 4;
					i = 0;
				}
			}
			FlushMouseMsgBuffer();
		}
	}
	if (flag == 2)
	{
		putimage(0, 0, &menu1);
		Sleep(15);
		i = InputBox(user.name, 20, "����������ǳƣ�", "�����û�", NULL, 0, 0, false);           //�����û���Ϣ
		if (i == false)
			MessageBox(NULL, "����ȡ����", "�����û�", MB_OK | MB_ICONHAND);
		else
		{
			//if (user.name == NULL)
			strcpy(user.name, "�ο�");
			InputBox(numb, 10, "�����õ���������", "�����û�", "5", 0, 0);
			user.num = atoi(numb);
			Mainmenu(user);                                                                           //������Ϸ�˵�
		}
	}
	else if (flag == 4)
	{
		putimage(0, 0, &menu1);
		//�˴���Ӻ�����ȡ�û���Ϣ
		Read(user);

	}
}

void Mainmenu(USER& user)
{
	int mouseX = 0, mouseY = 0;
	int isMouseDown = 0;
	int gamemode = 0;
	MOUSEMSG mmsg;

	for (int i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));           //���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
		cleardevice();                      //����
		Sleep(15);                          //��ʱ15ms
	}

	setbkmode(TRANSPARENT);
	//����
	settextcolor(RGB(241, 149, 60));
	settextstyle(58, 30, "����", 0, 0, 600, false, false, false);
	outtextxy(152, 92, "ѡ����Ϸ�ؿ�");
	settextcolor(RGB(255, 227, 153));
	outtextxy(150, 90, "ѡ����Ϸ�ؿ�");

	FlushMouseMsgBuffer();
	BeginBatchDraw();
	while (gamemode == 0)
	{
		//��Ϸģʽѡ��ť
		setlinecolor(RGB(255, 199, 44));
		setlinestyle(PS_SOLID, 1);
		settextstyle(26, 10, _T("����"));
		setfillcolor(RGB(255, 199, 44));
		if (MouseHit())                                 //��ȡ�����Ϣ
		{
			mmsg = GetMouseMsg();
			switch (mmsg.uMsg)
			{
			case WM_MOUSEMOVE:	    mouseX = mmsg.x; mouseY = mmsg.y;	break;
			case WM_LBUTTONDOWN:	isMouseDown = 1;					break;
			case WM_LBUTTONUP:		isMouseDown = 0;					break;
			}
		}
		//ģʽ1��ť
		if (checkButton(mouseX, mouseY) == 1)
		{
			settextcolor(RGB(255, 199, 44));
			if (isMouseDown)                             //������Ӧ
				gamemode = 1;
		}
		else
			settextcolor(RGB(255, 255, 255));
		fillrectangle(250, 220, 375, 255);
		outtextxy(275, 225, _T("����ũ��"));

		//ģʽ2��ť
		if (checkButton(mouseX, mouseY) == 2)
		{
			settextcolor(RGB(255, 199, 44));
			if (isMouseDown)
				gamemode = 2;
		}
		else
			settextcolor(RGB(255, 255, 255));
		fillrectangle(250, 280, 375, 315);
		outtextxy(275, 285, _T("ɳĮ̽��"));

		//ģʽ3��ť
		if (checkButton(mouseX, mouseY) == 3)
		{
			settextcolor(RGB(255, 199, 44));
			if (isMouseDown)
				gamemode = 3;
		}
		else
			settextcolor(RGB(255, 255, 255));
		fillrectangle(250, 340, 375, 375);
		outtextxy(275, 345, _T("�´�ɭ��"));
		//���벻ͬ��Ϸģʽ  
		//if(gamemode==1)
		FlushBatchDraw();
	}
	EndBatchDraw();
	Initgame(user, gamemode);
}

int checkButton(int mouseX, int mouseY)
{
	if (mouseX >= 250 && mouseX <= 375 && mouseY >= 220 && mouseY <= 255)
		return 1;
	else if (mouseX >= 250 && mouseX <= 375 && mouseY >= 280 && mouseY <= 315)
		return 2;
	else if (mouseX >= 250 && mouseX <= 375 && mouseY >= 340 && mouseY <= 375)
		return 3;
	else
		return -1;                          //ûѡ��	
}

void  Initgame(USER& user, int gamemode)                                 //1 ǽ 2 ���� 3 ����
{
	int a[3][10][10] =
	{
		{
			{0,0,0,0,0,0,0,0,0,1},
			{0,1,1,1,0,0,0,1,0,1},
			{0,1,0,0,0,0,0,1,0,1},
			{0,1,1,0,0,0,0,1,0,3},
			{0,0,1,0,1,0,0,1,1,0},
			{0,0,1,1,0,1,1,1,0,0},
			{0,1,1,0,0,1,0,0,0,1},
			{0,1,0,0,0,1,1,1,1,1},
			{0,0,0,0,0,0,1,0,0,1},
			{0,0,0,1,1,0,0,0,0,1}
		},
		{
			{0,0,0,0,0,0,0,0,0,1},
			{0,1,1,1,0,0,0,1,0,1},
			{0,1,0,0,0,0,0,1,0,1},
			{0,1,1,0,0,0,0,1,0,3},
			{0,0,1,1,1,0,0,1,1,0},
			{0,0,1,1,0,1,1,1,0,0},
			{0,1,1,0,0,1,0,0,0,1},
			{0,1,0,0,0,1,1,1,1,1},
			{0,0,0,0,0,0,1,0,0,1},
			{0,0,0,1,1,0,0,0,0,1}
		},
		{
			{0,0,0,0,0,0,0,0,0,1},
			{0,1,1,1,0,0,0,1,0,1},
			{0,1,0,0,0,0,0,1,0,1},
			{0,1,1,0,0,0,0,1,0,3},
			{0,0,1,0,1,0,0,1,1,0},
			{0,0,1,1,0,1,1,1,0,0},
			{0,1,1,0,0,1,0,0,0,1},
			{0,1,0,0,0,1,1,1,1,1},
			{0,0,0,0,0,0,1,0,0,1},
			{0,0,0,1,1,0,0,0,0,1}
		}
	};
	tool* head, * p;
	People people = { 5,0 };
	head = (tool*)malloc(sizeof(tool));
	head->next = NULL;
	for (int i = 0; i < user.num; i++)
	{
		p = (tool*)malloc(sizeof(tool));
		do
		{
			p->x = rand() % 10;
			p->y = rand() % 10;
		} while (a[gamemode - 1][p->x][p->y] != 0);
		a[gamemode - 1][p->x][p->y] = 2;
		p->flag = rand() % 2;
		p->next = head->next;
		head->next = p;
	}
	switch (gamemode)
	{
	case 1:   Mode1(user, a[0], head, people); break;
	case 2:   Mode2(user, a[1], head, people); break;
	case 3:   Mode3(user, a[2], head, people); break;
	}

}

void   Mode1(USER& user, int a[10][10], tool*& head, People people)
{
	int flag;
	putimage(0, 0, &back1);
	putimage(509, 146, &xianshi1);
	getimage(&img2, 40, 40, 40, 40);
	BeginBatchDraw();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (a[i][j] == 1)
				putimage((j + 1) * 40, (i + 1) * 40, &wall1);
			if (a[i][j] == 2)
			{
				putimage((j + 1) * 40, (i + 1) * 40, &box1, SRCAND);
				putimage((j + 1) * 40, (i + 1) * 40, &box2, SRCINVERT);
				//putimage((i + 1) * 30, (j + 1) * 30, &box);
			}
			if (a[i][j] == 3)
				putimage((j + 1) * 40, (i + 1) * 40, &door1);
		}
	}
	EndBatchDraw();
	InGame(user, a, head, 1, people);
}

void   Mode2(USER& user, int a[10][10], tool*& head, People people)
{
	int flag;
	putimage(0, 0, &back2);
	putimage(509, 146, &xianshi2);
	getimage(&img2, 40, 40, 40, 40);
	BeginBatchDraw();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (a[i][j] == 1)
				putimage((j + 1) * 40, (i + 1) * 40, &wall2);
			if (a[i][j] == 2)
			{
				putimage((j + 1) * 40, (i + 1) * 40, &box1, SRCAND);
				putimage((j + 1) * 40, (i + 1) * 40, &box2, SRCINVERT);
				//putimage((i + 1) * 30, (j + 1) * 30, &box);
			}
			if (a[i][j] == 3)
				putimage((j + 1) * 40, (i + 1) * 40, &door2);

		}
	}
	EndBatchDraw();
	InGame(user, a, head, 2, people);
}

void   Mode3(USER& user, int a[10][10], tool*& head, People people)
{
	int flag;
	putimage(0, 0, &back3);
	putimage(506, 145, &xianshi3);
	getimage(&img2, 40, 40, 40, 40);
	BeginBatchDraw();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (a[i][j] == 1)
				putimage((j + 1) * 40, (i + 1) * 40, &wall3);
			if (a[i][j] == 2)
			{
				putimage((j + 1) * 40, (i + 1) * 40, &box1, SRCAND);
				putimage((j + 1) * 40, (i + 1) * 40, &box2, SRCINVERT);
				//putimage((i + 1) * 30, (j + 1) * 30, &box);
			}
			if (a[i][j] == 3)
				putimage((j + 1) * 40, (i + 1) * 40, &door3);
		}
	}
	EndBatchDraw();
	InGame(user, a, head, 3, people);
}

void    InGame(USER& user, int a[10][10], tool*& head, int  gamemode, People people)
{
	tool* p, * r;
	MOUSEMSG mmsg;
	char s[10];                                     //��÷�
	char c = 0;
	int flag = 0;                                   //0 ��������״̬ 1 ������ʾ״̬
	int con = 0;                                     //0 ���ùر�״̬ 1 ������ʾ״̬ 2 ������Ϸ
	int isgame = 0;                                   // 0 ��Ϸ�� 1 �ص�ѡ��ؿ� 2 ��Ϸ����
	int isdown = 0;                                   //�����Ƿ��� 0 δ���� 1 ����
	int isBgm = 0;                                    //0 ���ֲ���״̬ 1 ������ͣ״̬
	setbkmode(TRANSPARENT);
	sprintf(s, "%d", user.score);
	settextcolor(RGB(255, 255, 255));
	settextstyle(18, 0, "����", 0, 0, 600, false, false, false);
	outtextxy(500, 20, "���������");
	outtextxy(500, 46, user.name);
	outtextxy(500, 75, "�÷֣�");
	outtextxy(500, 100, s);
	BeginBatchDraw();
	while (isgame != 1)
	{
		if (MouseHit())
		{
			BeginBatchDraw();
			mmsg = GetMouseMsg();
			if (WM_LBUTTONDOWN == mmsg.uMsg)
			{
				if (mmsg.x > 510 && mmsg.x < 610 && mmsg.y>148 && mmsg.y < 200)                                              //��ť����ʾ/���ء���Ӧ
				{
					//�˴����ϵ�����ʾ����
					if (flag == 0)
					{
						switch (gamemode)
						{
						case 1: putimage(509, 146, &yincang1); break;
						case 2: putimage(509, 146, &yincang2); break;
						case 3: putimage(506, 145, &yincang3); break;
						}
						p = head;
						while (p != NULL)
						{
							if (p->flag == 0)
							{
								putimage((p->y + 1) * 40, (p->x + 1) * 40, &img2);
								putimage((p->y + 1) * 40, (p->x + 1) * 40, &flower1, SRCAND);
								putimage((p->y + 1) * 40, (p->x + 1) * 40, &flower2, SRCINVERT);
							}
							if (p->flag == 1)
							{
								putimage((p->y + 1) * 40, (p->x + 1) * 40, &img2);
								putimage((p->y + 1) * 40, (p->x + 1) * 40, &boom1, SRCAND);
								putimage((p->y + 1) * 40, (p->x + 1) * 40, &boom2, SRCINVERT);
							}
							p = p->next;
						}
						flag = 1;
					}
					else if (flag == 1)
					{
						switch (gamemode)
						{
						case 1: putimage(509, 146, &xianshi1); break;
						case 2: putimage(509, 146, &xianshi2); break;
						case 3: putimage(506, 145, &xianshi3); break;
						}
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 10; j++)
							{
								if (a[i][j] == 2)
								{
									putimage((j + 1) * 40, (i + 1) * 40, &img2);
									putimage((j + 1) * 40, (i + 1) * 40, &box1, SRCAND);
									putimage((j + 1) * 40, (i + 1) * 40, &box2, SRCINVERT);
								}
							}
						}
						flag = 0;
					}
				}
				if (mmsg.x > 510 && mmsg.x < 610 && mmsg.y>235 && mmsg.y < 287)                                              //��ť�����ӡ���Ӧ
				{
					//�˴����ϵ������Ӵ���
					if (head == NULL) {
						head = (tool*)malloc(sizeof(tool));
						head->next = NULL;
					}
					p = (tool*)malloc(sizeof(tool));
					do
					{
						p->x = rand() % 10;
						p->y = rand() % 10;
					} while (a[p->x][p->y] != 0);
					a[p->x][p->y] = 2;
					p->flag = rand() % 2;
					p->next = head->next;
					head->next = p;
					user.num++;
					putimage((p->y + 1) * 40, (p->x + 1) * 40, &box1, SRCAND);
					putimage((p->y + 1) * 40, (p->x + 1) * 40, &box2, SRCINVERT);
				}
				if (mmsg.x > 510 && mmsg.x < 610 && mmsg.y>310 && mmsg.y < 362)                                              //��ť����ա���Ӧ
				{
					//�˴����ϵ�����մ���
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (a[i][j] == 2)
								putimage((j + 1) * 40, (i + 1) * 40, &img2);
						}
					}
					if (head != NULL) {
						head = head->next;
						while (head != NULL)
						{
							p = head;
							head = head->next;
							free(p);
						}
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 10; j++)
							{
								if (a[i][j] == 2)
									a[i][j] = 0;
							}
						}
						user.num = 0;
					}
				}
				if (mmsg.x > 510 && mmsg.x < 610 && mmsg.y>390 && mmsg.y < 442)                                              //��ť�����á���Ӧ
				{
					//�˴��������ô���
					if (con == 0)
					{
						putimage(90, 140, &set);
						con = 1;
					}
					else if (con == 1)
					{
						BeginBatchDraw();
						switch (gamemode)
						{
						case 1: putimage(0, 0, &back1); break;
						case 2: putimage(0, 0, &back2); break;
						case 3: putimage(0, 0, &back3); break;
						}
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 10; j++)
							{
								if (a[i][j] == 1)
									switch (gamemode)
									{
									case 1:putimage((j + 1) * 40, (i + 1) * 40, &wall1); break;
									case 2: putimage((j + 1) * 40, (i + 1) * 40, &wall2); break;
									case 3: putimage((j + 1) * 40, (i + 1) * 40, &wall3); break;
									}
								if (a[i][j] == 2)
								{
									putimage((j + 1) * 40, (i + 1) * 40, &box1, SRCAND);
									putimage((j + 1) * 40, (i + 1) * 40, &box2, SRCINVERT);
								}
								if (a[i][j] == 3)
									switch (gamemode)
									{
									case 1: putimage((j + 1) * 40, (i + 1) * 40, &door1); break;
									case 2: putimage((j + 1) * 40, (i + 1) * 40, &door2); break;
									case 3: putimage((j + 1) * 40, (i + 1) * 40, &door3); break;
									}
							}
						}
						outtextxy(500, 20, "���������");
						outtextxy(500, 52, user.name);
						outtextxy(500, 75, "�÷֣�");
						outtextxy(500, 100, s);
						EndBatchDraw();
						con = 0;
					}
				}
				if (con == 1)                                                                     //�����ý���
				{
					if (mmsg.x > 110 && mmsg.x < 190 && mmsg.y>230 && mmsg.y < 263)                 //��ť������"��Ӧ
					{
						//��ͼ��������
						BeginBatchDraw();
						switch (gamemode)
						{
						case 1: putimage(0, 0, &back1); break;
						case 2: putimage(0, 0, &back2); break;
						case 3: putimage(0, 0, &back3); break;
						}
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 10; j++)
							{
								if (a[i][j] == 1)
									switch (gamemode)
									{
									case 1:putimage((j + 1) * 40, (i + 1) * 40, &wall1); break;
									case 2: putimage((j + 1) * 40, (i + 1) * 40, &wall2); break;
									case 3: putimage((j + 1) * 40, (i + 1) * 40, &wall3); break;
									}
								if (a[i][j] == 2)
								{
									putimage((j + 1) * 40, (i + 1) * 40, &box1, SRCAND);
									putimage((j + 1) * 40, (i + 1) * 40, &box2, SRCINVERT);
								}
							}
						}
						outtextxy(500, 20, "���������");
						outtextxy(500, 52, user.name);
						outtextxy(500, 75, "�÷֣�");
						outtextxy(500, 100, s);
						putimage(50, 35, &help);
						EndBatchDraw();
						//Display(people);

					}
					if (mmsg.x > 220 && mmsg.x < 300 && mmsg.y>230 && mmsg.y < 263)                 //��ť���ؿ�"��Ӧ
					{
						user.score = 0;
						isgame = 1;
					}
					if (mmsg.x > 330 && mmsg.x < 410 && mmsg.y>230 && mmsg.y < 263)                 //��ť������"��Ӧ
					{
						if (isBgm == 0) {
							mciSendString("resume bgm", 0, 0, 0);
							isBgm = 1;
						}
						else if (isBgm == 1) {
							mciSendString("pause bgm", 0, 0, 0);
							isBgm = 0;
						}
					}
					if (mmsg.x > 440 && mmsg.x < 520 && mmsg.y>230 && mmsg.y < 263)                 //��ť���˳�"��Ӧ
					{
						Remember(user, a, head, gamemode, people);
						exit(0);
					}
				}
				if (isgame == 2)
				{
					if (mmsg.x > 185 && mmsg.x < 270 && mmsg.y>272 && mmsg.y < 310)
					{
						//user.score = 0;
						isgame = 1;
						break;
					}
					if (mmsg.x > 350 && mmsg.x < 430 && mmsg.y>272 && mmsg.y < 310)
					{
						score(user);
						exit(0);
					}
				}
			}
			FlushMouseMsgBuffer();
			FlushBatchDraw();
		}
		/*if (_kbhit())
		{
			if (_getch() == 0xE0)
				c = _getch();
			if (c == UP)
			{
				if(people.y<440 && people.y>45)
					people.y -= 5;
				Display(people);
			}
			if (c == DOWN)
			{
				if (people.y < 435 && people.y>40)
					people.y += 5;
				Display(people);
			}
			if (c == LEFT)
			{
				if (people.x < 440 && people.x>45)
					people.x -= 5;
				Display(people);
			}
			if (c == RIGHT)
			{
				if (people.x < 435 && people.x>40)
					people.x += 5;
				Display(people);
			}
		}
		else Display(people);*/
		//if (_kbhit())
		//while(1)
		//{
			//BeginBatchDraw();
			/*c = _getch();
			if (c== 0xE0||c==0)
				c = _getch();*/
				/*int goal_x = people.x;           // �ƶ���Ŀ��λ��
				int goal_y = people.y;*/
		if ((GetAsyncKeyState(VK_UP) & 1) == 1)
		{
			if (people.x > 0 && a[people.x - 1][people.y] != 1)          // Ŀ��λ�������λ�õ��ϱ�
				people.x--;
		}
		if ((GetAsyncKeyState(VK_DOWN) & 1) == 1)
		{
			if (people.x < 9 && a[people.x + 1][people.y] != 1)             // Ŀ��λ�������λ�õ��±�
				people.x++;
		}
		if ((GetAsyncKeyState(VK_LEFT) & 1) == 1)
		{
			if (people.y > 0 && a[people.x][people.y - 1] != 1)            // Ŀ��λ�������λ�õ����
				people.y--;
		}
		if ((GetAsyncKeyState(VK_RIGHT) & 1) == 1)
		{
			if (people.y < 9 && a[people.x][people.y + 1] != 1)            // Ŀ��λ�������λ�õ��ұ�
				people.y++;
		}
		if ((GetAsyncKeyState(VK_SPACE) & 1) == 1)
		{
			r = head;
			p = head->next;
			while (p != NULL)
			{
				if (p->x == (people.x) && p->y == (people.y))
				{
					if (p->flag == 0)
					{
						BeginBatchDraw();
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &img2);
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &flower1, SRCAND);
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &flower2, SRCINVERT);
						user.score += rand() % 10 + 1;                    //�����1-10��
						putimage(500, 100, &img2);
						sprintf(s, "%d", user.score);                    //��̬��ʾ�÷�
						outtextxy(500, 100, s);
						putimage((people.y + 1) * 40, (people.x + 1) * 40, &man1, SRCAND);
						putimage((people.y + 1) * 40, (people.x + 1) * 40, &man2, SRCINVERT);
						FlushBatchDraw();
						Sleep(700);
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &img2);
						putimage((people.y + 1) * 40, (people.x + 1) * 40, &img2);
						EndBatchDraw();
					}
					else if (p->flag == 1)
					{
						BeginBatchDraw();
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &img2);
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &boom1, SRCAND);
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &boom2, SRCINVERT);
						user.score -= rand() % 10 + 1;                    //�����1-10��
						putimage(500, 100, &img2);
						sprintf(s, "%d", user.score);
						outtextxy(500, 100, s);
						putimage((people.y + 1) * 40, (people.x + 1) * 40, &man1, SRCAND);
						putimage((people.y + 1) * 40, (people.x + 1) * 40, &man2, SRCINVERT);
						FlushBatchDraw();
						Sleep(700);
						putimage((p->y + 1) * 40, (p->x + 1) * 40, &img2);
						putimage((people.y + 1) * 40, (people.x + 1) * 40, &img2);
						EndBatchDraw();
					}
					a[p->x][p->y] = 0;
					r->next = p->next;
					free(p);
					p = r->next;
				}
				else
				{
					r = p;
					p = p->next;
				}
			}
		}
		if (con == 0 && isgame == 0)
			Display(people);
		if (a[people.x][people.y] == 3)
		{
			isgame = 2;
			//Sleep(20);
			putimage(90, 140, &end);
		}
	}
	EndBatchDraw();

	if (isgame == 1)
		Mainmenu(user);

}

void    Display(People people)
{
	getimage(&img1, (people.y + 1) * 40, (people.x + 1) * 40, 40, 40);
	BeginBatchDraw();
	putimage((people.y + 1) * 40, (people.x + 1) * 40, &man1, SRCAND);
	putimage((people.y + 1) * 40, (people.x + 1) * 40, &man2, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	putimage((people.y + 1) * 40, (people.x + 1) * 40, &img1);
	EndBatchDraw();

}

void    Read(USER& user) {

	FILE* fp1;
	tool* p, * head;
	People people;
	int gamemode, a[10][10];
	head = (tool*)malloc(sizeof(tool));
	head->next = NULL;
	/*if ((fp1 = fopen("record.txt", "r")) == NULL) {
		MessageBox(NULL, "δ��ȡ���浵��������ʼ����Ϸ��", "��ȡ�浵", MB_OK | MB_ICONHAND);
		//Mainmenu(user);
	}*/
	if ((fp1 = fopen("record.txt", "r")) != NULL) {
		fread(&user, sizeof(USER), 1, fp1);
		fread(&people, sizeof(People), 1, fp1);
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				fread(&a[i][j], sizeof(int), 1, fp1);
		fread(&gamemode, sizeof(int), 1, fp1);
		for (int i = 0; i < user.num; i++) {

			p = (tool*)malloc(sizeof(tool));
			fread(&p->x, sizeof(int), 1, fp1);
			fread(&p->y, sizeof(int), 1, fp1);
			fread(&p->flag, sizeof(int), 1, fp1);
			p->next = head->next;
			head->next = p;
		}
		fclose(fp1);
	}
	switch (gamemode)
	{
	case 1:   Mode1(user, a, head, people); break;
	case 2:   Mode2(user, a, head, people); break;
	case 3:   Mode3(user, a, head, people); break;
	}
}

void    score(USER user) {
	FILE* fp;
	if ((fp = fopen("info.txt", "a")) != NULL) {
		fprintf(fp, "%s %d\n", user.name, user.score);
		fclose(fp);
	}
}

void    Remember(USER user, int a[10][10], tool* head, int gamemode, People people) {
	FILE* fp;
	tool* p;
	if ((fp = fopen("record.txt", "w")) != NULL) {
		fwrite(&user, sizeof(USER), 1, fp);
		fwrite(&people, sizeof(People), 1, fp);
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				fwrite(&a[i][j], sizeof(int), 1, fp);
		fwrite(&gamemode, sizeof(int), 1, fp);
		p = head->next;
		while (p != NULL) {
			fwrite(&p->x, sizeof(int), 1, fp);
			fwrite(&p->y, sizeof(int), 1, fp);
			fwrite(&p->flag, sizeof(int), 1, fp);
			p = p->next;
		}
		fclose(fp);
	}
}

