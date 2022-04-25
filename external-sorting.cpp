#include <bits/stdc++.h>

using namespace std;

class Page {
public:
    int num_of_records;
    vector<int> records;

    Page() {
        num_of_records = 0;
    }
};

void merge(Page* arr, int run_size, int BUFFER_SIZE, int PAGE_SIZE) {
    vector<int> common;
    for (int i = 0; i < run_size*(BUFFER_SIZE-1); i++) {
        common.insert(common.begin(),
                        arr[i].records.begin(),
                        arr[i].records.end());
    }

    sort(common.begin(), common.end());

    int page_number = -1;
    for (int i = 0; i < common.size(); i++) {
        if (i % PAGE_SIZE == 0) {
            page_number++;
            arr[page_number].records.clear();
        }
        arr[page_number].records.push_back(common[i]);
    }
}

void sort_pages(int pages, Page* arr, int BUFFER_SIZE, int PAGE_SIZE) {
    for (int i = 0; i < pages; i++) {
        sort(arr[i].records.begin(), arr[i].records.end());
    }

    int run_size = 1;
    while (run_size < pages) {
        for (int j = 0; j < pages; j += run_size*(BUFFER_SIZE-1)) {
            merge(arr+j, run_size, BUFFER_SIZE, PAGE_SIZE);
        }
        run_size *= BUFFER_SIZE-1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int BUFFER_SIZE, PAGE_SIZE, NUM_RECORDS;
    cin >> BUFFER_SIZE >> PAGE_SIZE >> NUM_RECORDS;

    Page arr[NUM_RECORDS/PAGE_SIZE + 1];
    int page_number = -1;
    int value;
    for (int i = 0; i < NUM_RECORDS; i++) {
        if (i % PAGE_SIZE == 0) {
            page_number++;
            arr[page_number].records.clear();
        }
        cin >> value;
        arr[page_number].records.push_back(value);
    }

    sort_pages(page_number+1, arr, BUFFER_SIZE, PAGE_SIZE);



    return 0;
}
