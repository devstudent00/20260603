#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Engine/Model.h"
#include "Enemy.h"

namespace {
	int saikoro = -1;
}


PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize() {
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);

	const int ENEMY_COUNT = 5;
	srand((unsigned int)time(nullptr));

	for (int i = 0; i < ENEMY_COUNT; i++) {
		int x = rand() % 40 - 20;
		int  z = rand() % 40 - 20;

		auto enemy = Instantiate<Enemy>(this);
		enemy->SetPosition({(float) x, 5, (float) z});
	}
	
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