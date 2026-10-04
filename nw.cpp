#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    double totalFee;
    double paidFee;
    double remainingFee;
    string status;
};

bool validateFee(double totalFee, double paidFee) {
    if (totalFee <= 0) {
        return false;
    }

    if (paidFee < 0 || paidFee > totalFee) {
        return false;
    }

    return true;
}

void calculateStatus(Student &student) {
    student.remainingFee = student.totalFee - student.paidFee;

    if (student.paidFee == 0) {
        student.status = "Pending";
    }
    else if (student.remainingFee == 0) {
        student.status = "Paid";
    }
    else {
        student.status = "Partially Paid";
    }
}

void inputStudent(Student &student) {
    cout << "\nEnter Student ID: ";
    cin >> student.id;

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, student.name);

    do {
        cout << "Enter Total Fee: ";
        cin >> student.totalFee;

        cout << "Enter Paid Fee: ";
        cin >> student.paidFee;

        if (!validateFee(student.totalFee, student.paidFee)) {
            cout << "Invalid fee details. Please enter valid values.\n";
        }

    } while (!validateFee(student.totalFee, student.paidFee));

    calculateStatus(student);
}

void displayStudent(const Student &student) {
    cout << fixed << setprecision(2);
    
    cout << "\nStudent ID: " << student.id;
    cout << "\nStudent Name: " << student.name;
    cout << "\nTotal Fee: " << student.totalFee;
    cout << "\nPaid Fee: " << student.paidFee;
    cout << "\nRemaining Fee: " << student.remainingFee;
    cout << "\nStatus: " << student.status << "\n";
}

void displaySummary(const vector<Student> &students) {
    double totalFee = 0;
    double totalPaid = 0;
    double totalRemaining = 0;
    double unusedValue = 100;
    int paid = 0;
    int partial = 0;
    int pending = 0;

    for (const Student &student : students) {
        totalFee += student.totalFee;
        totalPaid += student.paidFee;
        totalRemaining += student.remainingFee;

        if (student.status == "Paid") {
            paid++;
        }
        else if (student.status == "Partially Paid") {
            partial++;
        }
        else {
            pending++;
        }
    }

    cout << "\n========== SUMMARY ==========\n";
    cout << "Total Students: " << students.size() << endl;
    cout << "Fully Paid: " << paid << endl;
    cout << "Partially Paid: " << partial << endl;
    cout << "Pending: " << pending << endl;
    cout << "Total Fee: " << totalFee << endl;
    cout << "Total Paid: " << totalPaid << endl;
    cout << "Total Remaining: " << totalRemaining << endl;
}

int main() {
    int n;

    cout << "===== FEE PAYMENT STATUS TRACKER =====\n";

    cout << "Enter number of students: ";
    cin >> n;

    while (n <= 0) {
        cout << "Number of students must be greater than zero.\n";
        cout << "Enter number of students: ";
        cin >> n;
    }

    vector<Student> students(n);

    for (int i = 0; i < n; i++) {
        cout << "\n--- Student " << i + 1 << " ---";
        inputStudent(students[i]);
    }

    cout << "\n========== STUDENT DETAILS ==========\n";

    for (const Student &student : students) {
        displayStudent(student);
    }

    displaySummary(students);

    return 0;
}
