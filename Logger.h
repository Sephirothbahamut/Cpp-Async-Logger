#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>

namespace engine 
	{
	class Logger
		{
		private:
			std::queue<std::string>* queue;
			std::ofstream log_file;
			std::thread* thread = nullptr;

			std::condition_variable work_available;
			std::mutex queue_free;
			bool running = true;

			void writer();
			void write_all(std::queue<std::string>* queue);

		public:
			void log(std::string string);
			Logger();
			~Logger();
		};
	}
