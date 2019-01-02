#ifndef STUDENTSERVICE_HPP_
#define STUDENTSERVICE_HPP_

#include <string>
#include <vector>
#include <iostream>

#include "Student.hpp"
#include "StudentRepository.hpp"
#include "University.hpp"
#include "UniversityRepository.hpp"

class StudentService {
  private:
    StudentRepository _studentRepository;
    UniversityRepository _universityRepository;

  public:
    StudentService(StudentRepository studentRepository,
        UniversityRepository universityRepository) {
      _studentRepository = studentRepository;
      _universityRepository = universityRepository;
    }

    bool add(std::string emailAddress, int universityId) {
      std::cout << "Log: Start add student with email " << emailAddress
          << std::endl;

      if (emailAddress.empty()) {
        return false;
      }

      if (_studentRepository.exists(emailAddress)) {
        return false;
      }

      University university = _universityRepository.getById(universityId);

      Student student = new Student(emailAddress, universityId);

      if (university.getPackageType() == PackageType::Standard) {
        student.setMonthlyEbookAllowance(10);
      } else if (university.getPackageType() == PackageType::Premium) {
        student.setMonthlyEbookAllowance(10 * 2);
      }

      _studentRepository.add(student);

      std::cout << "Log: End add student with email " << emailAddress
          << std::endl;

      return true;
    }

    std::vector<Student> getStudentsByUniversity() {
      //...
    }

    std::vector<Student> getStudentsByCurrentlyBorrowedEbooks() {
      //...
    }
};

#endif /* STUDENTSERVICE_HPP_ */
