#include "strings.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>

#define MAX_STRLEN 62

/* 
C-style concat function: error prone and restricted in size
*/
int my_concat(const char* left, const char*right, char *res)
{
    int ret = -1;
    if (left != NULL and right != NULL and res != NULL) {
        if (strlen(left) + strlen(right) < MAX_STRLEN) {
            strcpy(res, left);
            strcat(res, right);
            ret = 0;
        }
    }

    return ret;
}

void test_c_strings(void)
{
    char firstname[MAX_STRLEN >> 1];
    char lastname[MAX_STRLEN >> 1];
    std::cout << "Enter firstname" << std::endl;
    //fgets(firstname, sizeof(firstname), stdin);
    std::cin.getline(firstname, MAX_STRLEN >> 1);
    std::cout << "Enter lastname" << std::endl;
    std::cin.getline(lastname, MAX_STRLEN >> 1);
    //fgets(lastname, sizeof(lastname), stdin);
    std::cout << "Entered: "<<firstname <<"("<<strlen(firstname)<<") "
                <<lastname <<"("<<strlen(lastname)<<")"
                << std::endl;
    char result[MAX_STRLEN + 1]; // +1 added for terminating character
    int res = my_concat(firstname, lastname, result);
    if (res == 0) {
        std::cout << "Result: " <<result << std::endl;
    } else {
        std::cout << "C struct concat error" << std::endl;
    }
}


std::string my_concat(const std::string &left, const std::string right)
{
    std::string res = left + right;
    return res;
}

std::string ToUpper(const std::string &str)
{
    std::string str_ret(str);
    for (auto i=0; i< str.length(); i++) {
        str_ret[i] = toupper(str[i]);
    }
    return str_ret;
}
std::string ToLower(const std::string &str)
{
    std::string str_ret(str);
    for (auto i=0; i< str.length(); i++) {
        str_ret[i] = tolower(str[i]);
    }
    return str_ret;
}

void test_cpp_strings(void)
{
    // 1. Initialization
    std::string hello{"Hello!"};
    // 2. Access
    std::cout << hello << " " << hello[0] << std::endl;
    std::string buf;
    std::cout << "Enter string" << std::endl;
    std::getline(std::cin, buf);
    std::cout <<"Entered "<< buf;
    // 3. Size
    std::cout <<" of length "<< buf.length() << std::endl;
    // 4. Access and concat
    std::cout <<"Concatenated "<< hello + buf << std::endl;;
    buf.insert(0, "++");
    std::cout <<"After insert "<< buf << std::endl;
    // 5. Removal
    buf.erase(0, 2);
    std::cout <<"After erase "<< buf << std::endl;
    // 6. Search
    auto pos = buf.find('W', 0);
    if (pos != std::string::npos) {
        std::cout <<"Found "<< 'W' << " at " <<pos << std::endl;
    } else {
        std::cout <<"Not Found "<< 'W' << std::endl;
    }


    // ==========================
    std::string firstname;
    std::string lastname;
    std::cout << "Enter firstname" << std::endl;
    //fgets(firstname, sizeof(firstname), stdin);
    std::getline(std::cin, firstname);
    std::cout << "Enter lastname" << std::endl;
    std::getline(std::cin, lastname);
    //fgets(lastname, sizeof(lastname), stdin);
    std::cout << "Entered: "<<firstname <<"("<<firstname.length()<<") "
                <<lastname <<"("<<lastname.length()<<")"
                << std::endl;

    auto result = my_concat(firstname, lastname);
    std::cout << "Result: " <<ToUpper(result) << std::endl;

    using namespace std::string_literals;
    auto mystr = "Hello"s;



}

void test_sstream(void)
{
    std::stringstream ss {"10 30 2355"};
    int a;
    //while (!ss.fail()) {
    while (ss >> a) {
        
        
        std::cout << a <<std::endl;
    }
    int aaa = std::stoi("100");
    std::cout << aaa <<std::endl;
}


/*
 The find function in std::string uses a case-sensitive search.
  Write a function that also performs a case insensitive search.
   Use an enum to decide between case-sensitive and case-insensitive search.
*/

enum class Case{SENSITIVE, INSENSITIVE};
    
size_t Find(
    const std::string &source,         //Source string to be searched
    const std::string &search_string,  //The string to search for
    Case searchCase = Case::INSENSITIVE,//Choose case sensitive/insensitive search
    size_t offset = 0 ) {                //Start the search from this offset
        //Implementation
    
        /*
        return position of the first character 
        of the substring, else std::string::npos
        */
       if (searchCase == Case::INSENSITIVE) {
        std::string search_lower {ToLower(search_string)};
        size_t source_idx = 0;
        int search_idx = 0;
        for (size_t source_idx = 0; source_idx < source.length(); source_idx++) {
            if (tolower(source[source_idx]) == search_lower[search_idx]) {
                search_idx++;
                if (search_idx == search_lower.length()) {
                    source_idx -= (search_idx - 1);
                    return source_idx;
                }
            } else {
                search_idx = 0;
            }
        }
        return std::string::npos;
        } else {
            return source.find(search_string, offset);
        }
}

/* 
Add one more function called FindAll, that returns the starting indices of all the found substrings in a target string.
 Return the indices in a vector. Support case sensitive/insensitive search.
*/
std::vector<int>
FindAll(
 const std::string &target,              //Target string to be searched
 const std::string &search_string,       //The string to search for
 Case searchCase = Case::INSENSITIVE,    //Choose case sensitive/insensitive search
 size_t offset = 0) {                    //Start the search from this offset
     //Implementation
 
    /*
    Return indices of found strings,
    else an empty vector
    */
   std::vector<int> positions;
   size_t start_offset = 0;
   size_t ret = 0;
   while (ret != std::string::npos) {
    ret = Find(target, search_string, searchCase, start_offset);
    if (ret != std::string::npos) {
        positions.push_back(ret);
        start_offset = ret + 1;
    }
   }
}

void test_strings(void)
{
    //test_c_strings();
    //test_cpp_strings();
    //test_sstream();
    auto pos = Find("AbracaDabra", "DAB", Case::INSENSITIVE, 0);
    std::cout << "Find result: " << pos <<std::endl;
}