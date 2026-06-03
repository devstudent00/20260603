#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

Tank::Tank(GameObject* parent)
	: GameObject(parent, "Tank") {
	direction_ = {};
	direction_.z = 1.0f;
}

void Tank::Initialize() {
	hModel_ = Model::Load("TankBody.fbx");
}

void Tank::Update()
{
	if (Input::IsKey(DIK_W)) {
		transform_.position_.x += direction_.x / 2;
		transform_.position_.z += direction_.z / 2;
	}
	if (Input::IsKey(DIK_S)) {
		transform_.position_.x -= direction_.x / 2;
		transform_.position_.z -= direction_.z / 2;
	}
	if (Input::IsKey(DIK_A)) {
		// transform_.position_.x -= 0.1;
		transform_.rotate_.y -= 1;

	}
	if (Input::IsKey(DIK_D)) {
		// transform_.position_.x += 0.1;
		transform_.rotate_.y += 1;
	}

	direction_.x = cos(transform_.rotate_.y);
	direction_.z = sin(transform_.rotate_.y);
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
