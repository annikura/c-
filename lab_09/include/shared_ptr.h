#pragma once

#include "matrix.h"

class shared_ptr {
    public:
        void swap(shared_ptr & other);

        shared_ptr();
        shared_ptr(Matrix *obj);
        shared_ptr(const shared_ptr & other);
        shared_ptr & operator=(shared_ptr other);
        ~shared_ptr();

        Matrix* ptr() const;
        bool isNull() const;
        void reset(Matrix *obj);
        void reset();

        Matrix* operator->() const;
        Matrix& operator*() const;

    private:
        class Storage {
        public:
            void swap(Storage & other);

            Storage();
            Storage(Matrix* mtx);
            ~Storage();

            void incr();
            void decr();

            int getCounter() const;
            Matrix *getObject() const;

        private:
            Matrix *data_;
            int ref_count_;
        };

    private:
        Storage *storage_;
};
