#pragma once
#include "Engine//GameObject.h"

class TankHead : public GameObject {
private:
	int hModel_ = -1;
public:
	TankHead(GameObject* parent);
	~TankHead() {};

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

