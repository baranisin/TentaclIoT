#ifndef IOTIVITY_BAKALARKA_NULLPTREXCEPTION_H
#define IOTIVITY_BAKALARKA_NULLPTREXCEPTION_H

#include <exception>

class NullPtrException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "NULL POINTER!";
    }

};

#endif //IOTIVITY_BAKALARKA_NULLPTREXCEPTION_H
