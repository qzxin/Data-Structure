#include <iostream>
using namespace std;
// Á´±í·¨£ºhttp://blog.csdn.net/quzhongxin/article/details/45196005
template<class KeyType, class ValueType>
class HashTable {
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
        Node(KeyType k, ValueType v,Node* n = NULL) : key(k), value(v),next(n) {};
        Node():next(NULL) {};
    };
    const int TABLE_SIZE;
    Node** table;
    int Hash(KeyType key) {
        return key % TABLE_SIZE;
    };
public:
    HashTable(int size = 23):TABLE_SIZE(size) {
        table = new Node*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = new Node;
    };
	~HashTable() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			Node* head = table[i];
			while (head != NULL) {
				Node* next = head->next;
				delete head;
				head = next;
			}
		}
		delete []table;
	};
    void push(KeyType key, ValueType value) {
        int index = Hash(key);
        Node* head = table[index];
        Node* newItem = new Node(key, value, head->next);
        head->next = newItem;
    };
    void erase(KeyType key) {
        int index = Hash(key);
        Node* head = table[index];
        while (head->next != NULL) {
            if (head->next->key == key) {
                Node* tmp = head->next;
                head->next = head->next->next;
                delete tmp;
                break;
            }
            head = head->next;
        }
    };
    ValueType get(KeyType key) {
        int index = Hash(key);
        Node* head = table[index];
        while (head->next != NULL) {
            if (head->next->key == key) {
                return head->next->value;
            }
            head = head->next;
        }
        return ValueType();
    };

};

int main()
{
	HashTable<int, char> map;
	for (int i = 0; i < 100; i++) {
		map.push(i, i + '0');
	}
	cout << map.get(50) << endl;
	cout << map.get(60) << endl;
	map.erase(60);
	cout << map.get(60) << endl;
}

