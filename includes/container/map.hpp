/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:13:30 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/10 10:52:53 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <pair.hpp>
#include <reverse_iterator.hpp>

#include <memory>
#include <utility>
#include <map>
#include <iterator>

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > > class map {
		public:
			typedef Key																					key_type;
			typedef T																					mapped_type;
			typedef ft::pair<const Key, T>																value_type;
			typedef	std::size_t																			size_type;
			typedef std::ptrdiff_t																		difference_type;
			typedef Allocator																			allocator_type;
    		typedef Compare																				key_compare;
			typedef value_type&																			reference;
			typedef const value_type &																	const_reference;
			typedef typename Allocator::pointer															pointer;
			typedef	typename Allocator::const_pointer													const_pointer;
			typedef std::iterator<std::input_iterator_tag, long, long, const long *, long>				iterator;
			typedef const std::iterator<std::input_iterator_tag, long, long, const long *, long>		const_iterator;
			typedef ft::reverse_iterator<iterator>														reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>												const_reverse_iterator;

			class value_compare {
				friend class map;
				public:
					typedef	bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type  second_argument_type;

					bool operator()( const value_type & lhs, const value_type & rhs) const {
						return (comp(lhs.first, rhs.first));
					}
				protected:
					Compare c;
					value_compare(Compare c): c(c) { };
			};
			
			inline map();
			explicit map(const Compare & comp, const Allocator & alloc = Allocator());
			template<class InputIt> map(InputIt first, InputIt last, const Compare & comp, const Allocator & alloc = Allocator());
			map(const map & other);
			~map();
			map & operator=(const map& other);
			allocator_type get_allocator() const;
			T & at(const Key& key);
			const T & at(const Key & key) const;
			T & operator[](const Key & key);
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			void clear();
			ft::pair<iterator, bool> insert(const value_type & value);
			iterator insert(iterator hint, const value_type & value);
			template<class InputIt> void insert(InputIt first, InputIt last);
			void erase(iterator pos);
			size_type erase(const Key & key);
			void swap(map & other);
			size_type count (const Key & key) const;
			iterator find(const Key & key);
			const_iterator find(const Key & key) const;
			ft::pair<iterator, iterator> equal_range(const Key &key);
			ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
			iterator lower_bound(const Key & key);
			const_iterator lower_bound(const Key & key) const;
			iterator upper_bound(const Key & key);
			const_iterator upper_bound(const Key & key) const;
			key_compare key_comp() const;
			value_compare value_comp() const;
	};
}

#endif