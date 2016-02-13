#include "../inc/gpioaccess_if.h"
#include <vector>

GPIOAccessIf::GPIOAccessIf() {

}

GPIOAccessIf::~GPIOAccessIf() {

}

int GPIOAccessIf::boardToBcm(const unsigned int portNo) {
	switch (portNo) {
	case 3:
		return 2;
	case 5:
		return 3;
	case 7:
		return 4;
	case 8:
		return 14;
	case 10:
		return 15;
	case 11:
		return 17;
	case 12:
		return 18;
	case 13:
		return 27;
	case 16:
		return 23;
	case 18:
		return 24;
	case 19:
		return 10;
	case 21:
		return 9;
	case 22:
		return 25;
	case 23:
		return 11;
	case 24:
		return 8;
	case 26:
		return 7;
	default:
		return -1;
	}
}

std::string GPIOAccessIf::portDirectionToString(
		const GPIODirection direction) {
	switch (direction) {
	case GPIODirection::IN:
		return "in";

	case GPIODirection::OUT:
		return "out";

	default:
		return "";
	}
}
