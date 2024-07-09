#include"MyFunction.h"
//関数の定義

void InitBoard(Board& _board)
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			_board.tile[j][i] = j * BOARD_WIDTH + i + 1; //[j][i] = [列][行]の位置のタイル番号
			_board.tileRec[j][i] = Rect{ i * TILE_SIZE.x + 2 ,j * TILE_SIZE.y + 2 , TILE_SIZE.x - 4,TILE_SIZE.y - 4 };//{ X座標の計算, Y座標の計算},　幅（高さ）
		}
	}
}
//タイトル画面からゲーム画面への遷移
void TitleUpdate()
{
	if (StartButtonRect.leftClicked())//スタートボタンを押したら
		state = GAME_STATE::PLAY;//stateをプレイ画面へ

}
//タイトル画面の描画
void TitleDraw()
{
	String TitleStr = U"THE SLIDE PUZZLE";
	String StartStr = U"Push Here to Start GAME ";
	Point margin{ 3,3 };
	Point ajustSpace{ 0, -50 };
	Point startPoint = { Scene::Center().x, Scene::Center().y + 50 };
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace + margin, Palette::Lightslategray);
	FontAsset(U"TITLE_FONT")(TitleStr).drawAt(Scene::Center() + ajustSpace, Palette::Blueviolet);
	FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black), startPoint + ajustSpace,
				Palette::White);
	StartButtonRect = FontAsset(U"BUTTON_FONT")(StartStr).drawAt(TextStyle::Outline(0.2, Palette::Black),
	startPoint + ajustSpace, Palette::White).asRect();//ボタンの描画領域を取得
}
//プレイ画面からクリア画面への遷移
//_board タイルの位置を参照渡し
void PlayUpdate(Board& _board)
{
	if (MouseL.down())
	{
		Point cp = Cursor::Pos();
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			for (int i = 0; i < BOARD_WIDTH; i++)
			{
				if (IsPointInRect(cp, _board.tileRec[j][i]))//クリック地点がタイル上なら
				{
					Point p = { i,j };
					if (CanMoveIt(p, _board) == true)
					{
						SwapTile(p, _board);
						if (CheckClear(_board) == true)//CheckClearがtrueで返されたら
						{
							state = GAME_STATE::CLEAR;//stateをクリア画面へ
						}
					}
					else
					{
						//Print << _board.tile[j][i] << U"It Can't Move!";
					}
				}
			}
		}


	}


}

//プレイ画面を描画
//_board タイルの位置を参照渡し
void PlayDraw(Board& _board)
{
	Scene::SetBackground(Palette::Lemonchiffon);

	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			if (_board.tile[j][i] == BLANK_POS)
			{
				continue;//条件をスルー、for分の最初に戻る
			}

			_board.tileRec[j][i].draw(Palette::Lightblue);//タイルに色塗り
			_board.tileRec[j][i].drawFrame(2, 0, Palette::Darkblue);//枠線
			FontAsset(U"TILE_FONT")(ToString(_board.tile[j][i])).drawAt(_board.tileRec[j][i].center());
			//ToString() ()の中を文字列型にする  center()　中央に描画 　　　　　　　siv3dで使える機能

		}
	}
	//String PlayStr = U"プレイ画面";//StringはSiv3Dだけで使えるstringの上位型
	//FontAsset(U"TITLE_FONT")(PlayStr).drawAt(Scene::Center(), Palette::Cadetblue);
}

//クリア画面からタイトル画面への遷移
//_board タイルの位置を参照渡し
void ClearUpdate(Board& _board)
{
	if (MouseL.down())
	{
		InitGame(_board);//ボードをリセット
		state = GAME_STATE::TITLE;//stateをタイトル画面にする

	}
}
//クリア画面の描画
//_board タイルの位置を参照渡し
void ClearDraw(Board& _board)
{
	FontAsset(U"TITLE_FONT")(U"clear!!!!!!!!").drawAt(Scene::Center(), Palette::Red);
}

//ボードの初期化
//_board タイルの位置を参照渡し
void InitGame(Board& _board)
{
	Window::Resize(WSIZE);//ウィンドウサイズの指定
	state = GAME_STATE::TITLE;//stateをタイトル画面にする
	InitBoard(_board);
	MakeProblem(_board);
}
//クリックした場所が点と短形の中にあるかチェック
//_board タイルの位置を参照渡し
//_point クリックした場所を受け取る
//return trueかfalseでクリックした場所が点と短形の中にあるか返す
bool IsPointInRect(Point _point, Rect rect)
{
	if (_point.x >= rect.x && _point.x < rect.x + TILE_SIZE.x && _point.y >= rect.y && _point.y < rect.y + TILE_SIZE.y)//点が短形の中にあるかチェック
	{
		return true;
	}
	return false;
}

//指定した番号は動かせるタイルか
//_board タイルの位置を参照渡し
//_p 座標を受け取る
//return trueかfalseで指定した番号は動かせるタイルか返す
bool CanMoveIt(Point _p, Board& _board)
{
	Point blank = SearchTileNum(BLANK_POS, _board);

	if (_p.x == -1 || blank.x == -1) return false;
	int dist = (blank.x - _p.x) * (blank.x - _p.x) + (blank.y - _p.y) * (blank.y - _p.y);//blankと_pのマンハッタン距離の2乗を計算
	if (dist == 1)//距離が1なら)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//numの番号をさがしてタイルの二次元配列のインデックスをPoint型｛,｝で返す
//_board タイルの位置を参照渡し
//num 変換前の整数
//return Point型で整数のある場所を返す
Point SearchTileNum(int _num, Board& _board)
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			if (_board.tile[j][i] == _num)//_numを見つけたら
			{
				Point p = { i,j };//Point型(x,y)で返す
				return (p);
			}
		}
	}
	Point p = { -1,-1 };//エラー用
	return(p);
}

//タイル移動(その番号と空白セルを交換する)関数
//_board タイルの位置を参照渡し
//_p 座標を受け取る
void SwapTile(Point _p, Board& _board)
{
	Point blank = SearchTileNum(BLANK_POS, _board);//BLANK_POSをサーチ

	if (blank.x == -1 || _p.x == -1)
		return;
	if (CanMoveIt(_p, _board) == true)
	{
		std::swap(_board.tile[_p.y][_p.x], _board.tile[blank.y][blank.x]);
	}
	else
	{
		return;
	}
}
//問題作成関数
//_board タイルの位置を参照渡し
void MakeProblem(Board& _board)
{
	int level = 10;//高いほどシャッフル回数が増えて難しくなる
	Point p;
	for (int i = 0; i < level; i++)
	{
		while (true)//動かせるタイルを発見するまでランダムでタイルを選択
		{
			int num = rand() % 15 + 1;
			p = SearchTileNum(num, _board);
			if (CanMoveIt(p, _board) == true)
			{
				break;
			}
		}
		SwapTile(p, _board);//numのタイルを移動
	}
}

//クリア判定
//_board タイルの位置を参照渡し
bool CheckClear(Board& _board)
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			if (_board.tile[j][i] != j * BOARD_WIDTH + i + 1)//順番があっていないならfalse返して関数を抜ける
			{
				return(false);
			}
		}
	}
	return(true);//ここまでくれば整列されている
}
