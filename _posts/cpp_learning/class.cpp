#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Myclass {
public:
    Myclass(): m_age(0) {}
    Myclass(int age, string name) : m_age(age), m_name(name) {}

public:
    void get_age() {
        cout << "my age is " << m_age << endl;
        return;
    }

    void get_name() {
        cout << "my name is " << m_name << endl;
        return;
    }

    void set_age(int age);
    void set_name(string name);
    void dummy_update(int age, string name) {
        update(age, name);
    }

private:
    int m_age;
    string m_name;
    void update(int age, string name);
};

// Myclass::Myclass(): m_age(0) {}
// Myclass::Myclass(int age, string name): m_age(age), m_name(name) {}

void Myclass::set_age(int age) {
    m_age = age;
    return;
}

void Myclass::set_name(string name) {
    m_name = name;
    return;
}

void Myclass::update(int count, string name) {
    m_age += count;
    m_name += name;
}

class Newclass:Myclass {
public:
    void get_school();

private:
    string m_school;
    void set_school(string school);
};

void Newclass::set_school(string school) {
    m_school = school;
}

int main() {
    cout << "init Myclass!" << endl;
    Myclass me;
    Myclass my(0, "hust");
    cout << "now change my age and name!" << endl;
    me.set_age(100);
    me.set_name("liuagein");
    me.get_age();
    me.get_name();

    cout << "now update my age and name!" << endl;
    me.dummy_update(12, "hust");
    me.get_age();
    me.get_name();
    return 0;
}
