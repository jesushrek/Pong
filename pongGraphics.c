#include <raylib.h>
#include <stdlib.h>

#define WIDTH 40
#define HEIGHT 30

#define CELL 10

int main() { 
    int screenHeight = HEIGHT * CELL;
    int screenWidth = WIDTH * CELL;
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(144);

    int x = screenHeight / 2;
    int y = screenWidth / 2;

    int dx = 1;
    int dy = +1;

    int length = 5;
    int paddleWidth = CELL;
    int paddleHeight = CELL * length;
    int paddle_L = screenHeight / 2;
    int paddle_R = screenHeight / 2;

    while(!WindowShouldClose()) { 
        x += dx;
        y += dy;

        paddle_L = y;

        if(IsKeyPressed(KEY_J)) paddle_R += CELL * length;
        if(IsKeyPressed(KEY_K)) paddle_R -= CELL * length;

        if(paddle_L <= 0)
            paddle_L = 1;
        if(paddle_L + paddleHeight >= screenHeight)
            paddle_L = screenHeight - paddleHeight;

        if(paddle_R <= 0)
            paddle_R = 1;
        if(paddle_R + paddleHeight >= screenHeight)
            paddle_R = screenHeight - paddleHeight;


        if( y <= 0 || y >= (screenHeight - 1) - CELL)
            dy *= -1;

        if( x == paddleWidth && y >= paddle_L && y <= paddle_L + paddleHeight)
            dx *= -1;

        if( x + CELL == (screenWidth - paddleWidth) && y >= paddle_R && y <= paddle_R + paddleHeight)
            dx *= -1;

        if( x <= 0 || x >= screenWidth - 1 - CELL)
        {
            x = screenWidth / 2;
            y = screenHeight / 2;

            /*
               if( dx < 0 )
               dy = 1;
               if( dx > 0 )
               dy = -1;
               */

            if(dy >= screenWidth)
                dx = -1;
            if(dy <= 0)
                dx = +1;
            dy = -1;

            paddle_R = screenHeight / 2;
        }

        BeginDrawing();
        DrawRectangle(x, y, CELL, CELL, RED);
        ClearBackground(WHITE);

        DrawRectangle(0, paddle_L, paddleWidth, paddleHeight, BLACK);
        DrawRectangle(screenWidth - paddleWidth, paddle_R, paddleWidth, paddleHeight, BLACK);
        EndDrawing();
    }
    CloseWindow();
}
