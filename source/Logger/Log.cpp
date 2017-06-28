//
//  Log.cpp
//  File file is part of the "Logging" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Log.hpp"

#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

#include <iomanip>

#include <system_error>
#include <errno.h>

namespace Logger
{
	Log::Log()
	{
		_output = ::dup(STDERR_FILENO);
		
		if (_output == -1) {
			throw std::system_error(errno, std::generic_category(), "dup(STDERR_FILENO)");
		}
		
		_timer.reset();

		start_session();
	}

	Log::~Log()
	{
		::close(_output);
	}
	
	bool Log::is_tty() const
	{
		return isatty(_output);
	}
	
	void Log::start_session()
	{
		// Print out the current time
		time_t clock_time;
		time(&clock_time);

		struct tm current_local_time;
		localtime_r(&clock_time, &current_local_time);

		const std::size_t MAX_LENGTH = 1024;
		char date_buffer[MAX_LENGTH];
		strftime(date_buffer, MAX_LENGTH, "%c", &current_local_time);

		Message message;
		message << "Session started at " << date_buffer;
		append(Level::INFO, message.str());
	}

	std::string Log::header(Level level) {
		Message message;
		
		// Xterm colors for better readability on TTY:
		if (is_tty()) {
			if (level == Level::ERROR) {
				message << "\033[" << 31 << 'm';
			} else if (level == Level::WARN) {
				message << "\033[" << 33 << 'm';
			} else if (level == Level::DEBUG) {
				message << "\033[" << 36 << 'm';
			}
		}
		
		message << "[T+" << std::fixed << std::left
			<< std::setfill(' ') << std::setw(5) << std::setprecision(3) << _timer.time() << " "
			<< std::setw(6) << thread_name() << " "
			<< std::setw(5) << std::right << level_name(level) << "] ";
		
		// Restore defaults.
		message << "\033[0m";
		
		return message.str();
	}

	void Log::append(Level level, const std::string & string)
	{
		if (level & _level) {
			std::lock_guard<std::mutex> lock(_lock);
			
			_last = string;
			
			auto prefix = header(level);
			
			struct iovec iov[3];
			iov[0].iov_base = const_cast<char *>(prefix.data());
			iov[0].iov_len = prefix.size();
			iov[1].iov_base = const_cast<char *>(string.data());
			iov[1].iov_len = string.size();
			iov[2].iov_base = const_cast<char *>(EOL.data());
			iov[2].iov_len = EOL.size();
			
			::writev(_output, iov, 3);
		}
	}

	const std::string & Log::last()
	{
		std::lock_guard<std::mutex> lock(_lock);
		
		return _last;
	}

	void Log::enable(Level level)
	{
		_level |= level;
	}
	
	void Log::disable(Level level)
	{
		_level &= ~level;
	}

	void Log::set_thread_name(std::string name)
	{
		std::lock_guard<std::mutex> lock(_lock);
		
		_thread_names[std::this_thread::get_id()] = name;
	}

	// The logger state must be locked before calling this function:
	std::string Log::thread_name() const
	{
		auto thread_id = std::this_thread::get_id();
		auto i = _thread_names.find(thread_id);

		if (i != _thread_names.end()) {
			return i->second;
		} else {
			return "";
		}
	}
}
