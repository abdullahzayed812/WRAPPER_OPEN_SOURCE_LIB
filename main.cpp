#include <cctype>
#include <iostream>
#include <utility>
#include <vector>

class StudentGradesInfo {
 private:
  std::string studentId;
  std::vector<double> grades;
  std::vector<std::string> coursesNames;

  const double MAX_GRADE_PER_COURSE = 100.0;

  static int statisticsTotalPrints;

  std::string toLowerCase(const std::string& str) const {
    std::string result;

    for (int i = 0; i < str.size(); i++) {
      result += tolower(str[i]);
    }

    return result;
  }

  double adjustGrade(double grade) const {
    if (grade < 0) {
      return 0;
    } else if (grade > this->MAX_GRADE_PER_COURSE) {
      return this->MAX_GRADE_PER_COURSE;
    }

    return grade;
  }

 public:
  StudentGradesInfo(std::string id) : studentId(id) {}

  bool addGrade(double grade, const std::string& courseName) {
    grade = this->adjustGrade(grade);

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      if (this->toLowerCase(courseName) ==
          this->toLowerCase(this->coursesNames[i])) {
        return false;
      }
    }

    this->coursesNames.push_back(courseName);
    this->grades.push_back(grade);

    return true;
  }

  void printAllCourses() const {
    StudentGradesInfo::statisticsTotalPrints++;

    std::cout << "Grades for student id: " << this->studentId << "\n";

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      std::cout << "\t Course name: " << coursesNames[i]
                << "\t Grade: " << this->grades[i] << "\n";
    }
  }

  bool getCourseGradesInfo(int pos,
                           std::pair<std::string, double>& gradesInfo) const {
    if (pos < 0 || pos >= (int)this->coursesNames.size()) {
      gradesInfo = std::make_pair("", -1);
      return false;
    }

    gradesInfo = std::make_pair(this->coursesNames[pos], this->grades[pos]);
    return true;
  }

  std::pair<double, double> getTotalGradesSum() const {
    double sum = 0, total = 0;

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      sum += this->grades[i];
      total += this->MAX_GRADE_PER_COURSE;
    }

    return std::make_pair(sum, total);
  }

  std::string getStudentId() const { return this->studentId; }

  int getTotalCoursesCount() const { return this->coursesNames.size(); }
};

int StudentGradesInfo::statisticsTotalPrints = 0;

class StudentGradesInfoWrapper {
 private:
  StudentGradesInfo studentInfo;

 public:
  static int statisticsTotalPrint;
  static int statisticsTotalStudents;

  StudentGradesInfoWrapper(std::string studentId)
      : studentInfo(StudentGradesInfo(studentId)) {
    ++StudentGradesInfoWrapper::statisticsTotalStudents;
  }

  bool addGrade(double grade, const std::string& courseName) {
    return this->studentInfo.addGrade(grade, courseName);
  }

  void printAllCourses() const {
    ++StudentGradesInfoWrapper::statisticsTotalPrint;

    this->studentInfo.printAllCourses();
  }

  bool getCourseGradesInfo(int pos,
                           std::pair<std::string, double>& result) const {
    return this->studentInfo.getCourseGradesInfo(pos, result);
  }

  std::pair<double, double> getTotalGradesSum() const {
    return this->studentInfo.getTotalGradesSum();
  }

  std::string getStudentId() { return this->studentInfo.getStudentId(); }

  int getTotalCoursesCount() {
    return (int)this->studentInfo.getTotalCoursesCount();
  }
};

int StudentGradesInfoWrapper::statisticsTotalStudents = 0;
int StudentGradesInfoWrapper::statisticsTotalPrint = 0;

int main() {
  StudentGradesInfoWrapper st1("S001");
  st1.addGrade(80, "Math");
  st1.addGrade(90, "Programming 1");
  st1.addGrade(99, "Algorithms");

  st1.printAllCourses();

  std::pair<double, double> p = st1.getTotalGradesSum();
  std::cout << p.first << "/" << p.second << "\n";

  StudentGradesInfoWrapper st2("S002");
  st2.printAllCourses();
  st2.printAllCourses();
  st2.printAllCourses();

  std::cout << "Total Students: "
            << StudentGradesInfoWrapper::statisticsTotalStudents << "\n";
  std::cout << "Total Prints: "
            << StudentGradesInfoWrapper::statisticsTotalPrint << "\n";
}