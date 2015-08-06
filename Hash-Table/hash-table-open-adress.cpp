#include <iostream>
using namespace std;
// 开放地址法：http://blog.csdn.net/quzhongxin/article/details/45197553
template<class KeyType, class ValueType>
class HashTable {
private:
	struct Node {
		KeyType key;
		ValueType value;
		Node(KeyType k, ValueType v) : key(k), value(v){};
	};
	const int TABLE_SIZE;
	Node** table;
	int counts; //已有元素个数
	int Hash(KeyType key) {
		return key % TABLE_SIZE;
	};
public:
	HashTable(int max_nums):TABLE_SIZE(2*max_nums) {
		counts = 0;
		table = new Node* [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
	};
	~HashTable() {
		for (int i = 0; i < TABLE_SIZE; i++)
			delete table[i];
		delete []table;
		table = NULL;
	};
	void push(KeyType key, ValueType value) {
		if (counts >= TABLE_SIZE)
			throw("Hash Table is Full");
		int index = Hash(key);
		while (table[index] != NULL) {
			(++index) %= TABLE_SIZE;
		}
		table[index] = new Node(key, value);
		counts++;
	};
	void erase(KeyType key) {
		int index = Hash(key);
		while (table[index] != NULL)	{
			if (table[index]->key == key) {
				delete(table[index]);
				table[index] = NULL;
			}
			(++index) %= TABLE_SIZE;
		}
	};
	ValueType get(KeyType key) {
		int index = Hash(key);
		while (table[index] != NULL)	{
			if (table[index]->key == key) {
				return table[index]->value;
			}
			(++index) %= TABLE_SIZE;
		}
		return ValueType();
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