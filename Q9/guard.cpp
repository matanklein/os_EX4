class Guard {
public:
    // Constructor locks the mutex
    Guard() {
        Singleton::lock();
    }

    // Destructor unlocks the mutex
    ~Guard() {
        Singleton::unlock();
    }
};
