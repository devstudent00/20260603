#include "Enemy.h"
#include "Engine/Model.h"
#include "Ground.h"
#include <random>

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

	std::random_device rd;
	std::mt19937 gen(rd());

	float min = -0.25f;
	float max = 0.25f;
	std::uniform_real_distribution<float> dis(min, max);

	float x = dis(gen);
	float z = dis(gen);
	velocity_ = {x, 0, z};
}

void Enemy::Update()
{
	transform_.position_.x += velocity_.x;
	transform_.position_.z += velocity_.z;

	Ground* ground = (Ground*)FindObject("Ground");
	RayCastData data = {};
	data.start = transform_.position_;
	data.start.y = 0.0f;
	data.dir = { 0, -1, 0 };
	Model::RayCast(ground->GetModelHandle(), &data);
	if (data.hit) {

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
