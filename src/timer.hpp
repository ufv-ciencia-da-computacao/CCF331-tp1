#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <ostream>
using namespace std;

class Timer {
private:
	clock_t startTime;
	clock_t delta;

public:

	Timer() {
		startTime = 0;
		delta = 0;
	}

	Timer(int min, int sec, int millis) {
		delta = (clock_t) (min*60000 + sec*1000 + millis) * CLOCKS_PER_SEC / 1000;
	}

	void start() {
		startTime = clock();
		delta = 0;
	}

	void stop() {
		delta = clock() - startTime;
	}

	friend ostream& operator<<(ostream &out, const Timer &t) {
		clock_t curr = t.delta * 1000 / CLOCKS_PER_SEC;
		int min = curr / 60000;
		int sec = (curr / 1000) % 60;
		int millis = curr % 1000;

		out << "00:";
		if(min < 10) out << "0";
		out << min << ":";
		if(sec < 10) out << "0";
		out << sec << ".";
		if(millis < 100) out << "0";
		if(millis < 10) out << "0";
		out << millis;

		return out;
	}

	bool operator<=(const Timer &t) {
		clock_t clk = clock() - startTime;
		return clk <= t.delta;
	}

};

#endif