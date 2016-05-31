#ifndef IOTIVITY_BAKALARKA_EMPTYNAMEEXCEPTION_H
#define IOTIVITY_BAKALARKA_EMPTYNAMEEXCEPTION_H

#include <exception>

class EmptyStringException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Name is empty string!";
    }

};

#endif //IOTIVITY_BAKALARKA_EMPTYNAMEEXCEPTION_H
