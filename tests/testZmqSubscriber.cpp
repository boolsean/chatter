#include "Subscriber.h"


int main() {
    zmq::context_t context(1);

    Subscriber sub(context);

    return 0;
}
