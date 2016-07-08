Exercise 2
==========
Implement a thread-safe hashmap including the following features:
1. Constructing the map with fixed table size given upfront.
2. Thread-safe support lookup, insertion, and deletion.
3. Do not use a global lock to ensure thread-safety: multiple writers should be able to access one instance of the map at the same time.
4. You are not allowed to use STL containers.
5. You may use all concurrency-related features in C++11 and C++14.
6. Please include a main program or unit test that checks that the map works.
7. Please explain in a short note your approach to thread-safety.
8. You will get bonus points for:
   - table resizing
   - genericity (not bound to specific types)
   - good test coverage


# Solution
## Linux build
For test coverage Google's C++ test framework is used. In order to build the project Google Test Libraries (https://github.com/google/googletest) must be installed on your Linux machine. Steps to make the project
* cd project_dir
* make
* use *make clean* of cleaning

# Notes
* table resizing can be done using resize function.
* std::thread is used for creating threads.
* std::mutex with std::lock_guard is used for ensuring thread-safety.
* std::lock_guard is used because it will lock only once on construction and unlock on destruction.
* test coverage is done using Google's C++ test framework.












