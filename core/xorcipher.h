#pragma once
#include <string>

namespace XorCipher {
bool transformFile(const std::string& inPath,
                   const std::string& outPath,
                   const std::string& key); // returns success
}
