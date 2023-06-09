#include "TimedCall.h"
TimedCall::TimedCall() {

}

void TimedCall::Update() {

	if (isFinish) {
		return;
	}
	time--;
	if (time <= 0) {
		isFinish = true;
		//callBack

	}
}