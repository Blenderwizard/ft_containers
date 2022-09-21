/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:21:49 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/21 11:08:42 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>
#include <algorithm>
#include <limits>

#include "pair.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"
#include "../stack.hpp"

namespace ft {
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> > class RBTree {
		public:
			typedef T															value_type;
			typedef typename value_type::first_type								key_type;
			typedef typename value_type::second_type							mapped_type;
			typedef Compare														value_compare;
			typedef Alloc														allocator_type;
			typedef ft::Node<T>													node_type;
			typedef typename Alloc::template rebind<node_type>::other			node_allocator;
			typedef	typename node_allocator::pointer							node_pointer;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef std::ptrdiff_t												difference_type;
			typedef std::size_t													size_type;
			typedef ft::red_black_tree_iterator<T>								iterator;
			typedef ft::red_black_tree_iterator<const T>						const_iterator;
			typedef	ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			inline RBTree(const Compare & comp = value_compare(), const allocator_type & a = allocator_type()) : val_alloc(a), node_alloc(node_allocator()), compare(comp), root(0x0), tree_size(0) { }

			inline RBTree(const RBTree & src) {
				if (this->empty())
					this->_clear_tree();
				this->node_alloc = src.node_alloc;
				this->val_alloc = src.val_alloc;
				this->compare = src.compare;
				this->root = 0x0;
				this->tree_size = 0;
				if (!src.empty())
					this->insert(src.cbegin(), src.cend());
			}
		
			inline RBTree& operator=(const RBTree & src) {
				if (this->empty())
					this->_clear_tree();
				this->node_alloc = src.node_alloc;
				this->val_alloc = src.val_alloc;
				this->compare = src.compare;
				this->root = 0x0;
				this->tree_size = 0;
				if (src.empty())
					return(*this);
				this->insert(src.cbegin(), src.cend());
				return *this;
			}

			inline ~RBTree() {
				this->_clear_tree();
			}

			inline iterator end() {
				return (iterator(0x0, this->_tree_min(), this->_tree_max()));
			}

			inline const_iterator end() const {
				return (iterator(0x0, this->_tree_min(), this->_tree_max()));
			}

			inline const_iterator cend() const {
				return (iterator(0x0, this->_tree_min(), this->_tree_max()));
			}

			inline iterator begin() {
				return (iterator(this->_tree_min(), this->_tree_min(), this->_tree_max()));
			}

			inline const_iterator begin() const {
				return (iterator(this->_tree_min(), this->_tree_min(), this->_tree_max()));
			}

			inline const_iterator cbegin() const {
				return (iterator(this->_tree_min(), this->_tree_min(), this->_tree_max()));
			}

			inline reverse_iterator rbegin() {
				return (reverse_iterator(this->end()));
			}

			inline const_reverse_iterator rbegin() const {
				return (reverse_iterator(this->end()));
			}

			inline const_reverse_iterator rcbegin() const {
				return (reverse_iterator(this->end()));
			}

			inline reverse_iterator rend() {
				return (reverse_iterator(this->begin()));
			}

			inline const_reverse_iterator rend() const {
				return (const_reverse_iterator(this->begin()));
			}

			inline const_reverse_iterator rcend() const {
				return (const_reverse_iterator(this->begin()));
			}

			inline node_pointer search(const key_type & value, node_pointer node) const {
				if(!node)
					return 0x0;
				if (this->compare(value, node->value->first))
					return this->search(value, node->left);
				if (this->compare(node->value->first, value))
					return this->search(value, node->right);
				return node;
			}

			inline iterator find(const key_type & value) {
				node_pointer ret = this->search(value, this->root);
				if (ret == 0x0)
					return this->end();
				return iterator(ret, this->_tree_min(), this->_tree_max());
			}

			inline const_iterator find(const key_type & value) const {
				node_pointer ret = this->search(value, this->root);
				if (ret == 0x0)
					return this->end();
				return iterator(ret, this->_tree_min(), this->_tree_max());
			}
			
			inline ft::pair<iterator, bool> insert(const value_type & value) {
				node_pointer new_node = this->_insert_into_tree(value);
				if (!new_node) {
					return ft::make_pair(this->find(value.first), false);
				}
				return ft::make_pair(iterator(new_node, this->_tree_min(), this->_tree_max()), true);
			}

			inline iterator insert(iterator hint, const value_type & value) {
				node_pointer pos = hint.node();
				while (1) {
					if (!pos || pos->value->first == value.first)
						break;
					if (!this->compare(pos->value->first, value.first))
						pos = pos->left;
					else
						pos = pos->right;
				}
				if (pos)
					return (iterator(pos, this->_tree_min(), this->_tree_max()));
				node_pointer new_node = this->_insert_into_tree(value);
				return (iterator(new_node, this->_tree_min(), this->_tree_max()));
			}
			
			template <class InputIt> inline void insert(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last) {
				for (; first != last; first++)
					this->_insert_into_tree(*first);
			}

			inline void erase(iterator & it) {
				this->erase(it->first);
			}

			inline size_type erase(const key_type & value) {
				node_pointer ret = this->search(value, this->root);
				if (ret != 0x0)
					this->_erase_node(ret);
				return (ret != 0x0);
			}

			inline iterator erase(iterator & first, iterator & last) {
				ft::stack<const key_type> todel;
				for (; first != last && first != this->end(); first++)
					todel.push(first->first);
				while (todel.size() != 0) {
					this->erase(todel.top());
					todel.pop();
				}
				return (last);
			}

			inline size_type size() const {
				return (this->tree_size);
			}

			// Thanks sspina for the help
			inline size_type max_size() const {
				size_type div = sizeof(node_pointer) * 4 + sizeof(value_type);
				div = (div / 8) * 8;
				return (std::numeric_limits<size_type>::max() / div);
			}
			
			inline bool empty() const {
				return (this->tree_size == 0);
			}

			inline value_compare value_comp() const {
				return (this->compare);
			}
			
			inline void clear() {
				this->_clear_tree();
			}

			inline iterator lower_bound(const key_type & value) {
				iterator last = this->end();
				for (iterator first = this->begin(); first != last; ++first) {
					if (!this->compare(first->first, value)) {
						return (first);
					}
				}
				return (last);
			}

			inline const_iterator lower_bound(const key_type & value) const{
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (!this->compare(first->first, value)) {
						return (first);
					}
				}
				return (last);
			}

			inline const_iterator clower_bound(const key_type & value) const{
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (!this->compare(first->first, value)) {
						return (first);
					}
				}
				return (last);
			}

			inline iterator upper_bound(const key_type & value) {
				iterator last = this->end();
				for (iterator first = this->begin(); first != last; ++first){
					if (this->compare(value, first->first)) {
						return (first);
					}
				}
				return (last);
			}

			inline const_iterator upper_bound(const key_type & value) const {
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (this->compare(value, first->first)) {
						return (first);
					}
				}
				return (last);
			}

			inline const_iterator cupper_bound(const key_type & value) const {
				const_iterator last = this->cend();
				for (const_iterator first = this->cbegin(); first != last; ++first) {
					if (this->compare(value, first->first)) {
						return (first);
					}
				}
				return (last);
			}

			inline void swap(RBTree &other) {
				std::swap(this->root, other.root);
				std::swap(this->tree_size, other.tree_size);
				std::swap(this->node_alloc, other.node_alloc);
				std::swap(this->val_alloc, other.val_alloc);
				std::swap(this->compare, other.compare);
			}

			inline ft::pair<iterator, iterator> equal_range(const key_type & value) {
				return (ft::make_pair(this->lower_bound(value), this->upper_bound(value)));
			}

			inline ft::pair<const_iterator, const_iterator> equal_range(const key_type & value) const {
				return (ft::make_pair(this->clower_bound(value), this->cupper_bound(value)));
			}
			
			inline allocator_type get_allocator() const {
				return (this->val_alloc);
			}

		protected:
			inline node_pointer _tree_min() const {
				if (!this->root)
					return (0x0);
				return this->root->min();
			}
			
			inline node_pointer _tree_max() const {
				if (!this->root)
					return (0x0);
				return this->root->max();
			}
			
			inline void _rotate_right(node_pointer	node) {
				if (!node || !node->left) 
					return;
				node_pointer y = node->left;
				node->left = y->right;
				if (node->left)
					node->left->parent = node;
				if (!node->parent)
					this->root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->parent = node->parent;
				node->parent = y;
				y->right = node;
			}

			inline void _rotate_left(node_pointer	node) {
				if (!node || !node->right) 
					return;
				node_pointer y = node->right;
				node->right = y->left;
				if (node->right)
					node->right->parent = node;
				if (!node->parent)
					this->root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->parent = node->parent;
				node->parent = y;
				y->left = node;
			}

			inline node_pointer _insert_into_tree(const value_type & value) {
				if (this->search(value.first, this->root))
					return (0x0);
				node_pointer new_node = this->_create_node(value);
				if (!this->root) {
					this->root = new_node;
				} else {
					node_pointer current = this->root;
					while (1) {
						if (this->compare(current->value->first, new_node->value->first)) {
							if (!current->right) {
								new_node->parent = current;
								current->right = new_node;
								break;
							} else
								current = current->right;
						} else {
							if (!current->left) {
								new_node->parent = current;
								current->left = new_node;
								break;
							} else {
								current = current->left;
							}
						}
					}
				}
				this->_insert_rebalance(new_node);
				this->tree_size++;
				return (new_node);
			}
			
			inline void _insert_rebalance(node_pointer node) {
				node_pointer parent = node->parent;
				if (!parent) {
					node->is_black = true;
					return;
				} else if (parent->is_black) {
					return;
				}
				node_pointer grandparent = 0x0;
				node_pointer uncle = 0x0;
				if (node && node->parent)
					grandparent = node->parent->parent;
				if (grandparent) {
					if (node->parent == grandparent->left)
						uncle = grandparent->right;
					else
						uncle = grandparent->left;
				}
				if (!parent->is_black && (uncle && !uncle->is_black)) {
					parent->is_black = true;
					uncle->is_black = true;
					grandparent->is_black = false;
					this->_insert_rebalance(grandparent);
				} else if (grandparent && parent == grandparent->left) {
					if (node == parent->right) {
						node = parent;
						this->_rotate_left(parent);
					}
					parent->is_black = true;
					if (grandparent) {
						grandparent->is_black = false;
						this->_rotate_right(grandparent);
					}
				} else {
					if (node == parent->left) {
						node = parent;
						this->_rotate_right(parent);
					}
					parent->is_black = true;
					if (grandparent) {
						grandparent->is_black = false;
						this->_rotate_left(grandparent);
					}
				}
			}

			inline void _transplant(node_pointer where, node_pointer what) {
				if (!where->parent)
					this->root = what;
				else if (where == where->parent->left)
					where->parent->left = what;
				else
					where->parent->right = what;
				if (what)
					what->parent = where->parent;
			}

			inline void _erase_node(node_pointer & node) {
				node_pointer x = 0x0, y = node, tmp = 0x0;
				bool y_last_color_black = y->is_black;
				if (!node->left && !node->right) {
					tmp = this->_create_node(*(node->value));
					tmp->is_black = true;
					this->_transplant(node, tmp);
					x = tmp;
				} else if (!node->left) {
					x = node->right;
					this->_transplant(node, node->right);
				} else if (!node->right){
					x = node->left;
					this->_transplant(node, node->left);
				} else {
					y = node->prev();
					x = y->left;
					if (!x) {
						tmp = this->_create_node(*(node->value));
						tmp->is_black = true;
						tmp->parent = y;
						y->left = tmp;
						x = tmp;
					}
					y_last_color_black = y->is_black;
					if (y->parent != node) {
						this->_transplant(y, x);
						y->left = node->left;
						if (y->left)
							y->left->parent = y;
					}
					this->_transplant(node, y);
					y->is_black = node->is_black;
					y->right = node->right;
					if (y->right)
						y->right->parent = y;
				}
				this->_delete_node(node);
				this->tree_size--;
				if (y_last_color_black)
					this->_erase_rebalance(x);
				if (tmp) {
					this->_transplant(tmp, NULL);
					this->_delete_node(tmp);
				}
			}
			
			inline void _erase_rebalance(node_pointer node) {
				node_pointer sibling;
				while (node != this->root && node->is_black) {
					if (node == node->parent->left) {
						sibling = node->parent->right;
						if (!sibling->is_black) {
							sibling->is_black = true;
							node->parent->is_black = false;
							this->_rotate_left(node->parent);
							sibling = node->parent->right;
						}
						if (sibling && (!sibling->left || sibling->left->is_black) && (!sibling->right || sibling->right->is_black)) {
							sibling->is_black = false;
							node = node->parent;
						} else {
							if (sibling->right->is_black) {
								sibling->left->is_black = true;
								sibling->is_black = false;
								this->_rotate_right(sibling);
								sibling = node->parent->right;
							}
							sibling->is_black = node->parent->is_black;
							node->parent->is_black = true;
							sibling->right->is_black = true;
							this->_rotate_left(node->parent);
							node = this->root;
						}
					} else {
						sibling = node->parent->left;
						if (!sibling->is_black) {
							sibling->is_black = true;
							node->parent->is_black = false;
							this->_rotate_right(node->parent);
							sibling = node->parent->right;
						}
						if (sibling && (!sibling->right || sibling->right->is_black) && (!sibling->left || sibling->left->is_black)) {
							sibling->is_black = false;
							node = node->parent;
						} else {
							if (sibling->left->is_black) {
								sibling->right->is_black = true;
								sibling->is_black = false;
								this->_rotate_left(sibling);
								sibling = node->parent->left;
							}
							sibling->is_black = node->parent->is_black;
							node->parent->is_black = true;
							sibling->left->is_black = true;
							this->_rotate_right(node->parent);
							node = this->root;
						}
					}
				}
				node->is_black = true;
			}

			inline void _clear_tree() {
				this->_destroy_tree(this->root);
				this->root = 0x0;
				this->tree_size = 0;
			}

			inline void _destroy_tree(node_pointer node) {
				if (!node)
					return;
				this->_destroy_tree(node->left);
				this->_destroy_tree(node->right);
				this->_delete_node(node);
			}

			inline node_pointer	_create_node(const value_type & value) {
				node_pointer new_node = this->node_alloc.allocate(1);
				this->node_alloc.construct(new_node, Node<T>());
				new_node->value = this->val_alloc.allocate(1);
				this->val_alloc.construct(new_node->value, value);
				return (new_node);
			}

			inline void _delete_node(node_pointer node) {
				if (!node)
					return;
				this->val_alloc.destroy(node->value);
				this->val_alloc.deallocate(node->value, 1);
				this->node_alloc.destroy(node);
				this->node_alloc.deallocate(node, 1);
			}

		private:
			allocator_type				val_alloc;
			node_allocator				node_alloc;
			value_compare 				compare;
			node_pointer				root;
			size_type					tree_size;

	};

	template<class Content, class Compare, class Alloc> inline void swap(const  RBTree<Content, Compare, Alloc> & lhs, const  RBTree<Content, Compare, Alloc> & rhs) {
		lhs.swap(rhs);
	}
}

#endif