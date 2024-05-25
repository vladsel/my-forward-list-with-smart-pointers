# my-forward-list-with-smart-pointers

(23.12.2021) Implementation of a singly linked list with the following operations defined:
a) Basic operations with a list: construction, inserting elements into the beginning of the list, iterating through the list, list size, deleting elements.
b) Move operations (Move constructor, Move assignment)
c) The method for inserting elements at the beginning must have an overload for rvalue references, and move objects correctly.
d) Constructing a list using a constructor that accepts a std::initializer_list.
e) The list must be template, and work not only with primitive values, but also with objects (and free them correctly)
f) Ideally, you should strive for a class interface like std::forward_list, but you do not need to implement absolutely all methods.
To work with memory, it is correct to use smart pointers (std::unique_ptr).
