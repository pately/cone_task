#include <iostream>
#include <map>
#include <chrono>

namespace {
const uint64_t KBigNumber = 123456789012345678;

/**
 * @brief The ExerciseOne class
 */
class ExerciseOne {
public:
    ExerciseOne() {}
    uint64_t Recursion(const uint64_t number) {
        const auto& handle = results_.find(number);
        if (handle != results_.end()) {
            return handle->second;
        }
        if(number < 2) {
            results_[number] = 1;
            return 1;
        }
        if ((number % 2) == 0) {
            if((number & (number - 1)) == 0){
                results_[number] = 1;
                return 1;
            }
            else{
                const auto answer = Recursion(number/2);
                results_[number] = answer;
                return answer;
            }
        }  else {
            const auto new_numer= number / 2;
            const auto answer = static_cast<uint64_t>(Recursion(new_numer) + Recursion(new_numer - 1));
            results_[number] = answer;
            return answer;
        }
    }
private:
    std::map<uint64_t, uint64_t> results_;
};
}  // namespace
int  main(int argc, char** argv) {
    using Clock = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
    const auto& t0 = Clock::now();

    ExerciseOne exercise_;
    const auto result = exercise_.Recursion(KBigNumber);

    const auto& ms = std::chrono::duration_cast<microseconds>(Clock::now() - t0);
    std::cout << "The result is : " << result
              << "\nTime Taken : " << ms.count() << " microseconds"<<std::endl;
    return 0;
}
