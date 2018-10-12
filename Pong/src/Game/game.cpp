/*#include "Game\game.h"

#include "sl.h"

#include "screen\Menu\menu.h"
#include "screen\Win\win.h"
#include "screen\Gameplay\gameplay.h"
#include "screen\Credits\credits.h"

namespace GameInit
{
	static void Init();
	static void Update();
	static void Draw();
	static void Close();
	Texture2D texture;
	Music MusicLoop;

	void Init() {
		InitWindow(Gameplay::screenWidth, Gameplay::screenHeight, "Pong");
		InitAudioDevice();
		MusicLoop = LoadMusicStream("res/music.ogg");
		PlayMusicStream(MusicLoop);
	}

	void Update() {
		UpdateMusicStream(MusicLoop);
		switch (screen)
		{
		case GAME:
			if (Gameplay::firstInit)
			{


				Gameplay::initGame();
				Gameplay::firstInit = false;
			}
			Gameplay::updateGame();
			break;
		case MENU:
			initMenu::UpdateMenu();
			break;
		case WIN:
			initWin::UpdateWin();
			break;
		case CREDITS:
			initCredits::UpdateCredits();
			break;
		default:
			break;
		}
	}
	
	void Draw() {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		switch (screen)
		{
		case GAME:
			Gameplay::DrawGame();
			break;
		case MENU:
			initMenu::DrawMenu();
			break;
		case WIN:
			initWin::DrawWin(Gameplay::left, Gameplay::right);
			break;
		case CREDITS:
			initCredits::DrawCredits();
			break;
		}
		EndDrawing();
	}



	void Close() {
		UnloadMusicStream(MusicLoop);   // Unload music stream buffers from RAM
		CloseAudioDevice();
		CloseWindow();
	}
	void LoadScreen()
	{
		Init();
		// Main game loop
		while (!WindowShouldClose())    // Detect window close button or ESC key
		{
			Update();
			Draw();
		}
		//--------------------------------------------------------------------------------------   
	
		Close();
		// Close window and OpenGL context
		//--------------------------------------------------------------------------------------
	}

}
*/