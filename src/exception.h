//
// Created by hlx on 2023-05-09.
//

#ifndef MYSTL_EXCEPTION_H
#define MYSTL_EXCEPTION_H

#include <stdexcept>

namespace mystl {

    class out_of_range : public std::exception {
    public:
        explicit out_of_range(const char *msg) : message(msg) {}

        const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };


}

#endif //MYSTL_EXCEPTION_H
