#pragma once
#include <string>

namespace PasswordUtils {
std::string generate(int length);
std::string evaluate(const std::string& pwd); // returns "Weak"/"Moderate"/"Strong"
}
