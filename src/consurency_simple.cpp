#include <thread>
#include <iostream>
#include <fstream>
#include "integer.h"
#include <future>
#include <chrono>
#include <list>

const auto n_chars = (1 << 10);

void long_writer(std::string &fname, integer_move::Integer &start) {
    std::cout << __func__ <<" started"  <<std::endl;
    const std::string filename {fname};
    std::ofstream out(filename, std::ios::out);
    if (!out.is_open()){
        std::cout << "Error opening file" <<std::endl;
        return;
    }
    const char base = 'a';
    constexpr int num_chars = static_cast<int>('z') - static_cast<int>('a');
    for (auto i = 0; i < n_chars; i++) {
        out << static_cast<char>(static_cast<int>(base) + (i + start.getVal()) % num_chars);
    };
    out.close();
    std::cout << __func__ <<" finished"  <<std::endl;
}

void test_simple_1(void) {
    std::cout << __func__ <<" started"  <<std::endl;
    integer_move::Integer s{10};
    std::string fname{"file.txt"};
    std::thread t(long_writer, std::ref(fname), std::ref(s));
    t.join();
    std::cout << __func__ <<" finished"  <<std::endl;
    
}

int long_sum(int x, int y){
    using namespace std::chrono_literals;
    const auto start = std::chrono::high_resolution_clock::now();

 
    
    std::this_thread::sleep_for(2s);
    
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Waited " << elapsed.count() << '\n';
    return x+y;
}

void test_simple_2_ret_vals(void) {
    std::cout << __func__ <<" started"  <<std::endl;
    std::packaged_task<int(int, int)> task_sum{long_sum};
    std::future<int> ft = task_sum.get_future();
    std::thread t{std::move(task_sum), 10, 20}; // move task_sum object into a thread and start
    //task_sum(10, 20); // Actual execution start if run the object in the main thread
    
    auto result = ft.get(); // t is blocked here
    std::cout << __func__ <<" finished with res: " <<result  <<std::endl;
    t.join();
}


std::list<int> shared_list{};
std::mutex m;
void producer(void)
{
    for (int i = 0; i < 1000; i++) {
        m.lock(); // this is bad: because if code before unlock throws an exception, there will be a dead lock
        shared_list.push_back(i);
        m.unlock();
    }
}

void producer_safe(void)
{
    for (int i = 0; i < 1000; i++) {
        std::lock_guard<std::mutex> lg(m);
        shared_list.push_back(i);
    }
}

void test_simple_mutex(void) {
    std::thread t1(producer_safe);
    std::thread t2(producer_safe);
    auto id1 = t1.get_id();
    auto id2 = t2.get_id();
    //auto nh = t1.native_handle(); // return linux pthread
    pthread_t nh = t1.native_handle(); // return linux pthread
    int res =  pthread_setname_np(/*pthread_t thread*/nh, "Thread1");
    auto n_cores = std::thread::hardware_concurrency(); // number of cores available on cpu
    t1.join();
    t2.join();
    std::cout << "Test_simple mutex tids["<<id1 <<", " << id2 <<"], ncores = "<<n_cores <<": count = " << shared_list.size() << std::endl;
}

int sum_task(int count) {
    using namespace std::chrono_literals;
    int sum{0};
    for (int i = 0; i < count; i++) {
        sum += i;
        std::this_thread::sleep_for(1ms);
    }
    return sum;
}

void test_async_task(void) {
    using namespace std::chrono_literals;
    std::future<int> f = std::async(std::launch::async, sum_task, 200);
    std::this_thread::sleep_for(1000ms);
    std:: cout << "waiting for result" << std::endl;
    auto res = f.get();
    std:: cout << "Result = " << res<< std::endl;
}

int sum_task_with_promise(std::promise<int> &p) {
    using namespace std::chrono_literals;
    auto f = p.get_future();
    try {
        auto count = f.get();
        int sum{0};
        for (int i = 0; i < count; i++) {
            sum += i;
            std::this_thread::sleep_for(1ms);
        }
        return sum;
    }catch (std::exception &ex) {
        std:: cout << "Caught exception: " << ex.what() <<  std::endl;
        return -1;
    }
}

void test_async_task_with_promise(void) {
    using namespace std::chrono_literals;
    std::promise<int> p;
    std::future<int> f = std::async(std::launch::async, sum_task_with_promise, std::ref(p));
    std::this_thread::sleep_for(1000ms);
    p.set_value(200);
    std:: cout << "waiting for result" << std::endl;
    auto res = f.get();
    std:: cout << "Result = " << res<< std::endl;
}

void test_async_task_with_promise_and_exception(void) {
    using namespace std::chrono_literals;
    std::promise<int> p;
    std::future<int> f = std::async(std::launch::async, sum_task_with_promise, std::ref(p));
    std::this_thread::sleep_for(1000ms);
    try {
        throw std::runtime_error("Test error");
        p.set_value(200);
        std:: cout << "waiting for result" << std::endl;
        auto res = f.get();
        std:: cout << "Result = " << res<< std::endl;
    } catch (std::exception &ex) {
        p.set_exception(std::make_exception_ptr(ex));
    }
    
}


void test_concurrency_simple(void)
{
    test_simple_2_ret_vals();
    test_simple_mutex();
    test_async_task();
    test_async_task_with_promise();
    test_async_task_with_promise_and_exception();
}