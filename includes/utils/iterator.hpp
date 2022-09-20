/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:33:09 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/20 12:54:03 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "iterator_traits.hpp"
#include "pair.hpp"

namespace ft {
	template <typename T> class random_access_iterator {
		public:
			typedef std::random_access_iterator_tag						iterator_category;
			typedef typename ft::iterator_traits<T*>::value_type 		value_type;
			typedef typename ft::iterator_traits<T*>::reference 		reference;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef pointer												iterator_type;
            
			inline random_access_iterator() : current(0x0) {}

			inline random_access_iterator(pointer x): current(x) {}

			inline random_access_iterator(const random_access_iterator & rai): current(rai.current) {}
		
			inline random_access_iterator<value_type> & operator=(const random_access_iterator & rai) {
				if (this != &rai)
					this->current = rai.current;
				return (*this);
			}
			
			inline virtual ~random_access_iterator() {}

			inline operator random_access_iterator<const T>() const {
				return (this->current);
			}

			inline pointer base() const {
				return (this->current);
			}

			inline reference operator*() const {
				return *(this->current);
			}

			inline pointer operator->() {
				return &(this->operator*());
			}

			inline random_access_iterator & operator++() {
				this->current++;
				return (*this);
			}

			inline random_access_iterator operator++(int) {
				random_access_iterator ret(*this);
				operator++();
				return (ret);
			}

			inline random_access_iterator & operator--() {
				this->current--;
				return (*this);
			}

			inline random_access_iterator operator--(int) {
				random_access_iterator ret(*this);
				operator--();
				return (ret);
			}

			inline random_access_iterator operator+(const difference_type & count) const {
				return (this->current + count);
			}

			inline random_access_iterator operator-(const difference_type & count) const {
				return (this->current - count);
			}

			inline random_access_iterator operator+=(const difference_type & count) {
				this->current += count;
				return (*this);
			}

			inline random_access_iterator operator-=(const difference_type & count) {
				this->current -= count;
				return (*this);
			}

			inline reference operator[](const difference_type & count) {
				return (*(this->current + count));
			}
		
		private:
			pointer current;
	};
	
	template <typename T> inline bool operator==(const ft::random_access_iterator<T> & rai1, const ft::random_access_iterator<T> & rai2) {
		return (rai1.base() == rai2.base());
	}

	template <typename T_RAI1, typename T_RAI2> inline bool operator==(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() == rai2.base());
	}

	template <typename T> inline bool operator!=(const ft::random_access_iterator<T> & rai1, const ft::random_access_iterator<T> & rai2) {
		return (rai1.base() != rai2.base());
	}

	template <typename T_RAI1, typename T_RAI2> inline bool operator!=(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() != rai2.base());
	}

	template <typename T> inline bool operator<(const ft::random_access_iterator<T> & rai1, const ft::random_access_iterator<T> & rai2) {
		return (rai1.base() < rai2.base());
	}

	template <typename T_RAI1, typename T_RAI2> inline bool operator<(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() < rai2.base());
	}

	template <typename T> inline bool operator>(const ft::random_access_iterator<T> & rai1, const ft::random_access_iterator<T> & rai2) {
		return (rai1.base() > rai2.base());
	}

	template <typename T_RAI1, typename T_RAI2> inline bool operator>(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() > rai2.base());
	}

	template <typename T> inline bool operator<=(const ft::random_access_iterator<T> & rai1, const ft::random_access_iterator<T> & rai2) {
		return (rai1.base() <= rai2.base());
	}

	template <typename T_RAI1, typename T_RAI2> inline bool operator<=(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() <= rai2.base());
	}

	template <typename T> inline bool operator>=(const ft::random_access_iterator<T> & rai1, const ft::random_access_iterator<T> & rai2) {
		return (rai1.base() >= rai2.base());
	}

	template <typename T_RAI1, typename T_RAI2> inline bool operator>=(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() >= rai2.base());
	}

	template <typename T> inline ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type count, typename ft::random_access_iterator<T> & rai) {
		return (&(*rai) + count);
	}

	template <typename T_RAI1, typename T_RAI2> inline typename ft::random_access_iterator<T_RAI1>::difference_type operator+(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() + rai2.base());
	}

	template <typename T> inline typename ft::random_access_iterator<T>::difference_type operator-(const ft::random_access_iterator<T> & rai1, const ft::random_access_iterator<T> & rai2) {
		return (rai1.base() - rai2.base());
	}

	template <typename T_RAI1, typename T_RAI2> inline typename ft::random_access_iterator<T_RAI1>::difference_type operator-(const ft::random_access_iterator<T_RAI1> & rai1, const ft::random_access_iterator<T_RAI2> & rai2) {
		return (rai1.base() - rai2.base());
	}

	template <typename T> struct Node {
		public:
			inline explicit Node(T *val = 0) :	value(val), parent(0), left(0), right(0), is_black(false) {}
	
			inline Node(Node const & other) {
				this->is_black = other.is_black;
				this->value = other.value;
				this->parent = other.parent;
				this->right = other.right;
				this->left = other.left;
			};

			inline Node & operator=(const Node & other) {
				this->is_black = other.is_black;
				this->value = other.value;
				this->parent = other.parent;
				this->right = other.right;
				this->left = other.left;
				return *this;
			}

			inline Node * min() {
				if (!this->left)
					return this;
				return this->left->min();
			}

			inline Node * max() {
				while (!this->right)
					return this;
				return this->right->max();
			}

			inline Node* next() {
				if (this->right)
					return (this->right->min());
				if (this->parent && this == this->parent->left)
					return (this->parent);
				Node* next = this;
				while (next && next->parent && next == next->parent->right)
					next = next->parent;
				if (next) {
					return (next->parent);
				}
				return 0x0;
			}

			inline Node* prev() {
				if (this->left)
					return (this->left->max());
				if(this->parent && this == this->parent->right)
					return (this->parent);
				Node* prev= this;
				while (prev && prev->parent && prev == prev->parent->left)
					prev = prev->parent;
				if (prev) {
					return (prev->parent);
				}
				return 0x0;
			}

			inline virtual ~Node(){}
			
			T *					value;
			Node *				parent;
			Node *				left;
			Node *				right;	
			bool				is_black;
	};

	template <typename T> class red_black_tree_iterator {
		public:
			typedef std::bidirectional_iterator_tag						iterator_category;
			typedef typename ft::iterator_traits<T *>::value_type 		value_type;
			typedef typename ft::iterator_traits<T *>::reference 		reference;
			typedef typename ft::iterator_traits<T *>::pointer			pointer;
			typedef typename ft::iterator_traits<T *>::difference_type	difference_type;
			typedef ft::Node<value_type> * 								node_pointer;
			typedef ft::Node<const value_type> * 						const_node_pointer;


			inline red_black_tree_iterator() : _node(0x0), _tree_min(0x0), _tree_max(0x0) {}

			inline explicit red_black_tree_iterator(node_pointer node, node_pointer min, node_pointer max) : _node(node), _tree_min(min), _tree_max(max) {}

			inline red_black_tree_iterator(const red_black_tree_iterator & other) {
				*this = other;
			}

			inline red_black_tree_iterator & operator=(const red_black_tree_iterator & other) {
				this->_node = other.node();
				return *this;
			}

			inline operator red_black_tree_iterator<const T>() const {
				return red_black_tree_iterator<const T>((const_node_pointer) this->_node, (const_node_pointer) this->_tree_min, (const_node_pointer) this->_tree_max);
			}

			inline reference operator*() const {
				return *(this->_node->value);
			}

			inline pointer operator->() const {
				return this->_node->value;
			}

			inline red_black_tree_iterator & operator++() {
				if (!this->_node)
					this->_node = this->_tree_min;
				else
					this->_node = this->_node->next();
				return *this;
			}

			inline red_black_tree_iterator operator++(int) {
				red_black_tree_iterator<value_type> temp = *this;
				if (!this->_node)
					this->_node = this->_tree_min;
				else
					this->_node = this->_node->next();
				return temp;
			}

			inline red_black_tree_iterator & operator--() {
				if (!this->_node)
					this->_node = this->_tree_max;
				else
					this->_node = this->_node->prev();
				return *this;
			}

			inline red_black_tree_iterator operator--(int) {
				red_black_tree_iterator<value_type> temp = *this;
				if (!this->_node)
					this->_node = this->_tree_max;
				else
					this->_node = this->_node->prev();
				return temp;
			}

			inline node_pointer node() const {
				return (this->_node);
			}

			inline bool operator==(const red_black_tree_iterator & it) {
				return (this->_node == it._node);
			}
			
			inline bool operator!=(const red_black_tree_iterator & it) {
				return (this->_node != it._node);
			}

		private:
			node_pointer _node;
			node_pointer _tree_min;
			node_pointer _tree_max;
	};
}

#endif