#include <bits/stdc++.h>

using namespace std;


int BUCKET_SIZE = 2;
vector<int> created;


int Hash(int key) {
	return key;
}


class Bucket {
public:
	int local_depth;
	int* ptr;
	int size;

	Bucket() {
		local_depth = 1;
		ptr = (int*) malloc(sizeof(int) * BUCKET_SIZE);
		size = 0;
	}

	bool insert(int value) {
		if (size < BUCKET_SIZE) {
			ptr[size++] = value;
			return true;
		}
		return false;
	}

	bool search(int value) {
		for (int i = 0; i < size; i++) {
			if (ptr[i] == value) return true;
		}
		return false;
	}

	bool remove(int value) {
		int i = 0;
		for (; i < size; i++) {
			if (ptr[i] == value) {
				break;
			}
		}
		if (i < size) {
			for (; i < size; i++) ptr[i] = ptr[i+1];
		}
		else return false;

		--size;
		return true;
	}

	void clear() {
		size = 0;
	}
};


class ExtendibleHashMap {
public:
	int global_depth, num_buckets;
	vector< Bucket* > directory;

	ExtendibleHashMap() {
		global_depth = 1;
		num_buckets = 2;
		directory.push_back(new Bucket);
		directory.push_back(new Bucket);

		created.push_back(0);
		created.push_back(1);
	}

	ExtendibleHashMap(int depth) {
		global_depth = depth;
		num_buckets = (1 << depth);
		for (int i = 0; i < (1 << depth); i++) {
			directory.push_back(new Bucket);
			directory[i]->local_depth = depth;
			created.push_back(i);
		}
	}

	void double_directory() {
		for (int i = 0; i < (1<<global_depth); i++) {
			directory.push_back(directory[i]);
		}
		global_depth++;
	}

	void split_bucket(int bucket) {
		bucket %= (1 << directory[bucket]->local_depth);
		if (directory[bucket]->local_depth == global_depth) double_directory();

		int new_bucket = bucket + (1 << (directory[bucket]->local_depth));
		directory[new_bucket] = new Bucket;
		++num_buckets;
		created.push_back(new_bucket);

		int mask = (1 << global_depth)-1;
		int old_count = 0, new_count = 0;

		for (int i = 0; i < directory[bucket]->size; i++) {
			if ((directory[bucket]->ptr[i] & mask) == bucket) {
				directory[bucket]->ptr[old_count++] = directory[bucket]->ptr[i];
			}
			else {
				directory[new_bucket]->ptr[new_count++] = directory[bucket]->ptr[i];
			}
		}

		directory[bucket]->size = old_count;
		directory[bucket]->local_depth++;
		directory[new_bucket]->size = new_count;
		directory[new_bucket]->local_depth = directory[bucket]->local_depth;
	}

	bool insert(int value) {
		int hashed = Hash(value);
		int bucket = hashed & ((1 << global_depth) - 1);

		while (!(directory[bucket]->insert(value))) {
			split_bucket(bucket);
			bucket = hashed & ((1 << global_depth) - 1);
		}
		return true;
	}

	bool search(int value) {
		int hashed = Hash(value);
		int bucket = hashed & ((1 << global_depth) - 1);

		return directory[bucket]->search(value);
	}

	bool remove(int value) {
		int hashed = Hash(value);
		int bucket = hashed & ((1 << global_depth) - 1);

		return directory[bucket]->remove(value);
	}
};


void printMap(ExtendibleHashMap hashmap) {
	cout << "hashmap.global_depth: " << hashmap.global_depth << " hashmap.directory.size(): " << hashmap.directory.size() << "\n";
	for (int i = 0; i < (1 << hashmap.global_depth); i++) {
		cout << "i: " << i << ", local_depth: " << hashmap.directory[i]->local_depth << ", size: " << hashmap.directory[i]->size << " -> "; 
		for (int j = 0; j < hashmap.directory[i]->size; j++) {
			cout << hashmap.directory[i]->ptr[j] << " ";
		}
		cout << endl;
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int depth;
	cin >> depth >> BUCKET_SIZE;

	ExtendibleHashMap hashmap(depth);

	int type, value;
	while (true) {
		cin >> type;
		if (type == 2) {
			cin >> value;
			hashmap.insert(value);
		}
		else if (type == 3) {
			cin >> value;
			// cout << hashmap.search(value) << endl;
		}
		else if (type == 4) {
			cin >> value;
			hashmap.remove(value);
		}
		else if (type == 5) {
			cout << hashmap.global_depth << endl;
			cout << hashmap.num_buckets << endl;
			for (int i = 0; i < created.size(); i++) {
				cout << hashmap.directory[created[i]]->size << " " << hashmap.directory[created[i]]->local_depth << endl;
			}
		}
		else if (type == 6) {
			break;
		}
	}

	return 0;
}
