//
// Created by elad on 13/06/2020.
//
#include <iostream>
#include <iterator>


#ifndef MATALA5_CONTAINERS_ACCUMULATE_H
#define MATALA5_CONTAINERS_ACCUMULATE_H


namespace itertools {

    // deafult function for the accumulate
    typedef struct {
        template<typename T>
        T operator()(T a, T b) const {
            return a + b;
        }

    } myFunc;


    template<typename Container, typename Func = myFunc>
    class accumulate {
        Container x;
        // f cannot take reference because if we send a func that is lambada type its not kept in the memory, so
        // we dont have reference to it.
        // const Func &f = myFunc();
        Func f;

    public:
        accumulate(Container X, Func func = myFunc()) : x(X), f(func) {}

    public:
        class iterator {
            // taking out the continer T iterators.
            typename Container::iterator itBegin;
            typename Container::iterator itEnd;
            // now taking the begin iterator's type of value using value_type
            typename Container::value_type data;


            Func func;


        public:
            explicit iterator(typename Container::iterator begin, typename Container::iterator end, Func F) :
                    itBegin(begin),
                    itEnd(end),
                    func(F), data((*begin)) {}

            //copy constructor
            iterator(const iterator &other) = default;

            iterator &operator=(const iterator &other) {
                if (&other != this) {
                    iterator(other.itBegin, other.itEnd, other.func);
                }
                return *this;
            }

            auto operator*() const { return data; }

            // prefix ++i
            iterator &operator++() {
                ++itBegin;
                // calling the function that determines which arithmetic operation on both indices.
                if (itBegin != itEnd) {
                    data = func(data, *itBegin);

                }
                return *this;
            }

            //postfix i++
            iterator operator++(int dummyFlag) {
                // points to the first element in the object(itBegin)
                iterator t = *this;
                ++(*this);
                return t;
            }

            bool operator!=(const iterator &ri) const {
                return !operator==(ri);
            }


            bool operator==(const iterator &ri) const {
                return itBegin == ri.itBegin;
            }

        };

        iterator begin() { return iterator(x.begin(), x.end(), f); }

        iterator end() { return iterator(x.end(), x.end(), f); }


    };
}
#endif //MATALA5_CONTAINERS_ACCUMULATE_H
