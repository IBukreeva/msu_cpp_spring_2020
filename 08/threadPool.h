#include <thread>
#include <future>
#include <condition_variable>
#include <functional>
#include <mutex>

#include <queue>
#include <vector>

class ThreadPool{
public:
    explicit ThreadPool(size_t poolSize) :pool_size(poolSize), is_destructing(false) {
        for(size_t i=0;i<pool_size;i++) {
            threads.emplace_back([this]() {
                while(true){
                    std::unique_lock<std::mutex> lock(mtx_tasks);
		    link_cond.wait(lock, [this](){
                        return (!(tasks.empty()) || is_destructing);
                        });
		    if (is_destructing) return;
		    auto task = std::move(tasks.front());
		    tasks.pop();
                    lock.unlock(); 
		    task();
            }});

        }
    }
    ~ThreadPool(){
        is_destructing = true;
        link_cond.notify_all();
	for(size_t i=0; i<pool_size;i++){
	    threads[i].join();
	}
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{

        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()> > (std::bind(func, args...));
        {
	    std::lock_guard<std::mutex> lock(mtx_tasks);
            if(is_destructing){
                throw std::runtime_error("The pool is not active");
            }
	    tasks.emplace([task](){ (*task)(); });
	}
	link_cond.notify_one();
	return task->get_future();
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::condition_variable link_cond;
    std::mutex mtx_tasks;
    
    bool is_destructing;
    size_t pool_size;
};
