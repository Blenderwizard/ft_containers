/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:33:09 by jrathelo          #+#    #+#             */
/*   Updated: 2022/08/29 16:28:15 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>

#include "./utils/enable_if.hpp"
#include "./utils/iterator.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/is_integral.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> > class vector {
		public:
			typedef T															value_type;
			typedef Allocator													allocator_type;
			typedef value_type&													reference;
			typedef const value_type&											const_reference;
			typedef ft::random_access_iterator<value_type>						iterator;
			typedef ft::random_access_iterator<const value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type; 
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::pointer							pointer;

			explicit vector(const Allocator & alloc = Allocator()): _alloc(alloc), first(0x0), last(0x0), vector_size(0x0) {}
			
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _alloc(alloc), first(0x0), last(0x0), vector_size(0x0) {
				this->first = _alloc.allocate(count);
				this->vector_size = this->first + count;
				this->last = this->first;
				for(; count > 0; count--) {
					_alloc.construct(this->last, value);
					(this->last)++;
				}
			}

			template<class InputIt> vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0x0) : _alloc(alloc) {
				// TODO: Need to check if the Input Iterators are correct
				difference_type count = dist(first, last);
				this->first = _alloc.allocate(count);
				this->vector_size = this->first + count;
				this->last = this->first;
				for (; count > 0; count--) {
					_alloc.construct(this->last, *(first)++);
					(this->last)++;
				}
			}

			vector(const vector& other) : _alloc(other._alloc), first(0x0), last(0x0), vector_size(0x0) {
				this->insert(this->begin(), other.begin(), other.end());
			}

			~vector() {
				this->clear();
				_alloc.deallocate(this->first, this->capacity());
			}

			vector& operator=(const vector& other) {
				if (other != *this) {
					this->clear();
					this->insert(this->end(), other.begin(), other.end());
				}
				return (*this);
			}

			void assign(size_type count, const T& value) {
				this->clear();
				if (count == 0)
					return ;
				if (size_type(this->vector_size - this->first) >= count ) {
					for (; count > 0; count--) {
						this->_alloc.construct(this->last , value);
						(this->last)++;
					}
				} else {
					this->_alloc.deallocate(this->first, this->capacity());
					this->first = this->_alloc.allocate(count);
					this->last = this->first;
					this->vector_size = this->first + count;
					for (; count > 0; count--) {
						_alloc.construct(this->last, value);
						(this->last)++;
					}
				}
			}

			template<class InputIt> void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0x0) {
				this->clear();
				for(; first != last; first++) {
					this->push_back(*first);
				}
			}

			allocator_type get_allocator() const {
				return this->_alloc;
			}

			reference at(size_type pos) {
				if (pos >= this->size())
					throw std::exception();
				return ((*this)[pos]);
			}

			const_reference at(size_type pos) const {
				if (pos >= this->size())
					throw std::exception();
				return ((*this)[pos]);
			}

			reference operator[](size_type pos) {
				return (*(this->first + pos));
			}
			const_reference operator[](size_type pos) const {
				return (*(this->first + pos));
			}

			reference front() {
				return (*(this->first));
			}
			const_reference front() const {
				return (*(this->first));
			}

			reference back() {
				return (*(this->last - 1));
			}
			const_reference back() const {
				return (*(this->last - 1));
			}

			T* data() {
				if (this->size() == 0)
					return (0x0);
				return (*(front()));
			}

			const T* data() const {
				if (this->size() == 0)
					return (0x0);
				return (*(front()));
			}

			// ITERATORS
			iterator begin() {
				return (this->first);
			}

			const_iterator begin() const {
				return (this->first);
			}

			iterator end() {
				if (this->empty())
					return (this->first);
				return (this->last);
			}
			
			const_iterator end() const {
				if (this->empty())
					return (this->first);
				return (this->last);
			}

			reverse_iterator rbegin() {
				return (reverse_iterator(this->end()));
			}
			
			const_reverse_iterator rbegin() const {
				return (reverse_iterator(this->end()));
			}

			reverse_iterator rend() {
				return (reverse_iterator(this->begin()));
			}
			
			const_reverse_iterator rend() const {
				return (reverse_iterator(this->begin()));
			}

			// CAPACITY
			bool empty() const {
				if (this->size() == 0)
					return (true);
				return (false);
			}

			size_type size() const {
				return (this->last - this->first);
			}

			size_type max_size() const {
				return allocator_type().max_size();
			}

			void reserve(size_type new_cap) {
				if (new_cap > this->max_size())
					throw(std::length_error("vector::reserve"));
				else if (new_cap > this->capacity()) {
					pointer prev_start = this->first;
					pointer prev_end = this->last;
					size_type prev_size = this->size();
					size_type prev_cap = this->capacity();

					this->first = _alloc.allocate(new_cap);
					this->vector_size = this->first + new_cap;
					this->last = this->first;
					for (;prev_start != prev_end; prev_start++) {
						_alloc.construct(this->last, *prev_start);
						(this->last)++;
					}
					_alloc.deallocate(prev_start - prev_size, prev_cap);
				}
			}

			size_type capacity() const {
				return (this->vector_size - this->first);
			}

			// MODIFIERS
			void clear() {
				size_type size = this->size();
				for (size_type i = 0; i < size; i++) {
					(this->last)--;
					_alloc.destroy(last);
				}
			}

			iterator insert(iterator pos, const T&value) {
				// if (pos < this->begin() || pos > this->end())
				// 	throw std::exception();
				difference_type loc = &(*pos) - this->first;
				if (size_type(this->vector_size - this->last) >= this->size() + 1) {
					for (size_type i = 0; i < (size_type) loc; i++)
						this->_alloc.construct(this->last);
					this->last++;
					this->_alloc.construct(&(*pos), value);
				} else {
					int new_capacity;
					if (this->size() * 2 > 0)
						new_capacity = this->size() * 2;
					else
						new_capacity = 1;
					pointer new_first = this->_alloc.allocate(new_capacity);
					pointer new_last = new_first + this->size() + 1;
					pointer new_vector_size = new_first + new_capacity;
					for (size_type i = 0; i < (size_type) loc; i++)
						this->_alloc.construct(new_first, *(this->first + i));
					for (size_type i = 0; i < this->size() - loc; i++)
						this->_alloc.construct(new_last - 1, *(this->last - i - 1));
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->first + 1);
					if (this->first)
						this->_alloc.deallocate(this->first, this->capacity());
					this->first = new_first;
					this->last = new_last;
					this->vector_size = new_vector_size;
				}
				return (iterator(this->first + loc));
			}

			void insert(iterator pos, size_type count, const T& value) {
				if (count == 0)
					return;
				if (count > this->max_size())
					throw std::exception();
			}

			template<class InputIt> void insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0x0) {
				// TODO check if valid iterators
				for (; first != last; ++first) 
					this->insert(pos, *(first));
			}
			
			// iterator erase(iterator pos);
			// iterator erase(iterator first, iterator last);

			void push_back(const T& value) {
				if (this->last == vector_size) {
					if (this->size() > 0) {
						this->reserve((int) this->size() * 2);
					} else {
						this->reserve((int) 1);
					}
				}
				_alloc.construct(this->last, value);
				(this->last)++;
			}

			void pop_back() {
				_alloc.destroy(&this->back());
				(this->last)--;
			}
			
			// void resize(size_type count);
			// void resize(size_type count, T value = T());

			void swap(vector& other) {
				if (other != *this) {
					pointer save_start = other.first;
					pointer save_end = other.last;
					pointer save_end_capacity = other.vector_size;
					allocator_type save_alloc = other._alloc;

					other.first = this->first;
					other.last = this->last;
					other.vector_size = this->vector_size;
					other._alloc = this->_alloc;

					this->first = save_start;
					this->last = save_end;
					this->vector_size = save_end_capacity;
					this->_alloc = save_alloc;
				}
			}
		private:
			allocator_type	_alloc;
			pointer			first;
			pointer			last;
			pointer			vector_size;

			template<class InputIt> typename ft::iterator_traits<InputIt>::difference_type dist (InputIt first, InputIt last) {
				typename ft::iterator_traits<InputIt>::difference_type rtn = 0;
				for (; first != last; first++) {
					rtn++;
				}
			return (rtn);
			}
	};
}

#endif