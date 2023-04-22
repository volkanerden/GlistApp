/*
 * FrameTimer.cpp
 *
 *  Created on: Mar 16, 2023
 *      Author: Volkan
 */

#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer() {

}

FrameTimer::~FrameTimer() {
	last = steady_clock::now();
}
float FrameTimer::Mark(){
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

