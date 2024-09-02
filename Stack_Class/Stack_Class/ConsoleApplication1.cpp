#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <stack>
#include <chrono>
#include <list>
#include <vector>
#pragma warning(disable: 2440)
//template<class _Ty, class _Alloc = std::allocator<std::list<_Ty, _Alloc>::value_type>> class std::list<_Ty, _Alloc>

template<typename T>
class Stack {//даём пустой список должен образоваться пустой стек и можем работать с ним
private:
    T* arr;
    int top;
    int capacity;

public:
    Stack(int size) : capacity(size), top(-1) {
        arr = new T[size];
    }
    Stack(const std::vector<double>& Stack1) : capacity(3), top(-1){
        arr = new T[3];
    }
    Stack(std::list<T> numbers) {
        if (numbers.empty()) throw std::runtime_error("Stack underflow");
        else if (numbers.size() == 0) {
            arr = new T[3];
            capacity = 3;
            top = -1;
        }
        else {
            *this = Stack<T>(numbers.size());
            for (T value : numbers) {
                push(value);
            }
        }
    }

    Stack(const Stack<T>& s) : capacity(s.capacity), top(s.top) {
        arr = new T[s.capacity];
        std::copy(s.arr, s.arr + s.capacity, arr);
    }

    Stack(Stack<T>&& s) : capacity(s.capacity), top(s.top), arr(s.arr) {
        s.arr = nullptr;
        s.capacity = 0;
        s.top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(T value) {
        if (top == capacity - 1) {
            T* tmp = new T[capacity * 2];
            std::memcpy(tmp, arr, capacity * 2);
        }
        arr[++top] = value;
    }

    T pop() {
        if (empty()) {
            throw std::runtime_error("Stack underflow");
        }
        return arr[top--];
    }

    T check_pop() const {
        if (empty()) {
            throw std::runtime_error("Stack underflow");
        }
        return arr[top];
    }

    bool empty() const {
        return top == -1;
    }

    int size() const {
        return top + 1;
    }

    void clear() {
        capacity = 10;
        arr = new T[capacity];
        top = 0;
    }

    T top_element() const {
        if (empty()) {
            throw std::runtime_error("Stack underflow");
        }
        return arr[top];
    }

    void swap(T& value) {
        if (empty()) {
            throw std::runtime_error("Stack underflow");
        }
        std::swap(arr[top], value);
    }

    Stack<T>& operator=(const Stack<T>& s) {
        if (this != &s) {
            delete[] arr;

            capacity = s.capacity;
            top = s.top;
            arr = new T[s.capacity];
            std::copy(s.arr, s.arr + s.capacity, arr);
        }
        return *this;
    }

    Stack<T>& operator=(Stack<T>&& s) {
        if (this != &s) {
            delete[] arr;

            capacity = s.capacity;
            top = s.top;
            arr = s.arr;

            s.arr = nullptr;
            s.capacity = 0;
            s.top = -1;
        }
        return *this;
    }

    bool operator==(const Stack<T>& s) const {
        if (size() != s.size()) {
            return false;
        }

        for (int i = 0; i <= top; ++i) {
            if (arr[i] != s.arr[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Stack<T>& s) const {
        return !(*this == s);
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
        for (int i = 0; i <= s.top; ++i) {
            os << s.arr[i] << " ";
        }

        return os << '\n';
    }


};

struct TestStruct {
    int id;
    std::string name;
    TestStruct() {
        id = 13;
        name = "Ivan";
    }
    friend std::ostream& operator<<(std::ostream& os, const TestStruct& test) {
        os << test.id << " " << test.name;
        return os;
    }
    bool operator!=(const TestStruct& test) const {
        return !(test.id == this->id && test.name == this->name);
    }
    bool operator==(const TestStruct& test) const {
        return (test.id == this->id && test.name == this->name);
    }
};

void intTests() {
    std::cout << "INT Tests\n";
    std::cout << "******************************\n";

    std::cout << "TEST1\n";
    Stack<int>testINT = Stack<int>(10);
    testINT.push(-1);
    std::cout << testINT;

    std::cout << "TEST2\n";
    std::cout << testINT.check_pop() << " ";
    std::cout << testINT.empty() << "\n";

    std::cout << "TEST3\n";
    testINT.pop();
    std::cout << testINT.empty() << "\n";

    std::cout << "TEST4\n";
    testINT.push(10);
    testINT.push(-2);
    testINT.push(-7);
    //testINT.clear();
    std::cout << testINT << "\n";

    std::cout << "TEST5\n";
    int a = 3;
    std::cout << testINT;
    testINT.swap(a);
    std::cout << testINT;
    std::cout << a << std::endl;

    std::cout << "TEST6\n";
    Stack<int>testINT1 = testINT;
    std::cout << testINT1;

    std::cout << "TEST7\n";
    std::cout << (testINT == testINT1) << "\n";

    std::cout << "TEST8\n";
    std::cout << (testINT != testINT1) << "\n";
    std::cout << "******************************\n";
}

void doubleTests() {
    std::cout << "DOUBLE Tests\n";
    std::cout << "******************************\n";

    std::cout << "TEST1\n";
    std::vector<double> vector;
    Stack<double>testdouble123(vector);
    std::cout << testdouble123;
    testdouble123.push(3.5);
    std::cout << testdouble123;

    Stack<double>testdouble = Stack<double>(10);
    testdouble.push(1.5);
    std::cout << testdouble;

    std::cout << "TEST2\n";
    std::cout << testdouble.check_pop() << " ";
    std::cout << testdouble.empty() << "\n";

    std::cout << "TEST3\n";
    testdouble.pop();
    std::cout << testdouble.empty() << "\n";

    std::cout << "TEST4\n";
    testdouble.push(7.22);
    std::cout << testdouble.top_element() << "\n";

    std::cout << "TEST5\n";
    double a = 3.12;
    testdouble.swap(a);
    std::cout << testdouble;

    std::cout << "TEST6\n";
    Stack<double>testdouble1 = testdouble;
    std::cout << testdouble1;

    std::cout << "TEST7\n";
    std::cout << (testdouble == testdouble1) << "\n";

    std::cout << "TEST8\n";
    std::cout << (testdouble != testdouble1) << "\n";
    std::cout << "******************************\n";
}

void stringTests() {
    std::cout << "STRING Tests\n";
    std::cout << "******************************\n";

    std::cout << "TEST1\n";
    Stack<std::string>testString = Stack<std::string>(10);
    testString.push("hello");
    std::cout << testString;

    std::cout << "TEST2\n";
    std::cout << testString.check_pop() << " ";
    std::cout << testString.empty() << "\n";

    std::cout << "TEST3\n";
    testString.pop();
    std::cout << testString.empty() << "\n";

    std::cout << "TEST4\n";
    testString.push("world");
    std::cout << testString.top_element() << "\n";

    std::cout << "TEST5\n";
    std::string a = "MSU";
    testString.swap(a);
    std::cout << testString;

    std::cout << "TEST6\n";
    Stack<std::string>testString1 = testString;
    std::cout << testString1;

    std::cout << "TEST7\n";
    std::cout << (testString == testString1) << "\n";

    std::cout << "TEST8\n";
    std::cout << (testString != testString1) << "\n";
    std::cout << "******************************\n";
}

void structTests() {
    std::cout << "STRUCT Tests\n";
    std::cout << "******************************\n";
    TestStruct test = TestStruct();

    std::cout << "TEST1\n";
    Stack<TestStruct>testStruct = Stack<TestStruct>(10);
    testStruct.push(test);
    std::cout << testStruct;

    std::cout << "TEST2\n";
    std::cout << testStruct.check_pop() << " ";
    std::cout << testStruct.empty() << "\n";

    std::cout << "TEST3\n";
    testStruct.pop();
    std::cout << testStruct.empty() << "\n";

    std::cout << "TEST4\n";
    test.id = 12;
    test.name = "Ivan";
    testStruct.push(test);
    std::cout << testStruct.top_element() << "\n";

    std::cout << "TEST5\n";
    TestStruct a = TestStruct();
    testStruct.swap(a);
    std::cout << testStruct;

    std::cout << "TEST6\n";
    Stack<TestStruct>testStruct1 = testStruct;
    std::cout << testStruct1;

    std::cout << "TEST7\n";
    std::cout << (testStruct == testStruct1) << "\n";

    std::cout << "TEST8\n";
    std::cout << (testStruct != testStruct1) << "\n";
    std::cout << "******************************\n";
}

void timeTest() {
    std::cout << "TIME TEST\n";
    std::cout << "******************************\n";
    std::stack<int>basicStack;
    Stack<int>myStack = Stack<int>(100);

    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; i++) {
        basicStack.push(i);
    }
    auto end1 = std::chrono::steady_clock::now();

    auto res1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);

    auto start2 = std::chrono::steady_clock::now();
    for (int i = 0; i < 100; i++) {
        myStack.push(i);
    }
    auto end2 = std::chrono::steady_clock::now();

    auto res2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);

    //std::cout << "std::stack: " << res1 << "\n";
    //std::cout << "my stack: " << res2 << "\n";
    std::cout << "******************************\n";
}

void newTests() {
    std::cout << "LIST && SWAP TESTS\n";
    std::cout << "******************************\n";
    std::cout << "TEST1\n";
    std::initializer_list<int> list = {1, 2, 3, 4, 5};
    Stack<int> stack = Stack<int>((Stack<int>)list);
    std::cout << stack;

    std::cout << "TEST2\n";
    int a = 10;
    stack.swap(a);
    std::cout << stack.check_pop() << " " << a;
}


int main() {
    try {
        intTests();
        doubleTests();
        stringTests();
        structTests();
        timeTest();
        newTests();

    }
    catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Caught unknown exception\n";
    }
}
