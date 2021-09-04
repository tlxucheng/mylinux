#include <iostream>
#include <vector>
#include <list>

class MyHashMap {
public:
    /** Initialize your data structure here. */
    MyHashMap() {
         
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        
    }

private:
    std::vector<std::list<std::pair<int,int>>> map;
	size_t m_size = 10000;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
 
int main()
{
	return 0;
}