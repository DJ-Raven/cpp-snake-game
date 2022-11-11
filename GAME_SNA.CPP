#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
typedef struct data_s
{
	int x;
	int y;
};
data_s snake[3000];
int body = 0;
int px, py, sx = 30, sy = 12;
void border();
void go_right();
void go_up();
void go_down();
void go_left();
void show();
void show_point(int point);
void random_point();
void show_blood(int blood);
void show_time(int t);
void start();
void help();
void clr();
void main()
{
	textbackground(6);
	clrscr();
	_setcursortype(_NOCURSOR);
	char *menu[5], ch;
	int opt, y;
	menu[0] = "   Start Game   ";
	menu[1] = "      Help      ";
	menu[2] = "      Exit      ";
ag:
	opt = 0;
	border();
	window(32, 5, 49, 11);
	textbackground(1);
	clrscr();
	window(33, 6, 48, 10);
	textbackground(7);
	clrscr();
	do
	{
		y = 2;
		for (int i = 0; i <= 2; i++)
		{
			if (opt == i)
			{
				textcolor(0);
				textbackground(4);
			}
			else
			{
				textcolor(0);
				textbackground(7);
			}
			gotoxy(1, y++);
			cprintf("%s", menu[i]);
		}
		ch = getch();
		if (ch == 0)
			ch = getch();
		if (ch == 72 || ch == 80)
		{
			if (ch == 72)
				if (opt == 0)
					opt = i - 1;
				else
					opt--;
			else if (opt == i - 1)
				opt = 0;
			else
				opt++;
		}
	} while (ch != 13);
	switch (opt)
	{
	case 0:
		body = 0;
		sx = 30;
		sy = 12;
		start();
		goto ag;
	case 1:
		help();
		goto ag;
	case 2:
		break;
	}
}
void start()
{
	char ch, opt = 'r';
	int d = 100, du = 150, dr = 100, t = 0;
	int point = 0, b = 0, have = 0, hx, hy, ran, blood = 1;
	randomize();
	_setcursortype(_NOCURSOR);
	random_point();
	border();
	show_point(point);
	do
	{

		do
		{
			show_blood(blood);
			for (int i = body; i >= 0; i--)
			{
				snake[i + 1] = snake[i];
			}
			snake[0].x = sx;
			snake[0].y = sy;

			clr();
			gotoxy(px, py);
			textcolor(6);
			cprintf("%c", 2);
			if (have == 1)
			{
				t++;
				show_time(t);
				if (t == 100)
				{
					have = 0;
					t = 0;
				}
				textcolor(5);
				gotoxy(hx, hy);
				textbackground(2);
				cprintf("?");
				textbackground(0);
			}
			if (opt == 'r')
			{
				go_right();
			}
			else if (opt == 'l')
			{
				go_left();
			}
			else if (opt == 'u')
			{
				go_up();
			}
			else if (opt == 'd')
			{
				go_down();
			}
			delay(d);
			if (sx == px && sy == py)
			{
				if (dr > 50)
				{
					dr--;
					du--;
				}
				body++;
				show_point(++point);
				random_point();
				b++;
				if (b == 5)
				{
					have = 1;
					b = 0;
				ag:
					hx = random(80);
					if (hx == 0 || hx == 1)
						goto ag;
				ag1:
					hy = random(25);
					if (hy == 0 || hy == 1)
						goto ag1;
					for (i = 0; i <= body; i++)
					{
						if (hx == snake[i].x && hy == snake[i].y)
						{
							goto ag;
						}
					}
				}
			}
			if (sx == hx && sy == hy && have == 1)
			{
				gotoxy(45, 1);
				textbackground(7);
				cprintf("            ");
				textbackground(0);
				have = 0;
				t = 0;
				ran = random(5);
				if (ran == 0)
					point += 10;
				else if (ran == 1)
					if (blood < 10)
					{
						blood++;
					}
					else if (ran == 2)
					{
						dr -= 10;
						du -= 10;
					}
					else if (ran == 3)
					{
						dr += 10;
						du += 10;
					}
					else
						point += 100;
			}
			for (i = 0; i < body; i++)
			{
				if (sx == snake[i + 1].x && sy == snake[i + 1].y)
				{
					if (blood == 1)
					{
						textcolor(4);
						gotoxy(35, 12);
						cprintf("You Are Die");
						getch();
						goto end;
					}
					else
					{
						blood--;
						gotoxy(1, 1);
						textbackground(7);
						cprintf("                         ");
						textbackground(0);
					}
				}
			}
			if (sx == 80 || sx == 1 || sy == 1 || sy == 25)
			{
				gotoxy(35, 12);
				textcolor(4);
				cprintf("You Are Die");
				getch();
				goto end;
			}
		} while (!kbhit());
		ch = getch();
		if (ch == 0)
			ch = getch();
		if (ch == 72 || ch == 75 || ch == 77 || ch == 80 || ch == 4 || ch == 45 || ch == 61 || ch == 13)
		{
			if (ch == 72 && opt != 'd')
			{
				d = du;
				opt = 'u';
			}
			else if (ch == 75 && opt != 'r')
			{
				d = dr;
				opt = 'l';
			}
			else if (ch == 77 && opt != 'l')
			{
				d = dr;
				opt = 'r';
			}
			else if (ch == 80 && opt != 'u')
			{
				d = du;
				opt = 'd';
			}
			else if (ch == 4)
			{
				if (blood < 10)
				{
					blood++;
				}
			}
			else if (ch == 45)
			{
				if (d > 1)
				{
					dr--;
					du--;
				}
			}
			else if (ch == 61)
			{
				dr++;
				du++;
			}
			else if (ch == 13)
			{
				ch = getch();
			}
		}
	} while (ch != 27);
end:
}
void border()
{
	window(1, 1, 80, 25);
	textbackground(7);
	clrscr();
	window(2, 2, 79, 24);
	textbackground(0);
	clrscr();
}
void go_right()
{
	sx++;
	show();
}
void go_left()
{
	sx--;
	show();
}
void go_up()
{
	sy--;
	show();
}
void go_down()
{
	sy++;
	show();
}
void show()
{
	int i;
	textcolor(1);
	for (i = 0; i <= body; i++)
	{
		gotoxy(snake[i].x, snake[i].y);
		cprintf("%c", 219);
	}
}
void random_point()
{
	randomize();
px_again:
	px = random(80);
	if (px == 0 || px == 1)
		goto px_again;
py_again:
	py = random(25);
	if (py == 0 || py == 1)
		goto py_again;
	for (int i = 0; i <= body; i++)
	{
		if (px == snake[i].x && py == snake[i].y)
			goto px_again;
	}
}
void clr()
{
	window(2, 2, 79, 24);
	clrscr();
	window(1, 1, 80, 25);
}
void show_time(int t)
{
	window(1, 1, 80, 25);
	gotoxy(45, 1);
	textbackground(7);
	cprintf("Time : %d", t);
	if (t == 100)
	{
		gotoxy(45, 1);
		cprintf("           ");
	}
	window(1, 1, 80, 25);
	textbackground(0);
}
void show_point(int point)
{
	window(1, 1, 80, 25);
	gotoxy(65, 1);
	textbackground(7);
	textcolor(0);
	cprintf("Point : %d", point);
	window(2, 2, 79, 24);
	textbackground(0);
}
void show_blood(int blood)
{
	window(1, 1, 80, 25);
	gotoxy(3, 1);
	textbackground(7);
	textcolor(4);
	cprintf("Blood : ");
	for (int i = 1; i <= blood; i++)
	{
		cprintf("%c", 3);
	}
	window(2, 2, 79, 24);
	textbackground(0);
}
void help()
{
	window(2, 2, 79, 24);
	textbackground(6);
	clrscr();
	textcolor(7);
	window(25, 7, 70, 20);
	cprintf("Ctrl + d       to    Add blood");
	gotoxy(1, 2);
	cprintf("Press   Esc   to  Exit game");
	gotoxy(1, 3);
	cprintf("Press   Enter to  break");
	gotoxy(1, 10);
	cprintf("-->> Create by ( Laing Raven ) <<--");
	getch();
}