#include "Input.h"

void Input::Init()
{
	_states.resize(255);
}

void Input::InputKey(Obj& player, shared_ptr<Timer> timerPtr)
{
	HWND hwnd = GetActiveWindow();

	for (UINT key = 0; key < 255; key++)
	{
		if (GetAsyncKeyState(key) & 0x8000)
		{
			if (_states[key] == 1 || _states[key] == 2)
				_states[key] = 1;
			else
				_states[key] = 2;
		}
		else
		{
			int& state = _states[key];

			if (_states[key] == 1 || _states[key] == 2)
				_states[key] = 3;
			else
				_states[key] = 0;
		}
	}

	if (_states['W'] == 1)
	{
		player.transform.x += 5.0f * timerPtr->_deltaTime * cosf(XM_PI / 2.0f);
		player.transform.z += 5.0f * timerPtr->_deltaTime * sinf(XM_PI / 2.0f);
	}
	else if (_states['S'] == 1)
	{
		player.transform.x -= 5.0f * timerPtr->_deltaTime * cosf(XM_PI / 2.0f);
		player.transform.z -= 5.0f * timerPtr->_deltaTime * sinf(XM_PI / 2.0f);
	}
	else if (_states['A'] == 1)
	{
		player.transform.x -= 5.0f * timerPtr->_deltaTime * cosf(0.0f);
		player.transform.z -= 5.0f * timerPtr->_deltaTime * sinf(0.0f);
	}
	else if (_states['D'] == 1)
	{
		player.transform.x += 5.0f * timerPtr->_deltaTime * cosf(0.0f);
		player.transform.z += 5.0f * timerPtr->_deltaTime * sinf(0.0f);
	}
}