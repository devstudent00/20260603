#include "Bullet.h"
#include "Engine/Model.h"
#include "Ground.h"

Bullet::Bullet(GameObject* parent)
	: GameObject(parent, "Bullet"), hModel_(-1) {
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	move_ = {0, 0, 0};

	AddCollider(new SphereCollider(transform_.position_, 0.25f));
}

void Bullet::Update() {
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vMove = XMLoadFloat3(&move_);
	vPos = vPos + vMove;

	move_.y -= 0.005f;
	XMStoreFloat3(&transform_.position_, vPos);

	Ground* ground = (Ground*)FindObject("Ground");
	RayCastData data = {};
	data.start = transform_.position_;
	data.dir = { 0, 0, -1 };
	Model::RayCast(ground->GetModelHandle(), &data);
	if (data.hit) {
		KillMe();
	}
	else {

	}

	if (transform_.position_.z > 50 || transform_.position_.z < -50 ||
		transform_.position_.x > 50 || transform_.position_.x < -50) {
		KillMe();
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
