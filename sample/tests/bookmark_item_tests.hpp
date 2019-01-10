#pragma once

#ifndef _BOOKMARK_ITEM_TESTS_HPP
#define _BOOKMARK_ITEM_TESTS_HPP

#include <test_suite.hpp>
#include "../bookmarks.hpp"

namespace bookmark_item_tests {
	void create_with_name() {
		const char *name = "TEST NAME";
		bookmark_item item(name);
		ASSERT_TRUE(item.name == name, "bookmark_item stored name incorrectly");
	}

	DECLARE_TEST_SET({
		TEST(create_with_name);
	});
}


#endif