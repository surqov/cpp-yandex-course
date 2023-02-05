#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>

namespace ini {

using Section = std::unordered_map<std::string, std::string>;

struct BadInputException;

class Document {
public:
    Section& AddSection(std::string name);
    const Section& GetSection(const std::string& name) const;
    std::size_t GetSectionCount() const;
    std::size_t GetSectionParamCount(const std::string&& name) const;

private:
    std::unordered_map<std::string, Section> sections_;
};

Document Load(std::istream& input);
    
Section LoadSection(std::istream& input);

void ClearMyStringPlease(std::string& input);
}