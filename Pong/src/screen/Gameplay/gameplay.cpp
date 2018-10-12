/*#include "Game\game.h"

#include "sl.h"

#include "gameplay.h"
#include <ctime>
#include <iostream>

namespace GameInit
{
	Screen screen = MENU;
	namespace Gameplay
	{
		static bool checkBallInit();
	
		bool checkBallInit()
		{
			srand(time(0));
			if (rand() % 2 == 0) {
				return true;
			}
			else {
				return false;
			}
		}
	
		struct Ball {
			float x;
			float y;
			Vector2 position;
			Vector2 speed;
			int radius;
			bool active;
		};

		// Initialization
		//-------------------------------------------- Statics
		int screenWidth = 1600;
		int screenHeight = 900;
		static int checkGame = 1;
		static Rectangle box1;
		static Rectangle box2;
		static Ball ball;
		static bool InitGame = true;
		static bool direccionY = true;
		static bool colRight = false;
		static short int INIT_VELOCITY = 400;
		static short int randomMusic = 0;
		static const short int MAX_POINT = 10;
		static const short int HEIGHT_BOX = (screenHeight /5);
		static const short int WIDTH_BOX = (screenWidth / 45);
		static const short int RADIUS_BALL = (screenWidth / 45 / 2);
		static const short int SPEED_BALL_INIT = 0;
		static const short int MOVE_BOX = 400;
		static const short int INIT_SCORE = 0;
		static const short int INIT_LIMITCHECK = 0;
		static const short int LIMIT_TOP = 10;
		static const short int EXTRA_VELOCITY = 20;
		static Sound fxWav;
		static Sound fxWav2;
		static Sound fxWav3;
		static Sound fxWav4;
		static int scoreBox1 = INIT_SCORE;
		static int scoreBox2 = INIT_SCORE;
		static int limitCheck = INIT_LIMITCHECK;
		static int velocity = INIT_VELOCITY;
		//--------------------------------------------
	
		bool left = false;
		bool right = false;
		bool firstInit = true;
		//--------------------------------------------
		void initGame() {
			fxWav = LoadSound("res/Blip_Select.wav");
			fxWav2= LoadSound("res/Blip_Select2.wav");
			fxWav3= LoadSound("res/Blip_Select3.wav");
			fxWav4 = LoadSound("res/Blip_Select4.wav");
			
			velocity = INIT_VELOCITY;
			box1.height = HEIGHT_BOX;
			box1.width = WIDTH_BOX;
			box1.x = screenWidth / 20;
			box1.y = screenHeight / 2 - 40;
			//--------------------------------
			box2.height = HEIGHT_BOX;
			box2.width = WIDTH_BOX;
			box2.x = screenWidth-(screenWidth / 20);
			box2.y = screenHeight / 2 - 40;
			//--------------------------------
			ball.x = (float)screenWidth / 2;
			ball.y = (float)screenHeight / 2;
			ball.position = Vector2{ ball.x, ball.y };
			ball.speed = Vector2 { SPEED_BALL_INIT, SPEED_BALL_INIT };
			ball.radius = RADIUS_BALL;
			ball.active = false;
		}

		void updateGame()
		{
	
			SetExitKey(0);
			if (IsKeyDown(KEY_UP))
			{
				if (box2.y > 9)
				{
					box2.y -= MOVE_BOX * GetFrameTime();              // Player2 movement down
				}
			}
			else if (IsKeyDown(KEY_DOWN))
			{
				if (box2.y < screenHeight - HEIGHT_BOX)
				{
					box2.y += MOVE_BOX * GetFrameTime();              // Player2 movement down
				}
			}
			if (IsKeyDown(KEY_S))
			{
				if (box1.y < screenHeight - HEIGHT_BOX)
				{
					box1.y += MOVE_BOX * GetFrameTime();              // Player movement down
				}
			}
			else if (IsKeyDown(KEY_W))
			{
				if (box1.y > 9) {
					box1.y -= MOVE_BOX * GetFrameTime();              // Player movement down
				}
			}
			if (IsKeyDown(KEY_M))
			{
				screen = MENU;
				limitCheck = INIT_LIMITCHECK;
				ball.x = (float)screenWidth / 2;
				ball.y = (float)screenHeight / 2;
				scoreBox1 = INIT_SCORE;
				scoreBox2 = INIT_SCORE;
				velocity = INIT_VELOCITY;
			}
			//Ball Movement
#pragma region Ball
	//-------------------------------------------------------
	//Primer tiro de bocha
			if (checkBallInit() && InitGame)
			{
				if (checkBallInit())
				{
					colRight = true;
				}
				else
				{
					colRight = false;
				}
				direccionY = false;
				InitGame = false;
			}
			else if (checkBallInit() == false && InitGame)
			{
				if (checkBallInit())
				{
					colRight = true;
				}
				else
				{
					colRight = false;
				}
				direccionY = true;
				InitGame = false;
			}
			//---------------------------------------------------------
			//Bordes pantalla
			if (ball.y <= LIMIT_TOP)
			{
				direccionY = false;
			}
			if (ball.y >= (screenHeight - 5))
			{
				direccionY = true;
			}
			if (ball.x >= screenWidth)
			{
				scoreBox1++;

				if (scoreBox1 % 3 == 0)
				{
					velocity += 50;
				}

				if (limitCheck > 10) velocity -= EXTRA_VELOCITY;
				limitCheck = INIT_LIMITCHECK;
	
				ball.x = (float)screenWidth / 2;
				ball.y = (float)screenHeight / 2;
				InitGame = true;
			}
			if (ball.x <= 0)
			{

				scoreBox2++;
				if (scoreBox2 % 3 == 0) velocity++;
				if (limitCheck > 10)  velocity -= EXTRA_VELOCITY;
				limitCheck = 0;

				ball.x = (float)screenWidth / 2;
				ball.y = (float)screenHeight / 2;
				InitGame = true;
			}
			//--------------------------------------------------------

			//Colision barras/pelota
			if (CheckCollisionCircleRec(ball.position, ball.radius, box1))
			{
				ball.position.x += ball.radius;
				randomMusic = GetRandomValue(1, 4);
				switch (randomMusic) 
				{
				case 1:
					PlaySound(fxWav);
					break;
				case 2:
					PlaySound(fxWav2);
					break;
				case 3:
					PlaySound(fxWav3);
					break;
				case 4:
					PlaySound(fxWav4);
					break;
				}
				
				limitCheck++;
				colRight = false;
				if (ball.position.y < box1.y + 40)
				{
					
					direccionY = true;

					if (ball.position.y > box1.y + 60)
					{
						velocity += 50;

					}
					else
					{
						velocity = INIT_VELOCITY;
					}
				}
				else
				{
					direccionY = false;

					if (ball.position.y < box1.y + 20)
					{

						velocity += 50;

					}
					else
					{
						velocity = INIT_VELOCITY;
					}
				}
			}
			if (CheckCollisionCircleRec(ball.position, ball.radius, box2))
			{
				ball.position.x -= ball.radius;
				randomMusic = GetRandomValue(1, 4);
				switch (randomMusic) {
				case 1:
					PlaySound(fxWav);
					break;
				case 2:
					PlaySound(fxWav2);
					break;
				case 3:
					PlaySound(fxWav3);
					break;
				case 4:
					PlaySound(fxWav4);
					break;
				}
				colRight = true;
				limitCheck++;
				if (ball.position.y < box2.y + 40)
				{
					direccionY = true;

					if (ball.position.y > box2.y + 70)
					{
						velocity += 50;
					}
					else
					{
						velocity = INIT_VELOCITY;
					}
				}
				else {
					direccionY = false;

					if (ball.position.y < box2.y + 10)
					{
						velocity += 20;
					}
					else
					{
						velocity = INIT_VELOCITY;
					}
				}
			}
			if (colRight) {
				if (direccionY)
				{
					ball.y -= velocity * GetFrameTime();
				}
				else
				{
					ball.y += velocity * GetFrameTime();
				}

				ball.x -= velocity * GetFrameTime();

			}
			else
			{
				if (direccionY)
				{
					ball.y -= velocity * GetFrameTime();
				}
				else
				{
					ball.y += velocity  * GetFrameTime();
				}
				ball.x += velocity * GetFrameTime();

			}
			if (scoreBox2 == MAX_POINT)
			{

				screen = WIN;
				right = true;

				scoreBox1 = INIT_SCORE;
				scoreBox2 = INIT_SCORE;
				velocity = INIT_VELOCITY;
			}
			else if (scoreBox1 == MAX_POINT)
			{
				screen = WIN;
				left = true;

				scoreBox1 = INIT_SCORE;
				scoreBox2 = INIT_SCORE;
				velocity = INIT_VELOCITY;
			}
			if (limitCheck == 10)
			{
				limitCheck++;
				velocity += EXTRA_VELOCITY;
				
			}
			ball.position = Vector2{ ball.x, ball.y };
			
#pragma endregion
			//----------------------------------------------------------------------------------
			// TODO: Update your variables here
			//----------------------------------------------------------------------------------
			// Draw
			//----------------------------------------------------------------------------------

		}

		void DrawGame()
		{
			DrawRectangleRec(box1, BLACK);
			DrawRectangleRec(box2, BLACK);
			DrawCircleV(ball.position, ball.radius, MAROON);
			DrawText(FormatText("%01i", scoreBox1), (screenWidth / 2) - 20, screenHeight / 20, 30, LIGHTGRAY);
			DrawText(FormatText(" | %01i", scoreBox2), (screenWidth / 2), screenHeight/20, 30, LIGHTGRAY);

			DrawText("PRESS M FOR RETURN TO THE MENU",	screenWidth / 2 - (MeasureText("PRESS M FOR RETURN TO THE MENU",15) / 2), screenHeight - screenHeight / 20 , 15, BLACK);
		}
		void closeAudio(){
			
		}
	}
}

*/