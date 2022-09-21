/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:37:48 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/21 19:37:02 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.hpp"


// Inspired by https://github.com/Mazoise/42TESTERS-CONTAINERS
int main() {
	std::cout << "BEGIN VECTOR TESTS" << std::endl << std::endl;
	{
		std::cout << "BEGIN VECTOR ASSIGN TESTS" << std::endl;
		NAMESPACE::vector<int> first;
		NAMESPACE::vector<int> second;
		NAMESPACE::vector<int> third;

		std::cout << "BEGIN VECTOR ASSIGN TEST 1" << std::endl;
		first.assign (7,100);
		std::cout << "Size: " << int (first.size()) << std::endl;
		print_vector(first);;
		std::cout << "END VECTOR ASSIGN TEST 1" << std::endl;

		std::cout << "BEGIN VECTOR ASSIGN TEST 2" << std::endl;
		NAMESPACE::vector<int>::iterator it = first.begin()+1;
		second.assign (it,first.end()-1);
		std::cout << "Size: " << int (first.size()) << std::endl;
		print_vector(second);
		std::cout << "END VECTOR ASSIGN TEST 2" << std::endl;

		std::cout << "BEGIN VECTOR ASSIGN TEST 3" << std::endl;
		int myints[] = {1776,7,4};
		std::cout << "Size: " << int (first.size()) << std::endl;
		third.assign(myints,myints+3);
		print_vector(third);
		std::cout << "END VECTOR ASSIGN TEST 3" << std::endl;

		std::cout << "END VECTOR ASSIGN TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN VECTOR AT && [] TESTS" << std::endl;

		std::cout << "BEGIN VECTOR AT && [] TEST 1" << std::endl;
		NAMESPACE::vector<int> myvector(10); 
		for (unsigned i = 0; i < myvector.size(); i++)
			myvector.at(i) = i;
		std::cout << "Size: " << int (myvector.size()) << std::endl;
		print_vector(myvector);
		std::cout << "END VECTOR AT && [] TEST 1" << std::endl;

		std::cout << "BEGIN VECTOR AT && [] TEST 2" << std::endl;
		NAMESPACE::vector<char> myvector2(10); 
		for (unsigned i = 0; i < myvector2.size(); i++)
			myvector2[i] = i + 97;
		std::cout << "Size: " << int (myvector2.size()) << std::endl;
		print_vector(myvector2);
		std::cout << "END VECTOR AT && [] TEST 2" << std::endl;

	
		std::cout << "END VECTOR AT && [] TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN VECTOR PUSH_BACK && POP_BACK && FRONT && BACK TESTS" << std::endl;

		std::cout << "BEGIN VECTOR PUSH_BACK && POP_BACK && FRONT && BACK TEST 1" << std::endl;
		NAMESPACE::vector<int> myvector; 
		for (unsigned i = 0; i < 10; i++)
			myvector.push_back(i);
		std::cout << "Size: " << int (myvector.size()) << std::endl;
		std::cout << "Front: " << int (myvector.front()) << std::endl;
		std::cout << "Back: " << int (myvector.back()) << std::endl;
		print_vector(myvector);
		std::cout << "END VECTOR PUSH_BACK && POP_BACK && FRONT && BACK TEST 1" << std::endl;

		std::cout << "BEGIN VECTOR PUSH_BACK && POP_BACK && FRONT && BACK TEST 2" << std::endl;
		for (unsigned i = 0; i < 5; i++)
			myvector.pop_back();
		std::cout << "Size: " << int (myvector.size()) << std::endl;
		std::cout << "Front: " << int (myvector.front()) << std::endl;
		std::cout << "Back: " << int (myvector.back()) << std::endl;
		print_vector(myvector);
		std::cout << "END VECTOR PUSH_BACK && POP_BACK && FRONT && BACK TEST 2" << std::endl;

	
		std::cout << "END VECTOR PUSH_BACK && POP_BACK && FRONT && BACK TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN VECTOR INSERT TESTS" << std::endl;

		NAMESPACE::vector<int> myvector (3,100);
		NAMESPACE::vector<int>::iterator it = myvector.begin();

		std::cout << "BEGIN VECTOR INSERT TEST 1" << std::endl;
		it = myvector.insert (it , 200);
		std::cout << "Returned iterator value: " << *it << std::endl;
		std::cout << "Size: " << int (myvector.size()) << std::endl;
		print_vector(myvector);
		std::cout << "END VECTOR INSERT TEST 1" << std::endl;

		std::cout << "BEGIN VECTOR INSERT TEST 2" << std::endl;
		myvector.insert(it,2,300);
		it = myvector.begin();
		NAMESPACE::vector<int> anothervector(2,400);
		myvector.insert(it+2,anothervector.begin(),anothervector.end());
		std::cout << "Size: " << int (myvector.size()) << std::endl;
		print_vector(myvector);
		std::cout << "END VECTOR INSERT TEST 2" << std::endl;

		std::cout << "BEGIN VECTOR INSERT TEST 3" << std::endl;
		int myarray [] = { 501,502,503 };
		myvector.insert(myvector.begin(), myarray, myarray+3);
		std::cout << "END VECTOR INSERT TEST 3" << std::endl;

		std::cout << "END VECTOR INSERT TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN VECTOR INSERT TESTS" << std::endl;

		NAMESPACE::vector<int> myvector (3,100);
		NAMESPACE::vector<int>::iterator it = myvector.begin();

		std::cout << "BEGIN VECTOR INSERT TEST 1" << std::endl;
		it = myvector.insert (it , 200);
		std::cout << "Returned iterator value: " << *it << std::endl;
		std::cout << "Size: " << int (myvector.size()) << std::endl;
		print_vector(myvector);
		std::cout << "END VECTOR INSERT TEST 1" << std::endl;

		std::cout << "BEGIN VECTOR INSERT TEST 2" << std::endl;
		myvector.insert(it,2,300);
		it = myvector.begin();
		NAMESPACE::vector<int> anothervector(2,400);
		myvector.insert(it+2,anothervector.begin(),anothervector.end());
		std::cout << "Size: " << int (myvector.size()) << std::endl;
		print_vector(myvector);
		std::cout << "END VECTOR INSERT TEST 2" << std::endl;

		std::cout << "BEGIN VECTOR INSERT TEST 3" << std::endl;
		int myarray [] = { 501,502,503 };
		myvector.insert(myvector.begin(), myarray, myarray+3);
		std::cout << "END VECTOR INSERT TEST 3" << std::endl;

		std::cout << "END VECTOR INSERT TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN VECTOR SWAP TESTS" << std::endl;
		NAMESPACE::vector<int> foo (3,100);
		NAMESPACE::vector<int> bar (5,200);
		std::cout << "BEGIN VECTOR SWAP TEST 1" << std::endl;
		std::cout << "foo size: " << foo.size() << std::endl;
		std::cout << "foo contains:" << std::endl;
		print_vector(foo);
		std::cout << "bar size: " << bar.size() << std::endl;
		std::cout << "bar contains:" << std::endl;
		print_vector(bar);
		std::cout << "swap happened" << std::endl;
		foo.swap(bar);
		std::cout << "foo size: " << foo.size() << std::endl;
		std::cout << "foo contains:" << std::endl;
		print_vector(foo);
		std::cout << "bar size: " << bar.size() << std::endl;
		std::cout << "bar contains:" << std::endl;
		print_vector(bar);
		std::cout << "END VECTOR SWAP TEST 1" << std::endl;
		std::cout << "END VECTOR SWAP TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN VECTOR RESERVE TESTS" << std::endl;
		std::cout << "BEGIN VECTOR RESERVE TEST 1" << std::endl;
		NAMESPACE::vector<int>::size_type sz;
		NAMESPACE::vector<int> foo;
		sz = foo.capacity();
		std::cout << "Making foo grow:\n";
		for (int i=0; i<100; ++i) {
			foo.push_back(i);
			if (sz!=foo.capacity()) {
				sz = foo.capacity();
				std::cout << "Capacity changed: " << sz << std::endl;
			}
		}
		std::cout << "END VECTOR RESERVE TEST 1" << std::endl;
		std::cout << "BEGIN VECTOR RESERVE TEST 2" << std::endl;
		NAMESPACE::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);
		std::cout << "Making bar grow:" << std::endl;
		for (int i = 0; i < 100; ++i) {
			bar.push_back(i);
			if (sz != bar.capacity()) {
				sz = bar.capacity();
				std::cout << "Capacity changed: " << sz << std::endl;
			}
		}
		try {
			bar.reserve(bar.max_size() * 2);
		} catch(std::exception& e) { std::cout << e.what() << std::endl; }
		std::cout << "END VECTOR RESERVE TEST 2" << std::endl;
		std::cout << "END VECTOR RESERVE TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN VECTOR BINARY EQUATION TESTS" << std::endl;
		std::cout << "BEGIN VECTOR BINARY EQUATION TEST 1" << std::endl;
		NAMESPACE::vector<int> foo (3,100);
		NAMESPACE::vector<int> bar (2,200);
		if (foo == bar) std::cout << "foo and bar are equal" << std::endl;
		if (foo != bar) std::cout << "foo and bar are not equal" << std::endl;
		if (foo < bar) std::cout << "foo is less than bar" << std::endl;
		if (foo > bar) std::cout << "foo is greater than bar" << std::endl;
		if (foo <= bar) std::cout << "foo is less than or equal to bar" << std::endl;
		if (foo >= bar) std::cout << "foo is greater than or equal to bar" << std::endl;
		std::cout << "END VECTOR BINARY EQUATION TEST 1" << std::endl;
		std::cout << "END VECTOR BINARY EQUATION TESTS" << std::endl;
	}
	std::cout << "END VECTOR TESTS" << std::endl << std::endl;
	std::cout << "BEGIN STACK TESTS" << std::endl << std::endl;
	{
		std::cout << "BEGIN STACK PUSH AND POP TESTS" << std::endl;
		std::cout << "BEGIN STACK PUSH AND POP TEST 1" << std::endl;
		NAMESPACE::stack<float> other_stack;
		NAMESPACE::vector<std::string> lst;
		lst.push_back("salut");
		lst.push_back("tu vas bien?");
		lst.push_back("super");
		lst.push_back("et toi?");
		NAMESPACE::stack<std::string, NAMESPACE::vector<std::string> > my_stack(lst);
		std::cout << std::boolalpha << other_stack.empty() << std::endl;
		other_stack.push(8.5);
		other_stack.push(42.4242);
		std::cout << other_stack.size() << std::endl;
		other_stack.pop();
		std::cout << other_stack.size() << std::endl;
		other_stack.push(78541.987);
		std::cout << other_stack.size() << std::endl;
		std::cout << other_stack.top() << std::endl;
		std::cout << std::boolalpha << other_stack.empty() << std::endl;
		const std::string const_top = my_stack.top();
		std::cout << "const top: " << const_top << std::endl;
		while (!my_stack.empty()) {
			std::cout << my_stack.top() << std::endl;
			my_stack.pop();
		}
		std::cout << "END STACK PUSH AND POP TEST 1" << std::endl;
		std::cout << "END STACK PUSH AND POP TESTS" << std::endl;
	}
	{
		std::cout << "BEGIN STACK BINARY EQUATION TESTS" << std::endl;
		std::cout << "BEGIN STACK BINARY EQUATION TEST 1" << std::endl;
		NAMESPACE::stack<int> a, b, c;
		a.push(10);
		a.push(20);
		a.push(30);
		b.push(10);
		b.push(20);
		b.push(30);
		c.push(30);
		c.push(20);
		c.push(10);
		if (a==b) std::cout << "a and b are equal" << std::endl;
		if (b!=c) std::cout << "b and c are not equal" << std::endl;
		if (b<c) std::cout << "b is less than c" << std::endl;
		if (c>b) std::cout << "c is greater than b" << std::endl;
		if (a<=b) std::cout << "a is less than or equal to b" << std::endl;
		if (a>=b) std::cout << "a is greater than or equal to b" << std::endl;
		std::cout << "END STACK BINARY EQUATION TEST 1" << std::endl;
		std::cout << "END STACK BINARY EQUATION TESTS" << std::endl;
	}
	std::cout << "END STACK TESTS" << std::endl << std::endl;
	std::cout << "BEGIN MAP TESTS" << std::endl << std::endl;
	{
		std::cout << "BEGIN MAP [] TESTS" << std::endl;
		std::cout << "BEGIN MAP [] TEST 1" << std::endl;
		NAMESPACE::map<char,int> mymap;
		NAMESPACE::map<char,int>::iterator it;
		mymap['a']=50;
		mymap['b']=100;
		mymap['c']=150;
		mymap['d']=200;
		std::cout << "mymap size: " << mymap.size() << std::endl;
		print_map(mymap);
		std::cout << "END MAP [] TEST 1" << std::endl;
		std::cout << "END MAP [] TESTS" << std::endl;
		std::cout << "BEGIN MAP FIND TESTS" << std::endl;
		std::cout << "BEGIN MAP FIND TEST 1" << std::endl;
		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase (it);
		std::cout << "elements in mymap:" << std::endl;
		std::cout << "a => " << mymap.find('a')->second << std::endl;
		std::cout << "c => " << mymap.find('c')->second << std::endl;
		std::cout << "d => " << mymap.find('d')->second << std::endl;
		std::cout << "END MAP FIND TEST 1" << std::endl;
		std::cout << "END MAP FIND TESTS" << std::endl;
	}
	std::cout << "BEGIN MAP LOWER UPPER AND EQUAL RANGE TESTS" << std::endl;
	{
		std::cout << "BEGIN MAP LOWER UPPER AND EQUAL RANGE TEST 1" << std::endl;
		NAMESPACE::map<char,int> mymap;
		NAMESPACE::map<char,int>::iterator itlow,itup;
		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;
		print_map(mymap);
		itlow=mymap.lower_bound('b');
		std::cout << "lower bound('b'): (" << itlow->first << ", " << itlow->second << ")" << std::endl;
		itup=mymap.upper_bound('d');
		std::cout << "upper bound('d'): (" << itup->first << ", " << itup->second << ")" << std::endl;
		std::cout << "erase from lower_bound('b') to upper_bound('d')" << std::endl;
		mymap.erase(itlow,itup);
		print_map(mymap);
		std::cout << "END MAP LOWER UPPER AND EQUAL RANGE TEST 1" << std::endl;
	}
	std::cout << "END MAP LOWER UPPER AND EQUAL RANGE TESTS" << std::endl;
	std::cout << "BEGIN MAP ERASE TESTS" << std::endl;
	{
		std::cout << "BEGIN MAP ERASE TEST 1" << std::endl;
		NAMESPACE::map<char,int> mymap;
		NAMESPACE::map<char,int>::iterator it;
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;
		print_map(mymap);
		std::cout << "Erase iterator at key 'b'" << std::endl;
		it = mymap.find('b');
		mymap.erase(it);
		print_map(mymap);
		std::cout << "END MAP ERASE TEST 1" << std::endl;
		std::cout << "BEGIN MAP ERASE TEST 2" << std::endl;
		std::cout << "Erase at key 'c'" << std::endl;
		mymap.erase('c');
		print_map(mymap);
		std::cout << "END MAP ERASE TEST 2" << std::endl;
		std::cout << "BEGIN MAP ERASE TEST 3" << std::endl;
		it = mymap.find('e');
		std::cout << "Erase from iterator at key 'e' to end" << std::endl;
		mymap.erase ( it, mymap.end() );
		print_map(mymap);
		std::cout << "END MAP ERASE TEST 3" << std::endl;
	}
	std::cout << "END MAP ERASE TESTS" << std::endl;
	std::cout << "BEGIN MAP INSERT TESTS" << std::endl;
	{
		std::cout << "BEGIN MAP INSERT TEST 1" << std::endl;
		NAMESPACE::map<char,int> mymap;
		NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,bool> ret;
		ret = mymap.insert(NAMESPACE::pair<char,int>('a',100));
		ret = mymap.insert(NAMESPACE::pair<char,int>('z',200));
		std::cout << "Size: " << mymap.size() << std::endl;
		print_map(mymap);
		std::cout << "END MAP INSERT TEST 1" << std::endl;
		std::cout << "BEGIN MAP INSERT TEST 2" << std::endl;
		ret = mymap.insert(NAMESPACE::pair<char,int>('z',500));
		if (ret.second == false) {
			std::cout << "Element 'z' already exists with a value of " << ret.first->second << std::endl;
		}
		std::cout << "END MAP INSERT TEST 2" << std::endl;
		std::cout << "BEGIN MAP INSERT TEST 3" << std::endl;
		NAMESPACE::map<char,int>::iterator it = mymap.begin();
		mymap.insert(it, NAMESPACE::pair<char,int>('b',300));
		mymap.insert(it, NAMESPACE::pair<char,int>('c',400));
		NAMESPACE::map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));
		std::cout << "mymap contains:" << std::endl;
		print_map(mymap);
		std::cout << "anothermap contains:" << std::endl;
		print_map(anothermap);
		std::cout << "END MAP INSERT TEST 3" << std::endl;
	}
	std::cout << "END MAP INSERT TESTS" << std::endl;
	std::cout << "END MAP TESTS" << std::endl;
	return (0);
}