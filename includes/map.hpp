/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:13:30 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/21 17:11:45 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>
#include <stdexcept>

#include "./utils/pair.hpp"
#include "./utils/iterator.hpp"
#include "./utils/red_black_tree.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/equal.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > > class map {
		public:
			typedef const Key													key_type;
			typedef T															mapped_type;
			typedef ft::pair<key_type, mapped_type>								value_type;
			typedef	std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;
			typedef Allocator													allocator_type;
    		typedef Compare														key_compare;
			typedef value_type &												reference;
			typedef const value_type &											const_reference;
			typedef typename Allocator::pointer									pointer;
			typedef	typename Allocator::const_pointer							const_pointer;

			class value_compare {
				protected:
					Compare c;
				public:
					typedef	bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type  second_argument_type;

					inline bool operator()( const value_type & lhs, const value_type & rhs) const {
						return (c(lhs.first, rhs.first));
					}

					inline value_compare() {};

					inline explicit value_compare(Compare c): c(c) { };
			};

			typedef ft::RBTree<value_type, value_compare, allocator_type>		tree_type;
			typedef typename tree_type::iterator								iterator;
			typedef typename tree_type::const_iterator							const_iterator;
			typedef typename tree_type::reverse_iterator						reverse_iterator;
			typedef	typename tree_type::const_reverse_iterator					const_reverse_iterator;

		private:
			allocator_type		_alloc;
			key_compare			compare;
			value_compare		vcompare;
			tree_type			tree;

		public:
			inline explicit map(const Compare & comp = Compare(), const Allocator & alloc = Allocator()) :
				_alloc(alloc),
				compare(comp),
				vcompare(value_compare(comp)),
				tree(tree_type())
			{}
			
			template <class InputIt> map(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0x0) :
				_alloc(alloc),
				compare(comp),
				vcompare(value_compare(comp)),
				tree(tree_type(value_compare(comp), alloc)) {
				this->tree.insert(first, last);
			}

			inline map(const map & other): _alloc(other._alloc), compare(other.compare), vcompare(other.vcompare), tree(other.tree) { }

			inline ~map() {
				this->clear();
			}

			inline map & operator=(const map & other) {
				this->tree = other.tree;
				this->compare = other.compare;
				this->vcompare = other.vcompare;
				return (*this);
			}

			inline allocator_type get_allocator() const {
				return (this->tree.get_allocator());
			}

			inline mapped_type & at(key_type & key) {
				iterator res = this->tree.find(ft::make_pair(key, mapped_type()));
				if (res == this->tree.end())
					throw std::out_of_range("map:: key not found");
				return (res->second);
			}

			inline const mapped_type & at(key_type & key) const {
				iterator res = this->tree.find(ft::make_pair(key, mapped_type()));
				if (res == this->tree.end())
					throw std::out_of_range("map:: key not found");
				return (res->second);
			}
			
			mapped_type & operator[](key_type & key) {
				iterator res = this->tree.find(ft::make_pair(key, mapped_type()));
				if (res == this->tree.end())
					res = this->tree.insert(ft::make_pair(key, mapped_type())).first;
				return (res->second);
			}

			inline iterator begin() {
				return (this->tree.begin());
			}

			inline const_iterator begin() const {
				return (this->tree.cbegin());
			}

			inline iterator end() {
				return (this->tree.end());
			}

			inline const_iterator end() const {
				return (this->tree.cend());
			}

			inline reverse_iterator rbegin() {
				return (this->tree.rbegin());
			}

			inline const_reverse_iterator rbegin() const {
				return (this->tree.rcbegin());
			}

			inline reverse_iterator rend() {
				return (this->tree.rend());
			}

			inline const_reverse_iterator rend() const {
				return (this->tree.rcend());
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

			template <class InputIt> inline void insert(InputIt first, InputIt last) {
				this->tree.insert(first, last);
			}

			inline void erase(iterator pos) {
				this->tree.erase(pos);
			}

			inline iterator erase(iterator first, iterator last) {
				return (this->tree.erase(first, last));
			}

			inline size_type erase(const key_type & key) {
				return (this->tree.erase(ft::make_pair(key, mapped_type())));
			}

			inline void swap(map & other) {
				std::swap(this->compare, other.compare);
				this->tree.swap(other.tree);
			}

			inline size_type count(const key_type & key) const {
				const_iterator res = this->tree.find(ft::make_pair(key, mapped_type()));
				if (res == this->tree.end())
					return (0);
				return (1);
			}

			inline iterator find(const key_type & key) {
				return (this->tree.find(ft::make_pair(key, mapped_type())));
			}

			inline const_iterator find(const key_type & key) const {
				return (this->tree.find(ft::make_pair(key, mapped_type())));
			}

			inline ft::pair<iterator, iterator> equal_range(const key_type & key) {
				return (this->tree.equal_range(ft::make_pair(key, mapped_type())));
			}

			inline ft::pair<const_iterator, const_iterator> equal_range(const key_type & key) const {
				return (this->tree.cequal_range(ft::make_pair(key, mapped_type())));
			}

			inline iterator lower_bound(const key_type & key) {
				return (this->tree.lower_bound(ft::make_pair(key, mapped_type())));
			}

			inline const_iterator lower_bound(const key_type & key) const {
				return (this->tree.clower_bound(ft::make_pair(key, mapped_type())));
			}

			inline iterator upper_bound(const key_type & key) {
				return (this->tree.upper_bound(ft::make_pair(key, mapped_type())));
			}

			inline const_iterator upper_bound(const key_type & key) const {
				return (this->tree.cupper_bound(ft::make_pair(key, mapped_type())));
			}

			inline key_compare key_comp() const {
				return (this->compare);
			}

			inline value_compare value_comp() const {
				return (this->vcompare);
			}
	};

	template <class Key, class T, class Compare, class Alloc> inline bool operator==(const ft::map<Key, T, Compare, Alloc> & vec1, const ft::map<Key, T, Compare, Alloc> & vec2) {
		if (vec1.size() != vec2.size())
			return (false);
		return (ft::equal(vec1.begin(), vec1.end(), vec2.begin()));
	}

	template <class Key, class T, class Compare, class Alloc> inline bool operator!=(const ft::map<Key, T, Compare, Alloc> & vec1, const ft::map<Key, T, Compare, Alloc> & vec2) {
		return (!(vec1 == vec2));
	}

	template <class Key, class T, class Compare, class Alloc> inline bool operator<(const ft::map<Key, T, Compare, Alloc> & vec1, const ft::map<Key, T, Compare, Alloc> & vec2) {
		typename ft::map<Key, T, Compare, Alloc>::const_iterator first1 = vec1.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator last1 = vec1.end();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator first2 = vec2.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator last2 = vec2.end();
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

	template <class Key, class T, class Compare, class Alloc> inline bool operator<=(const ft::map<Key, T, Compare, Alloc> & vec1, const ft::map<Key, T, Compare, Alloc> & vec2) {
		return (!(vec2 < vec1));
	}

	template <class Key, class T, class Compare, class Alloc> inline bool operator>(const ft::map<Key, T, Compare, Alloc> & vec1, const ft::map<Key, T, Compare, Alloc> & vec2) {
		return (vec2 < vec1);
	}

	template <class Key, class T, class Compare, class Alloc> inline bool operator>=(const ft::map<Key, T, Compare, Alloc> & vec1, const ft::map<Key, T, Compare, Alloc> & vec2) {
		return (!(vec1 < vec2));
	}
	
	template <class Key, class T, class Compare, class Alloc> inline void swap(ft::map<Key, T, Compare, Alloc> & vec1, ft::map<Key, T, Compare, Alloc> & vec2) {
		vec1.swap(vec2);
	}
}

#endif