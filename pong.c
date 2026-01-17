#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define HEIGHT 10
#define WIDTH 20
#define SPEED 100

/*\e[Line;ColumnH)*/

void setTerminalMode(bool enable)
{ 
    static struct termios oldt, newt;
    if(enable)
    { 
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        printf("\e[?25l");
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    { 
        printf("\e[?25h");
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}
int main() 
{ 
    setTerminalMode(true);
    int dx = 1;
    int dy = 1;

    int x = WIDTH / 2;
    int y = HEIGHT / 2;


    int length = 2;
    int paddle_L = (HEIGHT - length) / 2; 
    int paddle_R = (HEIGHT - length) / 2;

    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    int scoreRobot = 0;
    int scoreHuman = 0;

    while(true)
    { 
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\nrobot: %d Human : %d\n", scoreRobot, scoreHuman);
        printf("\e[%d;%dH ", y, x);
        char c = 0;
        read(STDIN_FILENO, &c, sizeof(c));

        if( c == 'k')
            paddle_R -= 3;
        if( c == 'j' )
            paddle_R += 2;

        //paddle_R = y - length / 2;
        if(paddle_R > HEIGHT - length) 
            paddle_R = HEIGHT - length;

        if(paddle_R < 1)
            paddle_R = 1;

        //left paddle
        paddle_L = y  - length / 2;
        if(paddle_L > HEIGHT - length)
            paddle_L = HEIGHT - length;

        if(paddle_L < 1)
            paddle_L = 1;


        x = x + dx;
        y = y + dy;

        for(int i = 0; i < length; ++i)
        { 
            printf("\e[%d;1H|", i + paddle_L); 
            printf("\e[%d;%dH|", i + paddle_R, (WIDTH - 1)); 
        }

        if(y <= 1 || y >= HEIGHT)
            dy *= -1;

        if( x == 0 || x == (WIDTH - 1) )
        { 
            if( x == 0 )
                ++scoreHuman;
            if( x == WIDTH - 1 )
                ++scoreRobot;

            x = WIDTH / 2;
            y = HEIGHT / 2;
            
            dy = (dx > 0)? -1 : 1;
        }

        if( x == 2 && ( y <= paddle_L + length && y >= paddle_L))
            dx *= -1;

        if( x == (WIDTH - 2) && ( y <= paddle_R + length && y >= paddle_R))
            dx *= -1;

        if(x <= 0 || x >= WIDTH)
            dx *= -1;

        printf("\e[%d;%dHo", y, x);
        fflush(stdout);
        usleep(100 * 1000);
    }
    setTerminalMode(false);
    return 0;
}
