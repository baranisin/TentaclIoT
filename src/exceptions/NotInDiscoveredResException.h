//
// Created by Patrik Baranišin on 15.5.2016.
//

#ifndef IOTIVITY_BAKALARKA_NOTINDISCOVEREDRESEXCEPTION_H
#define IOTIVITY_BAKALARKA_NOTINDISCOVEREDRESEXCEPTION_H

#include <exception>

class NotInDiscoveredResException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Resource with this uri is not discovered!";
    }

};
#endif //IOTIVITY_BAKALARKA_NOTINDISCOVEREDRESEXCEPTION_H
