#pragma once
#include "Engine//GameObject.h"
class Bullet : public GameObject {
private:
	int hModel_;
	XMFLOAT3 move_;  //弾の進行方向
	GameObject* fromBullet;
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

	void SetMoveVector(const XMFLOAT3& move) { move_ = move; }

	GameObject* GetFrom() { return fromBullet; }
	void SetFrom(GameObject* obj) { fromBullet = obj; }
};

