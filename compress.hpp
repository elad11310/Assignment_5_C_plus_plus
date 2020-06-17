//
// Created by elad on 17/06/2020.
//

#ifndef MATALA5_CONTAINERS_COMPRESS_H
#define MATALA5_CONTAINERS_COMPRESS_H


namespace itertools {


    template<typename Container, typename boolContainer>

    class compress {


        Container c1;
        boolContainer c2;

    public:
        compress(Container C1, boolContainer C2) : c1(C1), c2(C2) {}


        class iterator {
            typename Container::iterator c1Begin;
            typename Container::iterator c1End;
            typename boolContainer::iterator c2Begin;
            typename boolContainer::iterator c2End;


        public:
            iterator(typename Container::iterator c1B, typename Container::iterator c1E,
                     typename boolContainer::iterator c2B, typename boolContainer::iterator c2E) :
                    c1Begin(c1B), c1End(c1E), c2Begin(c2B), c2End(c2E) {}


            void operator=(decltype(*(c1Begin)) var) {

                *(c1Begin) = var;

            }


            auto operator*() {

                while (!(*c2Begin) && c2Begin != c2End) {
                    ++c1Begin;
                    ++c2Begin;
                }

                return *(c1Begin);
            }


            //++i
            iterator &operator++() {
                ++c1Begin;
                ++c2Begin;

                while (!(*c2Begin) && c2Begin != c2End) {
                    ++c1Begin;
                    ++c2Begin;
                }

                return *this;


            }

            //i++
            iterator operator++(int dummy) {

                iterator temp = *this;
                ++c1Begin;
                ++c2Begin;
                return temp;
            }


            bool operator==(iterator &other) {
                return c1Begin == other.c1Begin;
            }


            bool operator!=(iterator &other) {
                return !operator==(other);
            }


        };


        iterator begin() { return iterator(c1.begin(), c1.end(), c2.begin(), c2.end()); }

        iterator end() { return iterator(c1.end(), c1.end(), c2.end(), c2.end()); }

    };


};


#endif //MATALA5_CONTAINERS_COMPRESS_H

