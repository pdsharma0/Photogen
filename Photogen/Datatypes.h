#pragma once

#include <cstring>

#define COMPACT_STRING_SIZE 64

// A 64Byte string
struct CompactString {

	CompactString() {
		std::memset(str, '\0', sizeof(str));
	}

	CompactString(char* src) {
		std::memcpy(str, src, sizeof(str));
	}

	// Overload equality operator
	inline void operator=(const CompactString& src) const {
		memcpy((void*)str, src.str, sizeof(str));
	}

	char str[COMPACT_STRING_SIZE];
};
