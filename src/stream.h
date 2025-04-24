#ifndef STREAM_H_
#define STREAM_H_
#include <string>
#include <iostream>


class MyStream
{
    std::string m_filename;
    public:
    MyStream(const std::string &filename): m_filename(filename){
        std::cout <<"MyStream ()" <<std::endl;
    }
    ~MyStream() {
        std::cout <<"~MyStream ()" <<std::endl;
    }

    const std::string &get_name(void) {
        return m_filename;
    }
};

class MyInStream: virtual public MyStream
{
    std::istream &m_in;
public:
    MyInStream(const std::string &filename, std::istream &in): MyStream(filename), m_in(in){
        std::cout <<"MyInStream ()" <<std::endl;
    }
    ~MyInStream() {
        std::cout <<"~MyInStream ()" <<std::endl;
    }
    std::istream &operator >>(std::string &data) {
        m_in >> data;
        return m_in;
    }
};

class MyOutStream: virtual public MyStream
{
    std::ostream &m_out;
public:
    MyOutStream(const std::string &filename, std::ostream &o): MyStream(filename), m_out(o){
        std::cout <<"MyOutStream ()" <<std::endl;
    }
    ~MyOutStream() {
        std::cout <<"~MyOutStream ()" <<std::endl;
    }
    std::ostream &operator <<(const std::string &data) {
        m_out << data;
        return m_out;
    }
};

class MyIOStream: public MyInStream, public MyOutStream
{
    public:
    MyIOStream(const std::string &filename):
     MyInStream(filename, std::cin), MyOutStream(filename, std::cout), MyStream(filename){
        std::cout <<"MyInOutStream ()" <<std::endl;
    };
    ~MyIOStream() {
        std::cout <<"~MyInOutStream ()" <<std::endl;
    }
};

void test_multiple_inheritance(void);

#endif /* STREAM_H_ */