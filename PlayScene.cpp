#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"


PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize() {
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}