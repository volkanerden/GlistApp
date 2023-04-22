/*
 * FrameTimer.h
 *
 *  Created on: Mar 16, 2023
 *      Author: Volkan
 */

#ifndef SRC_FRAMETIMER_H_
#define SRC_FRAMETIMER_H_

#include <chrono>

class FrameTimer {
public:
	virtual ~FrameTimer();
	FrameTimer();
	float Mark();
private:
	std::chrono::steady_clock::time_point last;
};

#endif /* SRC_FRAMETIMER_H_ */
