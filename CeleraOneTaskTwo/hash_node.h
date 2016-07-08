#ifndef HASH_NODE_H_
#define HASH_NODE_H_
#include <cstddef>

/**
 * Hash node Class template
 * Used to store and access key value pair
 */
template <typename KEY, typename VALUE>
class Node {
public:
    /**
     * @brief Node Constructor
     */
    Node(): key_(), value_(), next_(nullptr) {}
    Node(const KEY &key, const VALUE &value) :
    key_(key), value_(value), next_(nullptr) {
    }

    /** Node Destructor
      */
    ~Node() {
        if (next_) delete next_;
    }

    /**
     * @brief getKey
     * @return  key
     */
    KEY getKey() const {
        return key_;
    }

    /**
     * @brief setKey
     * @param key
     */
    void setKey(VALUE key) const {
        key_ = key;
    }

    /**
     * @brief getValue
     * @return value
     */
    VALUE& getValue() {
        return value_;
    }

    /**
     * @brief setValue
     * @param value
     */
    void setValue(VALUE value) {
        value_ = value;
    }

    /**
     * @brief getNext
     * @return pointer to the next node
     */
    Node *getNext() const {
        return next_;
    }

    /**
     * @brief setNext set pointer to the next node
     * @param next
     */
    void setNext(Node *next) {
        next_ = next;
    }

private:
    KEY key_;
    VALUE value_;
    Node *next_;
};
#endif // HASH_NODE_H_
