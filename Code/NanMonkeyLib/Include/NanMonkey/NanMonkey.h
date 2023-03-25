#pragma once

namespace NanMonkey
{
	void NanAssert(const bool condition, const char* message);

//#define ASSERT(CONDITION, MESSAGE) assert(CONDITION)
//#define MESSAGE(MESSAGE) std::cout << MESSAGE;
//
//
//#define STREAM_POD_WRITE(STREAM, VALUE) STREAM.write((char*)&VALUE,sizeof(VALUE))
//#define STREAM_POD_READ(STREAM, VALUE) STREAM.read((char*)&VALUE,sizeof(VALUE))


}