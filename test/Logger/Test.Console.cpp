//
//  Test.Console.cpp
//  This file is part of the "Logger" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Logger/Console.hpp>

namespace Logger
{
	UnitTest::Suite ConsoleTestSuite {
		"Logger::Console",
		
		{"it should have shared log",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(Console::shared_log()) != nullptr;
			}
		},
		
		{"it can write log messages",
			[](UnitTest::Examiner & examiner) {
				int x = 10;
				
				Console::info("The value is", x);
				examiner.expect(Console::shared_log()->last()) == "The value is 10";
			}
		},
	};
}
