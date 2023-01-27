#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
#include <utility>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    if (step_size <= 1) {
        return;
    }
    vector<typename RandomIt::value_type> pool;
    pool.insert(pool.end(), std::make_move_iterator(first), std::make_move_iterator(last));
    int curr_pos = 0;
    while (!pool.empty()) {
        *(first++) = move(*(pool.begin() + curr_pos));
        pool.erase(pool.begin() + curr_pos);
        if (pool.empty()) {
            break;
        }
        curr_pos = (curr_pos + step_size - 1) % pool.size();
    }
}

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        assert(numbers_copy == numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        assert(numbers_copy == vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем
// об этом далее в нашем курсе

struct NoncopyableInt {
    int value;

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator==(const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator<<(ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<double> numbers;
    numbers.push_back({1.});
    numbers.push_back({2.});
    numbers.push_back({3.});
    numbers.push_back({4.});
    numbers.push_back({5.});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<double> expected;
    expected.push_back({1.});
    expected.push_back({3.});
    expected.push_back({5.});
    expected.push_back({4.});
    expected.push_back({2.});

    assert(numbers == expected);
}

int main() {
    TestIntVector();
    TestAvoidsCopying();
}