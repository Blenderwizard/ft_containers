/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:33:09 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/09 15:20:19 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <cstddef>
#include <iterator.hpp>
#include <reverse_iterator.hpp>

namespace ft {
	template<class T, class Allocator = std::allocator<T> > class vector {
		public:
			typedef T															value_type;
			typedef Allocator													allocator_type;
			typedef value_type&													reference;
			typedef const value_type&											const_reference;
			typedef ft::random_access_iterator<value_type>						iterator;
			typedef const ft::random_access_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef const ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type; 
			typedef typename allocator_type::size_type       					size_type;
			typedef typename allocator_type::pointer							pointer;

			explicit vector(const Allocator & alloc = allocator_type()): _alloc(alloc), first(0x0), last(0x0), vector_size(0x0) {}
			
			explicit vector(size_type count, const T& value, const Allocator& alloc = allocator_type()): _alloc(alloc), first(0x0), last(0x0), vector_size(0x0) {
				this->first = this->_alloc.allocate(count);
				this->vector_size = this->first + count;
				this->last = this->first;
				for(; count > 0; count--) {
					alloc.construct(this->last, value);
					(this->last)++;
				}
			}

			template<class InputIt> vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) : _alloc(alloc) {
				bool is_valid;
				// if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIt>::iterator_category >::value))
				// 	throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIt>::iterator_category >::type>());
				difference_type count = distance(this->first, this->last);
				this->first = _alloc.allocate( count );
				this->vector_size = this->first + count;
				this->last = this->first;
				while (count){
					_alloc.construct(this->last, *(this->first)++);
					(this->last)++;
					count--;
				}
			}

			vector(const vector& other) : _alloc(other._alloc), first(0x0), last(0x0), vector_size(0x0) {
				this->insert(this->begin(), other.begin(), other.end());
			}
			// vector(const vector& other, const Allocator& alloc);

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
					while (count) {
						_alloc.construct(this->last , value);
						(this->last)++;
						count--;
					}
				} else {
					_alloc.deallocate(this->first, this->capacity());
					this->first = _alloc.allocate(count);
					this->last = this->first;
					this->vector_size = this->first + count;
					while (count) {
						_alloc.construct(this->last, value);
						(this->last)++;
						count--;
					}
				}
			}
			template<class InputIt> void assign(InputIt first, InputIt last);

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
				else if (new_cap> this->capacity()) {
					pointer prev_start = this->first;
					pointer prev_end = this->last;
					size_type prev_size = this->size();
					size_type prev_cap = this->capacity();

					this->first = _alloc.allocate(new_cap);
					this->vector_size = this->first + new_cap;
					this->last = this->first;
					while (prev_start != prev_end) {
						_alloc.construct(this->last, *prev_start);
						(this->last)++;
						prev_start++;
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

			iterator insert(iterator pos, const T&value);
			void insert(iterator pos, size_type count, const T& value);
			template<class InputIt> void insert(iterator pos, InputIt first, InputIt last);
			
			iterator erase(iterator pos);
			iterator erase(iterator first, iterator last);

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
			
			void resize(size_type count);
			void resize(size_type count, T value = T());

			void swap(vector& other) {
				if (other == *this)
					return;
				
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
		private:
			allocator_type	_alloc;
			pointer			first;
			pointer			last;
			pointer			vector_size;

			template<class IT> typename ft::iterator_traits<IT>::difference_type distance (IT first, IT last){
				typename ft::iterator_traits<IT>::difference_type ret = 0;

				while (first != last) {
					first++;
					ret++;
				}
				return (ret);
			}
	};
}

#endif