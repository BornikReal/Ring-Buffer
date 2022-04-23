namespace bornik {
    template<typename InputIterator, typename Predicate>
    bool all_of(InputIterator first, InputIterator last, Predicate pred) {
        while (first != last && pred(*first))
            ++first;
        return (first == last);
    }

    template<typename InputIterator, typename Predicate>
    bool any_of(InputIterator first, InputIterator last, Predicate pred) {
        while (first != last && !pred(*first))
            ++first;
        return (first != last);
    }

    template<typename InputIterator, typename Predicate>
    bool none_of(InputIterator first, InputIterator last, Predicate pred) {
        while (first != last && !pred(*first))
            ++first;
        return (first == last);
    }

    template<typename InputIterator, typename Predicate>
    bool one_of(InputIterator first, InputIterator last, Predicate pred) {
        unsigned short num = 0;
        while (first != last) {
            if (pred(*first))
                num++;
            if (num >= 2)
                return false;
            ++first;
        }
        return num;
    }

    template<typename ForwardIterator, typename Compare>
    bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp) {
        ForwardIterator prev = first;
        ++first;
        while (first != last && comp(*prev, *first)) {
            ++prev;
            ++first;
        }
        return (last == first);
    }

    template<typename InputIterator, typename Predicate>
    bool is_partitioned(InputIterator first, InputIterator last, Predicate pred) {
        bool changed = false, cur = pred(*first);
        while (first != last) {
            if (cur != pred(*first)) {
                if (!changed) {
                    changed = true;
                    cur = pred(*first);
                } else
                    return false;
            }
            ++first;
        }
        return changed;
    }

    template<typename InputIterator, typename T>
    InputIterator find_not(InputIterator first, InputIterator last, T key) {
        while (first != last && *first == key)
            ++first;
        return first;
    }

    template<typename BidirectionalIterator, typename T>
    BidirectionalIterator find_backward(BidirectionalIterator first, BidirectionalIterator last, T key) {
        BidirectionalIterator end = last;
        --last;
        --first;
        while (last != first && *first != key)
            --last;
        if (first == last)
            return end;
        return last;
    }

    template<typename BidirectionalIterator, typename Compare>
    bool is_palindrome(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
        BidirectionalIterator end = last;
        --last;
        while (first != end) {
            if (!comp(*first, *last))
                return false;
            ++first;
            --last;
        }
        return true;
    }
}