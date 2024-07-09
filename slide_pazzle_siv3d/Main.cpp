# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include"MyFunction.h"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	//タイトル画面とスタートボタンのフォント（そのままほかのシーンに使いまわし）
	FontAsset::Register(U"TITLE_FONT", FontMethod::SDF, 40, Typeface::Bold);//atodekaeru
	FontAsset::Register(U"BUTTON_FONT", FontMethod::SDF, 20, Typeface::Mplus_Heavy);
	FontAsset::Register(U"TILE_FONT", FontMethod::SDF, 75, Typeface::Bold);
	Window::Resize(WSIZE);

	srand(static_cast<unsigned int>(time(nullptr)));
	Board myboard;
	InitGame(myboard);
	//std::swap(myboard.tile[2][2], myboard.tile[3][3]);

	while (System::Update())
	{
		switch (state)
		{
		case TITLE:
			TitleUpdate();
			TitleDraw();
			break;
		case PLAY:
			PlayUpdate(myboard);
			PlayDraw(myboard);
			break;
		case CLEAR:
			ClearUpdate(myboard);
			ClearDraw(myboard);
			break;
		case GAMEOVER:
			break;
		default:
			break;
		}
	}
}
