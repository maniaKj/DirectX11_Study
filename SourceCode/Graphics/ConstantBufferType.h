#pragma once
#include <DirectXMath.h>

struct CB_VS_vertexshader {
	DirectX::XMMATRIX wvpMatrix;
	DirectX::XMMATRIX worldMatrix;
	//float xOffset = 0;	//4bytes
	//float yOffset = 0;	//4bytes
};

struct CB_VS_vertexshader_2d {
	DirectX::XMMATRIX wvpMatrix;
};

//8 bytes -> 16 bytes(padding) -> 데이터 정렬 반드시 해야 함. 변수 위치 중요

struct CB_PS_light {
	DirectX::XMFLOAT3 ambientLightColor;
	float ambientLightStrength;
	//여기까지 16바이트

	DirectX::XMFLOAT3 dynamicLightColor;
	float dynamicLightStrength;
	//여기까지 또 16 바이트

	DirectX::XMFLOAT3 dynamicLightPosition;
	
	float dynamicLightAttenuation_a;
	float dynamicLightAttenuation_b;
	float dynamicLightAttenuation_c;
};