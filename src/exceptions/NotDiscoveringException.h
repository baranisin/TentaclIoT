//
// Created by kingofwolwes on 15.5.2016.
//

#ifndef IOTIVITY_BAKALARKA_NOTDISCOVERINGEXCEPTION_H
#define IOTIVITY_BAKALARKA_NOTDISCOVERINGEXCEPTION_H

#include <exception>

class NotDiscoveringException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Discovery has not started yet function will wait until discovery is started!";
    }

};
#endif //IOTIVITY_BAKALARKA_NOTDISCOVERINGEXCEPTION_H
