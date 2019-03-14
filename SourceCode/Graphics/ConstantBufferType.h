#pragma once
#include <DirectXMath.h>

struct CB_VS_vertexshader {
	DirectX::XMMATRIX mat;
	//float xOffset = 0;	//4bytes
	//float yOffset = 0;	//4bytes
};

//8 bytes -> 16 bytes(padding) -> 데이터 정렬 반드시 해야 함. 변수 위치 중요