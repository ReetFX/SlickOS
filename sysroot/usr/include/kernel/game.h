#include <stdbool.h>
#include <kernel/tty.h>

#define RES_Y 25
#define RES_X 80

bool gameOver = false;

int p1_y = 12;
int p2_y = 12;

int b_x = 40;
int b_y = 12;

int vx = 1;
int vy = 1;

int random_seed=0;

int maxrand(int seed,int max)
{
	random_seed = random_seed+seed * 1103515245 +12345;
	return (unsigned int)(random_seed / 65536) % (max+1); 
}

void draw()
{
	for(int y = 0; y < RES_Y; y++)
	{
		for(int x = 0; x < RES_X; x++)
		{
			if((y==p1_y && x == 79) || (y==p1_y-1 && x == 79) || (y==p1_y+1 && x == 79))
			{
				terminal_putchar('#');
            }
			else if((y==p2_y && x == 0) || (y==p2_y-1 && x == 0) || (y==p2_y+1 && x == 0))
			{
				terminal_putchar('#');
			}
			else if(y==b_y && x==b_x){
				terminal_putchar('O');
			}
			else{
				terminal_putchar(' ');
			}
		}
	}
}

void input()
{
	if(inb(KEYBOARD_PORT)==KEY_UP){
		if(p1_y>1){
				p1_y--;
			}
	}	
	if(inb(KEYBOARD_PORT)==KEY_DOWN){
			if(p1_y<23){
				p1_y++;
	        }   
    }
	if(inb(KEYBOARD_PORT)==KEY_W){
		if(p2_y>1){
			p2_y--;
		}
    }	
	if(inb(KEYBOARD_PORT)==KEY_S){
		if(p2_y<23){
			p2_y++;
		}
	}
	if(inb(KEYBOARD_PORT)==KEY_ESC){
		gameOver=true;
	}
}

void pong()
{
	terminal_clear();
	if(maxrand(5, 1)==1)
	{
		vx=-vx;
	}

	do{
		sleep(0x02FFFFFF);
		if(b_x==1 && b_y >= p2_y-1 && b_y <= p2_y+1)
		{
			b_x=2;
			vx=-vx;
		}
		if(b_x==78 && b_y >= p1_y-1 && b_y <= p1_y+1)
		{
			b_x=77;
			vx=-vx;
		}
		if(b_y>24 || b_y<1)
		{
			vy=-vy;
		}
		if(b_x<0 || b_x>80)
		{
			gameOver = true;
		}
		input();
		b_y+=vy;
		b_x+=vx;
		draw();
	}
	while(!gameOver);
	terminal_clear();
	printf("Game Over!\n");
}