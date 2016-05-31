
#ifndef IOTIVITY_BAKALARKA_THREADSTOPPEDEXCEPTION_H
#define IOTIVITY_BAKALARKA_THREADSTOPPEDEXCEPTION_H

#include <exception>

class ThreadStoppedException : public std::exception {
public:
    virtual const char *what() const throw() {
        return "Thread already stopped, cannot be started again!";
    }

};
#endif //IOTIVITY_BAKALARKA_THREADSTOPPEDEXCEPTION_H
