// Copyright 2021 GNDavydov

#ifndef INCLUDE_UNIQUE_PTR_HPP_
#define INCLUDE_UNIQUE_PTR_HPP_


namespace my_unique_ptr {
    template<class T>
    class unique_ptr {
    private:
        T *data_;

    public:
        unique_ptr() noexcept: data_(nullptr) {}

        explicit unique_ptr(T *data) noexcept: data_(data) {}

        unique_ptr(const unique_ptr &) = delete;

        unique_ptr(unique_ptr &&move) noexcept: data_(std::move(move.data_)) {
            move.data_ = nullptr;
        }

        unique_ptr &operator=(const unique_ptr &) = delete;

        unique_ptr &operator=(unique_ptr &&move) noexcept {
            if (this == &move) return *this;

            delete data_;
            data_ = std::move(move.data_);
            move.data_ = nullptr;
            return *this;
        }

        ~unique_ptr() noexcept {
            delete data_;
        }

        void reset(T *ptr = nullptr) {
            delete data_;
            data_ = ptr;
        }

        T *release() {
            T *ptr = data_;
            data_ = nullptr;
            return ptr;
        }

        void swap(unique_ptr &oth) noexcept {
            std::swap(data_, oth.data_);
        }

        T *operator->() const noexcept {
            return data_;
        }

        T &operator*() const noexcept {
            return *data_;
        }


        explicit operator bool() const noexcept {
            return data_;
        }

        T *get() const noexcept {
            return data_;
        }
    };
}

#endif //INCLUDE_UNIQUE_PTR_HPP_
