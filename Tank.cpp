#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Engine/Camera.h"

namespace {
	XMVECTOR vFront = { 0, 0, 1}; //タンクの前方向
	const float speed = 0.1;

	enum CAM_TYPE {
		FIXED, //固定カメラ
		TPS_COM, //三人称
		TPS_CAMROT,  //三人称視点カメラ（回転）
		FPS_CAM, //一人称視点カメラ
		CAM_TYPE_MAX
	};
}

Tank::Tank(GameObject* parent)
	: GameObject(parent, "Tank") {
	direction_ = {};
	direction_.z = 1.0f;
	camType_ = CAM_TYPE::FIXED;
}

void Tank::Initialize() {
	hModel_ = Model::Load("TankBody.fbx");
}

void Tank::Update() {

	if (Input::IsKeyDown(DIK_C)) {
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;

		Debug::Log("camType=");
		Debug::Log(camType_, true);
	}

	switch (camType_) {
	case CAM_TYPE::FIXED: {
		Camera::SetTarget(transform_.position_);
		Camera::SetPosition(XMFLOAT3(0, 20, -30));
		break;
	}
	case CAM_TYPE::FPS_CAM: {
		break;
	}
	case CAM_TYPE::TPS_CAMROT: {
		break;
	}
	case CAM_TYPE::TPS_COM: {
		Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z));

		auto pos = XMFLOAT3{ 0, 20, -10 };
		auto pos1 = transform_.position_;
		pos1.x -= pos.x;
		pos1.y -= pos.y;
		pos1.z -= pos.z;

		Camera::SetPosition(pos);
		break;
	}
	default:
		break;
	}

	if (Input::IsKey(DIK_W)) {
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
		
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
		vPos = vPos + speed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	if (Input::IsKey(DIK_S)) {
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
		vPos = vPos - speed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);
	}
	if (Input::IsKey(DIK_A)) {
		// transform_.position_.x -= 0.1;
		transform_.rotate_.y -= 1;

	}
	if (Input::IsKey(DIK_D)) {
		// transform_.position_.x += 0.1;
		transform_.rotate_.y += 1;
	}

	//Debug::Log("yAngle=");
	//Debug::Log(transform_.rotate_.y, true);

	direction_.x = cos(transform_.rotate_.y);
	direction_.z = sin(transform_.rotate_.y);

	Ground* ground = (Ground*)FindObject("Ground");
	RayCastData data = {};
	data.start = transform_.position_;
	data.start.y = 0.0f;
	data.dir = { 0, -1, 1 };
	Model::RayCast(ground->GetModelHandle(), &data);
	if (data.hit) {
		transform_.position_.y = -data.dist;
	}
	else {
		
	}
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
