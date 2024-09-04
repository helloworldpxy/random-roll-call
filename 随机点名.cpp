#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept> // 用于错误处理
 
using namespace std;
 
// 学生结构体，包含学生ID和姓名
struct Student {
    int id;
    string name;
};
 
// 全局变量，存储所有学生的向量
vector<Student> students;
 
// 添加学生函数，如果学生ID已存在则抛出异常
void addStudent(int id, const string& name) {
    for (const auto& student : students) {
        if (student.id == id) {
            throw invalid_argument("Student with this ID already exists.");
        }
    }
    students.push_back({id, name});
}
 
// 删除学生函数，如果学生ID不存在则抛出异常
void deleteStudent(int id) {
    auto it = remove_if(students.begin(), students.end(), [id](const Student& s) {
        return s.id == id;
    });
    if (it != students.end()) {
        students.erase(it, students.end());
    } else {
        throw invalid_argument("Student with this ID does not exist.");
    }
}
 
// 修改学生信息函数，如果学生ID不存在则抛出异常
void modifyStudent(int id, const string& newName) {
    for (auto& student : students) {
        if (student.id == id) {
            student.name = newName;
            return;
        }
    }
    throw invalid_argument("Student with this ID does not exist.");
}
 
// 随机选择一个学生并输出其信息
void randomPick() {
    if (students.empty()) {
        cout << "No students to pick from." << endl;
        return;
    }
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    int index = rand() % students.size();
    cout << "Randomly picked student: " << students[index].name << " (ID: " << students[index].id << ")" << endl;
}
 
// 显示所有学生信息
void displayStudents() {
    for (const auto& student : students) {
        cout << "ID: " << student.id << ", Name: " << student.name << endl;
    }
}
 
// 主函数，提供用户交互界面
int main() {
    int choice, id;
    string name;
 
    while (true) {
        cout << "1. Add Student\n2. Delete Student\n3. Modify Student\n4. Random Pick\n5. Display Students\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
 
        try {
            switch (choice) {
                case 1:
                    cout << "Enter ID: ";
                    cin >> id;
                    cout << "Enter Name: ";
                    cin >> name;
                    addStudent(id, name);
                    break;
                case 2:
                    cout << "Enter ID to delete: ";
                    cin >> id;
                    deleteStudent(id);
                    break;
                case 3:
                    cout << "Enter ID to modify: ";
                    cin >> id;
                    cout << "Enter new Name: ";
                    cin >> name;
                    modifyStudent(id, name);
                    break;
                case 4:
                    randomPick();
                    break;
                case 5:
                    displayStudents();
                    break;
                case 6:
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}