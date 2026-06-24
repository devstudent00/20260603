#include "TankHead.h"
#include "Engine/Model.h"
#include <dinput.h>
#include "Engine/Input.h"
#include "Bullet.h"

TankHead::TankHead(GameObject* parent)
	: GameObject(parent, "TankHead")  {
	point_ = 0;
}

void TankHead::Initialize() {
	hModel_ = Model::Load("TankHead.fbx");
}

void TankHead::Update() {
	if (Input::IsKey(DIK_LEFT)) {
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.rotate_.y += 1.0f;
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		const float spped = 0.2f;

		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");

		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);

		XMVECTOR vMove = XMVector3Normalize(XMVectorSubtract(vTop, vRoot));
		vMove = spped * vMove;
		XMFLOAT3 movePos = {};
		XMStoreFloat3(&movePos, vMove);

		//
		auto bullet = Instantiate<Bullet>(this->GetParent()->GetParent());
		bullet->SetPosition(cannonTop);
		bullet->SetMoveVector(movePos);
		bullet->SetFrom(this);

		//bullet->SetPosition(bulletPos);
		//bullet->SetRotate(transform_.rotate_);
	}
}

void TankHead::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
