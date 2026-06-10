#pragma once
#include "Engine/GameObject.h"

class Tank : public GameObject {
private:
	XMFLOAT3 direction_;
	int hModel_;

	int camType_;
public:

	Tank(GameObject* parent);
	~Tank() {};

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

