/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:54:53 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/21 12:10:19 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <algorithm>

#include "vector.hpp"
#include "./utils/iterator.hpp"
#include "./utils/reverse_iterator.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> > class stack {
		public:
			typedef T																				value_type;
			typedef value_type &																	reference;
			typedef const value_type &																const_reference;
			typedef typename ft::iterator_traits<typename Container::iterator>::difference_type		difference_type; 
			typedef typename Container::allocator_type::size_type		 							size_type;
			typedef Container																		container_type;
			
			explicit stack(const Container & cont = Container()) : c(cont) { }

			stack(const stack & other) : c(Container()) {
				this->c.insert(this->c.begin(), other.c.begin(), other.c.end());
			}
			
			~stack() {}

			stack & operator=(const stack & other) {
				if (other != *this) {
					this->c.clear();
					this->c.insert(this->c.end(), other.c.begin(), other.c.end());
				}
				return (*this);
			}

			reference top() {
				return (this->c.back());
			}
			
			const_reference top() const {
				return (this->c.back());
			}

			bool empty() const {
				return (this->c.empty());
			}

			size_type size() const {
				return (this->c.size());
			}
	
			void push(const value_type& value) {
				this->c.push_back(value);
			}

			void pop() {
				this->c.pop_back();
			}

			template<class Temp, class Containeremp> friend bool operator==(const ft::stack<Temp,Containeremp> & stack1, const ft::stack<Temp,Containeremp> & stack2);
			template<class Temp, class Containeremp> friend bool operator!=(const ft::stack<Temp,Containeremp> & stack1, const ft::stack<Temp,Containeremp> & stack2);
			template<class Temp, class Containeremp> friend bool operator<(const ft::stack<Temp,Containeremp> & stack1, const ft::stack<Temp,Containeremp> & stack2);
			template<class Temp, class Containeremp> friend bool operator<=(const ft::stack<Temp,Containeremp> & stack1, const ft::stack<Temp,Containeremp> & stack2);
			template<class Temp, class Containeremp> friend bool operator>(const ft::stack<Temp,Containeremp> & stack1, const ft::stack<Temp,Containeremp> & stack2);
			template<class Temp, class Containeremp> friend bool operator>=(const ft::stack<Temp,Containeremp> & stack1, const ft::stack<Temp,Containeremp> & stack2);
		protected:
			Container 	c;
	};
	
	template<class T, class Container> bool operator==(const ft::stack<T,Container> & stack1, const ft::stack<T,Container> & stack2) {
		return (stack1.c == stack2.c);
	}

	template<class T, class Container> bool operator!=(const ft::stack<T,Container> & stack1, const ft::stack<T,Container> & stack2) {
		return (stack1.c != stack2.c);
	}

	template<class T, class Container> bool operator<(const ft::stack<T,Container> & stack1, const ft::stack<T,Container> & stack2) {
		return (stack1.c < stack2.c);
	}

	template<class T, class Container> bool operator<=(const ft::stack<T,Container> & stack1, const ft::stack<T,Container> & stack2) {
		return (stack1.c <= stack2.c);
	}

	template<class T, class Container> bool operator>(const ft::stack<T,Container> & stack1, const ft::stack<T,Container> & stack2) {
		return (stack1.c > stack2.c);
	}
	
	template<class T, class Container> bool operator>=(const ft::stack<T,Container> & stack1, const ft::stack<T,Container> & stack2) {
		return (stack1.c >= stack2.c);
	}
}

#endif