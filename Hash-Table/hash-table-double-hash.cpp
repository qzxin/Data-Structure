#include <iostream>
#include <stdlib.h>
using namespace std;
// 双重散列法：http://blog.csdn.net/quzhongxin/article/details/45197553
template <class KeyType, class ValueType>
class HashTable {
private:
	struct Node {
		KeyType key;
		ValueType value;
		Node(KeyType k, ValueType v) : key(k), value(v) {};
	};
	Node **table;
	int counts;
	const int TABLE_SIZE;
	int Hash1(KeyType key) {
		return key % TABLE_SIZE;
	}
	int Hash2(KeyType key) {
		return key % 97 + 1;
	}
public:
	HashTable(int max_nums) : TABLE_SIZE(2*max_nums) {
		table = new Node *[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
		counts = 0;
	}
	~HashTable() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (table[i] != NULL) {
				delete table[i];
				table[i] = NULL;
			}
		}
		delete []table;
		table = NULL;
	}
	void push(KeyType key, ValueType value) {
		int index = Hash1(key);
		while (table[index] != NULL) {
			index += Hash2(key);
			index = Hash1(index);
		}
		table[index] = new Node(key, value);
	};

	ValueType get(KeyType key) {
		int index = Hash1(key);
		while (table[index] != NULL && table[index]->key != key) {
			index += Hash2(key);
			index = Hash1(index);
		}
		if (table[index] != NULL)
			return table[index]->value;
		return ValueType(); // 返回默认值
	};

	void erase(KeyType key) {
		int index = Hash1(key);
		while (table[index] != NULL && table[index]->key != key) {
			index += Hash2(key);
			index = Hash1(index);
		}
		if (table[index] != NULL) {
			delete table[index];
			table[index] = NULL;
		}
	};
};

int main() {
	HashTable<int, int> map(10);
	for (int i = 0; i < 10; i++) {
		int key = rand() % 100;
		int value = rand() % 100;
		cout << "key: " << key << " value: " << value << endl;
		map.push(key, value);
	}
	cout << endl << "Get: " << endl;
	cout << map.get(81) << endl;
	cout << map.get(5) << endl;
	cout << map.get(3) << endl;
	cout <<"erase : " << endl;
	map.erase(81);
	map.erase(2);
	cout << endl << "Get: " << endl;
	cout << map.get(81) << endl;
	cout << map.get(95) << endl;
}