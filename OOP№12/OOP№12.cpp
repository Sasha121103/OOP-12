// O#include <iostream>
/*Реализовать класс "Умный указатель" с поведением
shared_ptr<>. И проверить его работу.*/
template<typename T>
class SharedPointer {
private:
    T* ptr;                // Указатель на управляемый объект
    size_t* ref_count;      // Указатель на счетчик ссылок

public:
    // Конструктор
    explicit SharedPointer(T* p = nullptr) : ptr(p), ref_count(new size_t(1)) {
        std::cout << "SharedPointer created. Ref count = " << *ref_count << std::endl;
    }

    // Конструктор копирования
    SharedPointer(const SharedPointer<T>& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {
        ++(*ref_count);
        std::cout << "SharedPointer copied. Ref count = " << *ref_count << std::endl;
    }

    // Оператор присваивания
    SharedPointer<T>& operator=(const SharedPointer<T>& sp) {
        if (this != &sp) {
            release();               // Освободить текущий объект, если есть
            ptr = sp.ptr;            // Копировать указатель
            ref_count = sp.ref_count; // Копировать счетчик
            ++(*ref_count);
            std::cout << "SharedPointer assigned. Ref count = " << *ref_count << std::endl;
        }
        return *this;
    }

    // Деструктор
    ~SharedPointer() {
        release();
    }

    // Освобождение указателя
    void release() {
        if (ref_count) {
            --(*ref_count);
            std::cout << "SharedPointer destroyed. Ref count = " << *ref_count << std::endl;
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
                std::cout << "Managed object and ref_count deleted." << std::endl;
            }
        }
    }

    // Оператор разыменования
    T& operator*() const {
        return *ptr;
    }

    // Оператор доступа к членам
    T* operator->() const {
        return ptr;
    }

    // Получить текущий счетчик ссылок
    size_t use_count() const {
        return *ref_count;
    }
};

class Test {
public:
    Test() {
        std::cout << "Test object created." << std::endl;
    }

    ~Test() {
        std::cout << "Test object destroyed." << std::endl;
    }

    void sayHello() {
        std::cout << "Hello from Test object!" << std::endl;
    }
};

int main()
{
    SharedPointer<Test> sp1(new Test()); // Создание нового объекта
    {
        SharedPointer<Test> sp2 = sp1;
    }
    return 0;
}