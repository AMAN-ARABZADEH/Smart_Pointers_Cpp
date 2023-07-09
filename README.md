# Smart Pointers Example

Smart Pointers Example  in C++ and the problems with raw pointers.

This code demonstrates the usage of smart pointers in C++ and highlights the problems with raw pointers. 
It aims to educate beginners about the benefits of using smart pointers and why they should avoid using raw pointers in modern C++ programming.


## Problem with Raw Pointers

Raw pointers require manual memory management, which can lead to potential issues such as memory leaks and dangling pointers. 
The code showcases an example of allocating memory using a raw pointer and demonstrates the need for manual deallocation.

## Smart Pointers and Ownership

The code introduces the concept of smart pointers as objects that manage the lifetime of dynamically allocated objects. 
It explains the RAII (Resource Acquisition Is Initialization) principle, where resource acquisition is tied to object initialization, 
and the smart pointer's destructor is responsible for releasing the allocated resource.


## Example 1: std::unique_ptr
The code provides an example of using `std::unique_ptr`, which provides exclusive ownership of a dynamically allocated object. 
It shows how `std::unique_ptr` automatically deletes the object when it goes out of scope or is explicitly reset.


## Example 2: std::shared_ptr
The code demonstrates the usage of `std::shared_ptr`, which provides shared ownership of a dynamically allocated object. 
It explains that multiple shared pointers can point to the same object, and the object is deleted only when the last shared pointer is destroyed or reset.


## Example 3: std::weak_ptr
The code showcases `std::weak_ptr`, which provides a non-owning "weak" reference to an object managed by `std::shared_ptr`. 
It explains that  `std::weak_ptr` allows accessing the object if it still exists but without prolonging its lifetime. 
It also mentions that  `std::weak_ptr` does not contribute to the reference count of the object.

Please refer to the provided links to learn more about each smart pointer and their usage in C++.

## Sources:

- [std::unique_ptr - cppreference.com](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [std::shared_ptr - cppreference.com](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [std::weak_ptr - cppreference.com](https://en.cppreference.com/w/cpp/memory/weak_ptr)

Feel free to modify and enhance this code as needed for your GitHub repository.
