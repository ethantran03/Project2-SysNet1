#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstring> // for std::memset

const int MAX_STOPPING_TIME = 1000; // Maximum stopping time to track
int histogram[MAX_STOPPING_TIME + 1]; // Histogram array
std::mutex mtx; // Mutex for synchronization
int COUNTER = 1; // Global counter for numbers to process

// Function to compute the Collatz stopping time for a given number
int collatzStoppingTime(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2; // Even case
        } else {
            n = 3 * n + 1; // Odd case
        }
        steps++;
    }
    return steps;
}

// Function to be executed by each thread
void computeCollatz(int N) {
    while (true) {
        int current;
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (COUNTER > N) {
                break; // Exit if all numbers processed
            }
            current = COUNTER++; // Get the current number to process
        }
        
        int stoppingTime = collatzStoppingTime(current);
        if (stoppingTime <= MAX_STOPPING_TIME) {
            std::lock_guard<std::mutex> lock(mtx); // Lock for histogram update
            histogram[stoppingTime]++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./mt-collatz N T [-nolock]\n";
        return 1;
    }

    int N = std::stoi(argv[1]); // Upper limit for Collatz numbers
    int T = std::stoi(argv[2]); // Number of threads
    bool useLock = (argc < 4) || (strcmp(argv[3], "-nolock") != 0);

    std::memset(histogram, 0, sizeof(histogram)); // Initialize histogram

    std::vector<std::thread> threads; // Vector to hold threads

    // Start measuring time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Create threads
    for (int i = 0; i < T; i++) {
        threads.emplace_back(computeCollatz, N);
    }

    // Join threads
    for (auto &t : threads) {
        t.join();
    }

    // End measuring time
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    // Print histogram
    for (int i = 0; i <= MAX_STOPPING_TIME; i++) {
        std::cout << i << "," << histogram[i] << "\n"; // Print histogram format
    }

    // Print elapsed time
    std::cerr << N << "," << T << "," << elapsed.count() << "\n";

    return 0;
}

