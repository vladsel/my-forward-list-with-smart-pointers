#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>

using namespace std;

template <typename T>
struct node {
    T val;
    unique_ptr <node <T>> next;
    node() = default;
    node(T &x) : val(x) {}
    node(T &&x) : val(x) {}
};

template <typename T>
class forward_list {
public:
    forward_list() = default;
    ~forward_list() = default;
    forward_list(forward_list <T> &&list) noexcept;
    forward_list(const initializer_list <T> &list);
    void push_front(T &val);
    void push_front(T &&val);
    void print_list() const;
    T &operator[](const size_t pos);
    const T &operator[](const size_t pos) const;
    forward_list<T> &operator=(forward_list <T> &&list) noexcept;
    size_t size() const;
    void erase(const size_t pos);
private:
    T &return_value_by_pos_private(const unique_ptr <node <T>> &last, const size_t &pos, size_t &index) const;
    void push_front_private(unique_ptr <node <T>> &last, T &val);
    void push_front_private(unique_ptr <node <T>> &last, T &&val);
    void print_list_private(const unique_ptr <node <T>> &last) const;
    void delete_list(unique_ptr <node <T>> &last);
    void erase_private(unique_ptr <node <T>> &last, const size_t &pos, size_t &index);
private:
    unique_ptr <node <T>> head;
    size_t list_size = 0;
};

template<typename T>
inline forward_list<T>::forward_list(forward_list<T> &&list) noexcept {
    if (list.size() <= 0)
        throw exception("\nlist is empty\n");
    head.reset(list.head.release());
    list_size = list.list_size;
}

template<typename T>
inline forward_list<T>::forward_list(const initializer_list<T> &list) {
    for (auto temp : list)
        push_front(temp);
}

template<typename T>
inline void forward_list<T>::push_front(T &val) {
    if (!head) {
        head = make_unique<node <T>>(val);
    }
    else {
        push_front_private((*head).next, val);
    }
    list_size++;
}

template<typename T>
inline void forward_list<T>::push_front(T &&val) {
    if (!head) {
        head = make_unique<node <T>>(val);
    }
    else {
        push_front_private((*head).next, val);
    }
    list_size++;
}

template<typename T>
inline void forward_list<T>::print_list() const {
    if (!head) {
        throw exception("\nempty list\n");
    }
    else {
        print_list_private((*head).next);
        cout << (*head).val;
    }
}

template<typename T>
inline size_t forward_list<T>::size() const {
    return list_size;
}

template<typename T>
inline void forward_list<T>::erase(const size_t pos) {
    if (pos >= size()) {
        throw out_of_range("\nindex is out of range\n");
    }
    else {
        if (!head) {
            throw exception("\nempty list\n");
        }
        else {
            if (pos == 0) {
                head.reset(((*head).next).release());
            }
            else {
                size_t index = 0;
                erase_private((*head).next, pos, index);
            }
            list_size--;
        }
    }
}

template<typename T>
inline T &forward_list<T>::operator[](const size_t pos) {
    if (pos >= size()) {
        throw out_of_range("\nindex is out of range\n");
    }
    else {
        if (!head) {
            throw exception("\nempty list\n");
        }
        else {
            if (pos == 0)
                return (*head).val;
            else {
                size_t index = 0;
                return return_value_by_pos_private((*head).next, pos, index);
            }
        }
    }
}

template<typename T>
inline const T &forward_list<T>::operator[](const size_t pos) const {
    if (pos >= size()) {
        throw out_of_range("\nindex is out of range\n");
    }
    else {
        if (!head) {
            throw exception("\nempty list\n");
        }
        else {
            if (pos == 0)
                return (*head).val;
            else {
                size_t index = 0;
                return return_value_by_pos_private((*head).next, pos, index);
            }
        }
    }
}

template<typename T>
inline forward_list<T> &forward_list<T>::operator=(forward_list<T> &&list) noexcept {
    if (&list == this)
        return *this;
    if (head) {
        delete_list((*head).next);
        head.release();
        list_size = 0;
    }
    head.reset(list.head.release());
    list_size = list.list_size;
    return *this;
}

template<typename T>
inline T &forward_list<T>::return_value_by_pos_private(const unique_ptr<node<T>> &last,
                                                       const size_t &pos, size_t &index) const {
    if (last) {
        index++;
        if (index == pos)
            return (*last).val;
        else
            return return_value_by_pos_private((*last).next, pos, index);
    }
    else
        throw out_of_range("\nindex is out of range\n");
}

template<typename T>
inline void forward_list<T>::push_front_private(unique_ptr<node<T>> &last, T &val) {
    if (last)
        push_front_private((*last).next, val);
    else
        last = make_unique<node <T>>(val);
}

template<typename T>
inline void forward_list<T>::push_front_private(unique_ptr<node<T>> &last, T &&val) {
    if (last)
        push_front_private((*last).next, val);
    else
        last = make_unique<node <T>>(val);
}

template<typename T>
inline void forward_list<T>::print_list_private(const unique_ptr<node<T>> &last) const {
    if (last)
        print_list_private((*last).next);
    else
        return;
    cout << (*last).val << " <-- ";
}

template<typename T>
inline void forward_list<T>::delete_list(unique_ptr<node<T>> &last) {
    if (last)
        delete_list((*last).next);
    else
        return;
    last.release();
}

template<typename T>
inline void forward_list<T>::erase_private(unique_ptr<node<T>> &last, const size_t &pos, size_t &index) {
    if (last) {
        index++;
        if (index == pos)
            last.reset(((*last).next).release());
        else
            return erase_private((*last).next, pos, index);
    }
    else
        throw out_of_range("\nindex is out of range\n");
}
