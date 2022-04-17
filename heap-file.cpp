#include <bits/stdc++.h>

using namespace std;

int PAGE_SIZE;

class Page {
public:
    int used;
    vector<int> records;
    Page *next, *prev;

    Page() {
        used = 4;
        next = nullptr;
        prev = nullptr;
    }

    int empty_space() {
        return PAGE_SIZE - 4 - used;
    }

    bool insert(int sz, int pk) {
        if (empty_space() >= sz+4) {
            used += sz+4;
            records.push_back(pk);
            return true;
        }
        return false;
    }

    int search(int pk) {
        for (int i = 0; i < records.size(); i++) {
            if (records[i] == pk) return i;
        }
        return -1;
    }
};

class File {
public:
    Page* first;
    int pages;

    File() {
        first = nullptr;
        pages = 0;
    }

    void insert(int sz, int pk) {
        Page* curr = first, *last = nullptr;
        while (true) {
            if (!curr) {
                curr = new Page;
                if (!first) first = curr;
                pages++;
                if (last) {
                    last->next = curr;
                    curr->prev = last;
                }
            }
            if (curr->insert(sz, pk)) return;
            last = curr;
            curr = curr->next;
        }
    }

    void display_status() {
        cout << pages << " ";
        Page* curr = first;
        while(curr) {
            cout << curr->records.size() << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    pair<int, int> search(int pk) {
        int page_number = 0;
        Page* curr = first;
        while (curr) {
            if (curr->search(pk) >= 0) return {page_number, curr->search(pk)};
            curr = curr->next;
            page_number++;
        }
        return {-1, -1};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> PAGE_SIZE;

    File file;

    int type, sz, pk;

    while(true) {
        cin >> type;
        if (type == 1) { // INSERT
            cin >> sz >> pk;
            file.insert(sz, pk);
        }
        else if (type == 2) { // STATUS
            file.display_status();
        }
        else if (type == 3) { // SEARCH
            cin >> pk;
            pair<int, int> ans = file.search(pk);
            cout << ans.first << " " << ans.second << endl;
        }
        else break;
    }

    return 0;
}
