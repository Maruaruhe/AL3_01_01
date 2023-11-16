#pragma once
#include <stdint.h>
#include "Vec3.h"
#include <variant>
#include <iostream>
#include <map>

struct Item {
	std::variant<int32_t, float, Vector3> value;
};
struct Group {
	std::map<std::string, Item> items;
};


class GlobalVariables {
public:
	static GlobalVariables* GetInstance();

	void CreateGroup(const std::string& groupName);

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;

	std::map<std::string, Group> datas_;
};
