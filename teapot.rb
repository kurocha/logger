
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "3.0"

# Project Metadata

define_project "logger" do |project|
	project.title = 'Logger'
	project.summary = 'A brief one line summary of the project.'
	
	project.license = "MIT License"
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = "1.0.0"
end

# Build Targets

define_target 'logger-library' do |target|
	target.depends "Language/C++14"
	
	target.depends "Library/Time", public: true
	
	target.provides "Library/Logger" do
		source_root = target.package.path + 'source'
		
		library_path = build static_library: "Logger", source_files: source_root.glob('Logger/**/*.cpp')
		
		append linkflags library_path
		append header_search_paths source_root
	end
end

define_target "logger-tests" do |target|
	target.depends "Language/C++14"
	
	target.depends "Library/UnitTest"
	target.depends "Library/Logger"
	
	target.provides "Test/Logger" do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: 'Logger', source_files: test_root.glob('Logger/**/*.cpp'), arguments: arguments
	end
end

# Configurations

define_configuration "development" do |configuration|
	configuration[:source] = "http://github.com/kurocha/"
	configuration.import "logger"
	
	configuration.require 'generate-project'
	configuration.require 'generate-travis'
	
	# Provides all the build related infrastructure:
	configuration.require "platforms"
	configuration.require "build-files"
	
	# Provides unit testing infrastructure and generators:
	configuration.require "unit-test"
	
	# Provides some useful C++ generators:
	configuration.require "generate-cpp-class"
end

define_configuration "logger" do |configuration|
	configuration.public!
	
	configuration.require "time"
end
