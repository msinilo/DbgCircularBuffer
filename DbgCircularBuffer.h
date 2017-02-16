#ifndef DBG_CIRCULAR_BUFFER_H
#define DBG_CIRCULAR_BUFFER_H

#include <vector>

#define DBG_CBUFFER_ASSERT
// Requires <cassert>
//#define DBG_CBUFFER_ASSERT	assert

// TContainer needs to provide resize() method and a random access (operator[]).
template<typename T, typename TContainer = std::vector<T> >
class DbgCircularBuffer
{
public:
	explicit DbgCircularBuffer(size_t maxSize = 0)
	:	mMaxSize(maxSize),
		mCount(0),
		mStartIndex(0),
		mWriteIndex(0)
	{
		mItems.resize(maxSize);
	}

	void Reset(size_t maxSize)
	{
		mMaxSize = maxSize;
		mCount = 0;
		mStartIndex = 0;
		mWriteIndex = 0;
		mItems.resize(maxSize);
	}

	const T& operator[](size_t i) const
	{
		DBG_CBUFFER_ASSERT(i < Size());
		const size_t index = WrapIndex(i + mStartIndex);
		return(mItems[index]);
	}

	T& AddTail()
	{
		++mWriteIndex;
		size_t index = WrapIndex(mWriteIndex - 1);
		mWriteIndex = WrapIndex(mWriteIndex);
		if (mCount < mMaxSize)
		{
			++mCount;
		}
		else
		{
			mStartIndex = mWriteIndex;
		}
		return(mItems[index]);
	}
	size_t Size() const { return(mCount); }
	size_t MaxSize() const { return(mMaxSize); }

	DbgCircularBuffer(const DbgCircularBuffer&) = delete;
	DbgCircularBuffer& operator=(const DbgCircularBuffer&) = delete;

private:
	// Same as % mMaxSize, but no division.
	size_t WrapIndex(size_t idx) const
	{
		return(idx >= mMaxSize ? idx - mMaxSize : idx);
	}

	TContainer  	mItems;
	size_t			mMaxSize;
	size_t			mCount;
	size_t			mStartIndex;
	size_t			mWriteIndex;
};

#endif

