# CppAssert
Better assert() function for C++ (instead assert() from `<cassert>`)



## Usage
```C++
#include "cpp_assert.hpp"
```

### Default handler and output stream
Syntax:
```C++
ASSERT_DEFAULT(<bool expression>);
```

Example:
```C++
ASSERT_DEFAULT(1 == 1); // Pass
ASSERT_DEFAULT(1 > 2); // Assertion failed! Call default handler and write to std::cerr
ASSERT_DEFAULT((10 + 20 * 3) < 50); // Assertion failed!

std::string str = "Hello";
ASSERT_DEFAULT(str != "hello"); // Pass
```

### Custom handler and output stream
#### Handler?
_Handler is a function, functional object or overloaded operator ()_ \
_Handler calls when assertion is failed and should have the following signature:_
```C++
void (const char*, int, const char*, const char*, std::ostream&);
```
_Where:_
* _1st argument - current filename_
* _2nd argument - current line (position) in file_
* _3rd argument - current function name (with signature)_
* _4th argument - current expression_
* _5th argument - output stream_

#### Output stream?
_Output stream is a stream where handler will write some information about the failed assertion_ \
_Output stream should be derived from the `std::ostream`_

Syntax:
```C++
ASSERT_CUSTOM(<bool expression>, <handler>, <output stream>);
```

Example:
```C++
std::ofstream out_file_stream{...};

auto handler = [](const char* filename, int line, const char* func_name, const char* expr)
{ /* Some implementation ... */ };

ASSERT_CUSTOM(1 == 1, handler, std::cout); // Pass
ASSERT_CUSTOM(1 > 100, handler, out_file_stream); // Assertion failed! Call custom handler and write to out_file_stream


struct Handler
{
    void operator()(const char* filename, int line, const char* func_name, const char* expr)
    { /* Some implementation ... */ }
};

ASSERT_CUSTOM((5 + 5) > 10, Handler(), std::cout); // Assertion failed! Call custom handler and write to std::cout
```
