//
//  Console.cpp
//  File file is part of the "Logger" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Console.hpp"

namespace Logger
{
	namespace Console
	{
		Log * shared_log() {
			static Log log;
			
			return &log;
		}
	}
}
