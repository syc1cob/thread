#include <iostream>
#include <mutex>
#include <thread>
#include <sstream>
#include <condition_variable>

std::mutex m1;
std::condition_variable cv;

void printOddEven(bool isOdd, int bound){
    std::unique_lock<std::mutex> ulock(m1);
    while(number < bound){
        cv.wait(ulock, [&isOdd](){ return (number&1) == isOdd;});
        std::cout<<number++<<" "<<std::this_thread::get_id()<<std::endl;
        cv.notify_one();
    }
}
int main()
{
    thread oddThread(printOddEven, true, 10);
    thread evenThread(printOddEven, false, 10);
    oddThread.join();
    evenThread.join();
    return 0;
}
