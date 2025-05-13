#include "xorcipher.h"
#include <fstream>

bool XorCipher::transformFile(const std::string& inPath,
                              const std::string& outPath,
                              const std::string& key)
{
    std::ifstream in(inPath, std::ios::binary);
    std::ofstream out(outPath, std::ios::binary);
    if (!in || !out || key.empty()) return false;

    char ch;
    size_t i = 0;
    while (in.get(ch)) {
        ch ^= key[i % key.size()];
        out.put(ch);
        ++i;
    }
    return true;
}
