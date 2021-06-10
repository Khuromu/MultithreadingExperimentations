#include "Multithread.h"

/* Simple Print the number of threads on the machine */
void Multithread::PrintMachineThreadCount()
{
    const unsigned int nbThreads = std::thread::hardware_concurrency();

    std::cout << "Number of threads on this hardware: " << nbThreads << " threads" << std::endl;
}

/* Count Threads One by One */
void Multithread::PrintThreadCountOneByOne()
{
    const unsigned int nbThreads = std::thread::hardware_concurrency();

    for (unsigned int i = 0; i < nbThreads; i++)
    {
         countTest = countTest + 1;
         std::cout << "Thread Count:" << countTest << "\n" << std::endl;
    }
}

/* Count Threads One by One with MUTEX */
void Multithread::PrintMutexThreadCountOneByOne()
{
    const unsigned int nbThreads = std::thread::hardware_concurrency();

    for (unsigned int i = 0; i < nbThreads; i++)
    {
        mainMutex.lock();
        countTest = countTest + 1;
        std::cout << "Thread Count:" << countTest << "\n" << std::endl;
        mainMutex.unlock();
    }
}

/* Count Threads One By One With LOCK_GUARD */
void Multithread::PrintLockThreadCountOneByOne()
{
    const unsigned int nbThreads = std::thread::hardware_concurrency();

    for (unsigned int i = 0; i < nbThreads; i++)
    {
        std::lock_guard<std::mutex> lockGuard(mainMutex); //lock_guard: locks mutex at constructor and unlocks at destructor
        countTest = countTest + 1;
        std::cout << "Thread Count:" << countTest << "\n" << std::endl;
    }
}

/* Redo of printcount and printcount one by one with the use of condition variable */
void Multithread::PrimaryPrintThreadIDCondVar()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Thread ID:" << std::this_thread::get_id() << "\n" << std::endl;
    std::lock_guard<std::mutex> guard(mainMutex);
    bIsSync = true;
    condVar.notify_one();
}

void Multithread::SecondaryPrintThreadCountCondVar()
{
    countTest = countTest + 1;
    std::cout << "Thread Count FIRST:" << countTest << "\n" << std::endl;

    std::unique_lock<std::mutex> mlock(mainMutex);
    condVar.wait(mlock, std::bind(&Multithread::bIsSync, this));
    std::cout << "Thread Count SECOND:" << countTest << "\n" << std::endl;
}


/* Print Text with a static function */
void Multithread::StaticThreadFuncPrintText(std::string sample)
{
    for (int i = 0; i < 5; ++i)
        std::cout << sample << "from static: " << i << std::endl;
}

/* Print Text with a non-static function */
void Multithread::ThreadFuncPrintText(std::string sample)
{
    for (int i = 0; i < 5; ++i)
        std::cout << sample << "from non static: " << i << std::endl;
}


/* Grab data asynchronously */
std::string Multithread::FetchFirstStrAsync(std::string getStr)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return "From First: " + getStr;
}

std::string Multithread::FetchSecondStrAsync(std::string getStr)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return "From Second: " + getStr;
}