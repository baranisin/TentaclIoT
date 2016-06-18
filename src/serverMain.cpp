#include "LightServer.h"


int main() {
    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    condition_variable run_stopped;

    LightServer *ls = new LightServer("svetlo");

    run_stopped.wait(lock);
}