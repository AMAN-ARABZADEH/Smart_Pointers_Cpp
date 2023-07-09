#include <iostream>
#include <memory>

// Problem with Raw Pointers:
// Raw pointers require manual memory management, leading to potential memory leaks and dangling pointers.
void rawPointerExample() {
    int* rawPtr = new int(5); // Allocate memory dynamically
    std::cout << *rawPtr << std::endl;

    delete rawPtr; // Deallocate the memory

    // Memory leak: Forgot to delete the allocated memory
    // Dangling pointer: rawPtr is left pointing to deallocated memory
    // Accessing *rawPtr here would be undefined behavior
}

// Smart Pointers and Ownership:
// Smart pointers are objects that manage the lifetime of dynamically allocated objects.
// They automatically deallocate the memory when the object is no longer needed.

// RAII (Resource Acquisition Is Initialization) Principle:
// Smart pointers follow the RAII principle, which states that resource acquisition should be tied to object initialization.
// The smart pointer's destructor is responsible for releasing the allocated resource.

// Example 1: std::unique_ptr
// std::unique_ptr provides exclusive ownership of a dynamically allocated object.
// It automatically deletes the object when it goes out of scope or is explicitly reset.
// Read more: https://en.cppreference.com/w/cpp/memory/unique_ptr
void uniquePtrExample() {
    std::unique_ptr<int> uniquePtr = std::make_unique<int>(5); // Allocate memory and assign ownership to uniquePtr

    // Access the object using the * operator
    std::cout << *uniquePtr << std::endl;

    // No need to manually delete the object

    // uniquePtr automatically deletes the object when it goes out of scope
    // or when it is reset explicitly
}

// Example 2: std::shared_ptr
// std::shared_ptr provides shared ownership of a dynamically allocated object.
// It allows multiple shared pointers to point to the same object.
// The object is deleted only when the last shared pointer pointing to it is destroyed or reset.
// Read more: https://en.cppreference.com/w/cpp/memory/shared_ptr
void sharedPtrExample() {
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(5); // Allocate memory and assign shared ownership to sharedPtr

    // Access the object using the * operator
    std::cout << *sharedPtr << std::endl;

    // No need to manually delete the object

    // sharedPtr automatically deletes the object when the last shared pointer pointing to it is destroyed or reset
}

// Example 3: std::weak_ptr
// std::weak_ptr provides a non-owning "weak" reference to an object managed by std::shared_ptr.
// It allows accessing the object if it still exists, but without prolonging its lifetime.
// std::weak_ptr does not contribute to the reference count of the object.
// Read more: https://en.cppreference.com/w/cpp/memory/weak_ptr
void weakPtrExample() {
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(5); // Allocate memory and assign shared ownership to sharedPtr

    std::weak_ptr<int> weakPtr = sharedPtr; // Create weakPtr as a weak reference to the object

    // Access the object using the lock() member function
    if (std::shared_ptr<int> sharedLocked = weakPtr.lock()) {
        std::cout << *sharedLocked << std::endl;
    } else {
        std::cout << "Object no longer exists." << std::endl;
    }

    // No need to manually delete the object

    // sharedPtr automatically deletes the object when the last shared pointer pointing to it is destroyed or reset
    // weakPtr becomes empty if the object is deleted
}

int main() {
    rawPointerExample();
    uniquePtrExample();
    sharedPtrExample();
    weakPtrExample();

    return 0;
}

