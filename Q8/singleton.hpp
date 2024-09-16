#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

class Singleton {
protected:
    pthread_mutex_t* mutex = nullptr;

    // Protected constructor to prevent instantiation outside the class
    Singleton() {
        int shm_mutex_fd = shm_open("/mutex_mem", O_CREAT | O_RDWR, 0666);
        ftruncate(shm_mutex_fd, sizeof(pthread_mutex_t));
        mutex = static_cast<pthread_mutex_t*>(mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_mutex_fd, 0));

        static bool mutex_initialized = false;
        if (!mutex_initialized) {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);  // Set mutex to be shared between processes
            pthread_mutex_init(mutex, &attr);
            pthread_mutexattr_destroy(&attr);
            mutex_initialized = true;
        }
        std::cout << "Singleton constructor called!" << std::endl;
    }

    virtual ~Singleton() {
        munmap(mutex, sizeof(pthread_mutex_t));
    }

    // Pure virtual function for derived classes to implement specific actions
    virtual void action() = 0;

public:
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Templated getInstance method to handle derived classes
    template <typename T>
    static T& getInstance() {
        static T instance;
        return instance;
    }

    void runAction() {
        if (mutex != nullptr) {
            pthread_mutex_lock(mutex);  // Lock mutex
            action();
            pthread_mutex_unlock(mutex);  // Unlock mutex
        } else {
            std::cerr << "Mutex is not initialized!" << std::endl;
        }
    }
};

#endif // SINGLETON_HPP
