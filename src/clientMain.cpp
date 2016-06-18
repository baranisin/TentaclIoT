#include <unistd.h>
#include "Client.h"

int main() {
    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    condition_variable run_stopped;

    Client client = Client();
    client.startDiscovery();
    sleep(3);
    client.loadConfiguration();
    sleep(5);
//    client.outputActualConfiguration();
    run_stopped.wait(lock);
}