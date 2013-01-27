#include <iostream>
#include <future>
#include <chrono>
#include "sync_ostream.hpp"

sync_ostream sync_cout(std::cout);

void print(int i)
{
    sync_cout << "Call " << i << " from thread " << 
        std::this_thread::get_id() << "\n"; 
    std::this_thread::sleep_for(
        std::chrono::milliseconds(10)
    );
}

void test_sync_ostream()
{
    auto f1 = std::async(std::launch::async, [] {
        sync_cout << "Start 1";
        for(int i = 0; i < 10; ++i)
        {
            print(i); 
        }});
            
    auto f2 = std::async(std::launch::async, [] {
        sync_cout << "Start 2";
        for(int i = 0; i < 10; ++i)
        {
            print(i); 
        }});
            
    f1.wait();
    f2.wait();
}

int main()
{  
    test_sync_ostream();
}

