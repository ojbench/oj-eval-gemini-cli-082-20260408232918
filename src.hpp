#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>
using namespace std;

class LinkedHashMap;
struct Node{
    Node* next=nullptr;
    Node* timePre=nullptr;
    Node* timeNext=nullptr;

    int key=0;
    string value;
};

struct Data{
    int key;
    string value;
};

vector<Data> traverseByTime(const LinkedHashMap& obj);
vector<Data> traverseByIndex(const LinkedHashMap& obj);

class LinkedHashMap{
public:
    int len;
    Node** array;
    Node* beg;
    Node* current;
    vector<Data> (*forEachMethod)(const LinkedHashMap&);

    LinkedHashMap(int _len_,bool forEachByTime){
        len=_len_;
        beg=new Node();
        current=beg;
        array=new Node*[len];
        for(int i=0;i<len;i++)
            array[i]=nullptr;
        if(forEachByTime)
            forEachMethod=traverseByTime;
        else
            forEachMethod=traverseByIndex;
    }

    ~LinkedHashMap(){
        Node* p = beg;
        while(p != nullptr) {
            Node* tmp = p;
            p = p->timeNext;
            delete tmp;
        }
        delete[] array;
    }

    void insert(int key,string value){
        Node* newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        
        // Insert at the head of the singly linked list array[key]
        newNode->next = array[key];
        array[key] = newNode;
        
        // Insert at the tail of the doubly linked list
        current->timeNext = newNode;
        newNode->timePre = current;
        current = newNode;
    }

    void remove(int key,string value){
        Node* p = array[key];
        Node* pre = nullptr;
        while(p != nullptr) {
            if(p->value == value) {
                // Remove from singly linked list
                if(pre == nullptr) {
                    array[key] = p->next;
                } else {
                    pre->next = p->next;
                }
                
                // Remove from doubly linked list
                if(p->timePre != nullptr) {
                    p->timePre->timeNext = p->timeNext;
                }
                if(p->timeNext != nullptr) {
                    p->timeNext->timePre = p->timePre;
                } else {
                    // If p is the current (tail) node
                    current = p->timePre;
                }
                
                delete p;
                return;
            }
            pre = p;
            p = p->next;
        }
    }

    vector<string> ask(int key)const{
        vector<string> res;
        Node* p = array[key];
        while(p != nullptr) {
            res.push_back(p->value);
            p = p->next;
        }
        return res;
    }

    vector<Data> forEach()const{
        return forEachMethod(*this);
    }
};

vector<Data> traverseByTime(const LinkedHashMap& obj){
    vector<Data> res;
    Node* p = obj.beg->timeNext;
    while(p != nullptr) {
        Data d;
        d.key = p->key;
        d.value = p->value;
        res.push_back(d);
        p = p->timeNext;
    }
    return res;
}

vector<Data> traverseByIndex(const LinkedHashMap& obj){
    vector<Data> res;
    for(int i=0; i<obj.len; i++) {
        Node* p = obj.array[i];
        while(p != nullptr) {
            Data d;
            d.key = p->key;
            d.value = p->value;
            res.push_back(d);
            p = p->next;
        }
    }
    return res;
}

#endif //FINAL_SRC_HPP
