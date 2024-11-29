#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

class Subject;
class Marks {
public:
    int course_mark[7];  // Array to hold marks for theory, IT, and term work
    string type_of_marks[7] = {"Theory", "IT", "Term Work","Practical","Oral","Grade","Grade Point"};  // Types of marks
    int total_max_marks,total_marks_obtained;  // Maximum total marks for the subject

    void input_marks() {
        cout << "Enter the maximum total marks for the subject: ";
        cin >> total_max_marks;

        total_marks_obtained = 0;
        for (int i = 0; i <5;  i++) {
            cout << "Enter marks obtained in " << type_of_marks[i] << ": ";
            cin >> course_mark[i];
            total_marks_obtained += course_mark[i];
        }

        while (total_marks_obtained > total_max_marks) {
            cout << "Invalid! The total marks cannot exceed " << total_max_marks << ". Enter again:\n";
            total_marks_obtained = 0;
            for (int i = 0; i < 5; i++) {
                cout << "Enter marks obtained in " << type_of_marks[i] << ": ";
                cin >> course_mark[i];
                total_marks_obtained += course_mark[i];
            }
        }
    }

    void display_marks() const {
        cout << "Total Maximum Marks: " << total_max_marks << endl;
        float total_obtained = 0;
        for (int i = 0; i < 3; i++) {
            cout << "Marks for " << type_of_marks[i] << ": " << course_mark[i] << endl;
            total_obtained += course_mark[i];
        }
        cout << "Total Marks Obtained: " << total_obtained << " / " << total_max_marks << endl;
    }

    float getTotalMarksObtained() const {
        float total_obtained = 0;
        for (int i = 0; i < 5; i++) {
            if(course_mark[i]>=0)
            total_obtained += course_mark[i];
        }
        return total_obtained;
    }
};

// Class for subjects, inherits from Marks
class Subject : public Marks {
public:
    string name;
    string code;
    int credits;
    int GradePoint;
    char grade[2];

    Subject() : credits(0), name("undefined"), code("undefined") {}

    int inputSubject() {
        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter course code: ";
        getline(cin, code);
        cout << "Enter credits for the subject: ";
        cin >> credits;
        input_marks();
        gradePoint(total_marks_obtained);
        return credits;
    }
    void gradePoint(float mark) {
        float per = (mark/total_max_marks)*100;
        if(per>=90){
            GradePoint=10;
            strcpy(grade,"O");
        }
        else if(per>=80){
            GradePoint=9;
            strcpy(grade,"A+");
        }
        else if(per>=70){
            GradePoint=8;
            strcpy(grade,"A");
        }
        else if(per>=60){
            GradePoint=7;
            strcpy(grade,"B");
        }
        else if(per>=50){
            GradePoint=6;
            strcpy(grade,"C");
        }
        else if(per>=40){
            GradePoint=5;
            strcpy(grade,"D");
        }
        else if(per>=30){
            GradePoint=4;
            strcpy(grade,"E");
        }
        else{
            GradePoint=0;
            strcpy(grade,"F");
        }
    }
    void displaySubject() const {
        cout << "Subject: " << name << " (Code: " << code << ")" << endl;
        display_marks();
        cout << "Credits: " << credits << endl;
    }
};

// Class to represent a semester
class Semester {
public:
    int subjectCount,totalcredits;
    string semesterName;
    Subject subjects[10];  // Assuming a maximum of 10 subjects per semester

    Semester() : subjectCount(0) , totalcredits(0) {}

    void inputSemesterDetails(const string& semName) {
        semesterName = semName;
        cout << "Enter number of subjects in " << semName << ": ";
        cin >> subjectCount;
        for (int i = 0; i < subjectCount; i++) {
            cout << "\nEntering details for subject " << (i + 1) << ":\n";
            totalcredits+=subjects[i].inputSubject();
        }
    }

    void displaySemester() const {
        cout << "Semester: " << semesterName << endl;
        for (int i = 0; i < subjectCount; i++) {
            subjects[i].displaySubject();
        }
    }

    double calculateCGPA() const {
        double totalPoints = 0.0;
        int totalCredits = 0;

        for (int i = 0; i < subjectCount; i++) {
            double gradePoint = subjects[i].getTotalMarksObtained() / subjects[i].total_max_marks * 10; // Simplified CGPA logic
            totalPoints += gradePoint * subjects[i].credits;
            totalCredits += subjects[i].credits;
        }

        return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
    }
};

// Class to handle student result
class StudentResult {
public:
    string studentName, rollNo, branch;
    int semesterCount;
    Semester semesters[2];  // Assuming two semesters per academic year

    StudentResult() : semesterCount(2) {}

    void inputStudentDetails() {
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, studentName);
        cout << "Enter roll number: ";
        getline(cin, rollNo);
        cout << "Enter branch: ";
        getline(cin, branch);
    }

    void inputSemesterDetails() {
        for (int i = 0; i < semesterCount; i++) {
            semesters[i].inputSemesterDetails("Semester " + to_string(i + 1));
        }
    }

    void displayStudentDetails() const {
        // Header section for the report card
        cout << setw(200) << setfill('_') << "" << endl;  // Top line
        cout << setfill(' ') << "|" << setw(113) << "\e[1mGovernment of Goa\e[0m" << setw(94) << "|" << endl; // Centered heading
        cout << left << "|" << setw(199) << right << "|" << endl;  // Empty line
        cout << setfill(' ') << left << "|" << setw(118) <<right<< "\e[1mGoa College Of Engineering\e[0m" << setw(89) << right << "|" << endl;  // College name
        cout << setfill(' ') << "|" << setw(115) << "\e[1mFarmaguddi Ponda Goa\e[0m" << setw(92) << "|" << endl;  // College address
        // cout << setw(200) << setfill('_') << "" << endl;  // Bottom line
        cout<<"|"<<setw(199)<<setfill('_')<<right<<"|"<<endl;
        // Student details
        cout << "|" << setw(6) << left << "\e[1mName: \e[0m" << setw(192) <<setfill(' ')<< left << studentName << "|" << endl;  // Student name
        cout << "|" << setw(13) << left << "\e[1mRoll Number: \e[0m" << setw(185) <<setfill(' ')<< left << rollNo << "|" << endl;  // Roll number
        cout << "|" << setw(9) << left << "\e[1mProgram: \e[0m" << setw(189) <<setfill(' ')<< left << branch << "|" << endl;  // Branch/Program
        // cout<<"|"<<setw(199)<<setfill('_')<<right<<"|"<<endl;

        // Iterate over each semester to display results
        for (int semIdx = 0; semIdx < semesterCount; semIdx++) {
            cout<<"|"<<setw(199)<<setfill('_')<<right<<"|"<<endl;
            cout << setfill(' ') << "|" << setw(118) <<right<< "\e[1mExamination: " + semesters[semIdx].semesterName + "\e[0m" << setw(89) << "|" << endl;  // Semester title
            cout<<"|"<<setw(199)<<setfill('-')<<right<<"|"<<endl;

            // Header row for subjects and marks
            cout.fill(' ');
            cout << "|" << setw(13) << left << "Code" 
                << "|" << setw(53) << left << "Course" 
                << "|" << setw(11) << "Credit"
                << "|" << setw(11) << "Theory" 
                << "|" << setw(9) << "IT"
                << "|" << setw(13) << "Termwork"
                << "|" << setw(15) << "Theory Total" 
                << "|" << setw(15) << "Practical"
                << "|" << setw(11) << "Oral" 
                << "|" << setw(13) << "Total" 
                << "|" << setw(10) << "Grade" 
                << "|" << setw(13) << "Grade Point" << "|" << endl;
            cout<<"|"<<setw(199)<<setfill('_')<<right<<"|"<<endl;  // Line separator

            // Displaying each subject's marks
            for (int subIdx = 0; subIdx < semesters[semIdx].subjectCount; subIdx++) {
                const Subject& subject = semesters[semIdx].subjects[subIdx];
                cout.fill(' ');
                cout.precision(0);
                cout << "|" << setw(13) << left << subject.code 
                    << "|" << setw(53) << left << subject.name 
                    << "|" << setw(11) << subject.credits
                    << "|" << setw(11) << (subject.course_mark[0]>=0?to_string(subject.course_mark[0]):"NA") 
                    << "|" << setw(9) << (subject.course_mark[1]>=0?to_string(subject.course_mark[1]):"NA")
                    << "|" << setw(13) << (subject.course_mark[2]>=0?to_string(subject.course_mark[2]):"NA") // 
                    << "|" << setw(15) << subject.course_mark[0] + subject.course_mark[1] + subject.course_mark[2]
                    << "|" << setw(15) << (subject.course_mark[3]>=0?to_string(subject.course_mark[3]):"NA")
                    << "|" << setw(11) << (subject.course_mark[4]>=0?to_string(subject.course_mark[4]):"NA")
                    << "|" << setw(13) << subject.getTotalMarksObtained()
                    << "|" << setw(10) << subject.grade
                    << "|" << setw(13) << subject.GradePoint << "|" << endl;
                cout<<"|"<<setw(199)<<setfill('_')<<right<<"|"<<endl;  // Line separator
            }

            // Earned credits, SGPA, and status
            double sgpa = semesters[semIdx].calculateCGPA();
            cout.fill(' ');
            cout << "|" << setw(30) << right << "Earned Credits: " << setw(10) << left << semesters[semIdx].totalcredits
                << setw(30) << right << "SGPA: " << setw(10) << left << fixed << setprecision(2) << sgpa
                << setw(30) << right << "Status: " << setw(10) << left <<( sgpa > 4?"Pass":"Fail" )<< setw(79) << right << "|" << endl;
            // cout << setw(200) << setfill('_') << "" << endl;  // Line separator
        }
        double overallCGPA = 0;
        for (int i = 0; i < semesterCount; i++) {
            overallCGPA += semesters[i].calculateCGPA();
        }
        overallCGPA /= semesterCount;
        cout<<"|"<<setw(199)<<setfill('_')<<right<<"|"<<endl;
        // Overall CGPA calculation

        cout << "\nOverall CGPA: " << fixed << setprecision(2) << overallCGPA << endl;
    }


    // Save data to binary file
    void saveToFile() const {
        string filename = rollNo + ".bin";
        ofstream file(filename, ios::binary);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
        // Write student details
        file.write(reinterpret_cast<const char*>(&studentName), sizeof(studentName));
        file.write(reinterpret_cast<const char*>(&rollNo), sizeof(rollNo));
        file.write(reinterpret_cast<const char*>(&branch), sizeof(branch));

        // Write semester details
        for (int i = 0; i < semesterCount; i++) {
            file.write(reinterpret_cast<const char*>(&semesters[i].semesterName), sizeof(semesters[i].semesterName));
            file.write(reinterpret_cast<const char*>(&semesters[i].subjectCount), sizeof(semesters[i].subjectCount));

            // Write subjects details
            for (int j = 0; j < semesters[i].subjectCount; j++) {
                file.write(reinterpret_cast<const char*>(&semesters[i].subjects[j]), sizeof(semesters[i].subjects[j]));
            }
        }
        file.close();
    }

    // Edit marks with random file access
    void editMarks(const string& rollNo) {
        string filename = rollNo + ".bin";
        fstream file(filename, ios::in | ios::out | ios::binary);
        if (!file) {
            cout << "Error opening file for editing!" << endl;
            return;
        }

        int semesterIndex, subjectIndex;
        cout << "Enter the semester index (1 or 2): ";
        cin >> semesterIndex;
        semesterIndex--;

        cout << "Enter the subject index to edit: ";
        cin >> subjectIndex;
        subjectIndex--;

        streampos subjectPosition=sizeof(studentName)+sizeof(rollNo)+sizeof(branch);
        for(int i=0;i<semesterIndex;i++){
            subjectPosition+=sizeof(semesters[i].semesterName)+sizeof(semesters[i].subjectCount);
            for(int j=0;j<semesters[i].subjectCount;j++){
                subjectPosition+=sizeof(Subject);
            }
        }
        subjectPosition+=sizeof(semesters[semesterIndex].semesterName)+sizeof(semesters[semesterIndex].subjectCount);
        for(int i=0;i<subjectIndex;i++){
            subjectPosition+=sizeof(Subject);
        }
        file.seekp(subjectPosition);
        semesters[semesterIndex].subjects[subjectIndex].input_marks();
        file.write(reinterpret_cast<const char*>(&semesters[semesterIndex].subjects[subjectIndex]),sizeof(Subject));
        cout<<"Marks updated successfully!"<<endl;
        file.close();

    }
    void searchAndDisplayResult( string& rollNo) {
        string filename = rollNo + ".bin";
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "Error: No record found for roll number " << rollNo << "!" << endl;
            return;
        }

        // Read student details from the file
        file.read(reinterpret_cast<char*>(&studentName), sizeof(studentName));
        file.read(reinterpret_cast<char*>(&rollNo), sizeof(rollNo));
        file.read(reinterpret_cast<char*>(&branch), sizeof(branch));

        // Read semester details
        for (int i = 0; i < semesterCount; i++) {
            file.read(reinterpret_cast<char*>(&semesters[i].semesterName), sizeof(semesters[i].semesterName));
            file.read(reinterpret_cast<char*>(&semesters[i].subjectCount), sizeof(semesters[i].subjectCount));

            // Read subjects details
            for (int j = 0; j < semesters[i].subjectCount; j++) {
                file.read(reinterpret_cast<char*>(&semesters[i].subjects[j]), sizeof(semesters[i].subjects[j]));
            }
        }

        // Display the result details
        displayStudentDetails();
        file.close();
    }
        
    // edit branch to the file, without using seekp
    void updateBranchInFile(string& rollNo) {
        string filename = rollNo + ".bin";
        fstream file(filename, ios::in | ios::out | ios::binary);
        if (!file) {
            cout << "Error opening file for editing!" << endl;
            return;
        }
        // Read student details from the file
        file.read(reinterpret_cast<char*>(&studentName), sizeof(studentName));
        file.read(reinterpret_cast<char*>(&rollNo), sizeof(rollNo));
        file.read(reinterpret_cast<char*>(&branch), sizeof(branch));

        // Get new branch from user
        char* newBranch;
        newBranch = new char[30];
        cout << "Enter the updated branch: ";
        cin.ignore();  // Clear the input buffer
        cin.getline(newBranch,30);

        // Write the new branch to the file
        file.seekp(sizeof(studentName)+sizeof(rollNo),ios::beg);
        file.write(reinterpret_cast<const char*>(&newBranch), sizeof(newBranch));
        cout<<"Branch updated successfully!"<<endl;
        file.close();        
    }
};


int main() {
    StudentResult resultSystem;
    char choice;
    do {
        //make box for menu
        cout<<endl;
        cout<<"|"<<setfill('-')<<setw(51)<<right<<"|"<<endl;
        cout<<"|"<<setfill(' ')<<setw(51)<<right<<"|"<<endl;
        cout<<"|"<<setw(50)<<left<<"\e[1mStudent Result System\e[0m"<<setw(9)<<right<<"|"<<endl;
        cout<<"|"<<setfill(' ')<<setw(51)<<right<<"|"<<endl;
        cout<<"|"<<setw(50)<<left<<"1. Enter student details"<<setw(1)<<right<<"|"<<endl;
        cout<<"|"<<setw(50)<<left<<"2. Edit marks"<<setw(1)<<right<<"|"<<endl;
        cout<<"|"<<setw(50)<<left<<"3. Update branch"<<setw(1)<<right<<"|"<<endl;
        cout<<"|"<<setw(50)<<left<<"4. Search and display result"<<setw(1)<<right<<"|"<<endl;
        cout<<"|"<<setw(50)<<left<<"0. Exit"<<setw(1)<<right<<"|"<<endl;
        cout<<"|"<<setfill(' ')<<setw(51)<<right<<"|"<<endl;
        cout<<"|"<<setfill('-')<<setw(51)<<right<<"|"<<endl;
        cout<<endl;
        cout<<"Enter your choice: ";
        cin >> choice;
        string rollNo;
        switch (choice) {
            case '1':
                resultSystem.inputStudentDetails();
                resultSystem.inputSemesterDetails();
                resultSystem.saveToFile();
                break;
            case '2':
                cout << "Enter roll number to edit marks: ";
                cin >> rollNo;
                resultSystem.editMarks(rollNo);
                break;
            case '3':
                cout << "Enter roll number to append branch: ";
                cin >> rollNo;
                resultSystem.updateBranchInFile(rollNo);
                break;
            case '4':
                cout << "Enter roll number to search: ";
                cin >> rollNo;
                resultSystem.searchAndDisplayResult(rollNo);
                break;
            case '0':
                cout << "Exiting..." << endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
        cout<<"\nPress Enter to cotninue...";
        cin.ignore();
        cin.get();

        //clear screen
        cout << "\033[2J\033[1;1H";
    } while (1);

    return 0;
}
