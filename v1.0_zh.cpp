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
        throw invalid_argument("具有此ID的学生已存在。");
    }
    students.push_back({id, name});
}

// 删除学生函数，如果学生ID不存在则抛出异常
void deleteStudent(int id) {
    auto it = findStudent(id);
    if (it == students.end()) {
        throw invalid_argument("具有此ID的学生不存在。");
    }
    students.erase(it);
}

// 修改学生信息函数，如果学生ID不存在则抛出异常
void modifyStudent(int id, const string& newName) {
    auto it = findStudent(id);
    if (it == students.end()) {
        throw invalid_argument("具有此ID的学生不存在。");
    }
    it->name = newName;
}

// 随机选择一个学生并输出其信息
void randomPick() {
    if (students.empty()) {
        cout << "没有学生可供选择。" << endl;
        return;
    }
    int index = rand() % students.size();
    cout << "随机挑选的学生：" << students[index].name << " (ID: " << students[index].id << ")" << endl;
}

// 显示所有学生信息
void displayStudents() {
    if (students.empty()) {
        cout << "没有学生。" << endl;
        return;
    }
    for (const auto& student : students) {
        cout << "ID: " << student.id << ", 名字: " << student.name << endl;
    }
}

// 主函数，提供用户交互界面
int main() {
    int choice, id;
    string name;

    srand(time(0)); // 只在开始时进行一次随机数种子初始化

    while (true) {
        cout << "1. 添加学生\n2. 删除学生\n3. 修改学生\n4. 随机挑选\n5. 显示所有学生\n6. 退出\n";
        cout << "输入你的选择： ";
        if (!(cin >> choice)) {
            cerr << "输入无效。请输入一个数字。" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    cout << "输入ID: ";
                    if (!(cin >> id)) {
                        cerr << "输入无效。请输入一个数字。" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    cout << "输入名字: ";
                    cin >> name;
                    addStudent(id, name);
                    break;
                case 2:
                    cout << "输入要删除的ID：";
                    if (!(cin >> id)) {
                        cerr << "输入无效。请输入一个数字。" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    deleteStudent(id);
                    break;
                case 3:
                    cout << "输入要修改的ID：";
                    if (!(cin >> id)) {
                        cerr << "输入无效。请输入一个数字。" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    cout << "输入新的名字：";
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
                    cout << "选择无效。请重试。" << endl;
            }
        } catch (const invalid_argument& e) {
            cerr << "错误：" << e.what() << endl;
        }
    }
}