//
// Created by Patrik Baranišin on 15.5.2016.
//

#ifndef IOTIVITY_BAKALARKA_MORERESWITHSAMEURIEXCEPTION_H
#define IOTIVITY_BAKALARKA_MORERESWITHSAMEURIEXCEPTION_H

#include <exception>

class MoreResWithSameURIException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "More res with same URI exists!";
    }

};

#endif //IOTIVITY_BAKALARKA_MORERESWITHSAMEURIEXCEPTION_H
