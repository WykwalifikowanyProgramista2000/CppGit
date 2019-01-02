#ifndef UNIVERSITY_HPP_
#define UNIVERSITY_HPP_
#include <iostream>

enum class PackageType {
  Standard, Premium
};

class University {
  private:
    int _id;
    std::string _name;
    PackageType _packageType;
  public:
    University(int id, std::string name, PackageType packageType) :
        _id(id), _name(name), _packageType(packageType) {
    }
    PackageType getPackageType() {
      return _packageType;
    }
};

#endif /* UNIVERSITY_HPP_ */
