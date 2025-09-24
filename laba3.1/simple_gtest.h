#ifndef SIMPLE_GTEST_H
#define SIMPLE_GTEST_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>  // Добавил vector

// Простая реализация Google Test для C++11

class Test {
public:
    virtual ~Test() {}
    virtual void Run() = 0;
    virtual const char* Name() const = 0;
};

// Макросы для утверждений
#define EXPECT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            std::cout << "FAIL: " << #condition << " in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } else { \
            std::cout << "PASS: " << #condition << std::endl; \
        } \
    } while (0)

#define EXPECT_FALSE(condition) EXPECT_TRUE(!(condition))

#define EXPECT_EQ(expected, actual) \
    do { \
        auto e = (expected); \
        auto a = (actual); \
        if (e != a) { \
            std::cout << "FAIL: " << #expected << " == " << #actual << " (" << e << " vs " << a << ") in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } else { \
            std::cout << "PASS: " << #expected << " == " << #actual << std::endl; \
        } \
    } while (0)

#define EXPECT_NE(expected, actual) \
    do { \
        auto e = (expected); \
        auto a = (actual); \
        if (e == a) { \
            std::cout << "FAIL: " << #expected << " != " << #actual << " (" << e << " vs " << a << ") in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } else { \
            std::cout << "PASS: " << #expected << " != " << #actual << std::endl; \
        } \
    } while (0)

#define EXPECT_NEAR(val1, val2, abs_error) \
    do { \
        auto v1 = (val1); \
        auto v2 = (val2); \
        auto err = (abs_error); \
        if (std::abs(v1 - v2) > err) { \
            std::cout << "FAIL: " << #val1 << " near " << #val2 << " (" << v1 << " vs " << v2 << ", error: " << std::abs(v1-v2) << ") in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } else { \
            std::cout << "PASS: " << #val1 << " near " << #val2 << " (error: " << std::abs(v1-v2) << ")" << std::endl; \
        } \
    } while (0)

#define EXPECT_GT(lhs, rhs) \
    do { \
        auto l = (lhs); \
        auto r = (rhs); \
        if (!(l > r)) { \
            std::cout << "FAIL: " << #lhs << " > " << #rhs << " (" << l << " vs " << r << ") in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } else { \
            std::cout << "PASS: " << #lhs << " > " << #rhs << std::endl; \
        } \
    } while (0)

#define EXPECT_LT(lhs, rhs) \
    do { \
        auto l = (lhs); \
        auto r = (rhs); \
        if (!(l < r)) { \
            std::cout << "FAIL: " << #lhs << " < " << #rhs << " (" << l << " vs " << r << ") in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } else { \
            std::cout << "PASS: " << #lhs << " < " << #rhs << std::endl; \
        } \
    } while (0)

#define EXPECT_THROW(statement, exception_type) \
    do { \
        try { \
            statement; \
            std::cout << "FAIL: Expected exception " << #exception_type << " in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } catch (const exception_type&) { \
            std::cout << "PASS: Exception " << #exception_type << " caught" << std::endl; \
        } catch (...) { \
            std::cout << "FAIL: Wrong exception type in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } \
    } while (0)

#define EXPECT_NO_THROW(statement) \
    do { \
        try { \
            statement; \
            std::cout << "PASS: No exception thrown" << std::endl; \
        } catch (...) { \
            std::cout << "FAIL: Unexpected exception in " << __FILE__ << ":" << __LINE__ << std::endl; \
            return; \
        } \
    } while (0)

// Макрос для создания тестов
#define TEST(test_case_name, test_name) \
    class test_case_name##_##test_name##_Test : public Test { \
    public: \
        test_case_name##_##test_name##_Test() {} \
        const char* Name() const override { return #test_case_name "." #test_name; } \
        void Run() override; \
    }; \
    static test_case_name##_##test_name##_Test test_case_name##_##test_name##_instance; \
    void test_case_name##_##test_name##_Test::Run()

// Регистрация и запуск тестов (упрощенная версия)
class TestRegistry {
private:
    std::vector<Test*> tests_;
    
public:
    void AddTest(Test* test) {
        tests_.push_back(test);
    }
    
    int RunAllTests() {
        std::cout << "[==========] Running " << tests_.size() << " tests" << std::endl;
        int passed = 0;
        int failed = 0;
        
        for (Test* test : tests_) {
            std::cout << "[ RUN      ] " << test->Name() << std::endl;
            try {
                test->Run();
                std::cout << "[       OK ] " << test->Name() << std::endl;
                passed++;
            } catch (...) {
                std::cout << "[  FAILED  ] " << test->Name() << std::endl;
                failed++;
            }
        }
        
        std::cout << "[==========] " << (passed + failed) << " tests ran" << std::endl;
        std::cout << "[  PASSED  ] " << passed << " tests" << std::endl;
        if (failed > 0) {
            std::cout << "[  FAILED  ] " << failed << " tests" << std::endl;
            return 1;
        }
        return 0;
    }
    
    static TestRegistry& Instance() {
        static TestRegistry instance;
        return instance;
    }
};

// Автоматическая регистрация тестов
template<typename T>
class TestRegistrar {
public:
    TestRegistrar() {
        TestRegistry::Instance().AddTest(new T());
    }
};

#define REGISTER_TEST(test_class) \
    static TestRegistrar<test_class> test_class##_registrar

// Макрос для main функции (исправленный)
#define RUN_ALL_TESTS() \
    int main() { \
        return TestRegistry::Instance().RunAllTests(); \
    }

#endif // SIMPLE_GTEST_H