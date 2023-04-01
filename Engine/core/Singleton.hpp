#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T>
class Singleton {
public:
    static T& GetInstance(){
        static T instance;
        return instance;
    }

protected:
    Singleton(){}
    ~Singleton(){}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

#endif  // SINGLETON_HPP