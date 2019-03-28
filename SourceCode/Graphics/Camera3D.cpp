#include "Camera3D.h"

Camera3D::Camera3D() {
	this->pos = XMFLOAT3(0.0f, 0.0f, 1.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	UpdateMatrix();
}

void Camera3D::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ) {
	float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const DirectX::XMMATRIX & Camera3D::GetViewMatrix() const
{
	return this->viewMatrix;
}

const DirectX::XMMATRIX & Camera3D::GetProjectionMatrix() const
{
	return this->projectionMatrix;
}


void Camera3D::UpdateMatrix() //뷰 행렬 업데이트 + 이동 벡터 업데이트
{
	//카메라 회전 행렬 계산
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	//카메라 타겟 벡터 계산 - 카메라 정면 벡터 , 회전 행렬
	XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);
	//카메라 현재 위치에 다른 시점 방향 조정
	camTarget += this->posVector;
	//카메라 현재 각도에 따른 업벡터 조정
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRotationMatrix);
	//뷰 행렬 설정.
	this->viewMatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);

	this->UpdateDirectionVectors();
}
