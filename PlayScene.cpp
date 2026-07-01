#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Engine/Model.h"
#include "Enemy.h"
#include "Engine/Text.h"
#include "TankHead.h"

namespace {
	int saikoro = -1;
	Text* leftText = nullptr;
}


PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize() {
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
	leftText = new Text();
	leftText->Initialize();

	const int ENEMY_COUNT = 10;
	srand((unsigned int)time(nullptr));

	for (int i = 0; i < ENEMY_COUNT; i++) {
		int x = rand() % 40 - 20; //-20～20
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
void PlayScene::Draw() {
	if (leftText == nullptr) return;

	TankHead* tank = (TankHead*)FindObject("TankHead");
	if (tank == nullptr) return;
	std::string text = "Point: " + std::to_string(tank->GetPoint());
	leftText->Draw(15, 15, text.c_str());
}

//開放
void PlayScene::Release()
{
}