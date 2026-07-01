#include "Enemy.h"
#include "Engine/Model.h"
#include "Ground.h"
#include <random>
#include "Bullet.h"
#include "TankHead.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1) {
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("enemy3.fbx");
	assert(hModel_ > 0);
	Model::SetAnimFrame(hModel_, 1, 100, 2.0f);

	AddCollider(new BoxCollider(transform_.position_, { 1.25f, 3.0f, 1.25f }));
}

void Enemy::Update()
{
	transform_.position_.x += velocity_.x;
	transform_.position_.z += velocity_.z;

	if (transform_.position_.x > 20 || transform_.position_.x < -20 ||
		transform_.position_.z > 20 || transform_.position_.z < -20) {

	}

	Ground* ground = (Ground*)FindObject("Ground");
	RayCastData data = {};
	data.start = transform_.position_;
	data.start.y = 0.0f;
	data.dir = { 0, -1, 0 };
	Model::RayCast(ground->GetModelHandle(), &data);
	if (data.hit) {
		transform_.position_.y = -data.dist;
	}
	else {

	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget) {
	if (pTarget->GetObjectName() == "Bullet") {
		KillMe();
		TankHead* obj = dynamic_cast<TankHead*>(((Bullet*)pTarget)->GetFrom());
		if (obj == nullptr) return;
		obj->SetPoint(obj->GetPoint() + 1);
	}
}
