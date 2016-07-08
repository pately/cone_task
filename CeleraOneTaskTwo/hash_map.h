#ifndef HASH_MAP_H_
#define HASH_MAP_H_
#include "hash_node.h"
#include <mutex>

/**
 * Simple HashMap Class template
 */
template <typename KEY, typename VALUE> class HashMap {
public:
    /**
     * @brief HashMap Constructor with predefined size
     * @param max_size initial max size of HashMap
     */
    explicit HashMap(const uint64_t max_size);

    /**  destructor
      */
    ~HashMap();

    /**
     * @brief size This function returns the size of hashmap
     * @return size of hashmap
     */
    uint64_t size();

    /**
     * @brief resize Using resize we can resize the hashmap
     * @param size new size
     * @return new size
     */
    uint64_t resize(const uint64_t size);

    /**
     * @brief insert This function can be used to insert value as a key value pair
     * @return 0=success 1=fail
     */
    uint64_t insert(const KEY&, const VALUE&);

    /**
     * @brief find This function can be used to look up in hashmap using key
     * @return pointer of Node. nullptr=no success
     */
    Node<KEY, VALUE> *find(const KEY&);

    /**
     * @brief erase This function can be used to erase an entry in hashmap using key
     * @return 0=success 1=fail
     */
    uint64_t erase(const KEY&);

    /**
     * @brief clear Clears hashmap
     */
    void clear();

    /**
     * @brief operator [] Allows up to access value of hashmap using []
     * @return value
     */
    VALUE &operator [](const KEY&);

 private:
    uint64_t HashValue(KEY);
    Node<KEY, VALUE>** head_;  // pointer to node array
    uint64_t size_;
    uint64_t max_size_;
    std::mutex mutex_lock_;  // used to protect shared data from being simultaneously accessed by multiple threads
};

#endif // HASH_MAP_H_
