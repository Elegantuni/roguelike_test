#include <ncurses.h>
#include <stdlib.h>

int main(void)
{
	int width, height;
	int screenwidth = 80, screenheight = 24;
	int ch;
	enum area { space = 0, walldown, walldash, door, player };
	int areachoicewidth, areachoiceheight;
	const int screenwidthworld = screenwidth;
	const int screenheightworld = screenheight;
	int theworld[screenheightworld][screenwidthworld];
	int doorchoice;

	for(int i = 0; i < screenheightworld; i++)
	{
		for(int j = 0; j < screenwidthworld; j++)
		{
			theworld[i][j] = space;
		}
	}

	areachoicewidth = arc4random_uniform(screenwidth);
	areachoiceheight = arc4random_uniform(screenheight);

	theworld[areachoiceheight][areachoicewidth] = walldash;

	for(int i = areachoicewidth - 1; i >= 0; i--)
	{
		if(theworld[areachoiceheight][i] == space)
		{
			theworld[areachoiceheight][i] = walldash;
		}
		else
		{
			break;
		}
	}

	for(int i = areachoicewidth + 1; i < screenwidthworld; i++)
	{
		if(theworld[areachoiceheight][i] == space)
		{
			theworld[areachoiceheight][i] = walldash;
		}
		else
		{
			break;
		}
	}

	for(int i = areachoiceheight - 1; i >= 0; i--)
	{
		if(theworld[i][areachoicewidth] == space)
		{
			theworld[i][areachoicewidth] = walldown;
		}
		else
		{
			break;
		}
	}
	
	for(int i = areachoiceheight + 1; i < screenheightworld; i++)
	{
		if(theworld[i][areachoicewidth] == space)
		{
			theworld[i][areachoicewidth] = walldown;
		}
		else
		{
			break;
		}
	}

	doorchoice = arc4random_uniform(areachoicewidth);

	while(areachoicewidth != 0 && doorchoice == areachoicewidth)
	{
		doorchoice = arc4random_uniform(areachoicewidth);
	}

	theworld[areachoiceheight][doorchoice] = door;

	doorchoice = areachoicewidth + arc4random_uniform(screenwidthworld - areachoicewidth);

	while(areachoicewidth != screenwidthworld - 1 && doorchoice == areachoicewidth)
	{
		doorchoice = arc4random_uniform(screenwidthworld - areachoicewidth);
	}

	theworld[areachoiceheight][doorchoice] = door;

	doorchoice = arc4random_uniform(areachoiceheight);

	while(areachoiceheight != 0 && doorchoice == areachoiceheight)
	{
		doorchoice = arc4random_uniform(areachoiceheight);
	}

	theworld[doorchoice][areachoicewidth] = door;

	doorchoice = areachoiceheight + arc4random_uniform(screenheightworld - areachoiceheight);

	while(areachoiceheight != screenheightworld - 1 && doorchoice == areachoiceheight)
	{
		doorchoice = arc4random_uniform(screenheightworld - areachoiceheight);
	}

	theworld[doorchoice][areachoicewidth] = door;

	int theworlddoor[screenheightworld][screenwidthworld];

	for(int i = 0; i < screenheightworld; i++)
	{
		for(int j = 0; j < screenwidthworld; j++)
		{
			theworlddoor[i][j] = theworld[i][j];
		}
	}

	width = arc4random_uniform(screenwidth);
	height = arc4random_uniform(screenheight);

	while(theworld[height][width] != space)
	{
		width = arc4random_uniform(screenwidth);
		height = arc4random_uniform(screenheight);
	}

	theworld[height][width] = player;

	int terminateloop = 1;

	initscr();

	noecho();

	cbreak();

	clear();

	for(int i = 0; i < screenheightworld; i++)
	{
		for(int j = 0; j < screenwidthworld; j++)
		{
			if(theworld[i][j] == walldown)
			{
				mvprintw(i, j, "|");
			}

			if(theworld[i][j] == walldash)
			{
				mvprintw(i, j, "-");
			}
			
			if(theworld[i][j] == player)
			{
				mvprintw(i, j, "@");
			}

			if(theworld[i][j] == door)
			{
				mvprintw(i, j, "#");
			}
		}
	}

	move(height, width);

	refresh();

	while((ch = getch()) != 'q')
	{
		clear();
		
		theworld[height][width] = space;

		if(ch == 'a')
		{
			width--;

			if(width < 0)
			{
				width = 0;
			}

			if(theworld[height][width] != space && theworld[height][width] != door)
			{
				width = width++;
			}
		}
		else if(ch == 'd')
		{
			width++;

			if(width >= screenwidth)
			{
				width = screenwidth - 1;
			}

			if(theworld[height][width] != space && theworld[height][width] != door)
			{
				width--;
			}
		}
		else if(ch == 'w')
		{
			height--;

			if(height < 0)
			{
				height = 0;
			}

			if(theworld[height][width] != space && theworld[height][width] != door)
			{
				height++;
			}
		}
		else if(ch == 's')
		{
			height++;

			if(height >= screenheight)
			{
				height = screenheight - 1;
			}

			if(theworld[height][width] != space && theworld[height][width] != door)
			{
				height--;
			}
		}
		else if(ch == 'c')
		{
			if(theworlddoor[height-1][width-1] == door)
			{
				theworld[height-1][width-1] == door;
			}
			if(theworlddoor[height-1][width] == door)
			{
				theworld[height-1][width] = door;
			}
			if(theworlddoor[height-1][width+1] == door)
			{
				theworld[height-1][width+1] == door;
			}
			if(theworlddoor[height][width-1] == door)
			{
				theworld[height][width-1] = door;
			}
			if(theworlddoor[height][width] == door)
			{
				theworld[height][width] = door;
			}
			if(theworlddoor[height][width+1] == door)
			{
				theworld[height][width+1] = door;
			}
			if(theworlddoor[height+1][width-1] == door)
			{
				theworld[height+1][width-1] = door;
			}
			if(theworlddoor[height+1][width] == door)
			{
				theworld[height+1][width] = door;
			}
			if(theworlddoor[height+1][width+1] == door)
			{
				theworld[height+1][width+1] = door;
			}
		}

		theworld[height][width] = player;

		for(int i = 0; i < screenheightworld; i++)
		{
			for(int j = 0; j < screenwidthworld; j++)
			{
				if(theworld[i][j] == walldown)
				{
					mvprintw(i, j, "|");
				}

				if(theworld[i][j] == walldash)
				{
					mvprintw(i, j, "-");
				}
				
				if(theworld[i][j] == player)
				{
					mvprintw(i, j, "@");
				}

				if(theworld[i][j] == door)
				{
					mvprintw(i, j, "#");
				}
			}
		}
 
		move(height, width);

		refresh();
	}

	endwin();

	return 0;
}

