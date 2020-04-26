#include <iostream>

#include "shm.h"
#include "tools.h"

auto main(int argc, char *argv[]) -> int
{
	if (argc != 5)
	{
		std::cout << "Required: limit interval(us) buffer size buffer count" << std::endl;
		return 1;
	}

	auto limit = std::stoi(argv[1]);
	auto interval = std::stoi(argv[2]);
	auto buffer_size = std::stoi(argv[3]);
	auto buffer_count = std::stoi(argv[4]);

	Shm::remove("test");

	Shm segment(Shm::Option::o_create, "test", buffer_size, buffer_count);

	if (segment.get_status() & Shm::Status::s_error)
	{
		std::cout << "Error: shm create" << std::endl;
		return 1;
	}

	auto result = new char[buffer_size]();

	auto total(0);

	auto counter(0);

	auto data_loss(0);

	auto interval_exceed(0);

	auto last_progress(-1);

	while (counter < limit)
	{
		auto t0 = Clock::now();

		segment.read(Shm::Read::next, result, buffer_size);

		if (segment.get_status() & Shm::Status::s_no_data)
		{
			goto next;
		}

		if (segment.get_status() & Shm::Status::s_data_loss)
		{
			data_loss++;
			goto next;
		}

		if (segment.get_status() & Shm::Status::s_error)
		{
			std::cout << "Error: shm read" << std::endl;
			break;
		}

		counter++;

		{
			int progress = counter * 100 / limit;

			if (progress != last_progress && progress % 10 == 0)
			{
				std::cout << "Progress: " << progress << "%" << std::endl;
				last_progress = progress;
			}
		}

next:
		auto t1 = Clock::now();

		auto sleep_left = interval - duration_cast<microseconds>(t1 - t0).count();

		if (sleep_left <= 0)
		{
			interval_exceed++;
		}
		else
		{
			Tools::usleep(sleep_left);
		}

		total++;
	}

	std::cout << "--------------" << std::endl;
	std::cout << "Test completed" << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << "Read operations: " << counter << " of " << limit << std::endl;
	std::cout << "Reading attempts: " << total << std::endl;
	std::cout << "Data loss: " << data_loss << std::endl;
	std::cout << "Interval exceed: " << interval_exceed << std::endl;

	return 0;
}