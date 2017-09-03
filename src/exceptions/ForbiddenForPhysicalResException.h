//
// Created by Patrik Baranišin on 20.5.2016.
//

#ifndef IOTIVITY_BAKALARKA_FORBIDDENFORPHYSICALRESEXCEPTION_H
#define IOTIVITY_BAKALARKA_FORBIDDENFORPHYSICALRESEXCEPTION_H
#include <exception>

class ForbiddenForPhysicalResException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Physical resource cannot derive init(const unsigned int id, DiscoveryThread &dt) !";
    }

};
#endif //IOTIVITY_BAKALARKA_FORBIDDENFORPHYSICALRESEXCEPTION_H
