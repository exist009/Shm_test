#pragma once

#include <iostream>

#include <chrono>
#include <sched.h>

using std::chrono::microseconds;
using std::chrono::duration_cast;

typedef std::chrono::high_resolution_clock Clock;

namespace Tools
{
	void usleep(int us)
	{
		struct timespec t;
		t.tv_sec = us / 1000000;
		t.tv_nsec = (us % 1000000) * 1000;
		clock_nanosleep(CLOCK_MONOTONIC, 0, &t, NULL);
	}

	namespace Data
	{
		bool check(char *data, size_t size, int counter)
		{
			if (counter != *(int *)data)
			{
				return false;
			}

			counter %= 127;

			for (size_t i = sizeof(counter); i < size; i++)
			{
				if (i & 1)
				{
					if (data[i] != (char)counter) return false;
				}
				else
				{
					if (data[i] != (char)(127 - counter)) return false;
				}
			}

			return true;
		}

		void fill(char *data, size_t size, int counter)
		{
			*(int *)data = counter;

			counter %= 127;

			for (auto i = sizeof(counter); i < size; i++)
			{
				if (i & 1)
				{
					data[i] = counter;
				}
				else
				{
					data[i] = 127 - counter;
				}
			}
		}
	}
}


