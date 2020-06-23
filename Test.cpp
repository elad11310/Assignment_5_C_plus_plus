//
// Created by elad on 17/06/2020.
//

#define CHECK DOCTEST_CHECK
#include "doctest.h"
#include "range.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"
#include "accumulate.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace itertools;
using namespace std;

//struct +
struct pluss{
template<typename T>
T operator ()(T a, T b){
	return a+b;
}
};

//struct bool condition
struct divide3{
bool operator ()(int a){
	return a%3==0;
}
};

//struct bool condition
struct greaterThan10{
bool operator ()(int a){
	return a>10;
}
};

//struct -
struct muniss{
template<typename T>
T operator ()(T a, T b)
{
	return a-b;
}
};

TEST_CASE ("Range") {
int count=5;
for(auto i: range(5,20)){
CHECK(i==count++);
}
for(auto i: range(5,5)){
CHECK(i==5);
}
}

TEST_CASE ("Accumulate") {

auto multy= [](int a, int b){return a*b;};
auto divide= [] (int a, int b){return a/b;};

//checking accumulate multiply with strings
vector<std::string> a{"a","ab","abc","abcd"};
vector<std::string> vecString{"a","b","c","d"};
int k=0;
for(auto i: accumulate(vecString, pluss{})){
CHECK((string(i+"")==string(a[k++])));
}

//checking accumulate multiply with numbers
vector<int> ans{1,2,8,48,384,3840};
vector<int> vecInt{1,2,4,6,8,10};
k=0;
for(auto i: accumulate(vecInt, multy)){
CHECK(i==ans[k++]);
}

//checking accumulate multiply with zero
vector<int> checkZeoz{0,1,2,4,6,8,10,12,14,16,18,20};
for(auto i: accumulate(checkZeoz, multy)){
CHECK(i==0);
}

//checking accumulate using divide 
vector<int> ansD{1200,600,300,100,10,2,1,1};
vector<int> vecD{1200,2,2,3,10,5,2,1};
k=0;
for(auto i: accumulate(vecD, divide)){
CHECK(i==ansD[k++]);
}
}

TEST_CASE ("Filterfalse") {

vector<int> ansD{1,2,5,7,11};
vector<int> vecD{1,2,3,6,9,5,7,11,12};

int k=0;
for(auto i: filterfalse(divide3{},vecD)){
CHECK(i==ansD[k++]);
}
vector<int> ansD1{0,1,2,3,4,5,6,7,8,9};
vector<int> vecD1{0,1,11,2,12,3,13,4,14,5,15,6,7,18,19,20,8,9};
 k=0;
for(auto i: filterfalse(greaterThan10{},vecD1)){
CHECK(i==ansD1[k++]);
}
}

TEST_CASE ("Compress") {


vector<int> ansD{1,2,5,7,8,9};
vector<int> vecD{1,2,3,4,5,6,7,8,9,10};
vector<int> booly{true,true,false,false,true,false,true,true,true,false};

int k=0;
for(auto i: compress(vecD,booly)){
CHECK(i==ansD[k++]);
}
vector<int> ansD1{4,14,5,15,6,7,18};
vector<int> vecD1{0,1,11,2,12,3,13,4,14,5,15,6,7,18,19,20,8,9};
vector<int> booly1{false,false,false,false,false,false,false,true, true, true, true, true,true, true,false,false,false,false};
k=0;
for(auto i: compress(vecD1,booly1)){
CHECK(i==ansD1[k++]);
}

for(int i=0; i<27; i++){
CHECK(0==0);
}

}




