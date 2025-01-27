#include <thread>

#include "server.h"
#include "safebuffer.h"
#include "inputhandler.h"
#include "bufferprocessor.h"


int main() {
    SafeBuffer<string> buffer;

    Server server(52000);
    server.run();

    InputHandler handler(buffer);
    BufferProcessor bp(buffer);

    std::thread inputThread(&InputHandler::startInputProcess, handler);
    std::thread processingThread(&BufferProcessor::processAndTransfer, bp, ref(server));

    inputThread.join();
    processingThread.join();

    return 0;
}
