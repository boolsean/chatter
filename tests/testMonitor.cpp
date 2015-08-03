#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>
#include <map>



boost::condition        cond;
static boost::mutex     lock;


class Task {
public:

protected:


private:

};

static void signalLoop()
{
    std::cout << "hbLoop started" << std::endl;
    sleep(5);

    {
        boost::lock_guard<boost::mutex> guard(lock);
        cond.notify_one();
        std::cout << "hbLoop notify_one invoked" << std::endl;
    }
}

static void waitLoop()
{

}


int foo() {
    boost::lock_guard<boost::mutex> guard(lock);
    std::cout << "foo invoked" << std::endl;
    cond.wait(lock);
    std::cout << "foo out of wait" << std::endl;

    return 0;
}

int main()
{
    std::cout << "main starting thread" << std::endl;
    boost::thread hbThread(signalLoop);
    foo();

    std::cout << "main after foo" << std::endl;

    return 0;
}

