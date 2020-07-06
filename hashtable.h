#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct Node     //The hash chaining node
{
    int key;
    string name;
    Node * next;
};

class hash_table
{
private:
    int cnt;
    vector<Node*> map;
    int hashFunction(int _key) {return _key*_key%map.size();}  //The hash function
    void hash_insert(Node *tmp){
        int hashVal=hashFunction(tmp->key);
        Node *t=map[hashVal];
        map[hashVal]=tmp;
        tmp->next=t;
    }


public:
    hash_table() {
        cnt=0;
        map.resize(3);
        for(int i=0;i<map.size();i++)
            map[i]=nullptr;
    }
    hash_table(int n)
    {
        cnt=0;
        map.resize(n);
        for(int i=0;i<map.size();i++)
            map[i]=nullptr;
    }  //Constructor

    ~hash_table()
    {
        for(int i=0;i<map.size();i++)
        {
            Node *tmp=map[i];
            while(tmp!=nullptr)
            {
                Node *last=tmp;
                tmp=tmp->next;
                delete last;
            }
        }
    }

    void hash_insert(int _key, string _name);


    void hash_delete(int _key);

    Node* hash_search(int _key);

    void hash_edit(int _key, string _name);

    void printTable();
    void rehash(int n);
};


void hash_table::hash_insert(int _key, string _name)
{
    if(cnt==map.size())
        rehash(cnt*2);

    int hashValue = hashFunction(_key);
    //for loop bucket
    Node** tmp;
    tmp=&map[hashValue];

    while (*tmp)
    {
        if ((*tmp)->key == _key)
        {
            (*tmp)->name=_name;
            return;
        }
        tmp = &(*tmp)->next;
    }

    *tmp=new Node;
    (*tmp)->key=_key;
    (*tmp)->name=_name;
    (*tmp)->next=nullptr;
    cnt++;

}

//delete a hash node
void hash_table::hash_delete(int _key)
{
    //not exsit
    if(map[hashFunction(_key)] == nullptr)
    {
       cout<<"not found key="<<_key<<"!"<<endl;
       return;
    }

    int num = hashFunction(_key);
    Node* tmp = map[num];
    if(tmp==nullptr)
    {
        cout<<"not found key="<<_key<<"!"<<endl;
        return;
    }else if(tmp->key==_key)
    {
        map[num]=tmp->next;
        delete tmp;
    }else
    {
        Node* last = map[num];
        tmp=tmp->next;
        while(tmp!=nullptr)
        {
            if(tmp->key==_key)
            {
                last->next=tmp->next;
                delete tmp;
                return;
            }else
            {
                last=tmp;
                tmp=tmp->next;
            }
        }
        cout<<"not found key="<<_key<<"!"<<endl;
        return;
    }

}


/* Find a node using key*/
Node* hash_table::hash_search(int _key)
{
    if(map[hashFunction(_key)] == nullptr)
    {
        cout<<"not found key="<<_key<<"!"<<endl;
        return nullptr;
    }

    Node* p = map[hashFunction(_key)];
    while(p)
    {
        if(p->key == _key)
            return p;
        p = p->next;
    }
    cout<<"not found key="<<_key<<"!"<<endl;
    return nullptr;
}

void hash_table::hash_edit(int _key, string _name)
{
    Node *tmp=hash_search(_key);
    if(tmp==nullptr)
    {
        cout<<"not found key="<<_key<<"!insert node!"<<endl;
        hash_insert(_key,_name);
    }
    else
    {
        tmp->name=_name;
    }


}

void hash_table::printTable(){
    for(int i = 0; i < map.size(); i++){
        if(map[i] == nullptr) continue;
        Node* p = map[i];
        cout << "[Bucket " << i <<" ]";
        while(p){
            if(p->next!=nullptr)
                cout << " Key: " << p->key << " Name: " << p->name << " -> ";
            else
                cout << " Key: " << p->key << " Name: " << p->name ;
            p = p->next;
        }
        cout << endl;
    }
    return;
}

void hash_table::rehash(int n)
{
    if(n<cnt)
    {
        cout<<"rehash: n < size"<<endl;
        return;
    }

    vector<Node*> maplast=map;

    map.resize(n);

    for(int i=0;i<map.size();i++)
    {
        map[i]=nullptr;
    }

    for(int i=0;i<maplast.size();i++)
    {
        Node *tmp=maplast[i];
        Node *next;
        while(tmp!=nullptr)
        {
            next=tmp->next;
            hash_insert(tmp);
            tmp=next;
        }
    }

}
