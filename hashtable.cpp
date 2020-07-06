#include "hashtable.h"

int main()
{
    hash_table _hash_table;
    Node *_node = _hash_table.hash_search(3);   //此时表为空，测试search
    if(_node==nullptr)
    {
        cout<<"not found!"<<endl;
    }else
    {
        cout<<"key"<<_node->key<<" name"<<_node->name<<endl;
    }
    _hash_table.hash_insert(0, "Jim");
    _hash_table.hash_insert(1, "Tom");
    _hash_table.hash_insert(2, "Bob");
    _hash_table.hash_insert(3, "MAX");
    _hash_table.hash_insert(4, "Sally");
    _hash_table.hash_insert(5, "Alan");
    _hash_table.hash_insert(6, "Kevin");

    _hash_table.printTable();


    _hash_table.hash_delete(3);     //测试delete(int _key, string _name)接口


    cout << endl;
    _hash_table.printTable();
    cout << endl;

    _hash_table.rehash(23);
    _hash_table.printTable();

    return 0;
}
