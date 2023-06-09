#pragma once
#include <functional>

class TimedCall {
public:

	TimedCall();

	void Update();

	bool IsFinished() { return isFinish; }

private:

	uint32_t time;

	bool isFinish = false;
};
