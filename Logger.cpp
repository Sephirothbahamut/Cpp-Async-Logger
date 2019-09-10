#include "stdafx.h"
#include "Logger.h"

void Logger::writer()
		{
		while (running)
			{
			std::unique_lock<std::mutex> lock(queue_free);
			work_available.wait(lock);

			queue_write.swap(queue_log);

			lock.unlock();

			write_all();
			}
		}

	void Logger::write_all()
		{
		while (!queue_write.empty()) { log_file << queue_write.front() << std::endl; queue_write.pop(); }
		}

	void Logger::log(std::string string)
		{
		//std::unique_lock<std::mutex> lock(queue_free);

		queue_free.lock();
		queue_log.push(string);

		queue_free.unlock();

		work_available.notify_one();
		}

	Logger::Logger() : Logger("log.txt") {}
	Logger::Logger(std::string fname = "log.txt")
		{
		log_file.open(fname);
		thread = new std::thread(&Logger::writer, this);
		}
	Logger::~Logger()
		{
		log("Logger | Flushing logs after engine end");
		running = false;
		thread->join();
		delete thread;

		queue_write.swap(queue_log);
		write_all();
		log_file.close();
		}