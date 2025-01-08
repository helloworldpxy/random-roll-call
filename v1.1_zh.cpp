//written by HelloWorld05
//���������һ���򵥵�ѧ���������ѡ������
// version 1.1

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept> // ���ڴ�����
#include <limits>    // ����������뻺����

using namespace std;

// ѧ���ṹ�壬����ѧ��ID������
struct Student {
    int id;
    string name;
};

// ȫ�ֱ������洢����ѧ��������
vector<Student> students;

// ����ѧ������������ָ��ѧ���ĵ�����������������򷵻�end()
vector<Student>::iterator findStudent(int id) {
    return find_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; });
}

// ���ѧ�����������ѧ��ID�Ѵ������׳��쳣
void addStudent(int id, const string& name) {
    if (findStudent(id) != students.end()) {
        throw invalid_argument("���д�ID��ѧ���Ѵ��ڡ�");
    }
    students.push_back({id, name});
}

// ɾ��ѧ�����������ѧ��ID���������׳��쳣
void deleteStudent(int id) {
    auto it = findStudent(id);
    if (it == students.end()) {
        throw invalid_argument("���д�ID��ѧ�������ڡ�");
    }
    students.erase(it);
}

// �޸�ѧ����Ϣ���������ѧ��ID���������׳��쳣
void modifyStudent(int id, const string& newName) {
    auto it = findStudent(id);
    if (it == students.end()) {
        throw invalid_argument("���д�ID��ѧ�������ڡ�");
    }
    it->name = newName;
}

// ���ѡ��һ��ѧ�����������Ϣ
void randomPick() {
    if (students.empty()) {
        cout << "û��ѧ���ɹ�ѡ��" << endl;
        return;
    }
    int index = rand() % students.size();
    cout << "�����ѡ��ѧ����" << students[index].name << " (ID: " << students[index].id << ")" << endl;
}

// ��ʾ����ѧ����Ϣ
void displayStudents() {
    if (students.empty()) {
        cout << "û��ѧ����" << endl;
        return;
    }
    for (const auto& student : students) {
        cout << "ID: " << student.id << ", ����: " << student.name << endl;
    }
}

// �����û�����ĺ���
template<typename T>
bool getInput(T& input) {
    if (!(cin >> input)) {
        cerr << "������Ч��������һ�����֡�" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// ���������ṩ�û���������
int main() {
    int choice, id;
    string name;

    srand(static_cast<unsigned int>(time(0))); // ֻ�ڿ�ʼʱ����һ����������ӳ�ʼ��

    while (true) {
        cout << "1. ���ѧ��\n2. ɾ��ѧ��\n3. �޸�ѧ��\n4. �����ѡ\n5. ��ʾ����ѧ��\n6. �˳�\n";
        cout << "�������ѡ�� ";
        
        if (!getInput(choice)) {
            continue; // �ٴ�ѯ���û�����
        }

        try {
            switch (choice) {
                case 1:
                    cout << "����ID: ";
                    if (!getInput(id)) break;
                    cout << "��������: ";
                    cin >> name;
                    addStudent(id, name);
                    break;
                case 2:
                    cout << "����Ҫɾ����ID��";
                    if (!getInput(id)) break;
                    deleteStudent(id);
                    break;
                case 3:
                    cout << "����Ҫ�޸ĵ�ID��";
                    if (!getInput(id)) break;
                    cout << "�����µ����֣�";
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
                    cout << "ѡ����Ч�������ԡ�" << endl;
            }
        } catch (const invalid_argument& e) {
            cerr << "����" << e.what() << endl;
        }
    }
}
