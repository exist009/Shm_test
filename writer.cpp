#include <iostream>

#include "shm.h"
#include "tools.h"

auto main(int argc, char *argv[]) -> int
{
	if (argc != 2)
	{
		std::cout << "Required: Interval required(us)" << std::endl;
		return 1;
	}

	auto interval = std::stoi(argv[1]);

	Shm segment(Shm::Option::o_open, "test");

	if (segment.get_status() & Shm::Status::s_error)
	{
		std::cout << "Error: shm open" << std::endl;
		return 1;
	}

	auto size = segment.get_buffer_size();

	auto data = new char[size]();

	auto counter(0);

	while (true)
	{
		auto t0 = Clock::now();

		Tools::Data::fill(data, size, counter);

		segment.write(data, size);

		auto t1 = Clock::now();

		auto sleep_left = interval - duration_cast<microseconds>(t1 - t0).count();

		counter++;

		if (sleep_left <= 0)
		{
			std::cout << "Warning: interval exceeded" << std::endl;
		}
		else
		{
			Tools::usleep(sleep_left);
		}
	}

	return 0;
}