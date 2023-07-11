#include <iostream>
#include <memory>
#include <vector>
/*
 * Auther: Aman Arabzadeh
 * Date: 2023-07-10
 *  Smart Pointers Example in C++ and the problems with raw pointers.
 *  Read more here:
 *  https://github.com/AMAN-ARABZADEH/Smart_Pointers_Cpp/tree/main 
 */
struct Person {
    std::string name{};
    std::string address{};
    size_t age{};

};
// Overloading the stream insertion operator (<<) for Person
std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Name: " << person.name << std::endl;
    os << "Address: " << person.address << std::endl;
    os << "Age: " << person.age << std::endl;
    return os;
}

// Example for using weak_ptr
// Imagine the chicken and egg problem, Which one came first?

// Forward declaration of Post to assure the compiler that it exists.
struct Post;

// Comment struct with a weak reference to the corresponding post
struct Comment {
    std::string text;
    std::weak_ptr<Post> post;
};

// Post struct with a vector of shared pointers to comments
struct Post {
    std::string content;
    std::vector<std::shared_ptr<Comment>> comments;
};




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



// When to use std::unique_ptr on an object:
/*
    std::unique_ptr<Person>: Use std::unique_ptr if you want exclusive ownership of the Person object.
    This means that only one std::unique_ptr can own the object at any given time. unless we give the ownership of element/object to the new one by using std::move.

    Example:
*/
    std::cout << "\n========= Example using std::unique_ptr ===========\n\n";
    std::unique_ptr<Person> personPtr1 = std::make_unique<Person>();
    personPtr1->name = "John Doe";
    personPtr1->address = "123 London St";
    personPtr1->age = 30;

    std::cout << *personPtr1; // Don't forget to dereference to access the object's values (operator<< is overloaded)
    std::cout << std::endl;    std::cout << std::endl;
    /// OBservation here, We cannot directly push_back std::unique_ptr

    // cannot directly push_back std::unique_ptr<Person> into a vector.
    // std::unique_ptr enforces exclusive ownership, meaning it cannot be copied.
    // However, We can use std::make_unique to create a std::unique_ptr<Person> and then move it into the vector using std::move.
    // we use std::move to transfer ownership of the std::unique_ptr<Person> into the vector using push_back.
    // By moving the std::unique_ptr, we transfer ownership from person1 to the vector.
    // After the move, person1 becomes empty (nullptr), and the vector owns the Person object.
    std::vector<std::unique_ptr<Person>> persons;

    // Create and add Person objects to the vector
    for (int i = 1; i <= 3; i++) {
        std::unique_ptr<Person> person = std::make_unique<Person>();
        person->name = "Person " + std::to_string(i);
        person->address = "Address " + std::to_string(i);
        person->age = 30 + i;
        persons.push_back(std::move(person));
    }

    // Access and print the information of each Person object in the vector
    for (const auto& personPtr : persons) {
        std::cout << *personPtr << std::endl;
    }
    std::cout << std::endl;



    ///////// More allocating dynamic using vector
    std::vector<std::unique_ptr<Person>> uniquePtrVector;
    uniquePtrVector.push_back(std::make_unique<Person>(Person{"John Doe", "123 London St", 30}));
    uniquePtrVector.push_back(std::make_unique<Person>(Person{"Jane Smith", "456 Oslo St", 25}));
    // We have to do it by reference else won't work , we get ERROR
    for(const auto&data : uniquePtrVector){
        std::cout << *data << " ";
    }






// When to use std::shared_ptr on an object:
/*
    std::shared_ptr<Person>: Use std::shared_ptr if you want shared ownership of the Person object.
    Multiple std::shared_ptr instances can share ownership of the same object.
    The object will be automatically deallocated when the last std::shared_ptr pointing to it is destroyed.

    Example:
*/
    std::cout << "\n=========== Example using std::shared_ptr ===========\n\n";

    std::shared_ptr<Person> p1  = std::make_shared<Person>();
    p1->name = "Mona Lisa";
    p1->address = "Paris";
    p1->age = 520;
    std::shared_ptr<Person> p2{p1};
    std::shared_ptr<Person> p3{p2};

    // prints the values of ps
    std::cout << "P1 is: " << *p1 << std::endl;
    std::cout << "P2 is: " << *p2 << std::endl;
    std::cout << "P2 is: " << *p3 << std::endl<< std::endl;

    // Print the addresses of the shared pointers
    std::cout << "p1 Address is: " << p1.get() << std::endl;
    std::cout << "p2 Address is: " << p2.get() << std::endl;
    std::cout << "p3 Address is: " << p3.get() << std::endl<< std::endl;

    // Print the initial reference counts
    std::cout << "Initial reference count of p1: " << p1.use_count() << std::endl;
    std::cout << "Initial reference count of p2: " << p2.use_count() << std::endl;
    std::cout << "Initial reference count of p3: " << p3.use_count() << std::endl << std::endl;

    // Reset p2 and p3
    p2.reset();
    p3.reset();

    // Print the updated reference counts
    std::cout << "Reference count of p1 after resetting p2 and p3: " << p1.use_count() << std::endl;
    std::cout << "Reference count of p2 after resetting: " << p2.use_count() << std::endl;
    std::cout << "Reference count of p3 after resetting: " << p3.use_count() << std::endl<< std::endl;




    // Create shared pointers to Person objects using std::make_shared
    std::shared_ptr<Person> personPtrSimple1 = std::make_shared<Person>();
    personPtrSimple1->name = "John Doe";
    personPtrSimple1->address = "123 Main St";
    personPtrSimple1->age = 30;

    std::shared_ptr<Person> personPtrSimple2 = std::make_shared<Person>();
    personPtrSimple2->name = "Jane Smith";
    personPtrSimple2->address = "456 Elm St";
    personPtrSimple2->age = 25;
    std::shared_ptr<Person> personPtrSimple3 = std::make_shared<Person>();
    personPtrSimple3 = personPtrSimple1;



    // Create a vector of shared pointers to Person objects
    std::vector<std::shared_ptr<Person>> personPtrSimples;

    // Add the shared pointers to the vector using push_back
    personPtrSimples.push_back(personPtrSimple1);
    personPtrSimples.push_back(personPtrSimple2);
    personPtrSimples.push_back(personPtrSimple3);


    // Print the information of the Person objects using the vector and at
    size_t counter{0};
    for(const auto &person : personPtrSimples){
        ++counter;
        std::cout << "Person: " << counter  << "\n" << *person << std::endl;
        std::cout << "Use count: " << person.use_count() << std::endl;
    }
    // Get the updated reference counts
    std::cout << "Reference count of personPtr1: " << personPtrSimple1.use_count() << std::endl;
    std::cout << "Reference count of personPtr2: " << personPtrSimple2.use_count() << std::endl;

    // Reset the shared pointers
    personPtrSimple1.reset();
    personPtrSimple2.reset();

    // Check if the shared pointers are empty
    if (!personPtrSimple1) {
        std::cout << "personPtr1 is empty" << std::endl;
    }

    if (!personPtrSimple2) {
        std::cout << "personPtr2 is empty" << std::endl;
    }

    // Get the updated reference counts in the vector
    std::cout << "Reference count of personPtrs[0]: " << personPtrSimples.at(0).use_count() << std::endl;
    std::cout << "Reference count of personPtrs[1]: " << personPtrSimples.at(1).use_count() << std::endl;









// When to use std::weak_ptr in conjunction with std::shared_ptr:
/*
    std::weak_ptr<Person>: Use std::weak_ptr in conjunction with std::shared_ptr if you need a non-owning, weak reference to the Person object.
    Unlike std::shared_ptr, std::weak_ptr does not contribute to the ownership count and does not prevent the object from being deallocated.
    It can be used to check if the object is still valid before accessing it.
    Always created from std::shared_ptr.
    Used to prevent strong reference cycles which could prevent objects from being deleted.

    Example:
*/

    std::cout << "\n==== Example using std::weak_ptr in conjunction with std::shared_ptr =====\n\n";
    std::shared_ptr<Person> sharedPtr3 = std::make_shared<Person>();
    sharedPtr3->name = "John Doe";
    sharedPtr3->address = "123 London St";
    sharedPtr3->age = 30;

    std::weak_ptr<Person> weakPtr = sharedPtr3;

    if (std::shared_ptr<Person> sharedLocked = weakPtr.lock()) {
        std::cout << *sharedLocked;
    } else {
        std::cout << "Object no longer exists." << std::endl;
    }


    //////

    /*
        In a real-world scenario, consider a social networking application where users can create posts and comment on those posts.
        Each post can have a list of comments.
        The relationship between posts and comments can be modeled using shared pointers, where each post holds a shared pointer to its comments.
        However, comments don't need to own the posts.
     */
    // Create a post
    std::shared_ptr<Post> post = std::make_shared<Post>();
    post->content = "Check out this amazing photo!";

    // Create comments
    std::shared_ptr<Comment> comment1 = std::make_shared<Comment>();
    comment1->text = "Beautiful shot!";
    comment1->post = post;

    std::shared_ptr<Comment> comment2 = std::make_shared<Comment>();
    comment2->text = "I wish I could take pictures like this.";
    comment2->post = post;

    std::shared_ptr<Comment> comment3 = std::make_shared<Comment>();
    comment3->text = "I like it.";
    comment3->post = post;
    // Add comments to the post
    post->comments.push_back(comment1);
    post->comments.push_back(comment2);
    post->comments.push_back(comment3);
    // Print the post and its comments
    std::cout << "Post: " << post->content << std::endl;
    std::cout << "Comments:" << std::endl;
    for (const auto& comment : post->comments) {
        if (auto sharedPost = comment->post.lock()) {
            std::cout << "- " << comment->text << " (Post: " << sharedPost->content << ")" << std::endl;
        } else {
            std::cout << "- " << comment->text << " (Post no longer exists)" << std::endl;
        }
    }


    /// NOTES
    /*
     The purpose of using std::weak_ptr in this example is to create a non-owning, weak reference from comments to the corresponding post.
     This allows accessing the post as long as it is valid, without prolonging its lifetime unnecessarily.
     By using std::weak_ptr, the code avoids creating a strong reference cycle between posts and comments, ensuring that both can be deallocated properly when they are no longer needed.


     // Read more:
     https://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful
     https://en.cppreference.com/w/cpp/memory/weak_ptr
     https://en.cppreference.com/w/cpp/memory/shared_ptr
     */
    return 0;
}
