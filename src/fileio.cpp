#include "fileio.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

void test_raw_strings(void)
{
    std::string filename {R"(C:\temp\new_file.txt)"};
    std::string filename2 {R"MSG(C:\temp\new_file.txt("whatever!!!"))MSG"};
    std::cout << filename <<std::endl;
}

std::string test_path(void)
{
    std::filesystem::path p{R"(/home/konstantin/Projects/Udemy/Complete_modern_cpp/newfile.txt)"};
    if (p.has_filename()) {
        std::cout << p.filename() << std::endl;
    }

    // Loop over path entries:
    std::cout << "-----> Loop over path directories:" << std::endl;
    for (const auto &part : p) {
        std::cout << part << std::endl;
    }

    std::filesystem::directory_iterator begin_p{p.parent_path()};
    std::filesystem::directory_iterator end_p{};

    // Loop over directory content:
    std::cout << "-----> Loop over directory entries:" << std::endl;
    while (begin_p != end_p) {
        std::cout << *begin_p << std::endl;
        begin_p++;
    }
    return p.parent_path();
}

static std::filesystem::path get_path(const std::string &basedir, const std::string &filename)
{
    std::filesystem::path p{basedir};
    p /= filename;
    return p;
}

void test_output(const std::string &basedir, const std::string &filename)
{
    std::filesystem::path p{get_path(basedir, filename)};
    std::cout << "Outputing to a file: " <<p.string() << std::endl;
    std::ofstream out{p.string()};
    if (! out.is_open()) {
        std::cout << "Wrong filename. No such file." << std::endl;
        return;
    }
    std::string message {"Hello World!"};
    out << message <<std::endl;
    out << p.string() <<std::endl;
    for (char ch:message) {
        out.put(ch);
    }
    std::cout << "Current position of get pointer: "<<out.tellp() <<std::endl;
    //out.seekp(5);
    out.close();
}

void test_input(const std::string &basedir, const std::string &filename)
{
    std::filesystem::path p{get_path(basedir, filename)};
    std::cout << "Inputing from a file: " <<p.string() << std::endl;
    std::ifstream in{p.string()};
    //in.open(p.string()); - same
    if (! in.is_open()) {
        std::cout << "Wrong filename. No such file." << std::endl;
        return;
    }
    std::string message;
    std::cout << "Current position of get pointer: "<<in.tellg() <<std::endl;
    //in.seekg(5);
    in.seekg(-5, std::ios::end); // seek from the end (end -5)
    std::cout << "Current position of get pointer (+5): "<<in.tellg() <<std::endl;
    while (std::getline(in, message)) // in.eof()
    {
        std::cout << "Red: " <<message << std::endl;
    }
    if (in.good()) {
        std::cout << "Input finished. All I succesful." << std::endl;
    }
    in.clear(); // clear all the bit flags
    //in.setstate(std::ios::failbit);

    //char ch{};
    //while(in.get(ch))
    in.close();
}

void test_copy(const std::string &basedir, const std::string &filename_src, const std::string &filename_dst)
{
    std::filesystem::path src{get_path(basedir, filename_src)};
    std::filesystem::path dst{get_path(basedir, filename_dst)};
    std::ifstream in{src};
    if (! in.is_open()) {
        std::cout << "Wrong filename. No such file." << std::endl;
        return;
    }
    std::ofstream out{dst};
    if (! out.is_open()) {
        std::cout << "Wrong filename. No such file." << std::endl;
        return;
    }
    std::string message;
    while (std::getline(in, message)) // in.eof()
    {
        out <<message << std::endl;
    }
    in.close();
    out.close();
}

void test_bin(const std::string &basedir, const std::string &filename) {

    std::filesystem::path p{get_path(basedir, filename)};
    std::cout << "Outputing to a file: " <<p.string() << std::endl;
    std::ofstream out{p.string(), std::ios::binary|std::ios::out};
    if (! out.is_open()) {
        std::cout << "Wrong filename. No such file." << std::endl;
        return;
    }
    int val{1024};
    out.write((const char*)&val, sizeof(val));
    out.close(); 


    // read:
    std::ifstream in{p.string(), std::ios::binary|std::ios::in};
    //in.open(p.string()); - same
    if (! in.is_open()) {
        std::cout << "Wrong filename. No such file." << std::endl;
        return;
    }
    int red_val{0};
    in.read(( char*)&red_val, sizeof(red_val));
    std::cout << "Red from binary: " <<red_val << std::endl;
    in.close();
}

void test_fileio(void)
{
    test_raw_strings();
    const std::string basedir = test_path();
    std::cout << "Got basedir: " <<basedir << std::endl;
    test_output(basedir, "test_output.txt");
    test_input(basedir, "test_output.txt");

    std::filesystem::path cur_p{std::filesystem::current_path()};
    std::cout << "Got current path: " <<cur_p << std::endl;
    test_copy(basedir, "newfile.txt", "copy.txt");
    test_bin(basedir, "data.bin");
}