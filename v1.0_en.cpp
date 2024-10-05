//written by HelloWorld05
//这个程序是一个简单的学生随机名字选择器。
// version 1.0

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept> // 用于错误处理
#include <limits>    // 用于清除输入缓冲区

using namespace std;

// 学生结构体，包含学生ID和姓名
struct Student {
    int id;
    string name;
};

// 全局变量，存储所有学生的向量
vector<Student> students;

// 查找学生函数，返回指向学生的迭代器，如果不存在则返回end()
auto findStudent(int id) {
    return find_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; });
}

// 添加学生函数，如果学生ID已存在则抛出异常
void addStudent(int id, const string& name) {
    if (findStudent(id) != students.end()) {
        throw invalid_argument("Student with this ID already exists.");
    }
    students.push_back({id, name});
}

// 删除学生函数，如果学生ID不存在则抛出异常
void deleteStudent(int id) {
    auto it = findStudent(id);
    if (it == students.end()) {
        throw invalid_argument("Student with this ID does not exist.");
    }
    students.erase(it);
}

// 修改学生信息函数，如果学生ID不存在则抛出异常
void modifyStudent(int id, const string& newName) {
    auto it = findStudent(id);
    if (it == students.end()) {
        throw invalid_argument("Student with this ID does not exist.");
    }
    it->name = newName;
}

// 随机选择一个学生并输出其信息
void randomPick() {
    if (students.empty()) {
        cout << "No students to pick from." << endl;
        return;
    }
    int index = rand() % students.size();
    cout << "Randomly picked student: " << students[index].name << " (ID: " << students[index].id << ")" << endl;
}

// 显示所有学生信息
void displayStudents() {
    if (students.empty()) {
        cout << "No students available." << endl;
        return;
    }
    for (const auto& student : students) {
        cout << "ID: " << student.id << ", Name: " << student.name << endl;
    }
}

// 主函数，提供用户交互界面
int main() {
    int choice, id;
    string name;

    srand(time(0)); // 只在开始时进行一次随机数种子初始化

    while (true) {
        cout << "1. Add Student\n2. Delete Student\n3. Modify Student\n4. Random Pick\n5. Display Students\n6. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cerr << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    cout << "Enter ID: ";
                    if (!(cin >> id)) {
                        cerr << "Invalid input. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    cout << "Enter Name: ";
                    cin >> name;
                    addStudent(id, name);
                    break;
                case 2:
                    cout << "Enter ID to delete: ";
                    if (!(cin >> id)) {
                        cerr << "Invalid input. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    deleteStudent(id);
                    break;
                case 3:
                    cout << "Enter ID to modify: ";
                    if (!(cin >> id)) {
                        cerr << "Invalid input. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
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