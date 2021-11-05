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

//Using 2 seperate functions
/*int count =1;

class Base{
    public:
    Base(){
        
    }
    void printEven(int end){
        while(count < end){
            m1.lock();
            if(0 == (count&1)){
                std::cout<<count++<<" "<<std::this_thread::get_id()<<std::endl;
            }
            m1.unlock();
        }
    }
    void printOdd(int end){
        while(count < end){
            m1.lock();
            if(count&1){
                std::cout<<count++<<" "<<std::this_thread::get_id()<<std::endl;
            }
            m1.unlock();
        }
    }
};

int main()
{
    Base obj;
    std::thread t1(&Base::printEven, &obj,10);
    std::thread t2(&Base::printOdd, &obj, 10);
    t1.join();
    t2.join();

    return 0;
}*/

//Output
/*1 140286979901184
2 140286988293888
3 140286979901184
4 140286988293888
5 140286979901184
6 140286988293888
7 140286979901184
8 140286988293888
9 140286979901184
10 140286988293888*/
