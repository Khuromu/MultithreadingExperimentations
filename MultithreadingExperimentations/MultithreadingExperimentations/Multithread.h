#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <future>

#include <chrono>

class Multithread
{
public:
	/* Simple Print the number of threads on the machine */
	void PrintMachineThreadCount();

	/* Count Threads One by One */
	void PrintThreadCountOneByOne();

	/* Count Threads One By One With MUTEX*/
	void PrintMutexThreadCountOneByOne();

	/* Count Threads One By One With LOCK_GUARD */
	void PrintLockThreadCountOneByOne();

	/* Redo of printcount and printcount one by one with the use of condition variable & sleep-for */
	//One on main thread, the other on second thread
	void PrimaryPrintThreadIDCondVar();
	void SecondaryPrintThreadCountCondVar();

	/* Print Text with a static function */
	static void StaticThreadFuncPrintText(std::string sample);

	/* Print Text with a non-static function */
	void ThreadFuncPrintText(std::string sample);

	/* Grab strings asynchronously */
	std::string FetchFirstStrAsync(std::string getStr);
	std::string FetchSecondStrAsync(std::string getStr);

private:
	std::string globalStr = "";
	int countTest = 0;
	std::mutex mainMutex;
	bool bIsSync = false;
	std::condition_variable condVar;
};
