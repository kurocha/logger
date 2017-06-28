//
//  Test.Log.cpp
//  This file is part of the "Logger" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Logger/Log.hpp>

namespace Logger
{
	UnitTest::Suite LogTestSuite {
		"Logger::Log",
		
		{"it can print out messages",
			[](UnitTest::Examiner & examiner) {
				Log log;
				
				log.append(Level::INFO, "The tests appear to be working.");
				examiner.expect(log.last()) == "The tests appear to be working.";
				
				log.append(Level::DEBUG, "Frobulate the log device.");
				examiner.expect(log.last()) == "Frobulate the log device.";
				
				log.append(Level::WARN, "Initializing full disk erasure.");
				examiner.expect(log.last()) == "Initializing full disk erasure.";
				
				log.append(Level::ERROR, "Telephone mainframe interconnect failed!");
				examiner.expect(log.last()) == "Telephone mainframe interconnect failed!";
			}
		},
		
		{"it can enable/disable different levels",
			[](UnitTest::Examiner & examiner) {
				Log log;
				
				log.disable(Level::DEBUG);
				
				// Capture the current last output, if any.
				auto last = log.last();
				
				log.append(Level::DEBUG, "Frobulate the log device.");
				
				examiner << "Last log output shouldn't have changed." << std::endl;
				examiner.expect(log.last()) == last;
			}
		},
	};
}
