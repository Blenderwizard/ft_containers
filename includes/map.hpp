/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:13:30 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/08 16:13:42 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>

#include "./utils/pair.hpp"
#include "./utils/iterator.hpp"
#include "./utils/red_black_tree.hpp"
#include "./utils/reverse_iterator.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > > class map {
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const Key, T>							value_type;
			typedef	std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Allocator										allocator_type;
    		typedef Compare											key_compare;
			typedef value_type&										reference;
			typedef const value_type &								const_reference;
			typedef typename Allocator::pointer						pointer;
			typedef	typename Allocator::const_pointer				const_pointer;
			typedef ft::red_black_tree_iterator<T>					iterator;
			typedef ft::red_black_tree_iterator<const T>			const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			class value_compare {
				friend class map;
				public:
					typedef	bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type  second_argument_type;

					inline bool operator()( const value_type & lhs, const value_type & rhs) const {
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

			inline allocator_type get_allocator() const {
				return (this->tree.get_allocator());
			}

			inline T & at(const Key& key) {
				iterator res = this->tree.find(ft::make_pair(key, mapped_type()));
				if (res == this->tree.end())
					throw std::out_of_range("map::at: key not found");
				return (res->second);
			}

			inline const T & at(const Key & key) const {
				iterator res = this->tree.find(ft::make_pair(key, mapped_type()));
				if (res == this->tree.end())
					throw std::out_of_range("map::at: key not found");
				return (res->second);
			}
			
			T & operator[](const Key & key);

			inline iterator begin() {
				return (tree.begin());
			}

			inline const_iterator begin() const {
				return (tree.begin());
			}

			inline iterator end() {
				return (tree.end());
			}

			inline const_iterator end() const {
				return (tree.end());
			}

			inline reverse_iterator rbegin() {
				return (tree.rbegin());
			}

			inline const_reverse_iterator rbegin() const {
				return (tree.rbegin());
			}

			inline reverse_iterator rend() {
				return (tree.end());
			}

			inline const_reverse_iterator rend() const {
				return (tree.end());
			}
			
			inline bool empty() const {
				return (this->tree.empty());
			}

			inline size_type size() const {
				return (this->tree.size());
			}

			inline size_type max_size() const {
				return (this->tree.max_size());
			}

			inline void clear() {
				this->tree.clear();
			}

			inline ft::pair<iterator, bool> insert(const value_type & value) {
				return (this->tree.insert(value));
			}

			inline iterator insert(iterator hint, const value_type & value) {
				return (this->tree.insert(hint, value));
			}

			template<class InputIt> void insert(InputIt first, InputIt last);

			inline void erase(iterator pos) {
				this->tree(erase);
			}

			inline size_type erase(const Key & key) {
				return (this->tree.erase(max_size(key, mapped_type())));
			}

			inline void swap(map & other) {
				std::swap(this->compare, other.compare);
				this->tree.swap(other.tree);
			}

			inline size_type count (const Key & key) const;

			inline iterator find(const Key & key) {
				return (this->tree.find(make_pair(key, mapped_type())));
			}

			inline const_iterator find(const Key & key) const {
				return (this->tree.find(make_pair(key, mapped_type())));
			}

			inline ft::pair<iterator, iterator> equal_range(const Key &key) {
				return (this->tree.equal_range(make_pair(key, mapped_type())));
			}

			inline ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
				return (this->tree.equal_range(make_pair(key, mapped_type())));
			}

			inline iterator lower_bound(const Key & key) {
				return (this->tree.lower_bound(make_pair(key, mapped_type())));
			}

			inline const_iterator lower_bound(const Key & key) const {
				return (this->tree.lower_bound(make_pair(key, mapped_type())));
			}

			inline iterator upper_bound(const Key & key) {
				return (this->tree.upper_bound(make_pair(key, mapped_type())));
			}

			inline const_iterator upper_bound(const Key & key) const {
				return (this->tree.upper_bound(make_pair(key, mapped_type())));
			}

			inline key_compare key_comp() const {
				return (this->compare);
			}

			inline value_compare value_comp() const {
				return (this->tree.value_comp());
			}

		private:
			allocator_type	_alloc;
			tree_type		tree;
			key_compare		compare;
	};
}

#endif