#ifndef UTILS_H
#define UTILS_H

#ifdef BOOST
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/asio.hpp>
#endif
#include <vector>
#include <string>
#include <memory>
#include <cassert>

#ifdef __APPLE__
#include <sys/types.h>
#endif

#ifdef _WIN32
#ifdef DLL_EXPORT
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif
#endif
#ifndef _WIN32
#define LIBRARY_API
#endif

namespace utils
{
#ifdef BOOST
std::string encode64(const std::vector<uint8_t> &val);
std::string encode64(const uint8_t *buffer, uint len);
#endif

std::vector<uint8_t> decode64(const std::string &val);

std::string hex(uint8_t *buffer, uint32_t length);

std::vector<uint8_t> from_hex(std::string str);

std::string replace(const std::string &str, const std::string &from, const std::string &to);

template <typename... Args>
std::string format(const std::string &format, Args... args)
{
    size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
} // namespace utils

#define CHECK_WALLY_RET(r) \
    if (r != WALLY_OK)     \
        throw runtime_error(utils::format("wally function returns error code %d, at %s(%d), in function '%s'", r, __FILE__, __LINE__, __func__));

#define THROW_ERROR(x) throw runtime_error(utils::format("%s, %s : %d in %s", x, __func__, __LINE__, __FILE__));



#endif
