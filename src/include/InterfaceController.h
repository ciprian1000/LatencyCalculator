#pragma once

#include <functional>
#include <string>
#include <vector>

namespace expertake {
struct MenuItem {
	MenuItem(std::string _description, std::function<void()> _action);
	MenuItem(const MenuItem& item) = delete;
	MenuItem(MenuItem&& item) noexcept;

	std::string description;
	std::function<void()> action;
};

class InterfaceController {
public:
	~InterfaceController() = default;

	void AddMenuItem(MenuItem& item);

	void Reset();

private:
	std::string mDescription;
	std::vector<MenuItem> mMenu;
};

} // expertake
