#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::string sharedString = " ";
std::mutex wait;

void axWorker() {
    while (sharedString.size() < 30) {
        {
            std::lock_guard<std::mutex> lock(wait);
            sharedString += "1";
            std::this_thread::sleep_for(std::chrono::nanoseconds(10000000));
            sharedString += "2";
        }
        std::cout << " " << sharedString << std::endl;
    }
}

int main() {
    std::thread aThread(axWorker);
    std::thread xThread(axWorker);
    aThread.join();
    xThread.join();

    std::cout << "Final string: " << sharedString << std::endl;

    return 0;
}