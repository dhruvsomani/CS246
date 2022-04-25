#include <bits/stdc++.h>

using namespace std;

class Page {
    int num_of_records;
    vector<int> records;

    Page() {
        num_of_records = 0;
    }
}

void sort(int pages, Page* arr, int BUFFER_SIZE) {
    for (int i = 0; i < pages; i++) {
        sort(arr[i]->records.begin(), arr[i]->records.end());
    }

    int run_size = 1;
    while (run_size < pages) {
        for (int j = 0; j < pages; j += run_size) {
            
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    

    return 0;
}
