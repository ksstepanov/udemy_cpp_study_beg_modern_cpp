#include "stl_set_map_hash.h"
#include <set>
#include <functional>
#include <iostream>

#include <map>
#include <unordered_set>
#include <algorithm>
#include "integer.h"
#include <filesystem>
#include <fstream>

#include <list>
#include <deque>
#include <vector>


void test_stl_set(void)
{
    // by default sorts in acsending order:
    std::set<int> stl_set{1, 20, 2, 33, 444, 2, 10};
    stl_set.insert(122);
    for (auto &x : stl_set){
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    stl_set.erase(stl_set.begin()); //erase first element
    stl_set.erase(33); // erase element by value
    auto itr = stl_set.find(20);// find element with value 20. if not found 
    if (itr != stl_set.end()) {
        std::cout << "Element 20 found " << std::endl;
    } else {
        std::cout << "Element 20 not found " << std::endl;
    }


    std::set<int, std::greater<int>> stl_set2{1, 20, 2, 33, 444, 2, 10};
    stl_set2.insert(122);
    for (auto &x : stl_set2){
        std::cout << x << ", ";
    }
    std::cout << std::endl;

    std::cout << "Find all occurences in multiset: " << std::endl;
    std::multiset<int, std::greater<int>> stl_set3{1, 20, 2, 33, 444, 2, 10};
    stl_set3.insert(122);
    stl_set3.insert(122);
    stl_set3.insert(122);
    auto found = stl_set3.equal_range(122); // find all occurences of element with value=122 -> std::pair<begin, end>
    while (found.first != found.second) {
        std::cout << *found.first++ << ", ";
    }
    std::cout << std::endl;

}

void test_stl_map(void)
{
    std::cout << "STL::map " <<std::endl;
    std::map<int, std::string> pairs {
        {1, "Petya"},
        {2, "Kolya"},
        {3, "Katya"}
    };
    pairs.insert(std::pair<int, std::string>(4, "Vasya"));
    pairs.insert(std::make_pair(5, "Sasha"));

    pairs[4] = "Lena"; // use [] for insertion. Note avoid this for searching!
    for (auto &itr: pairs) {
        std::cout << "{" <<itr.first << ", " <<itr.second << "}, ";
    }
    std::cout << std::endl;
}

void test_unordered_set(void)
{
    std::cout << "STL::unordered_set " <<std::endl;
    std::unordered_set<std::string> s;
    s.insert("Vasya");
    s.insert("Petya");
    s.insert("Petya1");
    s.insert("Petya2");
    s.insert("Petya3");
    s.insert("Petya4");

    for (auto &x : s){
        std::cout << "#b"<<s.bucket(x) <<" - " << x << ", ";
    }
    std::cout << std::endl;
    std::cout << "Bucket_count: " <<s.bucket_count() << std::endl;
    std::cout << "Size: " <<s.size()<< std::endl;
    std::cout << "Load factor: " <<s.load_factor()<< std::endl; // lf = size/bucket_count
}

void std_hash(void)
{
    std::hash<std::string> h;
    std::string test {"Hello!"};
    std::cout << "Hash for " <<test <<" = " <<h(test) <<std::endl; 
}

class MyEmployee2
{
    std::string m_name;
    int m_id;
    std::string m_prog_lang;
    public:
    MyEmployee2(const std::string &name, int id, const std::string &prog_lang): m_name(name), m_id(id), m_prog_lang(prog_lang){};
    int get_id(void) const {
        return m_id;
    }

    const std::string &get_name(void) const {
        return m_name;
    }
    const std::string &get_prog_lang(void) const {
        return m_prog_lang;
    }
    friend std::ostream & operator <<(std::ostream &out, const MyEmployee2 &e);

    bool operator <(const MyEmployee2 &e) const{
        return m_id < e.m_id;
    }
};

std::ostream & operator <<(std::ostream &out, const MyEmployee2 &e) {
    out << "[MyEmployee2]: {" <<e.m_name <<", "<<e.m_id <<", "<<e.m_prog_lang <<"} "; 
    return out;
}

struct MyEmployee2Hash {
    size_t operator ()(const MyEmployee2 &e) const{
        auto s1 = std::hash<std::string>{}(e.get_name());
        auto s2 = std::hash<int>{}(e.get_id());
        auto s3 = std::hash<std::string>{}(e.get_prog_lang());
        return s1 ^ s2 ^ s3; // Note, better use hash combine: https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
    }
};

struct EmpEquality {
    bool operator () (const MyEmployee2 &e1, const MyEmployee2 &e2) const {
        return e1.get_id() == e2.get_id() && e1.get_name() == e2.get_name() && e1.get_prog_lang() == e2.get_prog_lang();
    }
};

void test_hash_with_employee(void) {
    std::unordered_set<MyEmployee2, MyEmployee2Hash, EmpEquality> ehash_set;
    ehash_set.insert(MyEmployee2("Vasya", 1, "C++"));
    ehash_set.insert(MyEmployee2("Petya", 2, "Python"));
    ehash_set.insert(MyEmployee2("katya", 3, "Java"));
    std::cout << "Employee hash set:" <<std::endl;
    for (auto &x : ehash_set){
        std::cout << x << ", " <<std::endl;
    }
    std::cout << std::endl;
}

struct EmpFilterByProgL{
    std::vector<int> m_ids;
    const std::string m_s;// {"Python"}

    // Question: should use && and std::forward in the line below?
    EmpFilterByProgL(const std::string &s): m_ids{}, m_s(s){};
    //EmpFilterByProgL(const EmpFilterByProgL &c):m_ids{c.m_ids}, m_s{c.m_s}{};
    //EmpFilterByProgL(std::string &&s): m_ids{}, m_s(std::forward<std::string>(s)){};
    void operator ()(const MyEmployee2 &emp){
        if (emp.get_prog_lang() == m_s){
            m_ids.push_back(emp.get_id());
        }
    }
    friend std::ostream & operator <<(std::ostream &out, const EmpFilterByProgL &efbp);
};

std::ostream & operator <<(std::ostream &out, const EmpFilterByProgL &efbp) {
    std::for_each(efbp.m_ids.begin(), efbp.m_ids.end(), [](int x){std::cout << x << ", ";}) ;
    return out;
}

void test_algorithms_1(void) {
    std::cout << "Use algorithms on user defined objects: sort" <<std::endl;
    std::vector<MyEmployee2> evector {
        MyEmployee2("Vasya", 4, "C++"),
        MyEmployee2("Petya", 0, "Python"),
        MyEmployee2("Katya", 1, "Java"),
        MyEmployee2("Lena", 2, "Rust"),
        MyEmployee2("Misha", 3, "Python")
    };
    std:sort(evector.begin(), evector.end());
    std::cout << "Employee sorted vector by id:" <<std::endl;
    for (auto &x : evector){
        std::cout << x << ", " <<std::endl;
    }
    std::cout << std::endl;
    
    std::sort(evector.begin(), evector.end(), [](const MyEmployee2 &e1, const MyEmployee2 &e2)->bool{return e1.get_name() < e2.get_name();});
    std::cout << "Employee sorted vector by Name:" <<std::endl;
    for (auto &x : evector){
        std::cout << x << ", " <<std::endl;
    }
    std::cout << std::endl;

    std::cout << "Use algorithms on user defined objects: count" <<std::endl;
    auto py_count = std::count_if(evector.begin(), evector.end(), [](const MyEmployee2 &e)-> bool{ return e.get_prog_lang() == "Python";});
    std::cout << "Employes with m_prog_lang=Python: " << py_count <<std::endl;

    auto itr_java = std::find_if(evector.begin(), evector.end(), [](const MyEmployee2 &e){return e.get_prog_lang() == "Java";});
    if (itr_java != evector.end()) {
        std::cout << "Found java prog: " << *itr_java <<std::endl;
    } else {
        std::cout << "Java prog: N/A" <<std::endl;
    }
    std::cout << "Print with for_each: " <<std::endl;
    std::for_each(evector.begin(), evector.end(), [](const MyEmployee2 &e){std::cout << e << ", " <<std::endl;});
    auto ids_for_python = std::for_each(evector.begin(), evector.end(), EmpFilterByProgL("Python"));//
    std::cout << "Employes with m_prog_lang=Python ids: " << ids_for_python <<std::endl;
}

void container_changes_182_plus(void) {
    std::cout << "Test emplace with vector" <<std::endl;
    std::vector<integer_move::Integer> v_int;
    v_int.push_back(5);
    v_int.emplace_back(10);
    v_int.emplace_back(20);
    std::for_each(v_int.begin(), v_int.end(), [](const integer_move::Integer &x){std::cout << x << ", ";}) ;


    // Vector shrink:
    std::cout << "Test shrink with vector" <<std::endl;
    std::vector<int> v_large;
    for (int i = 0; i < 100; i++)
        v_large.emplace_back(i);
    std::cout << "Large vector size/capacity = " << v_large.size() << "/" << v_large.capacity() <<std::endl;
    v_large.erase(v_large.begin(), v_large.end() - 10);
    v_large.shrink_to_fit(); // will make capacity same as the size
    std::cout << "Large vector size/capacity after erase = " << v_large.size() << "/" << v_large.capacity() <<std::endl;
}

static std::filesystem::path get_path(const std::string &basedir, const std::string &filename)
{
    std::filesystem::path p{basedir};
    p /= filename;
    return p;
}

void read_file_to_std_vector(void) {
    std::string basedir{};
    std::string filename{};
    std::filesystem::path p{get_path(basedir, filename)};
    std::cout << "Inputing from a file: " <<p.string() << std::endl;
    std::ifstream in{p.string()};
    if (! in.is_open()) {
        std::cout << "Wrong filename. No such file." << std::endl;
        return;
    }
    auto size = std::filesystem::file_size(p.string());
    std::vector<char> buf;
    buf.resize(size);
    in.read(buf.data(), size); // data() function to get raw buffer
    std::cout << buf.data() <<std::endl;
}

void test_std_erase(void)
{
    std::cout << "Test erase with list, vector, deque" <<std::endl;
    std::vector<int> v1{1, 2,3 , 4, 5, 2};
    std::deque<float>d1{1.0f, 2.0f};
    std::list<int>l1{2, 3, 4, 5};

    std::erase(v1, 2);
    std::erase(d1, 2);
    std::erase(l1, 2);
    auto printer = [](auto &&x){std::cout << x <<", ";};
    std::for_each(v1.begin(), v1.end(), printer);
    std::cout <<std::endl;

    std::for_each(d1.begin(), d1.end(), printer);
    std::cout <<std::endl;

    std::for_each(l1.begin(), l1.end(), printer);
    std::cout <<std::endl;

}

void test_emplace_with_std_set(void) {
    std::cout << "Test emplace with set" <<std::endl;
    std::set<std::string> sset;
    sset.emplace("New_str");
    sset.emplace("New_str2");
    sset.emplace_hint(sset.begin(), "New_str3"); // if you know that new element should be
    // inserted close to some iterator position, this is faster than just emplace

    auto printer = [](auto &&x){std::cout << x <<", ";};
    std::for_each(sset.begin(), sset.end(), printer);
    std::cout <<std::endl;

    //check that element exists in the container:
    auto it = sset.find("New_str");
    if (it != sset.end()) {
        std::cout << "found element with set.find" << std::endl;
    }

    bool found = sset.contains("New_str");
    if (found) {
        std::cout << "found element with std::contains" << std::endl;
    }

    // Change value of existing element: - this is not possible, because it disturb the order of the tree
    /*
    auto it = sset.find("New_str");
    if (it != sset.end()) {
        auto &actual_string = *it;
        actual_string[0] = 'C';
    }
    */
    auto it1 = sset.find("New_str");
    if (it1 != sset.end()) {
        auto actual_string = *it1; // create a copy. If type is copybale
        actual_string[0] = 'O';
        actual_string[1] = 'l';
        actual_string[2] = 'd';
        sset.erase(it1);
        sset.insert(actual_string);
    }
    std::for_each(sset.begin(), sset.end(), printer);
    std::cout <<std::endl;

    // Change value : c++17 way:
    auto change_node = sset.extract("New_str2");
    change_node.value()[0] = 'O';
    change_node.value()[1] = 'l';
    change_node.value()[2] = 'd';
    sset.insert(std::move(change_node)); // Note: auto change_node is not copiable
    std::for_each(sset.begin(), sset.end(), printer);
    std::cout <<std::endl;
}

void test_stl_set_map_hash(void)
{
    //test_stl_set();
    //test_stl_map();
    //test_unordered_set();
    //std_hash();
    //test_hash_with_employee();
    //test_algorithms_1();
    container_changes_182_plus();
    test_std_erase();
    test_emplace_with_std_set();
}