#include "TankHead.h"
#include "Engine/Model.h"

TankHead::TankHead(GameObject* parent)
	: GameObject(parent, "TankHead")  {
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
}

void TankHead::Update()
{

}

void TankHead::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
