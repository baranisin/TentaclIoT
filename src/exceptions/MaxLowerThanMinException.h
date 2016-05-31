//
// Created by kingofwolwes on 15.5.2016.
//

#ifndef IOTIVITY_BAKALARKA_MAXLOWERTHANMINEXCEPTION_H
#define IOTIVITY_BAKALARKA_MAXLOWERTHANMINEXCEPTION_H
#include <exception>

class MaxLowerThanMinException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "MAX value is lower then MIN value!";
    }

};
#endif //IOTIVITY_BAKALARKA_MAXLOWERTHANMINEXCEPTION_H
