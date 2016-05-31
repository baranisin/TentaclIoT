//
// Created by kingofwolwes on 20.5.2016.
//

#ifndef IOTIVITY_BAKALARKA_FORBIDDENFORVIRTUALRESEXCEPTION_H
#define IOTIVITY_BAKALARKA_FORBIDDENFORVIRTUALRESEXCEPTION_H
#include <exception>

class ForbiddenForVirtualResException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Virtual resource cannot derive init(const unsigned int id, RCSRemoteResourceObject::Ptr r)!";
    }

};
#endif //IOTIVITY_BAKALARKA_FORBIDDENFORVIRTUALRESEXCEPTION_H
