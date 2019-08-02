#include "stdafx.h"
#include "Logger.h"

namespace engine
	{
	void Logger::writer()
		{
		while (running)
			{
			std::unique_lock<std::mutex> lock(queue_free);
			while (queue->empty()) { work_available.wait(lock); }

			std::queue<std::string>* tmp = queue;
			queue = new std::queue<std::string>();

			lock.unlock();

			write_all(tmp);
			}
		}
	void Logger::write_all(std::queue<std::string>* queue)
		{
		while (!queue->empty()) { log_file << queue->front() << std::endl; queue->pop(); }
		delete queue;
		}

	void Logger::log(std::string string)
		{
		std::unique_lock<std::mutex> lock(queue_free);

		bool was_empty = queue->empty();
		queue->push(string);

		lock.unlock();

		if (was_empty) { work_available.notify_one(); }
		}

	Logger::Logger()
		{
		log_file.open("log.txt");
		queue = new std::queue<std::string>();
		thread = new std::thread(&Logger::writer, this);
		}

	Logger::~Logger()
		{
		running = false;
		thread->join();
		delete thread;

		write_all(queue);
		delete queue;
		}

	Logger logger;
	}