#pragma once

#include "stdafx.h"
#include <chrono>
#include <string>
#include <iostream>


class ExecutionTimer
{
public:
	using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock,
		std::chrono::steady_clock>;
	ExecutionTimer(string id) {
		strID = id;
	}
	~ExecutionTimer()
	{
		now();
	}
	void now() {
		string msg;
		msg = strID
			+ "\t Elapsed : "
			+ to_string(std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start).count())
			+ "\n";
		CString str(msg.c_str());
		TRACE(str);
	}

private:
	Clock::time_point start = Clock::now();
	string strID;
};