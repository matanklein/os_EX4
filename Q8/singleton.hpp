#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <pthread.h>

// Abstract class for the Singleton pattern
class Singleton {
protected:
    // Protected constructor and destructor to prevent direct instantiation and deletion
    Singleton() = default;
    virtual ~Singleton() = default;

public:
    // Disable copy constructor and assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Pure virtual functions that must be implemented by derived classes
    virtual void changeBoard() = 0;
    virtual void printBoard() = 0;
};

#endif // SINGLETON_HPP
