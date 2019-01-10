#pragma once
#ifndef _BOOKMARKS_HPP
#define _BOOKMARKS_HPP

#include <string>
#include <memory>

struct bookmark_item {
	std::string name;

	bookmark_item() {}
	bookmark_item(const std::string &name) : name(name) {}
	virtual ~bookmark_item() {}
};

struct folder : public bookmark_item {
	std::vector<std::shared_ptr<bookmark_item>> items;
};

struct bookmark : public bookmark_item {
	std::string url;
};

#endif