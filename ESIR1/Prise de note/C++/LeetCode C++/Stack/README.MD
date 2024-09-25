# C++ Stack Overview

## What is a Stack?

A **stack** is a linear data structure that follows the **Last-In, First-Out (LIFO)** principle. This means that the last element added to the stack is the first one to be removed. 

Imagine a stack of plates: 
- You can only remove the top plate (the last one you put on).
- Similarly, you can only add a new plate on top.

### Stack Schema:

```plaintext
   _______
  |   5   |  <-- Top element (last added, first to be removed)
  |   3   | 
  |   2   | 
  |   1   |  <-- Bottom element (first added, last to be removed)
   -------
```

## Stack in C++

### Initializing a Stack

To use a stack in C++, you first need to include the '<stack>' library.

```cpp
#include <stack>
```

You can initialize a stack with a specific data type (e.g., char, int, etc.):

```cpp
std::stack<char> stack;
std::stack<int> numStack;
```

### Basic Stack Operations

1. Check if the stack is empty
	- This operation returns 'true' if the stack is empty, otherwise 'false'.

```cpp
stack.empty();  // Returns true if empty, false otherwise
```

2. Push an element to the stack:
	- This operation adds an element to the top of the stack.

```cpp
stack.push('A');  // Adds 'A' to the top of the stack
numStack.push(10);  // Adds 10 to the top of the stack
```

3. Get the top element
	- This operation removes the top element from the stack.

```cpp
stack.pop();  // Removes 'A' from the stack
numStack.pop();  // Removes 10 from the stack
```

4. Pop the top element
	- This operation removes the top element from the stack

```cpp
stack.pop();  // Removes 'A' from the stack
numStack.pop();  // Removes 10 from the stack
```

5. Get the size of the stack (optional for convenience):
	- You can check how many elements are in the stack

```cpp
int size = stack.size();  // Returns the number of elements in the stack
```

### Exemple of a stack in Action

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> numStack;

    // Push elements onto the stack
    numStack.push(1);
    numStack.push(2);
    numStack.push(3);

    // Output the top element
    std::cout << "Top element: " << numStack.top() << std::endl;  // 3

    // Remove the top element
    numStack.pop();

    // Output the new top element
    std::cout << "New top element: " << numStack.top() << std::endl;  // 2

    return 0;
}
```

### Real-World Uses of Stack in LeetCode
Stacks are commonly used in problems like:

- **Balanced Parentheses**: Where you need to ensure that every opening parenthesis has a corresponding closing one.
- **Depth-First Search (DFS)**: In graph traversal algorithms.
- **Backtracking**: When you need to explore all possible options and revert when necessary.
