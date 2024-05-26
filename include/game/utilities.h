//
// Created by mac on 5/23/24.
//

#ifndef PAC_PLUS_UTILITIES_H
#define PAC_PLUS_UTILITIES_H

#include <string>

class Utilities {
   public:
    static inline auto IsInteger(const std::string &s) -> bool {
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
            return false;
        }

        char *p;
        strtol(s.c_str(), &p, 10);
        return (*p == 0);
    }
};

#endif  // PAC_PLUS_UTILITIES_H
