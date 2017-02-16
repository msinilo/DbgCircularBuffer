#include "DbgCircularBuffer.h"

namespace
{
	TEST(DefaultCtorEmpty)
	{
		DbgCircularBuffer<size_t> buf;
		CHECK_EQUAL(0, buf.Size());
	}
	TEST(ResetChangesMaxSize)
	{
		DbgCircularBuffer<size_t> buf(128);
		CHECK_EQUAL(0, buf.Size());
		CHECK_EQUAL(128, buf.MaxSize());
	}
	TEST(AddNoWrap)
	{
		DbgCircularBuffer<size_t> buf;
		buf.Reset(16);
		for (size_t i = 0; i < 16; ++i)
		{
			buf.AddTail() = i;
		}
		for (size_t i = 0; i < 16; ++i)
		{
			CHECK_EQUAL(i, buf[i]);
		}
	}
	TEST(AddWrap)
	{
		static const size_t BSIZE = 10;
		static const size_t NUM_ELEMS = 16;
		DbgCircularBuffer<size_t> buf;
		buf.Reset(BSIZE);
		for (size_t i = 0; i < NUM_ELEMS; ++i)
		{
			buf.AddTail() = i;
		}
		CHECK_EQUAL(BSIZE, buf.Size());
		static const size_t ELEMS_OVERWRITTEN = NUM_ELEMS - BSIZE;
		for (size_t i = 0; i < buf.Size(); ++i)
		{
			CHECK_EQUAL(i + ELEMS_OVERWRITTEN, buf[i]);
		}
	}
}