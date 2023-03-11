#include "people.h"

using namespace std;

Person::Person(const string& name, int age, Gender gender) 
    : _name(name)
    , _age(age)
    , _gender(gender) {
    }

const std::string& Person::GetName() const {
    if (!(_name.size())) {
        throw std::logic_error("Not implemented"s);
    }
    return _name;
}

int Person::GetAge() const {
    return _age;
}

Gender Person::GetGender() const {
    return _gender;
}

Programmer::Programmer(const string& name, int age, Gender gender) 
    : Person(name, age, gender) {
}

void Programmer::AddProgrammingLanguage(ProgrammingLanguage language) {
    _languages.insert(language);
}

bool Programmer::CanProgram(ProgrammingLanguage language) const {
    return _languages.find(language) != _languages.end();
}

Worker::Worker(const string& name, int age, Gender gender)
    : Person(name, age, gender) {
}

void Worker::AddSpeciality(WorkerSpeciality speciality) {
    _specialities.insert(speciality);
}

bool Worker::HasSpeciality(WorkerSpeciality speciality) const {
    return _specialities.find(speciality) != _specialities.end();
}