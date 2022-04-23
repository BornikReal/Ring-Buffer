template<class type_name>
class ringbuffer;

template<class T>
class ringbuffer_ra_iterator : public std::iterator<std::random_access_iterator_tag, T> {
    friend class ringbuffer<T>;

private:
    T *val_;
    T *begin_;
    T *end_;
    long long pos_{};
    long long size_{};
protected:
    explicit ringbuffer_ra_iterator(T *val, T *begin, T *end, unsigned long long pos, long long size) {
        val_ = val;
        pos_ = (long long) pos;
        begin_ = begin;
        end_ = end;
        size_ = size;
    }

public:
    ringbuffer_ra_iterator() = default;

    ringbuffer_ra_iterator(const ringbuffer_ra_iterator<T> &rhs) = default;

    ringbuffer_ra_iterator &operator=(const ringbuffer_ra_iterator<T> &rhs) = default;

    ~ringbuffer_ra_iterator() = default;

    T &operator*() const {
        return *val_;
    }

    ringbuffer_ra_iterator &operator++() {
        ++pos_;
        if (pos_ > size_) {
            val_ -= (pos_ - 1);
            pos_ = 0;
            return *this;
        }
        ++val_;
        if (val_ == end_)
            val_ = begin_;
        return *this;
    }

    const ringbuffer_ra_iterator operator++(int) {
        ringbuffer_ra_iterator<T> new_it(*this);
        ++(*this);
        return new_it;
    }

    ringbuffer_ra_iterator operator+(long long rhs) const {
        ringbuffer_ra_iterator new_it(*this);
        long long n = rhs % size_;
        if (pos_ + n > size_) {
            new_it.pos_ = n - (size_ - pos_);
            new_it.val_ = val_ - pos_ + new_it.pos_;
            return new_it;
        } else
            new_it.pos_ = pos_ + n;
        if (end_ - val_ <= n)
            new_it.val_ = begin_ + n - (end_ - val_);
        else
            new_it.val_ += n;
        return new_it;
    }

    ringbuffer_ra_iterator &operator+=(long long rhs) {
        *this = *this + rhs;
        return *this;
    }

    ringbuffer_ra_iterator &operator--() {
        --pos_;
        if (pos_ < 0) {
            val_ = val_ - pos_ + size_ - 1;
            pos_ = size_;
            return *this;
        }
        --val_;
        if (val_ == (begin_ - 1))
            val_ = end_ - 1;
        return *this;
    }

    const ringbuffer_ra_iterator operator--(int) {
        ringbuffer_ra_iterator<T> new_it(*this);
        --(*this);
        return new_it;
    }

    ringbuffer_ra_iterator operator-(long long rhs) const {
        ringbuffer_ra_iterator new_it(*this);
        long long n = rhs % size_;
        if (pos_ - n < 0) {
            new_it.pos_ = size_ - (n - pos_);
            new_it.val_ = val_ - pos_ + new_it.pos_;
            return new_it;
        } else
            new_it.pos_ = pos_ - n;
        if (val_ - begin_ <= n)
            new_it.val_ = end_ - (n - (val_ - begin_));
        else
            new_it.val_ -= n;
        return new_it;
    }

    long long operator-(const ringbuffer_ra_iterator<T> &rhs) const {
        return pos_ - rhs.pos_;
    }

    ringbuffer_ra_iterator &operator-=(long long rhs) {
        *this = *this - rhs;
        return *this;
    }

    bool operator==(const ringbuffer_ra_iterator &rhs) const {
        return (val_ == rhs.val_) && (pos_ == rhs.pos_);
    }

    bool operator!=(const ringbuffer_ra_iterator &rhs) const {
        return !((val_ == rhs.val_) && (pos_ == rhs.pos_));
    }

    bool operator<(const ringbuffer_ra_iterator &rhs) const {
        if (pos_ >= size_)
            return true;
        if (rhs.pos_ >= size_)
            return false;
        return pos_ < rhs.pos_;
    }

    bool operator<=(const ringbuffer_ra_iterator &rhs) const {
        if (pos_ >= size_)
            return true;
        if (rhs.pos_ >= size_)
            return false;
        return pos_ <= rhs.pos_;
    }

    bool operator>(const ringbuffer_ra_iterator &rhs) const {
        if (pos_ >= size_)
            return false;
        if (rhs.pos_ >= size_)
            return true;
        return pos_ > rhs.pos_;
    }

    bool operator>=(const ringbuffer_ra_iterator &rhs) const {
        if (pos_ >= size_)
            return false;
        if (rhs.pos_ >= size_)
            return true;
        return pos_ >= rhs.pos_;
    }

    T operator[](long long rhs) const {
        return *(*this + rhs);
    }
};
