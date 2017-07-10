# Logger

Atomic log operations with TTY colors for readability.

[![Build Status](https://travis-ci.org/kurocha/logger.svg?branch=master)](https://travis-ci.org/kurocha/logger)

## Setup

The build tool `teapot` needs to be installed (which requires [Ruby][2]):

	$ gem install teapot

[2]: http://www.ruby-lang.org/en/downloads/

### Install Dependencies

To fetch project dependencies, run the following:

	$ cd logger
	$ teapot fetch

### Validate Behaviour

The project can be checked by running unit tests:

	$ cd logger
	$ teapot Test/Logger

## Usage

### `Logger::Log`

The main object for logging.

```c++
Logger::Log log;

log.append(Level::DEBUG, "Defragulate the heap!")
```

### `Logger::Console`

Provides a high level static interface to logging.

```
namespace MyProgram
{
	using namespace Logger::Console;
	
	void my_function(int x)
	{
		info("The value is", x);
		// debug, info, warn, error are available and work the same way.
	}
}
```

## Contributing

1. Fork it.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.

## License

Released under the MIT license.

Copyright, 2017, by [Samuel G. D. Williams](http://www.codeotaku.com/samuel-williams).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
