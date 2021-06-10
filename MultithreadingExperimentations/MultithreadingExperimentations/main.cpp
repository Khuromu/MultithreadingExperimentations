#include "Multithread.h"

    /* --- GLOBALS --- */
// For the use of vectors of threads
std::mutex mutexSample;
int countTest = 0;

/* --- For the use of vectors of threads --- */
void PrintLockDummy()
{
    std::lock_guard<std::mutex> lockGuard(mutexSample);
    countTest = countTest + 1;
    std::cout << "Thread Count:" << countTest << "\n" << std::endl;
}

/* --- For the use of promise --- */
void PromiseTestFunc(std::promise<int>* promiseVar)
{
    std::cout << "Future Thread OK" << std::endl;
    promiseVar->set_value(86);

    //*Every std::promise object has an associated std::future object, through which others can fetch the value set by promise
    //std::future<int> futureObj = promiseVar.get_future();
    //*Thread fetches the value set by other Thread in std::promise through std::future’s get function
    //int val = futureObj.get();
    //*If value is not yet set by other thread, this call will get blocked until other thread sets the value in promise object
    //promiseVar.set_value(45);
}

    /* MAIN */
int main()
{
    Multithread* multithreadObj = new Multithread();

    /* --- Simple Print the number of threads on the machine --- */
    multithreadObj->PrintMachineThreadCount();


    /* --- Count Threads One by One --- */
    //multithreadObj->PrintThreadCountOneByOne();


    /* --- Count Threads One by One with MUTEX --- */
    //multithreadObj->PrintMutexThreadCountOneByOne();


    /* --- Count Threads One By One With LOCK_GUARD --- */
    //multithreadObj->PrintLockThreadCountOneByOne();


    /* --- Use of thread vectors --- */
    /*std::vector<std::thread> threadVec;
    const unsigned int nbThreads = std::thread::hardware_concurrency();
    for (unsigned int i = 0; i < nbThreads; i++)
    {
        //currently needs a global function for I did not find any other way to use vectors for now
        threadVec.push_back(std::thread(PrintLockDummy));
    }

    // To add a new thread in a specific space in vec, we have to move it
    std::thread newThread;

    if (threadVec[1].joinable())
        threadVec[1].join();

    threadVec[1] = std::move(newThread);


    for (std::thread& threadInVec : threadVec)
    {
        if (threadInVec.joinable())
            threadInVec.join();
    }*/


    /* --- Condition Variable --- */
    /*std::thread firstThread(&Multithread::SecondaryPrintThreadCountCondVar, multithreadObj);
    std::thread secondThread(&Multithread::PrimaryPrintThreadIDCondVar, multithreadObj);

    if (secondThread.joinable())
        secondThread.join();
    if (firstThread.joinable())
        firstThread.join();*/


    /* --- Promise & Future --- */
    /*std::promise<int> promiseVar;
    std::future<int> futureObj = promiseVar.get_future();
    std::thread promiseThread(PromiseTestFunc, &promiseVar); //explanations step by step in the func's comments
    std::cout << "Print Value of the future object: " << futureObj.get() << std::endl;

    if (promiseThread.joinable())
        promiseThread.join();*/


    /* --- Static & non-static --- */
    /*std::thread threadFromNonStatic(&Multithread::ThreadFuncPrintText, multithreadObj, "Print Dummy ");
    if (threadFromNonStatic.joinable())
        threadFromNonStatic.join();

    std::thread threadFromStatic(&Multithread::StaticThreadFuncPrintText, "Print Dummy ");
    if (threadFromStatic.joinable())
        threadFromStatic.join();*/


    /* --- Asynchronous threads with printed timer --- */
    /*std::chrono::system_clock::time_point startPoint = std::chrono::system_clock::now();

    //Get from FetchDataAsync
    std::future<std::string> getFromDatabase = std::async(std::launch::async, &Multithread::FetchFirstStrAsync, multithreadObj, "[First str success] ");

    //Get from FetchFileDataAsync / the ptr is a successful test!
    std::string fileData = multithreadObj->FetchSecondStrAsync("[Second str success]");

    //will block until data available in future<std::string> object
    std::string dataBaseData = getFromDatabase.get();

    std::chrono::system_clock::time_point endPoint = std::chrono::system_clock::now();
    __int64 diffPoint = std::chrono::duration_cast<std::chrono::seconds> (endPoint - startPoint).count();
    std::cout << "Total time: " << diffPoint << "sec." << std::endl;

    //combine data & print total
    std::string finalData = dataBaseData + "& " + fileData;
    std::cout << "Data: " << finalData << std::endl;*/


    if (multithreadObj != nullptr)
        delete multithreadObj;

}