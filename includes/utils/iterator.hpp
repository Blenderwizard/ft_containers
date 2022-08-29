/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:33:09 by jrathelo          #+#    #+#             */
/*   Updated: 2022/08/29 10:47:51 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iterator_traits.hpp>

namespace ft {
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> class iterator {
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
    };

	class random_access_iterator_tag {};

	template <typename T> class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;
            
			random_access_iterator() : current(0x0) {}

			random_access_iterator(pointer x): current(x) {}

			random_access_iterator(const random_access_iterator& rai): current(rai.current) {}
		
			random_access_iterator & operator=(const random_access_iterator & rai) {
				if (this != &rai)
					this->current = rai.current;
				return (*this);
			}
			
			virtual ~random_access_iterator() {}

			pointer base() const {
				return (this->current);
			}

			reference operator*() const {
				return *(this->current);
			}

			pointer operator->() {
				return &(this->operator*());
			}

			random_access_iterator & operator++() {
				this->current++;
				return (*this);
			}

			random_access_iterator operator++(int) {
				random_access_iterator ret(*this);
				operator++();
				return (ret);
			}

			random_access_iterator & operator--() {
				this->current--;
				return (*this);
			}

			random_access_iterator operator--(int) {
				random_access_iterator ret(*this);
				operator--();
				return (ret);
			}

			random_access_iterator operator+(difference_type count) const {
				return (this->current + count);
			}

			random_access_iterator operator-(difference_type count) const {
				return (this->current - count);
			}

			random_access_iterator operator+=(difference_type count) {
				this->current += count;
				return (*this);
			}

			reference operator[](difference_type count) {
				return (*(operator + (count)));
			}
		
		private:
			pointer current;
	};

	// Out of class random acess iterator defs
	
	template <typename T> typename ft::random_access_iterator<T>::difference_type operator==(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() == rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator==(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() == rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator!=(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() != rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator!=(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() != rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator<(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() < rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator<(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() < rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator>(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() > rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator>(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() > rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator<=(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() <= rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator<=(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() <= rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator>=(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() >= rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator>=(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() >= rai2.base());
	}

	template<typename T> ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type count, typename ft::random_access_iterator<T> & rai) {
		return (&(*rai) + count);
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator-(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() - rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator-(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() - rai2.base());
	}

	template<class T> struct Node{
		public:
			explicit Node(T *srcval = 0) :	value(srcval), parent(0), left(0), right(0), is_black(false), is_nil(0) {}
	
			Node(Node const & other) {
				this->is_black = other.is_black;
				this->value = other.value;
				this->parent = other.parent;
				this->is_nil = other.is_nil;
				this->right = other.right;
				this->left = other.left;
			};

			Node& operator=(const Node& other) {
				this->is_black = other.is_black;
				this->value = other.value;
				this->is_nil = other.is_nil;
				this->parent = other.parent;
				this->right = other.right;
				this->left = other.left;
				return *this;
			}

			virtual ~Node(){}
		private:
			T	*value;
			Node*	parent;
			Node*	left;
			Node*	right;	
			bool	is_black;
			bool	is_nil;
	};

	class red_black_tree_iterator_tag {};

	template<typename T> class red_black_tree_iterator {
		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename ft::iterator_traits<T*>::value_type 		value_type;
			typedef typename ft::iterator_traits<T*>::reference 		reference;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef Node<typename ft::remove_const<value_type>::type >* node_pointer;

			red_black_tree_iterator() {}

			red_black_tree_iterator(void *node): _node(static_cast<node_pointer>(node)) {}

			red_black_tree_iterator(const red_black_tree_iterator<typename ft::remove_const<value_type>::type > & other) {
				*this = other;
			}

			red_black_tree_iterator& operator=(const red_black_tree_iterator<typename ft::remove_const<value_type>::type>& other) {
				this->_node = other.node();
				return *this;
			}

			reference operator*() const {
				return *(_node->value);
			}

			pointer operator->() const {
				return _node->value;
			}

			red_black_tree_iterator& operator++() {
				if (_node->right && !_node->right->is_nil) {
					_node = tree_min(_node->right);
				}
				else {
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->right) {
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return *this;
			}

			red_black_tree_iterator operator++(int) {
				red_black_tree_iterator<value_type> temp = *this;
				if (!_node->right->is_nil) {
					_node = tree_min(_node->right);
				}
				else {
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->right) {
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return temp;
			}

			red_black_tree_iterator& operator--() {
				if (_node->left && !_node->left->is_nil) {
					_node = tree_max(_node->left);
				}
				else {
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->left) {
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return *this;
			}

			red_black_tree_iterator operator--(int) {
				red_black_tree_iterator<value_type> temp = *this;
				if (_node->left && !_node->left->is_nil) {
					_node = tree_max(_node->left);
				}
				else {
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->left) {
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return temp;
			}

			node_pointer node() const {
				return _node;
			}

		private:
			node_pointer _node;

			node_pointer tree_min(node_pointer n) const {
				while(n->left != NULL && !n->left->is_nil)
					n = n->left;
				return n;
			}

			node_pointer tree_max(node_pointer n) const {
				while (!n->right->is_nil)
					n = n->right;
				return n;
			}
	};

	// Out of class defs for red black tree iterators

	template<typename RBTI1, typename RBTI2> bool operator==(const red_black_tree_iterator<RBTI1> & lhs, const red_black_tree_iterator<RBTI2> & rhs) {
		return (lhs.node() == rhs.node());
	}

	template<typename RBTI1, typename RBTI2> bool operator!=(const red_black_tree_iterator<RBTI1> & lhs, const red_black_tree_iterator<RBTI2> & rhs) {
		return (lhs.node() != rhs.node());
	}

	template <bool is_valid, typename T> struct valid_tag {
		typedef T type;
		const static bool value = is_valid;
	};

	template <typename T> struct check_iterator_tagged_ft : public valid_tag<false, T> { };
	template <> struct check_iterator_tagged_ft<ft::random_access_iterator_tag> : public valid_tag<true, ft::random_access_iterator_tag> { };
	template <> struct check_iterator_tagged_ft<ft::red_black_tree_iterator_tag> : public valid_tag<true, ft::red_black_tree_iterator_tag> { };
}

#endif