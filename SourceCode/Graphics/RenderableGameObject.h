#pragma once
#include "GameObject3D.h"

class RenderableGameObject : public GameObject3D {
public:
	bool Initialize(const std::string & filePath, ID3D11Device * device, ID3D11DeviceContext * deviceContex, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader);
	void Draw(const DirectX::XMMATRIX & viewProjectionMatrix);

protected:
	Model model;
	void UpdateMatrix() override;


	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
};