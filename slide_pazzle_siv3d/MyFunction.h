#pragma once

enum GAME_STATE
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER,
};
const int BOARD_WIDTH = 4;
const int BOARD_HEIGHT = 4;
const int BLANK_POS = 16;
const Size TILE_SIZE = { 128, 128 };//タイル１枚のサイズ　幅、高さ
const Size WSIZE = BOARD_WIDTH * TILE_SIZE;//windowの大きさ 4x {128, 128} 縦横同じなのでどっちかかけてやる
//String str = ToString(a); これで数値と文字列の変換ができる(Siv3dの機能)
//Rect rec{ x,y,width };
//rec.center();　.centerで真ん中の座標をとる

//関数宣言
GAME_STATE state = GAME_STATE::TITLE;//ゲーム状態の変数と、状態の初期化
//GAME_STATE state = GAME_STATE::PLAY;//プレイ画面を呼び出す
//GAME_STATE state = GAME_STATE::CLEAR;//クリア画面を呼び出す
Rect StartButtonRect;


struct Board
{
	//         　行    列
	int tile[BOARD_HEIGHT][BOARD_WIDTH];
	//四角形のタイルの位置(行列)
	Rect tileRec[BOARD_HEIGHT][BOARD_WIDTH];
};

//プロトタイプ宣言
void TitleUpdate();
void TitleDraw();

void PlayUpdate(Board& _board);
void PlayDraw(Board& _board);

void ClearUpdate(Board& _board);
void ClearDraw(Board& _board);
void InitGame(Board& _board);
bool IsPointInRect(Point point, Rect rect);
bool CanMoveIt(Point _p, Board& _board);
Point SearchTileNum(int num, Board& _board);
void SwapTile(Point _p, Board& _board);
void MakeProblem(Board& _board);
bool CheckClear(Board& _board);

////ボードの初期化
////_board タイルの位置を参照渡し
//void InitBoard(Board& _board);
//
////タイトル画面からゲーム画面への遷移
//void TitleUpdate();
//
////タイトル画面の描画
//void TitleDraw();
//
////プレイ画面からクリア画面への遷移
////_board タイルの位置を参照渡し
//void PlayUpdate(Board& _board);
//
////プレイ画面を描画
////_board タイルの位置を参照渡し
//void PlayDraw(Board& _board);
//
////クリア画面からタイトル画面への遷移
////_board タイルの位置を参照渡し
//void ClearUpdate(Board& _board);
//
////クリア画面の描画
////_board タイルの位置を参照渡し
//void ClearDraw(Board& _board);
//
////ボードの初期化
////_board タイルの位置を参照渡し
//void InitGame(Board& _board);
//
//// クリックした場所が点と短形の中にあるかチェック
////_board タイルの位置を参照渡し
////_point クリックした場所を受け取る
////return trueかfalseでクリックした場所が点と短形の中にあるか返す
//bool IsPointInRect(Point _point, Rect rect);
//
////指定した番号は動かせるタイルか
////_board タイルの位置を参照渡し
////_p 座標を受け取る
////return trueかfalseで指定した番号は動かせるタイルか返す
//bool CanMoveIt(Point _p, Board& _board);
//
////numの番号をさがしてタイルの二次元配列のインデックスをPoint型｛,｝で返す
////_board タイルの位置を参照渡し
////num 変換前の整数
////return Point型で整数のある場所を返す
//Point SearchTileNum(int _num, Board& _board);
//
////タイル移動(その番号と空白セルを交換する)関数
////_board タイルの位置を参照渡し
////_p 座標を受け取る
//void SwapTile(Point _p, Board& _board);
//
////問題作成関数
////_board タイルの位置を参照渡し
//void MakeProblem(Board& _board);
//
////クリア判定
////_board タイルの位置を参照渡し
//bool CheckClear(Board& _board);
