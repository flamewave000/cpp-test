#pragma once
#ifndef _TEST_ASSERTION_HPP
#define _TEST_ASSERTION_HPP

#include <exception>

namespace cpp_test {

class assertion_error : public std::exception {
  private:
	const int _line;
	const char *_file;
	const char *_what;

  public:
	assertion_error(int line, const char *file, const char *what) : _line(line), _file(file), _what(what) {}
	virtual ~assertion_error() {}
	virtual const char *what() const _NOEXCEPT { return _what; }
};

/* Assertion Macros */
#define ASSERT_TRUE(cond, msg) \
	if (!(cond))               \
	throw cpp_test::assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_FALSE(cond, msg) \
	if (cond)                   \
	throw cpp_test::assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_NULL(ptr, msg) \
	if (ptr != nullptr)       \
	throw cpp_test::assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_NON_NULL(ptr, msg) \
	if (ptr == nullptr)           \
	throw cpp_test::assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_ZERO(val, msg) \
	if (val != 0)             \
	throw cpp_test::assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_NON_ZERO(val, msg) \
	if (val == 0)                 \
	throw cpp_test::assertion_error(__LINE__, __FILE__, msg)

}

#endif