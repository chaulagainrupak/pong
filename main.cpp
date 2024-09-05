#include <iostream>
#include "raylib.h"

using namespace std;


const int width = 1280;
const int height = 600;

int playerScore = 0;
int cpuScore = 0;


Color green = Color{60, 179, 113, 255};
Color darkGreen = Color{46, 139, 87, 255};
Color yellow = Color{255, 255, 59, 255};

class Ball{
public:
int x, y;
int speed_x = 7; 
int speed_y = 7;

int radius;

void Draw(){
    DrawCircle(x, y, radius, yellow);
}
void resetBall(){

    x = width / 2 ;
    y = height / 2 ;
}

void Update(){

    if (x + radius >= GetScreenWidth()){

        cpuScore++;
        speed_x *= -1;

        resetBall();
    }

    if (x - radius <= 0){

        playerScore++;
        speed_x *= -1;

        resetBall();
    }

    if(y + radius >=  GetScreenHeight() || y - radius <= 0){
        speed_y *= -1;
    }

    x += speed_x;
    y += speed_y;
}

};

class Paddle{
protected:

void limitMovement(){
    if (y <= 0){
        y = 0;
    }

    if(y + height >= GetScreenHeight()){
        y = GetScreenHeight() - height;
    } 
}

public:
int x, y;
int speed;
int width, height;


void Draw(){
    DrawRectangle(x, y, width, height, WHITE);
}

void Update(){
    
    if(IsKeyDown(KEY_UP)){
        y -= speed;
    }

    if(IsKeyDown(KEY_DOWN)){
    y += speed;
    }

    limitMovement();
}
};


class CpuPaddle: public Paddle {

public:
    void Update(int ball_y){

        if (y + height / 2 > ball_y){
            y = y - speed;
        }
        if (y + height / 2 <= ball_y){
            y = y + speed;
        }

        limitMovement();
    }
};

Ball ball;
Paddle paddle;
CpuPaddle cpu;

int main (){

    std::cout << "Game Starting!" << std::endl;
    
    // Giving all the attributes to all the objects so that we can change things easily and quickly



    ball.x = width / 2;
    ball.y = height / 2;

    ball.radius = 12;

    paddle.width = 20;
    paddle.height = 120;
    paddle.speed = 6;
    paddle.x = width - 28;
    paddle.y = (height - paddle.height ) / 2; 

        
    cpu.width = 20;
    cpu.height = 120;
    cpu.speed = 6;
    cpu.x  = 8;
    cpu.y = (height - cpu.height ) / 2; 

    //

    InitWindow(width, height, "A Pong Game!");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(green);

            DrawRectangle(0, 0, width / 2, height, darkGreen);

            DrawText(TextFormat("%i",cpuScore), width / 4 - 20, 20, 80, WHITE );
            DrawText(TextFormat("%i",playerScore), 3*width / 4 + 20 , 20, 80, WHITE );

            DrawText("Pong By Rupak Chaulagain", width / 5 , height / 2 , 60, Color{255, 255, 255, 120});

            ball.Update();
            paddle.Update();
            cpu.Update(ball.y);

            if (CheckCollisionCircleRec(
                                        Vector2{float(ball.x), float(ball.y)}, 

                                        float(ball.radius), 

                                        Rectangle{float(paddle.x), float(paddle.y), float(paddle.width), float(paddle.height)})
            ){
                ball.speed_x *= -1;
            }


            if (CheckCollisionCircleRec(
                                        Vector2{float(ball.x), float(ball.y)}, 

                                        float(ball.radius), 

                                        Rectangle{float(cpu.x), float(cpu.y), float(cpu.width), float(cpu.height)})
            ){
                ball.speed_x *= -1;
            }

            ball.Draw();
            paddle.Draw();
            cpu.Draw();




        EndDrawing();
    }

    CloseWindow();
    return 0;
}