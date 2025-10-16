/* Custom manipulators.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>

//{ endm manipulator
inline std::ostream& endm(std::ostream& os) {
    os << "[eol]\n";
    return os;
}
//}

//{ squares manipulator
class squares_wrapper {
public:
    squares_wrapper(std::ostream& os) : os_(os) {}
    
    template<typename T>
    std::ostream& operator<<(const T& value) {
        os_ << "[" << value << "]";
        return os_;
    }
    
private:
    std::ostream& os_;
};

class squares_manipulator {};
inline squares_manipulator squares;

inline squares_wrapper operator<<(std::ostream& os, const squares_manipulator&) {
    return squares_wrapper(os);
}
//}

//{ add manipulator
template<typename T>
class add_wrapper {
public:
    add_wrapper(std::ostream& os, const T& first) : os_(os), first_(first) {}
    
    template<typename U>
    std::ostream& operator<<(const U& second) {
        os_ << (first_ + second);
        return os_;
    }
    
private:
    std::ostream& os_;
    T first_;
};

class add_first_wrapper {
public:
    add_first_wrapper(std::ostream& os) : os_(os) {}
    
    template<typename T>
    add_wrapper<T> operator<<(const T& first) {
        return add_wrapper<T>(os_, first);
    }
    
private:
    std::ostream& os_;
};

class add_manipulator {};
inline add_manipulator add;

inline add_first_wrapper operator<<(std::ostream& os, const add_manipulator&) {
    return add_first_wrapper(os);
}
//}

#endif // __IOMANIP_HPP__