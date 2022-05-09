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
# define VECTOR_HPP

#include <iterator>

#include <reverse_iterator.hpp>

namespace ft {
	template<class T, class Allocator = std::allocator<T> > class vector {
		private:
			T array[];
		public:
			typedef T																					value_type;
			typedef Allocator																			allocator_type;
			typedef std::size_t																			size_type;
			typedef	std::ptrdiff_t																		difference_type;
			typedef value_type&																			reference;
			typedef const value_type&																	const_reference;
			typedef std::iterator<std::input_iterator_tag, long, long, const long *, long>				iterator;
			typedef const std::iterator<std::input_iterator_tag, long, long, const long *, long>		const_iterator;
			typedef ft::reverse_iterator<iterator>														reverse_iterator;
			typedef const ft::reverse_iterator<const_iterator>											const_reverse_iterator;
			
			vector();
			explicit vector(const Allocator & alloc);
			explicit vector(size_type count, const T& value, const Allocator& alloc = Allocator());
			explicit vector(size_type count);
			template<class InputIt> vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
			vector(const vector& other);
			vector(const vector& other, const Allocator& alloc);

			~vector();

			vector& operator=(const vector& other);

			void assign(size_type count, const T& value);
			template<class InputIt> void assign(InputIt first, InputIt last);

			allocator_type get_allocator() const;

			reference at(size_type pos);
			const_reference at(size_type pos) const;

			reference operator[](size_type pos);
			const_reference operator[](size_type pos) const;

			reference front();
			const_reference front() const;

			reference back();
			const_reference back() const;

			T* data();
			const T* data() const;

			// ITERATORS
			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			reverse_iterator rend();
			const_reverse_iterator rend() const;

			// CAPACITY
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			void reserve(size_type new_cap);
			size_type capacity() const;

			// MODIFIERS
			void clear();
			iterator insert(iterator pos, const T&value);
			void insert(iterator pos, size_type count, const T& value);
			template<class InputIt> void insert(iterator pos, InputIt first, InputIt last);
			iterator erase(iterator pos);
			iterator erase(iterator first, iterator last);
			void push_back(const T& value);
			void pop_back();
			void resize(size_type count);
			void resize(size_type count, T value = T());
			void swap(vector& other);
	};
}

#endif