#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "TankHead.h"
#include "Bullet.h"

namespace {
	XMVECTOR vFront = { 0, 0, 1}; //タンクの前方向
	const float speed = 0.1;
	const float CAM_HEIGHT_BIAS = 0.2f;

	enum CAM_TYPE {
		FIXED, //固定カメラ
		TPS_COM, //三人称
		TPS_CAMROT,  //三人称視点カメラ（回転）
		FPS_CAM, //一人称視点カメラ
		CAM_TYPE_MAX
	};
}

void Tank::SetFixedCam() {
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}

Tank::Tank(GameObject* parent)
	: GameObject(parent, "Tank") {
	camType_ = CAM_TYPE::FIXED;
}

void Tank::Initialize() {
	hModel_ = Model::Load("TankBody.fbx");
	Instantiate<TankHead>(this);
}

void Tank::Update() {

	if (Input::IsKeyDown(DIK_C)) {
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;

		Debug::Log("camType=");
		Debug::Log(camType_, true);
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		auto bullet = Instantiate<Bullet>(this->GetParent());
		bullet->SetPosition(transform_.position_);
	}

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
	

	switch (camType_) {
	case CAM_TYPE::FIXED: {
		SetFixedCam();
		break;
	}
	case CAM_TYPE::TPS_COM: {
		//3人称

		XMFLOAT3 camPos = transform_.position_;
		camPos.y += 10.0f;
		camPos.z -= 8.0f;
		Camera::SetPosition(camPos);

		XMFLOAT3 camTarget = transform_.position_;
		Camera::SetTarget(camTarget);
		break;
	}
	case CAM_TYPE::TPS_CAMROT: {
		XMFLOAT3 camPos;
		XMVECTOR vCam = { 0.0f, 3.0f, -7.0f, 0.0f };
		vCam = XMVector3TransformCoord(vCam, matRot);
		XMStoreFloat3(&camPos, vPos + vCam);
		Camera::SetPosition(camPos);

		XMFLOAT3 camTarget = transform_.position_;
		Camera::SetTarget(camTarget);

		break;
	}
	case CAM_TYPE::FPS_CAM: {
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);

		XMFLOAT3 camTarget = {};
		XMStoreFloat3(&camTarget, vPos + vMove);

		Camera::SetTarget(camTarget);
		break;
	}
	default:
		break;
	}

	if (Input::IsKey(DIK_W)) {
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

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}
