//
// Created by elad on 13/06/2020.
//

#include <cstddef>
#include <cassert>
#include <vector>

#ifndef MATALA5_CONTAINERS_RANGE_H
#define MATALA5_CONTAINERS_RANGE_H

#endif //MATALA5_CONTAINERS_RANGE_H

namespace itertools {
    template<typename T = size_t>
    class range {

        const T kStart, kEnd, step;
    public:
        range(const T Start, const T End, const T Step = 1) : kStart(Start), kEnd(End), step(Step) {
            // checking if the offset isn't 0
            // checking legal input
            assert(kStart >= 0 && kEnd > 0 && kStart <= kEnd && step > 0);
        }

        // default constructor.

        range(const T End) : kStart(0), kEnd(End), step(1) {
            assert(kEnd > 0);
        }


        ///// until now its for the range
        ///// now we build its iterator.


    public:

        class iterator {

            T val;
            const T step;

        public:
            iterator(T Val, const T Step) : val(Val), step(Step) {}

            operator T const() { return val; }

            operator const T &() { return val; }

            const T operator*() const { return val; }

            const iterator &operator++() {
                val += step;
                return *this;
            }

            bool operator!=(const iterator &ri) const {
                // checking first if val<0 (range on negative numbers) if not range on positive numbers.
                return val < 0 ? val > ri.val : val < ri.val;
            }


            bool operator==(const iterator &ri) const {
                return !operator!=(ri);
            }

        };

          iterator begin() const { return iterator(kStart, step); }

          iterator end() const { return iterator(kEnd, step); }


//    public:
//
//        // Conversion to any vector< T >
//        operator std::vector< T > ( void )
//        {
//            std::vector< T > retRange;
//            for( T i = kStart; i < kEnd; i += step )
//                retRange.push_back( i );
//            return retRange;    // use move semantics here
//        }

    };


}

