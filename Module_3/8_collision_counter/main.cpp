#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <sstream>

using namespace std;

template <typename Hash>
int FindCollisions(const Hash& hasher, istream& text) {
    unordered_map<size_t, unordered_set<std::string, Hash>> base;
    std::string word;
    int count_ = 0;
    while (text >> word) {
        size_t h = hasher(word);
        auto it = base.insert({h, {word}});
        count_ += !it.second;
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