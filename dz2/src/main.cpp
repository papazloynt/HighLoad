#include "server/server.h"

int main() {
    Server server(4, "../http-test-suite/");
    server.run();
    return 0;
}
