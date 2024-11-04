#include <iostream>
#include <iomanip>  // For setting output precision
using namespace std;

const int MAX_FRAMES = 100;  // Adjust according to maximum frame size expected
int n;                      // Length of the page reference stream
int frame_size;            // Number of frames available
int pages[100005];         // Page reference stream
int frames[MAX_FRAMES];    // Current pages in memory (frames)
int frame_count;           // Current number of frames

void print_frame_table(bool page_fault) {
    cout << "Page table after request: ";
    for (int i = 0; i < frame_size; i++) {
        if (frames[i] == -1)
            cout << "-- ";
        else
            cout << frames[i] << " ";
    }
    cout << (page_fault ? ">> page fault" : ">> Hit") << endl;
}

void optimal_page_replacement() {
    int page_faults = 0; // Count of page faults
    int page_hits = 0;   // Count of page hits

    // Initialize frames with -1 indicating empty
    for (int i = 0; i < frame_size; i++) {
        frames[i] = -1;
    }
    frame_count = 0;

    for (int i = 0; i < n; i++) {
        int k;
        bool page_found = false;

        // Check if page is already in the frames
        for (k = 0; k < frame_size; k++) {
            if (frames[k] == pages[i]) {
                page_found = true;
                page_hits++;
                break;
            }
        }

        // If page is not in the frames, it's a page fault
        if (!page_found) {
            // If there is still space in frames, just add the page
            if (frame_count < frame_size) {
                frames[frame_count++] = pages[i];
            } else {
                int index = i + 1;
                int farthest = index, replace_index = 0;

                // Find the frame to replace
                for (int j = 0; j < frame_size; j++) {
                    int next_use = n; // Assume this page won't be used again

                    // Find the next use of the current frame's page
                    for (int k = index; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            next_use = k;
                            break;
                        }
                    }

                    // Choose the page that will be used farthest in the future
                    if (next_use > farthest) {
                        farthest = next_use;
                        replace_index = j;
                    }
                }

                // Replace the selected page
                frames[replace_index] = pages[i];
            }

            page_faults++;
            print_frame_table(true);
        } else {
            print_frame_table(false);
        }
    }

    // Print results
    cout << "\nTotal Page Faults: " << page_faults << endl;
    cout << "Total Page Hits: " << page_hits << endl;
    cout << "Hit Ratio = " << fixed << setprecision(2) << (100.0 * page_hits / n) << "%" << endl;
    cout << "Fault Ratio = " << fixed << setprecision(2) << (100.0 * page_faults / n) << "%" << endl;
}

int main() {
    // Get the number of frames and the length of the page reference stream
    cout << "Enter number of frames: ";
    cin >> frame_size;

    cout << "Enter total number of page requests: ";
    cin >> n;

    cout << "Enter pages:\n";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    // Call the function to perform optimal page replacement
    optimal_page_replacement();

    return 0;
}



