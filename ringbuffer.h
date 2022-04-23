#include <iostream>
#include "iterator.h"

#pragma once

template<class type_name>
class ringbuffer {
private:
    type_name *container_;
    type_name *begin_;
    type_name *end_;
    long long size_{};
    long long capacity_{};
public:
    explicit ringbuffer(unsigned long long size = 0) : size_((long long) size), capacity_(0) {
        try {
            container_ = new type_name[size];
        }
        catch (...) {
            std::cout << "Allocation error: the buffer cannot allocate memory.\n";
            return;
        }
        begin_ = container_;
        end_ = container_ + capacity_;
    }

    ringbuffer(const ringbuffer &rhs) {
        container_ = nullptr;
        *this = rhs;
    }

    ringbuffer &operator=(const ringbuffer &rhs) {
        if (&rhs == this)
            return *this;
        delete[] container_;
        try {
            container_ = new type_name[rhs.size_];
        }
        catch (...) {
            std::cout << "Allocation error: the buffer cannot allocate memory.\n";
            return *this;
        }
        long long i = 0;
        for (auto it = rhs.begin(); it != rhs.end(); ++it) {
            container_[i] = *it;
            ++i;
        }
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        begin_ = container_;
        if (capacity_ != size_)
            end_ = container_ + capacity_;
        else
            end_ = container_;
        return *this;
    }

    [[nodiscard]] ringbuffer_ra_iterator<type_name> begin() const {
        return ringbuffer_ra_iterator<type_name>(begin_, container_, container_ + size_, 0, capacity_);
    }

    [[nodiscard]] ringbuffer_ra_iterator<type_name> end() const {
        return ringbuffer_ra_iterator<type_name>(end_, container_, container_ + size_, capacity_, capacity_);
    }

    void resize(unsigned long long new_size) {
        type_name *new_container;
        try {
            new_container = new type_name[new_size];
        }
        catch (...) {
            std::cout << "Allocation error: the buffer cannot allocate memory.\n";
            return;
        }
        long long i = 0;
        for (auto it = begin(); it != end(); ++it) {
            if (i == new_size)
                break;
            new_container[i] = *it;
            ++i;
        }
        begin_ = new_container;
        if (capacity_ > new_size)
            capacity_ = (long long) new_size;
        end_ = new_container + capacity_;
        size_ = (long long) new_size;
        delete[] container_;
        container_ = new_container;
    }

    type_name &operator[](long long rhs) {
        return *(begin() + rhs);
    }

    void push_back(type_name rhs) {
        if (capacity_ == size_)
            resize(size_ * 2);
        *end_ = rhs;
        ++end_;
        ++capacity_;
        if (end_ == (container_ + size_))
            end_ = container_;
    }

    void push_front(type_name rhs) {
        if (capacity_ == size_)
            resize(size_ * 2);
        --begin_;
        ++capacity_;
        if ((begin_ - container_) < 0)
            begin_ = container_ + size_ - 1;
        *begin_ = rhs;
    }

    void pop_back() {
        if (capacity_ == 0)
            return;
        else if (capacity_ == 1) {
            capacity_ = 0;
            begin_ = container_;
            end_ = container_;
            return;
        }
        --end_;
        --capacity_;
        if ((end_ - container_) < 0)
            end_ = container_ + size_ - 1;
    }

    void pop_front() {
        if (capacity_ == 0)
            return;
        else if (capacity_ == 1) {
            capacity_ = 0;
            begin_ = container_;
            end_ = container_;
            return;
        }
        ++begin_;
        --capacity_;
        if (begin_ == (container_ + size_))
            begin_ = container_;
    }

    size_t size() {
        return size_;
    }

    size_t capacity() {
        return capacity_;
    }

    type_name &front() {
        return *begin_;
    }

    type_name &back() {
        return *(end() - 1);
    }

    ~ringbuffer() = default;
};