#include "InterfaceController.h"

#include "util.h"

#include <iostream>

namespace expertake {

static const char* EMPTY_MENU_DESCRIPTION = "There are no options to choose.";
static const char* WRONG_SELECTION_DESCRIPTION = " is not a valid option.";
static const char* MENU_ITEM_SEPARATOR = ") ";

MenuItem::MenuItem(std::string _description, std::function<void()> _action)
	: description(_description)
	, action(std::move(_action))
{}

MenuItem::MenuItem(MenuItem&& item) noexcept
	: description(std::move(item.description))
	, action(std::move(item.action))
{
	item.description = "";
	item.action = []() {};
}

void InterfaceController::AddMenuItem(MenuItem& item) {
	mMenu.push_back(std::move(item));
}

void InterfaceController::Reset() {
	if (mMenu.empty()) {
		std::cout << EMPTY_MENU_DESCRIPTION << std::endl;
		return;
	}

	bool validOption = false;
	while (!validOption) {
		std::cout << mDescription << std::endl;
		for (int i = 0; i < mMenu.size(); i++) {
			std::cout << i + 1 << MENU_ITEM_SEPARATOR << mMenu[i].description << std::endl;
		}

		std::string selection;
		std::cin >> selection;
		unsigned int itemNum;
		validOption = convert(selection, itemNum);
		itemNum--;
		validOption = validOption && itemNum < mMenu.size();

		if (validOption) {
			mMenu[itemNum].action();
		} else {
			std::cout << selection << WRONG_SELECTION_DESCRIPTION << std::endl;
		}
	}
}

} // expertake
