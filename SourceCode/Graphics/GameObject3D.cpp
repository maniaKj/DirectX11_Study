#include "GameObject3D.h"

void GameObject3D::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	//lookatpos 와 cam pos가 동일한지 확인. 이 둘을 같을 수가 없음.
	if (lookAtPos.x == pos.x && lookAtPos.y == pos.y && lookAtPos.z == pos.z)
		return;

	lookAtPos.x = pos.x - lookAtPos.x;
	lookAtPos.y = pos.y - lookAtPos.y;
	lookAtPos.z = pos.z - lookAtPos.z;

	//pitch 각도 구하기
	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f) {
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f) {
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0) yaw += XM_PI;

	this->SetRotation(pitch, yaw, 0.0f);
}

void GameObject3D::UpdateMatrix()
{
	assert("UpdateMatrix ust be override" && 0);
}

void GameObject3D::UpdateDirectionVectors() {
	DirectX::XMMATRIX vecRotationMatirx = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, 0.0f);
	this->vec_forward = DirectX::XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatirx);
	this->vec_backward = DirectX::XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatirx);
	this->vec_left = DirectX::XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatirx);
	this->vec_right = DirectX::XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatirx);

	DirectX::XMMATRIX vecRotationMatirxNoY = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward_noY = DirectX::XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatirxNoY);
	this->vec_backward_noY = DirectX::XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatirxNoY);
	this->vec_left_noY = DirectX::XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatirxNoY);
	this->vec_right_noY = DirectX::XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatirxNoY);
}

const XMVECTOR & GameObject3D::GetForwardVector(bool omitY)
{
	if (omitY) return vec_forward_noY;
	return vec_forward;
}

const XMVECTOR & GameObject3D::GetRightVector(bool omitY)
{
	if (omitY) return vec_right_noY;
	return vec_right;
}

const XMVECTOR & GameObject3D::GetLeftVector(bool omitY)
{
	if (omitY) return vec_left_noY;
	return vec_left;
}

const XMVECTOR & GameObject3D::GetBackwardVector(bool omitY)
{
	if (omitY) return vec_backward_noY;
	return vec_backward;
}