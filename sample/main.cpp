#include <test_suite.hpp>
#include "tests.hpp"

using namespace std;
using namespace cpp_test;

int main(int argc, const char *argv[]) {
	bool verbose = argc > 1 ? string(argv[1]) == "-v" : false;
	evaluate(sample_tests, verbose);

	return EXIT_SUCCESS;
}