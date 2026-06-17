#pragma once
#include "Engine//GameObject.h"
class Bullet : public GameObject {
private:
	int hModel_;
public:
	Bullet(GameObject* parent);
	~Bullet() {};

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

