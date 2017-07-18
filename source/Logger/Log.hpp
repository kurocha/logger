//
//  Log.hpp
//  File file is part of the "Logging" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Level.hpp"

#include <sstream>
#include <Time/Timer.hpp>

#include <unordered_map>
#include <thread>
#include <mutex>

namespace Logger
{
	typedef int FileDescriptor;
	typedef std::stringstream Message;
	
	static const std::string EOL = "\n";
	
	class Log
	{
		std::mutex _lock;
		Time::Timer _timer;
		
		Level _level = Level::ALL;
		FileDescriptor _output;
		
		typedef std::unordered_map<std::thread::id, std::string> ThreadNamesT;
		ThreadNamesT _thread_names;
		
		bool is_tty() const;
		
		std::string header(Level level);
		
		/// Print out a logging header
		void start_session();
		
		std::string thread_name() const;
		
		std::string _last;
		
	public:
		Log();
		virtual ~Log();
		
		void append(Level level, const std::string & string);
		
		const std::string & last();
		
		void set_thread_name(std::string name);
		
		template <typename... TailT>
		void print(Level level, TailT... tail)
		{
			if (level & _level) {
				Message buffer;
				
				write(buffer, tail...);
				
				append(level, buffer.str());
			}
		}
		
		void enable(Level level);
		void disable(Level level);
		
	protected:
		template <typename HeadT, typename... TailT>
		static void write(Message & output, HeadT head, TailT... tail)
		{
			output << head << ' ';
			
			write(output, tail...);
		}
		
		template <typename HeadT, typename TailT>
		static void write(Message & output, HeadT head, TailT tail)
		{
			output << head << ' ' << tail;
		}
		
		template <typename HeadT>
		static void write(Message & output, HeadT head)
		{
			output << head;
		}
	};
}
