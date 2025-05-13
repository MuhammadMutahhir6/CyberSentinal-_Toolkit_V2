#include "passwordutils.h"
#include <random>
#include <cctype>

static const std::string CHARS =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789"
"!@#$%^&*()-_=+[]{}<>?/";

std::string PasswordUtils::generate(int length)
{
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, (int)CHARS.size() - 1);

    std::string out(length, ' ');
    for (char& c : out) c = CHARS[dist(rng)];
    return out;
}

std::string PasswordUtils::evaluate(const std::string& p)
{
    bool up=0, lo=0, di=0, sp=0;
    for (char c: p) {
        if (std::isupper((unsigned)c)) up=1;
        else if (std::islower((unsigned)c)) lo=1;
        else if (std::isdigit((unsigned)c)) di=1;
        else sp=1;
    }
    if (p.size() >= 8 && up && lo && di && sp) return "Strong";
    if (p.size() >= 6 && ((up && lo) || (di && sp))) return "Moderate";
    return "Weak";
}
