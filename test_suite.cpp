#include "test_suite.hpp"
#include <chrono>
#include <cstdio>

using namespace std;
using namespace std::chrono;

inline high_resolution_clock::time_point now() { return high_resolution_clock::now(); }
#define nano2milli(nano) (double)(nano).count() / 1000000.0

bool unit_test::operator()(bool verbose) const {
	try {
		_test();
		return true;
	} catch (assertion_error &ex) {
		if (verbose)
			fprintf(stderr, "\n\tASSERT %s\n", ex.what());
		return false;
	} catch (std::exception &ex) {
		if (verbose)
			fprintf(stderr, "\n\tEXCEPTION: %s\n", ex.what());
		return false;
	}
}

void evaluate(run_set_ptr tests, bool verbose) {
	nanoseconds dur_all;
	for (const named_test_set &test_set : tests()) {
		nanoseconds dur_set;
		printf("\033[33m!Running test set %s\033[0m\n", test_set.name);
		size_t total_tests = test_set.set.size();
		size_t passed_count = 0;
		for (const unit_test &test : test_set.set) {
			auto test_start = now();
			bool passed = test(verbose);
			nanoseconds dur_test = duration_cast<nanoseconds>(now() - test_start);
			dur_set += dur_test;
			if (passed)
				passed_count++;
			printf("\033[%s\033[0m (%lfms) %s\n", passed ? "32mPASSED" : "31mFAILED", nano2milli(dur_test), test.name());
		}
		double duration = nano2milli(dur_set);
		if (passed_count == total_tests) {
			printf("      \033[32m PASSED all %ld tests (%lfms)\033[0m\n", total_tests, duration);
		} else if (passed_count > 0) {
			printf("      \033[33mPARTIAL %ld/%ld tests passed (%lfms)\033[0m\n", passed_count, total_tests, duration);
		} else {
			printf("      \033[31m FAILED all %ld tests (%lfms)\033[0m\n", total_tests, duration);
		}
		dur_all += dur_set;
	}

	printf("final runtime: %lfms\n", nano2milli(dur_all));
}