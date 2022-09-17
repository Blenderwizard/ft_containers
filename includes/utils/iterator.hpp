/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:33:09 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/17 14:08:45 by jrathelo         ###   ########.fr       */
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
			inline explicit Node(T *val = 0) :	value(val), parent(0), left(0), right(0), is_black(false), is_nil(0) {}
	
			inline Node(Node const & other) {
				this->is_black = other.is_black;
				this->value = other.value;
				this->parent = other.parent;
				this->is_nil = other.is_nil;
				this->right = other.right;
				this->left = other.left;
			};

			inline Node & operator=(const Node & other) {
				this->is_black = other.is_black;
				this->value = other.value;
				this->is_nil = other.is_nil;
				this->parent = other.parent;
				this->right = other.right;
				this->left = other.left;
				return *this;
			}

			inline virtual ~Node(){}
			
			T *					value;
			Node *				parent;
			Node *				left;
			Node *				right;	
			bool				is_black;
			bool				is_nil;
	};

	template <typename T> class red_black_tree_iterator {
		public:
			typedef std::bidirectional_iterator_tag						iterator_category;
			typedef typename ft::iterator_traits<T *>::value_type 		value_type;
			typedef typename ft::iterator_traits<T *>::reference 		reference;
			typedef typename ft::iterator_traits<T *>::pointer			pointer;
			typedef typename ft::iterator_traits<T *>::difference_type	difference_type;
			typedef Node<value_type> * 									node_pointer;

			inline red_black_tree_iterator() {}

			inline red_black_tree_iterator(void *node): _node(static_cast<node_pointer>(node)) {}

			inline red_black_tree_iterator(const red_black_tree_iterator & other) {
				*this = other;
			}

			inline red_black_tree_iterator & operator=(const red_black_tree_iterator & other) {
				this->_node = other.node();
				return *this;
			}

			inline operator red_black_tree_iterator<const T>() const {
				return (this->_node);
			}

			inline reference operator*() const {
				return *(this->_node->value);
			}

			inline pointer operator->() const {
				return this->_node->value;
			}

			inline red_black_tree_iterator & operator++() {
				if (this->_node->right && !_node->right->is_nil) {
					this->_node = this->tree_min(_node->right);
				}
				else {
					node_pointer y = this->_node->parent;
					while (y != 0x0 && this->_node == y->right) {
						this->_node = y;
						y = y->parent;
					}
					this->_node = y;
				}
				return *this;
			}

			inline red_black_tree_iterator operator++(int) {
				red_black_tree_iterator<value_type> temp = *this;
				if (!this->_node->right->is_nil) {
					this->_node = this->tree_min(_node->right);
				}
				else {
					node_pointer y = this->_node->parent;
					while (y != 0x0 && this->_node == y->right) {
						this->_node = y;
						y = y->parent;
					}
					this->_node = y;
				}
				return temp;
			}

			inline red_black_tree_iterator & operator--() {
				if (_node->left && !_node->left->is_nil) {
					this->_node = this->tree_max(_node->left);
				}
				else {
					node_pointer y = this->_node->parent;
					while (y != 0x0 && this->_node == y->left) {
						this->_node = y;
						y = y->parent;
					}
					this->_node = y;
				}
				return *this;
			}

			inline red_black_tree_iterator operator--(int) {
				red_black_tree_iterator<value_type> temp = *this;
				if (this->_node->left && !this->_node->left->is_nil) {
					this->_node = this->tree_max(this->_node->left);
				}
				else {
					node_pointer y = _node->parent;
					while (y != 0x0 && this->_node == y->left) {
						this->_node = y;
						y = y->parent;
					}
					this->_node = y;
				}
				return temp;
			}

			inline node_pointer node() const {
				return this->_node;
			}

			inline bool operator==(const red_black_tree_iterator & it) {
				return (this->_node == it._node);
			}
			
			inline bool operator!=(const red_black_tree_iterator & it) {
				return (this->_node != it._node);
			}

		private:
			node_pointer _node;

			inline node_pointer tree_min(node_pointer node) const {
				while (node->left != NULL && !node->left->is_nil)
					node = node->left;
				return node;
			}

			inline node_pointer tree_max(node_pointer node) const {
				while (!node->right->is_nil)
					node = node->right;
				return node;
			}
	};
}

#endif