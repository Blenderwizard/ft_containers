/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:33:09 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/22 19:20:27 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <functional>
#include <stdexcept>

#include "./utils/enable_if.hpp"
#include "./utils/iterator.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/is_integral.hpp"
#include "./utils/equal.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> > class vector {
		public:
			typedef T															value_type;
			typedef Allocator													allocator_type;
			typedef value_type &												reference;
			typedef const value_type &											const_reference;
			typedef ft::random_access_iterator<value_type>						iterator;
			typedef ft::random_access_iterator<const value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type; 
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::pointer							pointer;

			inline explicit vector(const Allocator & alloc = Allocator()): _alloc(alloc), first(0x0), last(0x0), vector_size(0x0) {}
			
			inline explicit vector(size_type count, const value_type & value = value_type(), const Allocator & alloc = Allocator()): _alloc(alloc), first(0x0), last(0x0), vector_size(0x0) {
				this->first = this->_alloc.allocate(count);
				this->vector_size = this->first + count;
				this->last = this->first;
				for(; count > 0; count--) {
					this->_alloc.construct(this->last, value);
					(this->last)++;
				}
			}

			template<class InputIt> inline vector(InputIt first, InputIt last, const Allocator & alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0x0) : _alloc(alloc) {
				difference_type count = dist(first, last);
				this->first = this->_alloc.allocate(count);
				this->vector_size = this->first + count;
				this->last = this->first;
				for (; count > 0; count--) {
					this->_alloc.construct(this->last, *(first)++);
					(this->last)++;
				}
			}

			inline vector(const vector& other) : _alloc(other._alloc), first(0x0), last(0x0), vector_size(0x0) {
				this->insert(this->begin(), other.begin(), other.end());
			}

			inline ~vector() {
				this->clear();
				this->_alloc.deallocate(this->first, this->capacity());
			}

			inline vector& operator=(const vector & other) {
				if (other == *this)
					return (*this);
				this->clear();
				this->insert(this->end(), other.begin(), other.end());
				return (*this);
			}

			inline void assign(size_type count, const value_type & value) {
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
						this->_alloc.construct(this->last, value);
						(this->last)++;
					}
				}
			}

			template<class InputIt> inline void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0x0) {
				this->clear();
				for(; first != last; first++) {
					this->push_back(*first);
				}
			}

			inline allocator_type get_allocator() const {
				return this->_alloc;
			}

			inline reference at(size_type pos) {
				if (pos >= this->size())
					throw std::out_of_range("vector");
				return ((*this)[pos]);
			}

			inline const_reference at(size_type pos) const {
				if (pos >= this->size())
					throw std::out_of_range("vector");
				return ((*this)[pos]);
			}

			inline reference operator[](size_type pos) {
				return (*(this->first + pos));
			}

			inline const_reference operator[](size_type pos) const {
				return (*(this->first + pos));
			}

			inline reference front() {
				return (*(this->first));
			}

			inline const_reference front() const {
				return (*(this->first));
			}

			inline reference back() {
				return (*(this->last - 1));
			}

			inline const_reference back() const {
				return (*(this->last - 1));
			}

			inline value_type * data() {
				if (this->size() == 0)
					return (0x0);
				return (*(front()));
			}

			inline const value_type * data() const {
				if (this->size() == 0)
					return (0x0);
				return (*(front()));
			}

			inline iterator begin() {
				return (this->first);
			}

			inline const_iterator begin() const {
				return (this->first);
			}

			inline iterator end() {
				if (this->empty())
					return (this->first);
				return (this->last);
			}
			
			inline const_iterator end() const {
				if (this->empty())
					return (this->first);
				return (this->last);
			}

			inline reverse_iterator rbegin() {
				return (reverse_iterator(this->end()));
			}
			
			inline const_reverse_iterator rbegin() const {
				return (reverse_iterator(this->end()));
			}

			inline reverse_iterator rend() {
				return (reverse_iterator(this->begin()));
			}
			
			inline const_reverse_iterator rend() const {
				return (reverse_iterator(this->begin()));
			}

			inline bool empty() const {
				if (this->size() == 0)
					return (true);
				return (false);
			}

			inline size_type size() const {
				return (this->last - this->first);
			}

			inline size_type max_size() const {
				return allocator_type().max_size();
			}

			inline void reserve(size_type new_cap) {
				if (new_cap > this->max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				else if (new_cap > this->capacity()) {
					pointer prev_start = this->first;
					pointer prev_end = this->last;
					size_type prev_size = this->size();
					size_type prev_cap = this->capacity();

					this->first = _alloc.allocate(new_cap);
					this->vector_size = this->first + new_cap;
					this->last = this->first;
					for (;prev_start != prev_end; prev_start++) {
						this->_alloc.construct(this->last, *prev_start);
						(this->last)++;
					}
					this->_alloc.deallocate(prev_start - prev_size, prev_cap);
				}
			}

			inline size_type capacity() const {
				return (this->vector_size - this->first);
			}

			inline void clear() {
				size_type size = this->size();
				for (size_type i = 0; i < size; i++) {
					(this->last)--;
					this->_alloc.destroy(last);
				}
			}

			inline iterator insert(iterator pos, const value_type & value) {
				size_type loc = &(*pos) - this->first;
				if (this->size() == this->capacity())
					this->reserve(this->size() + 1);
				for (pointer it = this->last; it && it != this->first + loc; it--)
					*it = *(it - 1);
				pointer ret = (this->first + loc);
				*ret = value;
				(this->last)++;
				return (iterator(ret));
			}

			inline iterator insert(iterator pos, size_type count, const value_type & value) {
				if (count == 0)
					return (pos);
				if (count > this->max_size())
					throw std::exception();
				size_type loc = &(*pos) - this->first;
				if (this->capacity() - this->size() < count)
					this->reserve(this->size() + std::max(this->size(), count));
				for (pointer it = this->last + count - 1; it && it != this->first + loc + count - 1; it--)
					*it = *(it - count);
				for (size_type i = 0; i < count; i++)
					*(this->first + loc + i) = value;
				this->last += count;
				return (this->first + loc - count + 1);
			}

			template<class InputIt> inline void insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0x0) {
				size_type count = this->dist(first, last);
				if (size_type(this->vector_size - this->last) >= count) {
					for (size_type i = 0; i < this->size() - (&(*pos) - this->first); i++)
						this->_alloc.construct(this->last - i + (count - 1), *(this->last - i - 1));
					this->last += count;
					for (; &(*first) != &(*last); first++) {
						this->_alloc.construct(&(*pos), *first);
						pos++;
					}
				} else {
					size_type new_capacity;
					if (this->size() * 2 > 0)
						new_capacity = this->size() * 2;
					else
						new_capacity = 1;
					pointer new_first = this->_alloc.allocate(new_capacity);
					pointer new_last = new_first + this->size() + count;
					pointer new_vector_size = new_first + (this->size() * 2);
					if (size_type(new_vector_size - new_first) < this->size() + count) {
						if (new_first)
							this->_alloc.deallocate(new_first, new_vector_size - new_first);
						new_first = this->_alloc.allocate (this->size() + count);
						new_last = new_first + this->size() + count;
						new_vector_size = new_last;
					}
					for (size_type i = 0; i < (size_type) (&(*pos) - this->first); i++)
						this->_alloc.construct(new_first + i, *(this->first + i));
					for (int i = 0; &(*first) != &(*last); first++) {
						this->_alloc.construct(new_first + (&(*pos) - this->first) + i, *first);
						i++;
					}
					for (size_type i = 0; i < this->size() - (&(*pos) - this->first); i++)
						this->_alloc.construct(new_first + (&(*pos) - this->first) + count + i, *(this->first + (&(*pos) - this->first) + i));
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->first + i);
					this->_alloc.deallocate(this->first, this->capacity());

					this->first = new_first;
					this->last = new_last;
					this->vector_size = new_vector_size;
				}
			}
			
			inline iterator erase(iterator pos) {
				pointer loc = &(*pos);
				this->_alloc.destroy(&(*pos));
				if (&(*pos) + 1 == this->last)
					_alloc.destroy(&(*pos));
				else {
					for (difference_type i = 0; i < this->last - &(*pos) - 1; i++) {
						this->_alloc.construct(&(*pos) + i, *(&(*pos) + i + 1));
						this->_alloc.destroy(&(*pos) + i + 1);
					}
				}
				this->last -= 1;
				return (iterator(loc));
			}

			inline iterator erase(iterator first, iterator last) {
				pointer loc = &(*first);
				for (; &(*first) != &(*last); first++)
					this->_alloc.destroy(&(*first));
				for (difference_type i = 0; i < this->last - &(*last); i++) {
					this->_alloc.construct(loc + i, *(&(*last) + i));
					this->_alloc.destroy(&(*last) + i);
				}
				this->last -= (&(*last) - loc);
				return (iterator(loc));
			}

			inline void push_back(const value_type & value) {
				if (this->last == vector_size) {
					if (this->size() > 0) {
						this->reserve((int) this->size() * 2);
					} else {
						this->reserve((int) 1);
					}
				}
				this->_alloc.construct(this->last, value);
				(this->last)++;
			}

			inline void pop_back() {
				this->_alloc.destroy(&this->back());
				(this->last)--;
			}

			inline void resize(size_type count, value_type val = value_type()) {
				if (count > this->max_size())
					throw (std::length_error("vector::resize"));
				else if (count < this->size()) {
					this->reserve(count);
				}
				else
					this->insert(this->end(), count - this->size(), val);
				if (count != this->size())
					this->last = this->first + count;
			}

			inline void swap(vector & other) {
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

			template<class InputIt> inline typename ft::iterator_traits<InputIt>::difference_type dist(InputIt first, InputIt last) {
				typename ft::iterator_traits<InputIt>::difference_type rtn = 0;
				for (; first != last; first++) {
					rtn++;
				}
				return (rtn);
			}
	};

	template <class T, class Alloc> inline bool operator==(const ft::vector<T, Alloc> & vec1, const ft::vector<T, Alloc> & vec2) {
		if (vec1.size() != vec2.size())
			return (false);
		return (ft::equal(vec1.begin(), vec1.end(), vec2.begin()));
	}

	template <class T, class Alloc> inline bool operator!=(const ft::vector<T, Alloc> & vec1, const ft::vector<T, Alloc> & vec2) {
		return (!(vec1 == vec2));
	}

	template <class T, class Alloc> inline bool operator<(const ft::vector<T, Alloc> & vec1, const ft::vector<T, Alloc> & vec2) {
		typename ft::vector<T, Alloc>::const_iterator first1 = vec1.begin();
		typename ft::vector<T, Alloc>::const_iterator last1 = vec1.end();
		typename ft::vector<T, Alloc>::const_iterator first2 = vec2.begin();
		typename ft::vector<T, Alloc>::const_iterator last2 = vec2.end();
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class T, class Alloc> inline bool operator<=(const ft::vector<T, Alloc>& vec1, const ft::vector<T, Alloc> & vec2) {
		return (!(vec2 < vec1));
	}

	template <class T, class Alloc> inline bool operator>(const ft::vector<T, Alloc> & vec1, const ft::vector<T, Alloc> & vec2) {
		return (vec2 < vec1);
	}

	template <class T, class Alloc> inline bool operator>=(const ft::vector<T, Alloc> & vec1, const ft::vector<T, Alloc> & vec2) {
		return (!(vec1 < vec2));
	}
	
	template <class T, class Alloc> inline void swap(ft::vector<T,Alloc> & vec1, ft::vector<T,Alloc> & vec2) {
		vec1.swap(vec2);
	}
}

#endif