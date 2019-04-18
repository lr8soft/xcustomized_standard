#pragma once
#ifndef _game_timer_
#define _game_timer_
#include "game_timer_fwd.h"
#include<windows.h>
xc_std::game_timer::game_timer() :mSecondPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
mPausedTime(0), mPrevTime(0),mCurrTime(0), mStopped(false)
{
	_int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);//return frequnecy of hardware
	mSecondPerCount = 1.0 / (double)countsPerSec;
}

float xc_std::game_timer::TotalTime() const
{
	if (mStopped) {
		return (float)(((mStopTime - mPausedTime) - mBaseTime)*mSecondPerCount);
	}
	else {
		return (float)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondPerCount);
	}
	return 0.0f;
}

float xc_std::game_timer::DeltaTime() const
{
	return (float)mDeltaTime;
}

void xc_std::game_timer::Reset()
{
	_int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void xc_std::game_timer::Start()
{
	_int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	if (mStopped) {
		mPausedTime += (startTime-mStopTime);
		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void xc_std::game_timer::Stop()
{
	if (!mStopped) {
		_int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mStopTime = currTime;
		mStopped = true;
	}
}

void xc_std::game_timer::Tick()
{
	if (mStopped) {
		mDeltaTime = 0.0;
		return;
	}
	else {
		_int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mCurrTime = currTime;

		mDeltaTime = (mCurrTime - mPrevTime)*mSecondPerCount;
		mPrevTime = mCurrTime;
		if (mDeltaTime<0.0) {
			mDeltaTime = 0.0;
		}	
	}

}
#endif /*game_timer_fwd*/