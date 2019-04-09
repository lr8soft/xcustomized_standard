#pragma once
#ifndef _GAME_TIMER_
#define _GAME_TIMER_
namespace xc_std {
	class GameTimer
	{
	public:
		GameTimer();
		~GameTimer()=default;

		float TotalTime()const;
		float DeltaTime()const;

		void Reset();
		void Start();
		void Stop();
		void Tick();
	private:
		double mSecondPerCount;
		double mDeltaTime;
	
		_int64 mBaseTime;
		_int64 mPausedTime;
		_int64 mStopTime;
		_int64 mPrevTime;
		_int64 mCurrTime;

		bool mStopped;
	};
}

#endif

