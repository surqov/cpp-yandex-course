#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <iterator>

using namespace std;

template <typename Hash>
int FindCollisions(const Hash& hasher, istream& text) {
    unordered_map<size_t, unordered_set<string>> base;
    std::string word;
    int count_ = 0;
    while (text >> word) {
       size_t h = hasher(word);
       auto [it, inserted] = base[h].insert(word);
       count_ += inserted && base[h].size() > 1;
    }
    return count_;
}

struct DummyHash {
    size_t operator()(const string&) const {
        return 42;
    }
};

int main() {
    DummyHash dummy_hash;
    hash<string> good_hash;
    
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(dummy_hash, stream) << endl;
    }
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(good_hash, stream) << endl;
    }
} 