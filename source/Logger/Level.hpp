//
//  Level.hpp
//  File file is part of the "Logger" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <type_traits>

namespace Logger
{
	enum class Level : unsigned {
		ERROR = 1,
		WARN = 2,
		INFO = 4,
		DEBUG = 8,
		
		ALL = (1 | 2 | 4 | 8)
	};
	
	inline Level operator|(Level lhs, Level rhs)
	{
		using T = std::underlying_type<Level>::type;
		
		return static_cast<Level>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}
	
	inline Level& operator|=(Level & lhs, Level rhs)
	{
		using T = std::underlying_type<Level>::type;
		
		lhs = static_cast<Level>(static_cast<T>(lhs) | static_cast<T>(rhs));
		
		return lhs;
	}
	
	inline bool operator&(Level lhs, Level rhs)
	{
		using T = std::underlying_type<Level>::type;
		
		return (static_cast<T>(lhs) & static_cast<T>(rhs)) != 0;
	}
	
	inline Level& operator&=(Level & lhs, Level rhs)
	{
		using T = std::underlying_type<Level>::type;
		
		lhs = static_cast<Level>(static_cast<T>(lhs) & static_cast<T>(rhs));
		
		return lhs;
	}
	
	inline Level operator~(Level rhs)
	{
		using T = std::underlying_type<Level>::type;
		
		return static_cast<Level>(~static_cast<T>(rhs));
	}
	
	const char * level_name(Level level) noexcept;
}
