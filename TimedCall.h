#pragma once
#include <functional>

class TimedCall {
public:

	TimedCall(std::function<void(void)> f,uint32_t time);

	void Update();

	bool IsFinished() { return isFinish_; }

private:
	std::function<void(void)> f_;

	uint32_t time_;

	bool isFinish_ = false;
};
