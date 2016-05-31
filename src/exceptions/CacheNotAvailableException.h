#ifndef IOTIVITY_BAKALARKA_CACHENOTAVAILABLEEXCEPTION_H
#define IOTIVITY_BAKALARKA_CACHENOTAVAILABLEEXCEPTION_H

#include <exception>

class CacheNotAvailableException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Cache is not available!";
    }

};
#endif //IOTIVITY_BAKALARKA_CACHENOTAVAILABLEEXCEPTION_H
