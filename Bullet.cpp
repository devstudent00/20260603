#include "Bullet.h"
#include "Engine/Model.h"

Bullet::Bullet(GameObject* parent)
	: GameObject(parent, "Bullet") {
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
}

void Bullet::Update()
{
	transform_.position_.z += 1.0f;
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
