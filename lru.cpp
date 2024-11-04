#include <iostream>
using namespace std;

int main() {
    int q[20], p[50], c1, d, f, i, j, k = 0, n, r;
    int pageHits = 0; // Variable to count page hits
    int pageFaults = 0; // Variable to count page faults

    cout << "Enter the number of frames: ";
    cin >> f;

    cout << "Enter the total number of page requests: ";
    cin >> n;

    cout << "Enter pages: ";
    for (i = 0; i < n; i++) {
        cin >> p[i]; // Input reference string
    }

    // Initialize page frames
    for (i = 0; i < f; i++) {
        q[i] = -1; // Using -1 to indicate empty frames
    }

    cout << "\nPosition of frame table after each request :\n";

    for (i = 0; i < n; i++) {
        int currentPage = p[i];
        c1 = 0;

        // Check if the page is already present in any frame (Hit)
        for (j = 0; j < f; j++) {
            if (q[j] == currentPage) {
                c1 = 1; // Page hit
                pageHits++;
                break;
            }
        }

        // If page is not found in memory (Miss)
        if (c1 == 0) {
            pageFaults++; // Increment page fault count
            if (k < f) {
                // If there is still space in the frames
                q[k] = currentPage; // Insert the new page
                k++;
            } else {
                // If memory is full, implement LRU replacement
                int lastUsed[20] = {0}; // Array to store the last used time of pages
                for (r = 0; r < f; r++) {
                    lastUsed[r] = -1;
                    for (int x = i - 1; x >= 0; x--) {
                        if (q[r] == p[x]) {
                            lastUsed[r] = x; // Last used time of the page
                            break;
                        }
                    }
                }

                // Find the least recently used page
                int minIndex = 0;
                for (r = 1; r < f; r++) {
                    if (lastUsed[r] < lastUsed[minIndex]) {
                        minIndex = r;
                    }
                }

                // Replace the least recently used page
                q[minIndex] = currentPage;
            }

            // Print current state of the page frames after replacement
            cout << "Page table after request from " << currentPage << " -> ";
            for (j = 0; j < f; j++) {
                if (q[j] != -1) cout << q[j] << " ";
                else cout << "-- ";
            }
            cout << " >> page fault\n";
        } else {
            // Print current state of the page frames on a hit
            cout << "Page table after request from " << currentPage << " -> ";
            for (j = 0; j < f; j++) {
                if (q[j] != -1) cout << q[j] << " ";
                else cout << "-- ";
            }
            cout << " >> Hit\n";
        }
    }

    // Calculate ratios
    double hitRatio = static_cast<double>(pageHits) / n * 100;
    double faultRatio = static_cast<double>(pageFaults) / n * 100;

    cout << "\nNumber of page faults : " << pageFaults << endl;
    cout << "Number of page Hits : " << pageHits << endl;
    cout << "The hit ratio is: " << hitRatio << "%" << endl;
    cout << "The fault ratio is: " << faultRatio << "%" << endl;

    return 0;
}


