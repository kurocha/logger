//
//  Console.hpp
//  File file is part of the "Logger" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Log.hpp"

namespace Logger
{
	namespace Console
	{
		Log * shared_log();

		template <typename... TailT>
		void error(TailT... tail)
		{
			shared_log()->print(Level::ERROR, tail...);
		}

		template <typename... TailT>
		void warn(TailT... tail)
		{
			shared_log()->print(Level::WARN, tail...);
		}

		template <typename... TailT>
		void info(TailT... tail)
		{
			shared_log()->print(Level::INFO, tail...);
		}
		
		template <typename... TailT>
		void debug(TailT... tail)
		{
			shared_log()->print(Level::DEBUG, tail...);
		}
	}
}
