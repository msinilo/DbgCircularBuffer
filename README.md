# DbgCircularBuffer
Simple circular buffer class (C++), mostly for diagnostics

Usage:  
```
DbgCircularBuffer<size_t> buf(10);  
for (size_t i = 0; i < 16; ++i)  
{  
  buf.AddTail() = i;  
}  
CHECK_EQUAL(10, buf.Size());  
for (size_t i = 0; i < buf.Size(); ++i)  
{  
  printf("%d\n", buf[i]);  
}  
```
Prints numbers from 6-15 (inclusive). First 6 elements (0-5) have been overwritten (our buffer is FIFO, can hold up to 10 *most recent* elements).
