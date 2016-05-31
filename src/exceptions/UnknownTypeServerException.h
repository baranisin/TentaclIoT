#ifndef IOTIVITY_BAKALARKA_UNKNOWNTYPESERVEREXCEPTION_H
#define IOTIVITY_BAKALARKA_UNKNOWNTYPESERVEREXCEPTION_H

#include <exception>

class UnknownTypeServerException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "This Server type is not in ImplementedResourceTypes!";
    }

};
#endif //IOTIVITY_BAKALARKA_UNKNOWNTYPESERVEREXCEPTION_H
