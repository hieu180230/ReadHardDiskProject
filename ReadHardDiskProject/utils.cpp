#include "utils.h"
std::string utils::DectoHex(int dec)
{
	std::stringstream ss;
	ss << std::hex << dec;
	return ss.str();
}