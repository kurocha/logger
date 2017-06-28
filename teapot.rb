
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.3"

define_project "Logger" do |project|
	project.add_author "Samuel Williams"
	project.license = "MIT License"

	project.version = "1.0.0"
end

define_target "logger" do |target|
	target.build do |environment|
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Logger/**/*.hpp')
		
		build static_library: "Logger", source_files: source_root.glob('Logger/**/*.cpp')
	end
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Library/Time"
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.provides "Library/Logger" do
		append linkflags ->{install_prefix + "lib/libLogger.a"}
	end
end

define_target "logger-tests" do |target|
	target.build do |environment|
		test_root = target.package.path + 'test'
		
		run tests: "Logger", source_files: test_root.glob('Logger/**/*.cpp')
	end
	
	target.depends "Language/C++11", private: true
	
	target.depends "Library/UnitTest"
	target.depends "Library/Logger"
	
	target.provides "Test/Logger"
end

define_configuration "test" do |configuration|
	configuration[:source] = "http://github.com/kurocha/"
	
	configuration.require "platforms"
	configuration.require "build-files"
	
	configuration.require "unit-test"
	configuration.require "time"
	
	configuration.require "language-cpp-class"
end
