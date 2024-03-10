# STL Container Implementation

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![GitHub Actions](https://img.shields.io/badge/github%20actions-%232671E5.svg?style=for-the-badge&logo=githubactions&logoColor=white)

## Overview
This project is a custom implementation of the Standard Template Library (STL) containers in C++. It aims to replicate the functionality of various STL containers such as vectors, lists, maps, sets, and more, adhering closely to their original logic and behavior. This implementation is done in compliance with the C++17 standard and follows the Google coding style guidelines.

## Features
- Custom implementations of STL containers including arrays, lists, maps, sets, queues, stacks, and more.
- Full template classes to provide flexibility in container data types.
- Comprehensive unit tests for each container to ensure reliability and performance.
- Adherence to STL's original logic and memory management practices.

## Requirements
- GCC compiler with support for the C++17 standard.
- GTest library for running unit tests.

## Getting Started
To use this library in your project, follow these steps:

1. **Clone the repository:**

```bash
git clone https://github.com/LikimiaD/STL-Containers-Implementation.git
```

2. **Build the project:**

Navigate to the project directory and use the provided Makefile:

```bash
cd STL-Container-Implementation
make all
```

3. **Run unit tests:**

To ensure that all containers are working as expected, run the unit tests:

```bash
./test
```

## Directory Structure

```tree
.
├── LICENSE
├── Makefile
├── compiler.lua
├── include
│   ├── custom_array.h
│   ├── custom_list.h
│   ├── custom_map.h
│   ├── custom_multiset.h
│   ├── custom_queue.h
│   ├── custom_set.h
│   ├── custom_stack.h
│   ├── custom_vector.h
│   └── rb_tree.h
├── rules.lua
├── test
│   ├── array.test.cpp
│   ├── list.test.cpp
│   ├── main.cpp
│   ├── map.test.cpp
│   ├── multiset.test.cpp
│   ├── queue.test.cpp
│   ├── rb_tree.test.cpp
│   ├── set.test.cpp
│   ├── stack.test.cpp
│   └── vector.test.cpp
└── xmake.lua
```

For detailed instructions on building and running tests, see the following sections.

## Custom Array Container Implementation

The `CustomArray` container is a fixed-size array class template that offers a substantial part of the functionality of the standard `std::array` container found in the C++ Standard Template Library (STL). It is designed to work with C++17 and provides an efficient, stack-allocated, fixed-size collection of elements.

### Features and Design

* **Type-Safe Container:** `CustomArray` is a template class that allows users to define the type of elements (`T`) and the fixed size (`N`) of the array at compile-time, ensuring type safety.
* **Standard Iterator Support:** It supports both `iterator`, allowing the container to work with range-based for loops and standard algorithms.
* **Member Types:** Includes standard STL-like member types such as `value_type`, `reference`, `const_reference`, `iterator`, c`onst_iterator`, `size_type`, which makes it easier for users familiar with STL to use the `CustomArray`.
* **Element Access:** Provides methods for accessing elements, including `at()`, which throws an exception if the index is out of bounds, and `operator[]`, which does not. It also includes `front()`, `back()`, and `data()` for direct access to the underlying array.
* **Capacity and Size:** Implements `size()`, `max_size()`, and `empty()` methods to inquire about the container's size and capacity.
* **Modifiers:** Includes a `swap()` method for swapping the contents with another `CustomArray` of the same type and size, and a `fill()` method to fill the array with a specified value.

### Usage
Here is a basic example of how to declare and use a `CustomArray`:

```cpp
#include "include/custom_array.h"

int main() {
    // Create a CustomArray of integers with a fixed size of 5
    CustomArray<int, 5> myArray;

    // Initialize the array with values
    for (size_t i = 0; i < myArray.size(); ++i) {
        myArray[i] = static_cast<int>(i) * 10;
    }

    // Access and print elements
    for (const auto& element : myArray) {
        std::cout << element << ' ';
    }
    std::cout << '\n';

    // Use member functions
    std::cout << "Front element: " << myArray.front() << '\n';
    std::cout << "Back element: " << myArray.back() << '\n';

    // Fill the array with a specific value
    myArray.fill(42);

    // Print after filling
    for (const auto& element : myArray) {
        std::cout << element << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

## Custom List Container Implementation

The `CustomList` class is a custom implementation of a doubly-linked list that allows for dynamic size adjustment, providing flexibility and ease of use not found in fixed-size containers. This implementation follows the principles of the C++ Standard Template Library (STL) but is tailored to demonstrate the internal workings of such data structures.

### Features and Design

- **Dynamic Memory Allocation**: Unlike arrays, `CustomList` adjusts its size dynamically, offering efficient memory usage and flexibility in handling varying sizes of data.
- **Bidirectional Iteration**: With its custom iterator, `CustomListIterator`, the list supports both forward and backward traversal, enhancing its utility in various algorithms.
- **Template Class**: `CustomList` is a template class, making it suitable for storing any data type.
- **Element Access and Modification**: It provides methods for inserting, erasing, and accessing elements at any position, allowing for robust manipulation of the list's contents.
- **Utility Functions**: Includes functions for sorting, reversing, unique elements removal, and merging with other lists, providing comprehensive tools for data manipulation.

### Example Usage

```cpp
#include "include/custom_list.h"

int main() {
    // Create a CustomList and initialize it with integers
    CustomList<int> myList{1, 2, 3, 4, 5};

    // Add elements to the front and back
    myList.push_front(0);
    myList.push_back(6);

    // Remove the last element
    myList.pop_back();

    // Iterate through the list and print its contents
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // Reverse the list
    myList.reverse();

    // Print the reversed list
    for (const auto& value : myList) {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

### Technical Details

* The list is implemented as a doubly-linked list, where each node contains a data element, a pointer to the previous node, and a pointer to the next node.
* It supports all common operations such as insertion, deletion, traversal, and searching with efficiencies that vary based on the operation due to its non-contiguous memory allocation.
* The list's iterators are bidirectional, allowing for flexible navigation through the list's elements.

## Custom Map Container Implementation

The `Map` class is a custom implementation that mimics the behavior and functionality of the C++ Standard Template Library (STL) `std::map`. It is built on top of a Red-Black Tree (`RBTree`), ensuring efficient operations such as insertion, deletion, and lookup with logarithmic time complexity. This implementation demonstrates the integration of complex data structures to provide ordered associative mapping from keys to values.

### Features and Design

- **Key-Value Mapping**: Stores elements as pairs of keys and values. Each key in the map is unique, and it is associated with a specific value.
- **Ordering**: The elements in the map are ordered according to the keys, facilitating efficient retrieval and iteration in a sorted manner.
- **Red-Black Tree Backend**: Utilizes a Red-Black Tree for its underlying storage, balancing the tree to maintain a logarithmic height, which ensures efficient operations.
- **Custom Iterator**: Provides a `MapIterator` class to iterate over elements in the map, offering access to both keys and values during iteration.
- **Template Class**: Like STL containers, `Map` is a template class, allowing it to store any type of key-value pairs, provided the keys are comparable.

### Example Usage

```cpp
#include "include/map.h"

int main() {
    // Create a map of string keys to int values
    Map<std::string, int> myMap;

    // Insert some key-value pairs into the map
    myMap.insert({"apple", 5});
    myMap.insert({"banana", 8});
    myMap.insert({"cherry", 3});

    // Access and modify values by key
    myMap["apple"] = 10;

    // Iterate over the map and print key-value pairs
    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
        auto& pair = *it;
        std::cout << pair.first << ": " << pair.second << '\n';
    }

    // Check if a key exists in the map
    if (myMap.contains("banana")) {
        std::cout << "Banana is in the map.\n";
    }

    return 0;
}
```

### Technical Details

* The map supports operations like `insert`, `erase`, `find`, `at`, and `operator[]` for element access and manipulation, providing a rich set of functionalities for associative data handling.
* The `MapIterator` facilitates in-order traversal of the map, allowing users to iterate over the map's elements in key-sorted order, which is particularly useful for ordered data processing.

## Custom MultiSet Container Implementation

The `MultiSet` class encapsulates a custom implementation similar to the `std::multiset` found in the C++ Standard Template Library (STL). It utilizes a Red-Black Tree (`RBTree`) for its internal storage, ensuring that elements are stored in a sorted manner and allowing for efficient insertion, deletion, and lookup operations, including handling multiple instances of the same value.

### Features and Design

- **Sorted and Duplicate Elements**: Unlike a standard set, `MultiSet` allows for multiple elements with the same value, maintaining their order at all times.
- **Red-Black Tree Backend**: The use of a Red-Black Tree ensures that the container maintains its elements in sorted order automatically, with operations such as insertion, deletion, and search being highly efficient.
- **Custom Iterator**: Provides a `MultiSetIterator` for traversing the elements in sorted order, allowing for both forward and backward iteration through the container.
- **Template Class**: As a template class, `MultiSet` can store elements of any type that can be compared using the `<` operator, making it versatile for various use cases.

### Example Usage

```cpp
#include "include/multiset.h"

int main() {
    // Create a MultiSet and initialize it with some integers
    MultiSet<int> myMultiSet{5, 1, 3, 3, 7, 7, 7};

    // Insert additional values
    myMultiSet.insert(5);
    myMultiSet.insert(2);

    // Iterate over the MultiSet and print its contents
    for (auto it = myMultiSet.begin(); it != myMultiSet.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // Count occurrences of a specific value
    std::cout << "Number of '7's: " << myMultiSet.count(7) << '\n';

    // Check if a value exists in the MultiSet
    if (myMultiSet.contains(3)) {
        std::cout << "3 is in the MultiSet.\n";
    }

    return 0;
}
```

### Technical Details

* The MultiSet supports typical set operations, including `insert`, `erase`, `find`, and `count`, alongside specific operations like `equal_range`, `lower_bound`, and `upper_bound` to work with sorted data efficiently.
* The container's iterators facilitate in-order traversal, offering a straightforward way to navigate through the sorted elements.

## Custom Queue Container Implementation

The `CustomQueue` class is a custom implementation of a queue data structure, designed to mimic the behavior of the `std::queue` container adapter in the C++ Standard Template Library (STL). This implementation focuses on providing a simple yet efficient way to manage a sequence of elements in a first-in, first-out (FIFO) manner.

### Features and Design

- **FIFO Element Access**: Elements are inserted at the back and removed from the front, ensuring that the first element inserted is the first one to be removed.
- **Dynamic Resizing**: Automatically adjusts its storage capacity as elements are added, ensuring efficient memory usage without the need for manual resizing.
- **Template Class**: As with other container types in the STL, `CustomQueue` is a template class, allowing it to hold elements of any type.
- **Element Access**: Provides `front()` and `back()` accessors to respectively retrieve references to the first and the last element in the queue.

### Example Usage

```cpp
#include "include/queue.h"

int main() {
    // Create a CustomQueue and initialize it with some values
    CustomQueue<int> myQueue{1, 2, 3, 4, 5};

    // Add an element to the queue
    myQueue.push(6);

    // Access the front and back elements
    std::cout << "Front: " << myQueue.front() << ", Back: " << myQueue.back() << '\n';

    // Remove an element from the queue
    myQueue.pop();

    // Check if the queue is empty and print its size
    if (!myQueue.empty()) {
        std::cout << "Queue size: " << myQueue.size() << '\n';
    }

    return 0;
}
```

### Technical Details

* Provides a minimal and straightforward interface for queue operations, including `push()` for adding elements, `pop()` for removing the front element, and `emplace()` for in-place construction of elements.

## Custom Set Container Implementation

The `CustomSet` class offers a simplified version of a set, resembling the `std::set` found in the C++ Standard Template Library (STL). This custom implementation focuses on maintaining a collection of unique elements sorted by value, providing efficient operations for insertion, deletion, and search without allowing duplicate elements.

### Features and Design

- **Unique Elements**: Ensures all elements in the set are unique, automatically preventing duplicates upon insertion.
- **Sorted Order**: Maintains elements in a sorted order, enabling efficient search operations and ordered traversal.
- **Custom Iterator**: Includes a `CustomSetIterator` for navigating through the set elements, supporting both forward and backward iteration as well as arithmetic operations.
- **Dynamic Resizing**: Dynamically adjusts its capacity to accommodate new elements, ensuring optimal space utilization.

### Example Usage

```cpp
#include "include/set.h"

int main() {
    // Initialize a CustomSet with some numbers
    CustomSet<int> mySet{4, 1, 2, 3, 2, 4, 5};

    // Attempt to insert duplicates
    mySet.insert(3);
    mySet.insert(6);

    // Iterate over the set and print elements (duplicates are ignored)
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // Check for the presence of an element
    if (mySet.contains(3)) {
        std::cout << "3 is in the set\n";
    }

    // Remove an element
    mySet.erase(4);

    // Print size of the set
    std::cout << "Size of the set: " << mySet.size() << '\n';

    return 0;
}
```

## Technical Details

* The `CustomSetIterator` supports typical iterator operations like increment, decrement, and comparison, facilitating easy traversal of the set's elements.

## Custom Stack Container Implementation

The `CustomStack` class is a custom implementation designed to emulate the functionality of the `std::stack` container adapter found in the C++ Standard Template Library (STL). This implementation focuses on providing a last-in, first-out (LIFO) data structure, which is highly effective for various applications that require elements to be processed in reverse order of their addition.

### Features and Design

- **LIFO Element Access**: Elements are added to and removed from the top of the stack, ensuring that the last element added is the first one to be removed.
- **Dynamic Capacity**: Automatically resizes to accommodate new elements, ensuring that the stack can grow as needed without manual intervention.
- **Template Class**: As with other container types in STL, `CustomStack` is a template class, making it suitable for holding elements of any type.
- **Element Access and Modification**: Provides `top()` for accessing the top element, `push()` for adding elements, `pop()` for removing the top element, and `emplace()` for constructing elements in place.

### Example Usage

```cpp
#include "include/stack.h"

int main() {
    // Initialize a CustomStack with some values
    CustomStack<int> myStack{1, 2, 3, 4, 5};

    // Add an element to the stack
    myStack.push(6);

    // Access the top element
    std::cout << "Top element: " << myStack.top() << '\n';

    // Remove the top element
    myStack.pop();

    // Check if the stack is empty and print its size
    if (!myStack.empty()) {
        std::cout << "Stack size: " << myStack.size() << '\n';
    }

    return 0;
}
```

### Technical Details

* Internally, `CustomStack` may use an array or another container type to store its elements, implementing logic to manage capacity and size automatically.
* Provides a minimalistic interface focusing on essential stack operations, making it easy to use while still offering powerful capabilities for element management.

## Custom Vector Container Implementation

The `CustomVector` class is a custom implementation that mirrors the functionality of the `std::vector` in the C++ Standard Template Library (STL). This implementation aims to provide dynamic array functionality, allowing automatic resizing, flexible storage, and efficient access to elements.

### Features and Design

- **Dynamic Resizing**: Automatically increases its capacity to accommodate new elements, ensuring efficient storage management.
- **Element Access**: Offers direct access to elements through `operator[]`, `at()`, `front()`, `back()`, and `data()`, with bounds checking on `at()`.
- **Custom Iterators**: Includes a `CustomVectorIterator` for seamless iteration over its elements, supporting both forward and backward traversal.
- **Template Class**: As a template class, it can hold elements of any data type, making it versatile for a wide range of applications.

### Example Usage

```cpp
#include "include/vector.h"

int main() {
    // Initialize a CustomVector with an initial capacity
    CustomVector<int> myVector(10);

    // Fill the vector with values
    for (int i = 0; i < 10; ++i) {
        myVector.push_back(i * 10);
    }

    // Access and modify elements
    myVector[5] = 50;

    // Iterate over the vector
    for (auto it = myVector.begin(); it != myVector.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // Use range-based for loop
    for (const auto& value : myVector) {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

### Technical Details

* Internally, `CustomVector` manages its elements through a dynamically allocated array, resizing itself using `reallocate()` when necessary.
* Provides a comprehensive set of operations for manipulating its contents, including `insert()`, `erase()`, `push_back()`, `pop_back()`, and `clear()`, mirroring those found in std::vector.

## Makefile for STL Container Implementation

This Makefile is designed to facilitate the building, testing, and maintenance of the STL Container Implementation project. It leverages `xmake` for building the project and includes targets for debugging, linting, formatting, generating coverage reports, and cleaning up the project.

### Key Targets

- **all**: Builds the test suite and generates a coverage report.
- **debug**: Configures and builds the project in debug mode using `xmake`.
- **clean**: Cleans the build directory and removes any generated archive files.
- **lint**: Checks the code format against the Google style guide using `clang-format`.
- **format**: Automatically formats all `.cpp` and `.h` files in the project according to the Google style guide.
- **intellisense**: Generates a `compile_commands.json` file for better IDE integration and code analysis.
- **test**: Builds and runs the unit tests in release mode.
- **gcov_report**: Generates a coverage report using `gcov` and `genhtml`, then opens it in the default web browser.
- **valgrind**: Runs the unit tests under `valgrind` to detect memory leaks and errors.
- **fclean**: Performs a deep clean, removing the build directory and any `xmake` generated files.

### Usage

To use this Makefile, ensure you have `xmake`, `clang-format`, `gcov`, `genhtml`, and `valgrind` installed on your system. Then, you can execute any of the above targets using the `make` command. For example:

```bash
make test         # Builds and runs the unit tests
make format       # Formats all source files according to the Google style guide
make gcov_report  # Generates and opens the coverage report
```

### Notes

* The `EXTRA_BUILD_FLAGS` variable allows for passing additional flags to the `xmake build` command.
* The `CLANG_ARGS` variable specifies the arguments for `clang-format`, targeting all `.cpp` and `.h` files recursively.
* The `.RECIPEPREFIX` directive sets the character used for recipe lines to `>`, allowing for a more readable Makefile format.

## Contributing
Contributions to improve this implementation are welcome. Please follow the Google style guide for C++ code and ensure that any additions come with corresponding unit tests.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.