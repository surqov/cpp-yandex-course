#include "ini.h"
#include <algorithm>

using namespace std;

namespace ini {

Section& Document::AddSection(std::string name) {
    return sections_[name];
}

const Section& Document::GetSection(const std::string& name) const{
    static Section empty_ = {};
    if (sections_.count(name) == 0 || sections_.at(name).empty()) {
        return empty_;
    }
    return sections_.at(name);
}

std::size_t Document::GetSectionCount() const {
    return sections_.size();
}
    
std::size_t Document::GetSectionParamCount(const std::string&& name) const {
    return GetSection(name).size();
}
    
}

ini::Document ini::Load(std::istream& input){
    Document result;
    std::string line;
    std::string name;
    while (std::getline(input, line)) {
        if (line.empty() || line.find_first_not_of(' ') == std::string::npos) {
            continue;
        } else if (line[line.find_first_not_of(' ')] == '[') {
                name  = line.substr(1, line.find(']') - 1);
                ClearMyString(name);
                //std::cout << name << "\n";
                result.AddSection(name) = move(LoadSection(input));
        }
    }
    return result;
}
    
ini::Section ini::LoadSection(std::istream& input) {
    Section result;
    std::string line;
    while (input.peek() != '[' && std::getline(input, line)) {
        if (line.size() == 0 || line.find_first_not_of(' ') == std::string::npos) {
            continue;
        }
        std::string key = line.substr(0, line.find_first_of("="));
        std::string value = line.substr(line.find_first_of('=') + 1, line.size() - line.find_first_of('='));
        ClearMyString(key);
        ClearMyString(value);
        //std::cout << "|" << key << "|" << " : " <<  "|" << value << "|" << "\n";
        result[key] = value;     
    }
    return result;
}  

void ini::ClearMyString(std::string& key) {
    key = key.substr(key.find_first_not_of(" ["), key.find_last_not_of(' ') - key.find_first_not_of(' ') + 1);
}