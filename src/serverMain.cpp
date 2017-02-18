#include "LightServer.h"


int main() {
    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    condition_variable run_stopped;

    LightServer *ls = new LightServer("svetielko");
    ls->setPresenceOn();

    run_stopped.wait(lock);
}