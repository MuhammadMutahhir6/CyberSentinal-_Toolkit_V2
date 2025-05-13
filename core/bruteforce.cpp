#include "bruteforce.h"
#include <chrono>

static bool next(std::string& pwd,
                 const std::string& charset,
                 int maxLen)
{
    for (int i = (int)pwd.size() - 1; i >= 0; --i) {
        size_t pos = charset.find(pwd[i]);
        if (pos + 1 < charset.size()) {
            pwd[i] = charset[pos + 1];
            return true;
        }
        pwd[i] = charset[0];
    }
    if ((int)pwd.size() < maxLen) {
        pwd.push_back(charset[0]);
        return true;
    }
    return false;
}

std::string BruteForce::attack(const std::string& target,
                               int maxLen,
                               const std::string& charset,
                               Progress progress,
                               GuessCb  guessCb,
                               const std::atomic_bool& stop)
{
    std::string guess(1, charset[0]);

    size_t totalComb = 0, power = 1;
    for (int i = 1; i <= maxLen; ++i) { power *= charset.size(); totalComb += power; }

    size_t attempts = 0;
    auto last = std::chrono::steady_clock::now();

    while (!stop.load()) {
        guessCb(guess);
        if (guess == target) return guess;
        if (!next(guess, charset, maxLen)) break;

        if (++attempts % 2500 == 0) {
            auto now = std::chrono::steady_clock::now();
            if (now - last > std::chrono::milliseconds(150)) {
                progress(100.0 * attempts / totalComb);
                last = now;
            }
        }
    }
    return {};
}
