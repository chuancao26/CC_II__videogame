#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

int main() {
    std::condition_variable cond;
    std::mutex mtx;
    std::queue<int> intq;
    bool stopped = false;

    std::thread producer{[&]() {
        // Prepare a random number generator.
        std::default_random_engine gen{};
        std::uniform_int_distribution<int> dist{};
        std::size_t count = 10;

        while(count--) {
            std::lock_guard<std::mutex> L{mtx};
            intq.push(dist(gen));
            cond.notify_one();
        }

        std::lock_guard<std::mutex> L{mtx};
        std::cout << "Producer is done!" << std::endl;
        stopped = true;
        cond.notify_one();
    }};

    std::thread consumer{[&]() {
        do {
            std::unique_lock<std::mutex> L{mtx};
            cond.wait(L, [&]() {
                return stopped || !intq.empty();
            });

            while (!intq.empty()) {
                const auto val = intq.front();
                intq.pop();
                std::cout << "Consumer popped: " << val << std::endl;
            }

            if (stopped) {
                std::cout << "Consumer is done!" << std::endl;
                break;
            }
        } while (true);
    }};

    consumer.join();
    producer.join();

    std::cout << "Example Completed!" << std::endl;
    return 0;
}
