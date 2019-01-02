#ifndef STUDENTREPOSITORY_HPP_
#define STUDENTREPOSITORY_HPP_

#include <string>

#include "Student.hpp"

class StudentRepository {
public:
    bool exists(std::string emailAddress);
    void add(Student student);
};



#endif /* STUDENTREPOSITORY_HPP_ */
