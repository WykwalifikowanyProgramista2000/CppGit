#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include <string>
#include "Email.hpp"

class Student {
  private:
    int _universityId;
    int _monthlyEbookAllowance = 0;
    int _currentlyBorrowedEbooks = 0;
	
  public:
    Student(std::string emailAddress, int universityId) {
      _emailAddress = emailAddress;
      _universityId = universityId;
    }

    int getUniversityId() {
      return _universityId;
	}

    int getMonthlyEbookAllowance() {
      return _monthlyEbookAllowance;
    }

    int getCurrentlyBorrowedEbooks() {
      return _currentlyBorrowedEbooks;
    }

    void setMonthlyEbookAllowance(int monthlyEbookAllowance) {
      _monthlyEbookAllowance = monthlyEbookAllowance;
    }
};

#endif /* STUDENT_HPP_ */
