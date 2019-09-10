#pragma once

#include <fstream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>

class Logger
		{
		private:
			std::ofstream log_file;

			std::queue<std::string> queue_log;
			std::queue<std::string> queue_write;
			std::thread thread;

			std::condition_variable work_available;
			std::mutex queue_free;
			std::atomic<bool> running = true;

			void writer();
			void write_all();

		public:
			void log(std::string string);
			Logger();
			Logger(std::string fname);
			~Logger();
		};