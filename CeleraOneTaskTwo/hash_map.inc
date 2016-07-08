#include "hash_map.h"
#include <stdio.h>
#include <iostream>

template <typename KEY, typename VALUE>
HashMap<KEY, VALUE>::HashMap(const uint64_t max_size):size_(max_size), max_size_(max_size){
    resize(max_size_);
}

template <typename KEY, typename VALUE>
HashMap<KEY, VALUE>::~HashMap() {

}

template <typename KEY, typename VALUE>
uint64_t HashMap<KEY, VALUE>::size() {
    return size_;
}

template <typename KEY, typename VALUE>
uint64_t HashMap<KEY, VALUE>::resize(const uint64_t size) {    
    std::lock_guard<std::mutex> guard(mutex_lock_);
    head_ = new Node<KEY, VALUE>*[size]();
    for (uint64_t i = 0; i < max_size_; i++) {
        Node<KEY, VALUE> *temp = new Node<KEY, VALUE>();
        head_[i] = temp;
    }
    return (size_ = size);
}

template <typename KEY, typename VALUE>
uint64_t HashMap<KEY, VALUE>::insert(const KEY &key, const VALUE &value) {
    const auto hv = HashValue(key);
    const auto p = hv % max_size_;
    {
        std::lock_guard<std::mutex> guard(mutex_lock_);
        for (auto ptr = head_[p]; ptr->getNext(); ptr = ptr->getNext())
            if (ptr->getNext()->getKey() == key) return 1;
        Node<KEY, VALUE> *node = new Node<KEY, VALUE>(key, value);
        node->setNext(head_[p]->getNext());
        head_[p]->setNext(node);
    }
    ++size_;
    return 0;
}

template <typename KEY, typename VALUE>
Node<KEY, VALUE> *HashMap<KEY, VALUE>::find(const KEY &key) {
    const auto hv = HashValue(key);
    const auto p = hv % max_size_;
    std::lock_guard<std::mutex> guard(mutex_lock_);
    for (Node<KEY, VALUE> *ptr = head_[p]; ptr->getNext(); ptr = ptr->getNext())
        if (ptr->getNext()->getKey() == key) return ptr->getNext();
    return nullptr;
}

template <typename KEY, typename VALUE>
void HashMap<KEY, VALUE>::clear() {
    size_ = 0;
    std::lock_guard<std::mutex> guard(mutex_lock_);
    for (uint64_t i = 0; i < max_size_; i++) {
        if (head_[i]->getNext()) delete head_[i]->getNext();
    }
}

template <typename KEY, typename VALUE>
uint64_t HashMap<KEY, VALUE>::erase(const KEY &key) {
    const auto hv = HashValue(key);
    const auto p = hv % max_size_;
    std::lock_guard<std::mutex> guard(mutex_lock_);
    for (auto ptr = head_[p]; ptr->getNext(); ptr = ptr->getNext())
        if (ptr->getNext()->getKey() == key) {
            Node<KEY, VALUE> *temp = ptr->getNext();
            ptr->setNext(temp->getNext());
            temp->setNext(nullptr);
            delete temp;
            --size_;
            return 0;
        }
    return 1;
}

template<typename KEY, typename VALUE>
uint64_t HashMap<KEY, VALUE>::HashValue(KEY key) {
    return static_cast<uint64_t>(key);
}

template<typename KEY, typename VALUE>
VALUE &HashMap<KEY, VALUE>::operator [] (const KEY& index) {
    Node<KEY, VALUE> *ptr = find(index);
    if (ptr != nullptr) return ptr->getValue();
    VALUE *value = new VALUE();
    insert(index, *value);
    ptr = find(index);
    return ptr->getValue();
}
