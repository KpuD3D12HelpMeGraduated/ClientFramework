#pragma once
#include "Util.h"
#include "Timer.h"

class Input
{
public:
	vector<int> _states;

	//���� ������ �ʱ�ȭ
	void Init();

	//Ű �Է�
	void InputKey(Obj& player, shared_ptr<Timer> timerPtr);
};