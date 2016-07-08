#include "hash_map.h"
#include "hash_map.inc"
#include <iostream>
#include <memory>
#include <thread>
#include <gtest/gtest.h>

namespace {
const int kInitialSize = 50;
const int kReSize = 100;
const int kLargeSample = 100000;
const int kLargeSampleByTwo = 50000;
const int kNumberOfThreads = 4;

void MultiInsert(HashMap<int, std::string>& hmap) {
    for (auto i = 0; i < kLargeSample; i++)
        hmap.insert(i, std::to_string(i));
}

void MultiErase(HashMap<int, std::string>& hmap) {
    for (auto i = 0; i < kLargeSampleByTwo; i++)
        hmap.erase(i);
}
}  // namespace

TEST(Create, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);
    EXPECT_EQ(kInitialSize, hash_map.size());
}

TEST(Resize, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);
    hash_map.resize(kReSize);
    EXPECT_EQ(kReSize, hash_map.size());
}

TEST(InsertSize, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);
    // check sizes
    hash_map.insert(2, "2");
    EXPECT_EQ(kInitialSize + 1, hash_map.size());
    hash_map.insert(3, "3");
    EXPECT_EQ(kInitialSize + 2, hash_map.size());
    hash_map.insert(4, "4");
    EXPECT_EQ(kInitialSize + 3, hash_map.size());
}

TEST(InsertValues, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);
    // check values
    hash_map.insert(2, "2");
    EXPECT_EQ("2", hash_map[2]);

    hash_map.insert(3, "3");
    EXPECT_EQ("3", hash_map[3]);

    hash_map.insert(4, "4");
    EXPECT_EQ("4", hash_map[4]);
}

TEST(InsertReplace, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);

    hash_map.insert(2, "2");
    hash_map[2] =  "222";
    EXPECT_EQ("222", hash_map[2]);

    hash_map.insert(3, "3");
    hash_map[3] =  "333";
    EXPECT_EQ("333", hash_map[3]);

    hash_map.insert(4, "4");
    hash_map[4] =  "444";
    EXPECT_EQ("444", hash_map[4]);
}


TEST(Erase, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);
    hash_map.insert(2, "2");
    hash_map.insert(3, "3");
    hash_map.insert(4, "4");
    EXPECT_EQ(kInitialSize + 3, hash_map.size());

    hash_map.erase(2);
    EXPECT_EQ(kInitialSize + 2, hash_map.size());
}

TEST(Clear, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);
    EXPECT_EQ(kInitialSize, hash_map.size());
    hash_map.insert(2, "2");
    hash_map.insert(3, "3");
    hash_map.insert(4, "4");

    hash_map.clear();
    EXPECT_EQ(0, hash_map.size());
}

TEST(Find, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);
    hash_map.insert(2, "2");
    hash_map.insert(3, "3");
    hash_map.insert(4, "4");

    const auto& handle = hash_map.find(2);
    ASSERT_TRUE(handle);
    if (handle) {
        EXPECT_EQ(2, handle->getKey());
        EXPECT_EQ("2", handle->getValue());
    }
}

TEST(MultiThread, HashMap) {
    HashMap<int, std::string> hash_map(kInitialSize);

    std::vector<std::thread> threads;

    auto  thread1= std::thread(MultiInsert, std::ref(hash_map));
    threads.emplace_back(std::move(thread1));
    EXPECT_EQ(1, threads.size());


    auto  thread2= std::thread(MultiErase, std::ref(hash_map));
    threads.emplace_back(std::move(thread2));
    EXPECT_EQ(2, threads.size());


    auto  thread3= std::thread(MultiInsert, std::ref(hash_map));
    threads.emplace_back(std::move(thread3));
    EXPECT_EQ(3, threads.size());


    auto  thread4= std::thread(MultiErase, std::ref(hash_map));
    threads.emplace_back(std::move(thread4));
    EXPECT_EQ(4, threads.size());

    std::cout << std::endl << "[          ] Wait for threads to complete " << std::endl;

    for (std::thread& thread : threads) {
        thread.join();
      }

    // OK to destroy now
    threads.clear();
    EXPECT_EQ(0, threads.size());
}
