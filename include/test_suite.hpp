#pragma once
#ifndef _TEST_SUITE_HPP
#define _TEST_SUITE_HPP

#include <test_assertion.hpp>
#include <vector>

namespace cpp_test {

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

#define DECLARE_TEST_SET(__decl__)          \
	inline cpp_test::test_set __tests__() { \
		cpp_test::test_set __set__;         \
		__decl__;                           \
		return std::move(__set__);          \
	}
#define TEST(__test__) __set__.push_back(cpp_test::unit_test(#__test__, __test__))
#define TESTD(__test__, __name__) cpp_test::unit_test(__name__, __test__)

#define DECLARE_RUN_SET(__name__, __decl__) \
	inline cpp_test::run_set __name__() {   \
		cpp_test::run_set __set__;          \
		__decl__;                           \
		return std::move(__set__);          \
	}
#define RUN(__test_set__) __set__.push_back(cpp_test::named_test_set{#__test_set__, __test_set__::__tests__()})
#define RUND(__test_set__, __name__) __set__.push_back(cpp_test::named_test_set{__name__, __test_set__::__tests__()})

} // namespace cpp_test
#endif
