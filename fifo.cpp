#include <iostream>
using namespace std;
class FIFOPageReplacement {
    private:
        int frames[10];  // Array to store pages in memory (fixed to 10 for simplicity)
        int capacity;    // Number of frames (capacity)
        int front;       // The front pointer to the oldest page
        int pageHits;    // Number of page hits
        int pageMisses;  // Number of page faults (misses)
    public:
        // Constructor to initialize the object
        FIFOPageReplacement(int capacity) {
            this->capacity = capacity;
            front = 0;
            pageHits = 0;
            pageMisses = 0;
            for (int i = 0; i < capacity; i++) {
                frames[i] = -1; // Initialize frames with -1 (empty)
            }
        }
        // Function to check if a page is already in memory
        bool isPageInMemory(int page) {
            for (int i = 0; i < capacity; i++) {
                if (frames[i] == page) {
                    return true;  }
            }
            return false;
        }
        // Function to process a page reference
        void referencePage(int page) {
            cout << "Page table after request from " << page << " ->  ";
            // If page is already in memory, it's a hit
            if (isPageInMemory(page)) {
                pageHits++;
                printFrames();
                cout << "  >> Hit" << endl;
                return;
            }
            // If page is not in memory, replace the oldest page (FIFO)
            frames[front] = page;
            front = (front + 1) % capacity; // Move the front pointer
            pageMisses++;
            printFrames();
            cout << "  >> Page Fault" << endl;
        }
        // Function to print the current state of the frames
        void printFrames() {
            for (int i = 0; i < capacity; i++) {
                if (frames[i] == -1) {
                    cout << "-- ";
                } else {
                    cout << frames[i] << " ";  }  }
        }
        // Function to print the results
        void printResults(int totalRequests) {
            cout << "\nNumber of page hits: " << pageHits << endl;
            cout << "Number of page faults: " << pageMisses << endl;
            cout << "Hit Ratio: " << (float)pageHits / totalRequests * 100 << "%" << endl;
            cout << "Page Fault Ratio: " << (float)pageMisses / totalRequests * 100 << "%" << endl;
        }
};
int main() {
    int capacity, n;
    // Get number of frames
    cout << "Enter the number of frames: ";
    cin >> capacity;
    // Create FIFO page replacement object
    FIFOPageReplacement fifo(capacity);
    // Get the number of page requests
    cout << "Enter the total number of page requests: ";
    cin >> n;
    // Input page references and process them
    int page;
    cout << "Enter reference string: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> page;
        fifo.referencePage(page);
    }
    // Print results
    fifo.printResults(n);

    return 0;
}



