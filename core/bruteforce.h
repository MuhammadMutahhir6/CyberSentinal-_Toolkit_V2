#pragma once
#include <string>
#include <functional>
#include <atomic>

class BruteForce
{
public:
    using Progress = std::function<void(double)>;                 // 0‑100 %
       using GuessCb  = std::function<void(const std::string&)>;     // current guess

    /** Brute‑force a password.
     *  @param stop   reference to an atomic flag – set true to abort.
     *  Returns cracked password, or empty string if not found / aborted.
     */
    static std::string attack(const std::string& target,
                              int maxLen,
                              const std::string& charset,
                              Progress progress,
                              GuessCb  guessCb,
                              const std::atomic_bool& stop);
};
