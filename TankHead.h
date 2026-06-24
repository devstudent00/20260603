#pragma once
#include "Engine//GameObject.h"

class TankHead : public GameObject {
private:
	int hModel_ = -1;
	int point_;
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


	int GetPoint() { return point_; }
	void SetPoint(int point) { point_ = point; }
};

