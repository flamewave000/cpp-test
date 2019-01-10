#pragma once

#ifndef _TESTS_HPP
#define _TESTS_HPP

#include <test_suite.hpp>
#include "tests/bookmark_item_tests.hpp"

DECLARE_RUN_SET(sample_tests, {
	RUN(bookmark_item_tests);
})

#endif