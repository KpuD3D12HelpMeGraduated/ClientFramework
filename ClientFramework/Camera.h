#pragma once
#include "Util.h"

class Camera
{
public:
	XMFLOAT4X4 mWorld = Identity4x4(); //���� ��ȯ ���
	XMFLOAT4X4 mView = Identity4x4(); //�� ��ȯ ���
	XMFLOAT4X4 mProj = Identity4x4(); //���� ��ȯ ���

	//���� ��ȯ
	void TransformProjection(WindowInfo windowInfo);
};