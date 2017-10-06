/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
#include <valarray>
using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List(){
        L1Item<T>*p=new L1Item<T>();
        while(p!=NULL){
            delete p;
            p=p->pNext;
        }
    };

    void    clean(){
        ~L1List();
    };
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);
    T&      operator[](int i);

    bool    find(T& a, int& idx);
    int     insert(int i, T& a);
    int     remove(int i);

    int     push_back(T& a);
    int     insertHead(T& a);

    int     removeHead();
    int     removeLast();

    void    reverse();

    void    traverse(void (*op)(T&)) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}
///Insert item before the first item in list
// return 0 if success
template<class T>
int L1List<T>::insert(int i,T &data){
    if(i<0){
        return -1;
    }
    else if(i=0){
        insertHead(T &data);
        return 0;
    }
    else if(i>_size){
        push_back(data);
        return 0;
    }
    else{
        L1Item<T>*temp=new L1Item<T>();
        temp=_pHead;
        for(int j=0;j<i;j++){
            temp=temp->pNext;
        }
        L1Item<T>*p=new L1Item<T>();
        p->data=data;
        p->pNext=temp->pNext;
        temp->pNext=p;
        _size++;
        return 0;
    }
}

///find item in List
// return by address
// return 1 if find
template<class T>
bool L1List<T>::find(int&index, T&data){
    L1Item<T>*temp=_pHead;
    int i=0;
    while(temp!=NULL){
        if(data==temp->data){
            index=i;
            return 1;
        }
        i++;
        temp=temp->pNext;        
    }
    return 0;
}

///get item at(i) in list
//return data at i
template<class T>
T L1List<T>::at(int i){
    L1Item<T>*temp=_pHead;
    for(int j=0;j<=i;j++){
        temp=temp->pNext;
    }
    return temp->data;
}

///implement operator []
//return data at[i];
template<class T>
T L1List<T>::operator[](int i){
    return at(i);
}

///Reverse the list
template<class T>
void L1List<T>::reverse(){
    L1Item<T>*pLoc=_pHead->pNext;
    L1Item<T>*R_head=new L1Item<T>();
    L1Item<T>*pPre=_pHead;
    R_head=pPre;
    R_head->pNext=NULL;
    pPre=pLoc;
    pLoc=pLoc->pNext;
    while(pLoc!=NULL){
        pPre->pNext=R_head;
        R_head=pPre;
        pPre=pLoc;
        pLoc=pLoc->pNext;
    }
    pPre->pNext=R_head;
    R_head=pPre;
    _pHead=R_head;
}

///

#endif //A01_LISTLIB_H
