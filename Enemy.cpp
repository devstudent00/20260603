#include "Enemy.h"
#include "Engine/Model.h"
#include "Ground.h"

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Bullet"), hModel_(-1) {
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	AddCollider(new BoxCollider(transform_.position_, { 1.25f, 3.0f, 1.25f }));
}

void Enemy::Update()
{
	transform_.position_.z += 0.05;

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
	}
}
