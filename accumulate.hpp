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
       Func f ;

    public:
         accumulate(Container X, Func func=myFunc()) : x(X), f(func) {}

    public:
        class iterator {
            // taking out the continer T iterators.
            typename Container::iterator itBegin;
            typename Container::iterator itEnd;
            // now taking the begin iterator's type of value using decltype.(int,double,string...)
            decltype(*(x.begin())) data;
             Func func;


        public:
             explicit  iterator( typename Container::iterator begin, typename Container::iterator end,  Func F) :
                                                                                                     itBegin(begin),
                                                                                                     itEnd(end),
                                                                                                     func(F),data(*begin) {}
             //copy constructor
            iterator (const iterator & other)= default;
             iterator & operator =(const iterator & other){
                 if(&other!=this){
                    iterator(other.itBegin, other.itEnd, other.func) ;
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

         iterator begin()  { return iterator(x.begin(), x.end(), f); }

          iterator end()  { return iterator(x.end(), x.end(), f); }


    };
}
#endif //MATALA5_CONTAINERS_ACCUMULATE_H


//
//
//
//#ifndef ITERTOOLS_CFAR_A_MASTER_ACCUMULATE_HPP
//#define ITERTOOLS_CFAR_A_MASTER_ACCUMULATE_HPP
//
//#include "range.hpp"
//
//#include <iterator>
//
//namespace itertools {
//    typedef struct {
//        template<typename T>
//        T operator()(T a, T b) const {
//            return a+b;
//        }
//    }myFunc;
//    template <typename VAC, typename FUNC = myFunc>
//    class accumulate {
//        VAC data;
//        FUNC func;
//    public:
//        explicit accumulate(VAC x,FUNC f = myFunc()) : data(x), func(f) {}
//        class iterator{
//            decltype (*(data.begin())) _it_data;
//            typename VAC::iterator _iter;
//            typename VAC::iterator _it_end;
//            FUNC _it_func;
//        public:
//            explicit iterator(typename VAC::iterator it, typename VAC::iterator end, FUNC func)
//                    : _iter(it), _it_end(end), _it_func(func), _it_data(*it){};
//            iterator(const iterator& other) = default;
//            iterator& operator=(const iterator& other) {
//                if (&other != this){
//                    iterator(other._iter,other._it_end,other._it_func);
//                }
//                return *this;
//            }
//            iterator& operator++(){
//                ++_iter;
//                if(_iter != _it_end)
//                    _it_data = _it_func(_it_data, *_iter);
//                return *this;
//            }
//            iterator operator++(int){
//                iterator temp = *this;
//                ++(*this);
//                return temp;
//            }
//            bool operator==(const iterator& other) {
//                return (_iter == other._iter);
//            }
//            bool operator!=(const iterator& other) {
//                return (_iter != other._iter);
//            }
//
//            auto operator*(){
//                return _it_data;
//            }
//        };
//
//        iterator begin(){
//            return iterator(data.begin(), data.end(), func);
//        }
//        iterator end(){
//            return iterator(data.end(), data.end(), func);
//        }
//
//
//    };
//
//};
//#endif //ITERTOOLS_CFAR_A_MASTER_ACCUMULATE_HPP
