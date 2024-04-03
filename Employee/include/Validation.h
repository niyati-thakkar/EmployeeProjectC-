#ifndef _VALIDATION_H_
#define _VALIDATION_H_

#include <string>
#include <regex>

namespace Validation {
    inline bool validateID(std::string id) {
        return id.length() == 7;
    }

    inline bool validateString(std::string str) {
        if (str.length() != 0 && std::regex_match(str, std::regex("^[a-zA-Z][-a-zA-Z ']{1,49}$"))) {
            return true;
        }
        return false;
    }

    inline bool validatePincode(std::string str) {
        return str.length() == 6;
    }

    inline bool validateContact(std::string str) {
        return str.length() > 0 && std::regex_match(str, std::regex("\\(?\\d{3}[-\\) ]+\\d{3}[- ]?\\d{4}"));
    }

    inline bool validateEmail(std::string str) {
        return str.length() > 0 && std::regex_match(str, std::regex(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))"));
    }

    inline bool validateDate(std::string str) {
        return str.length() > 0 && std::regex_match(str, std::regex(R"((0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[1,2])-(19|20)\d{2})"));
    }

    inline bool validateText(std::string str) {
        return str.length() > 0 && std::regex_match(str, std::regex("^[a-zA-Z0-9 ,.-]*$"));
    }
}

#endif
