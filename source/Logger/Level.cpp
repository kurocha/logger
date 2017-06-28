//
//  Level.cpp
//  File file is part of the "Logger" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Level.hpp"

namespace Logger
{
	const char * level_name(Level level) noexcept
	{
		switch (level) {
			case Level::ERROR:
				return "ERROR";
			case Level::WARN:
				return "WARN";
			case Level::INFO:
				return "INFO";
			case Level::DEBUG:
				return "DEBUG";
			case Level::ALL:
				return "ALL";
			default:
				return "LOG";
		}
	}
}
