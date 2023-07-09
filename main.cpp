#include <iostream>
#include <memory>
#include <fstream>

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
// std::unique_ptr provides exclusive ownership of a dynamically allocated object.
// It automatically deletes the object when it goes out of scope or is explicitly reset.
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
// std::shared_ptr provides shared ownership of a dynamically allocated object.
// It allows multiple shared pointers to point to the same object.
// The object is deleted only when the last shared pointer pointing to it is destroyed or reset.
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
// std::weak_ptr provides a non-owning "weak" reference to an object managed by std::shared_ptr.
// It allows accessing the object if it still exists, but without prolonging its lifetime.
// std::weak_ptr does not contribute to the reference count of the object.
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

///////////// RAII Example for File Handling


class FileHandler {
public:
    explicit FileHandler(const std::string& filename)
            : fileStream(filename)
    {
        if (!fileStream) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    void writeData(const std::string& data) {
        if (fileStream.is_open()) {
            fileStream << data;
        }
    }

    std::string readData() {
        std::string content;
        fileStream.seekg(0); // Reset the file position to the beginning
        std::string line;
        while (std::getline(fileStream, line)) {
            content += line + '\n';
        }
        return content;
    }

private:
    std::fstream fileStream;
};

int main() {
    rawPointerExample<int>(5);
    uniquePtrExample<int>(5);
    sharedPtrExample<int>(5);
    weakPtrExample<int>(5);
    rawPointerExample<std::string>("RAw pointer.");
    try {
        FileHandler file("example.txt");
        file.writeData("Hello, RAII!\n");
        file.writeData("Hello, Friend\n");

        std::string fileContent = file.readData();
        std::cout << "File content:\n" << fileContent;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }



    return 0;
}
