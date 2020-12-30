#include <iostream> // std::cerr
#include <type_traits> // std::enable_if_t<>, std::is_invocable_r_v<>
#include <exception> // std::terminate()

#ifndef CPP_ASSERT_HPP
#define CPP_ASSERT_HPP

namespace alex
{
namespace assert
{
using Handler = void(*)(const char*, int, const char*, const char*, std::ostream&);

void __default_assertion_handler(const char* filename, int line, const char* function, const char* expression, std::ostream& out) noexcept
{
    out << "### In file: " << filename << "\n"
        << "### On line: " << line << "\n"
        << "### In function: " << function << "\n"
        << "### Assertion failed: '" << expression << "'\n";
}



template<bool expression, typename Handler,
         typename = std::enable_if_t<
             std::is_invocable_r_v<void, Handler, const char*, int, const char*, const char*, std::ostream&>
             >
>
constexpr void __assert_base(const char* filename, int line, Handler&& handler) noexcept
{
    if constexpr (!expression)
    {
        handler(filename, line);
        std::terminate();
    }
}
} // namespace assert
} // namespace alex



#define ASSERT_DEFAULT(expression)  \
    alex::assert::__assert_base<static_cast<bool>(expression)>(__FILE_NAME__, __LINE__, \
                                                                std::bind(alex::assert::__default_assertion_handler, std::placeholders::_1, std::placeholders::_2, __PRETTY_FUNCTION__, #expression, std::ref(std::cerr)))

#define ASSERT_CUSTOM(expression, handler, stream)  \
    alex::assert::__assert_base<static_cast<bool>(expression)>(__FILE_NAME__, __LINE__, \
                                                                std::bind(handler, std::placeholders::_1, std::placeholders::_2, __PRETTY_FUNCTION__, #expression, std::ref(stream)))

#endif // CPP_ASSERT_HPP
