#include <iostream>
#include <memory>
#include <fstream>
/*
 * Auther: Aman Arabzadeh
 * Date: 2023-07-09
 *  Smart Pointers Example in C++ and the problems with raw pointers.
 *  Read more here:
 *  https://github.com/AMAN-ARABZADEH/Smart_Pointers_Cpp/tree/main
 */
// Problem with Raw Pointers:
// Raw pointers require manual memory management, leading to potential memory leaks and dangling pointers.
template<typename T>
void rawPointerExample(T value) {
    T* rawPtr = new T(value); // Allocate memory dynamically
    std::cout << *rawPtr << std::endl;

    delete rawPtr; // Deallocate the memory

    // Memory leak: Forgot to delete the allocated memory
    // Dangling pointer: rawPtr is left pointing to deallocated memory
    // Accessing *rawPtr here would be undefined behavior
    // Ownership: Who owns what?
}

// Smart Pointers and Ownership:
// Smart pointers are objects that manage the lifetime of dynamically allocated objects.
// They automatically deallocate the memory when the object is no longer needed.

// Example 1: std::unique_ptr
// Read more: https://en.cppreference.com/w/cpp/memory/unique_ptr
template<typename T>
void uniquePtrExample(T value) {
    std::unique_ptr<T> uniquePtr = std::make_unique<T>(value); // Allocate memory and assign ownership to uniquePtr

    // Access the object using the * operator
    std::cout << *uniquePtr << std::endl;


    // No need to manually delete the object

    // uniquePtr automatically deletes the object when it goes out of scope
    // or when it is reset explicitly
}
// Example 2: std::shared_ptr
// Read more: https://en.cppreference.com/w/cpp/memory/shared_ptr
template<typename T>
void sharedPtrExample(T value) {
    std::shared_ptr<T> sharedPtr = std::make_shared<T>(value); // Allocate memory and assign shared ownership to sharedPtr

    // Access the object using the * operator
    std::cout << *sharedPtr << std::endl;

    // No need to manually delete the object

    // sharedPtr automatically deletes the object when the last shared pointer pointing to it is destroyed or reset
}

// Example 3: std::weak_ptr
// Read more: https://en.cppreference.com/w/cpp/memory/weak_ptr
template<typename T>
void weakPtrExample(T value) {
    std::shared_ptr<T> sharedPtr = std::make_shared<T>(value); // Allocate memory and assign shared ownership to sharedPtr

    std::weak_ptr<T> weakPtr = sharedPtr; // Create weakPtr as a weak reference to the object

    // Access the object using the lock() member function
    if (std::shared_ptr<T> sharedLocked = weakPtr.lock()) {
        std::cout << *sharedLocked << std::endl;
    } else {
        std::cout << "Object no longer exists." << std::endl;
    }

    // No need to manually delete the object

    // sharedPtr automatically deletes the object when the last shared pointer pointing to it is destroyed or reset
    // weakPtr becomes empty if the object is deleted
}


int main() {
    rawPointerExample<int>(5);
    uniquePtrExample<int>(5);
    sharedPtrExample<int>(5);
    weakPtrExample<int>(5);



    return 0;
}
