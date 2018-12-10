#pragma once
#ifndef _TEST_SUITE_HPP
#define _TEST_SUITE_HPP

#include <exception>
#include <vector>

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

class unit_test {
  private:
	const char *_name;
	void (*_test)();

  public:
	constexpr const char *name() const { return _name; }
	unit_test(const char *name, void (*test)()) : _name(name), _test(test) {}

	bool operator()(bool verbose) const;
};

typedef std::vector<unit_test> test_set;
struct named_test_set {
	const char *name;
	test_set set;
};
typedef std::vector<named_test_set> run_set;
typedef run_set (*run_set_ptr)();

void evaluate(run_set_ptr tests, bool verbose);

#define DECLARE_TEST_SET(__decl__) \
	inline test_set __tests__() {  \
		test_set __set__;          \
		__decl__;                  \
		return std::move(__set__); \
	}
#define TEST(__test__) __set__.push_back(unit_test(#__test__, __test__))
#define TESTD(__test__, __name__) unit_test(__name__, __test__)

#define DECLARE_RUN_SET(__name__, __decl__) \
	inline run_set __name__() {             \
		run_set __set__;                    \
		__decl__;                           \
		return std::move(__set__);          \
	}
#define RUN(__test_set__) __set__.push_back(named_test_set{#__test_set__, __test_set__::__tests__()})
#define RUND(__test_set__, __name__) __set__.push_back(named_test_set{__name__, __test_set__::__tests__()})

/* Assertion Macros */
#define ASSERT_TRUE(cond, msg) if(!(cond)) throw assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_FALSE(cond, msg) if(cond) throw assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_NULL(ptr, msg) if(ptr != nullptr) throw assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_NON_NULL(ptr, msg) if(ptr == nullptr) throw assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_ZERO(val, msg) if(val != 0) throw assertion_error(__LINE__, __FILE__, msg)
#define ASSERT_NON_ZERO(val, msg) if(val == 0) throw assertion_error(__LINE__, __FILE__, msg)

#endif
