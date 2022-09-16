/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:21:49 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/16 11:22:20 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>
#include <algorithm>

#include "pair.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"

namespace ft {
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> > class RBTree {
		public:
			typedef T															value_type;
			typedef Compare														value_compare;
			typedef Alloc														allocator_type;
			typedef typename Alloc::template rebind<Node<T> >::other			node_allocator;
			typedef	typename node_allocator::pointer							node_pointer;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef std::ptrdiff_t												difference_type;
			typedef std::size_t													size_type;
			typedef red_black_tree_iterator<T>									iterator;
			typedef red_black_tree_iterator<const T>							const_iterator;
			typedef	ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			inline RBTree(const Compare & comp, const allocator_type& a = allocator_type()) : val_alloc(a), node_alloc(node_allocator()), compare(comp), root(0x0), tree_size(0) {
				this->init_nil_head();
				this->root = this->header;
			}

			inline RBTree() : root(0x0), val_alloc(allocator_type()), node_alloc(node_allocator()), compare(value_compare()), tree_size(0) {
				this->init_nil_head();
				this->root = this->header;
			}

			inline RBTree(const RBTree & src) :  compare(src.compare), root(0x0) {
				*this = src;
			}

			template<class InputIt> inline RBTree(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last, const value_compare & comp, const allocator_type& alloc = allocator_type()): val_alloc(alloc), node_alloc(node_allocator()), compare(comp) {
				this->init_nil_head();
				this->root = this->header;
				for (; first != last; ++first)
					this->insert(*first);
			}
		
			inline RBTree& operator=(const RBTree & src){
				if (this == &src)
					return *this;
				this->node_alloc = src.node_alloc;
				this->val_alloc = src.val_alloc;
				this->compare = src.compare;
				if (this->root == NULL)
					this->init_nil_head();
				else
					this->clear_node(this->root);
				if (src.tree_size == 0)
					this->root = this->header;
				else {
					this->root = this->copy_node(src.root);
					this->copy_child(this->root, src.root);
				}
				this->tree_size = src.tree_size;
				return *this;
			}

			inline ~RBTree() {
				clear_node(this->root);
				this->val_alloc.destroy(this->header->value);
				this->val_alloc.deallocate(this->header->value, 1);
				this->node_alloc.deallocate(this->nil, 1);
				this->node_alloc.deallocate(this->header, 1);
			}

			inline iterator end() {
				return (iterator(this->header));
			}

			inline const_iterator end() const {
				return (const_iterator(this->header));
			}

			inline iterator begin() {
				if (this->tree_size == 0)
					return (iterator(this->header));
				return (iterator(tree_min(this->root)));
			}

			inline const_iterator begin() const {
				if (this->tree_size == 0)
					return (const_iterator(this->header));
				return (const_iterator(tree_min(this->root)));
			}

			inline reverse_iterator rbegin() {
				return (reverse_iterator(this->end()));
			}	

			inline const_reverse_iterator rbegin() const {
				return (const_reverse_iterator(this->end()));
			}	

			inline reverse_iterator rend() {
				return (reverse_iterator(this->begin()));
			}	

			inline const_reverse_iterator rend() const {
				return (const_reverse_iterator(this->begin()));
			}	

			inline pointer	create_value(const value_type &value){
				pointer new_val = this->val_alloc.allocate(1);
				this->val_alloc.construct(new_val, value);
				return new_val;
			}

			inline node_pointer copy_node(node_pointer other) {
				node_pointer new_node = this->node_alloc.allocate(1);
				this->node_alloc.construct(new_node, Node<T>());
				new_node->is_black = other->is_black;
				new_node->is_nil = other->is_nil;
				if (other->value) {
					new_node->value = this->val_alloc.allocate(1);
					this->val_alloc.construct(new_node->value, *other->value);
				}
				return (new_node);
			}
		
			inline void copy_child(node_pointer my_node, node_pointer other) {
				if (other->left->is_nil)
					my_node->left = this->nil;
				else {
					my_node->left = this->copy_node(other->left);
					my_node->left->parent = my_node;
					this->copy_child(my_node->left, other->left);
				}
				if (other->right->is_nil)
					my_node->right = this->nil;
				else if (other->right->right == 0x0) {
					my_node->right = this->header;
					this->header->parent = my_node;
				} else {
					my_node->right = this->copy_node(other->right);
					my_node->right->parent = my_node;
					this->copy_child(my_node->right, other->right);
				}
			}

			inline node_pointer search(const value_type & value, node_pointer node) const {
				if(!node || this->is_nil(node))
					return 0x0;
				if (this->compare(value, *node->value))
					return this->search(value, node->left);
				if (this->compare(*node->value, value))
					return this->search(value, node->right);
				return node;
			}

			inline iterator find(const value_type & value) {
				node_pointer ret = this->search(value, this->root);
				if (ret == 0x0)
					return this->end();
				return iterator(ret);
			}

			inline const_iterator find(const value_type & value) const {
				node_pointer ret = this->search(value, this->root);
				if (ret == 0x0)
					return this->end();
				return const_iterator(ret);
			}
			
			inline ft::pair<iterator, bool> insert(value_type const & value) {
				node_pointer find = this->search(value, this->root);
				if (find)
					return ft::pair<iterator, bool>(iterator(find), false);
				node_pointer new_node = this->node_alloc.allocate(1);
				this->node_alloc.construct(new_node, Node<value_type>(create_value(value)));
				new_node->left = this->nil;
				new_node->right = this->nil;
				this->_insert_into_tree(new_node, this->root);
				ft::pair<iterator, bool> ret(iterator(new_node), true);
				this->_insert_fixup(new_node);
				this->tree_size++;
				new_node = this->tree_max(this->root);
				new_node->right = this->header;
				this->header->parent = new_node;
				return ret;
			} 

			inline iterator insert(iterator position, const value_type & value) {
				node_pointer new_node = search(value,this->root);
				if (new_node)
					return (iterator(new_node));
				new_node = this->node_alloc.allocate(1);
				this->node_alloc.construct(new_node, Node<value_type>(this->create_value(value)));
				new_node->left = this->nil;
				new_node->right = this->nil;
				if (position == this->begin()){
					if (position != this->end() && this->compare(value, *position))
						this->_insert_into_tree(new_node, this->tree_min(this->root));
					else
						this->_insert_into_tree(new_node, this->root);
				}
				else if (position == this->end()){
					if (position != begin() && this->compare(*(--position), value))
						this->_insert_into_tree(new_node, this->header->parent);
					else
						this->_insert_into_tree(new_node, this->root);
				}
				else
					this->_insert_into_tree(new_node, this->root);
				this->_insert_fixup(new_node);
				this->tree_size++;
				node_pointer max_of_tree = this->tree_max(this->root);
				max_of_tree->right = this->header;
				this->header->parent = max_of_tree;
				return (iterator(new_node));
			}
			
			template <class InputIt> inline void insert(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last) {
				for (; first != last; first++)
					this->insert(*first);
			}

			inline void erase(iterator pos) {
				node_pointer y = pos.node(), x, for_free = y;
				bool y_original_is_black = y->is_black;
				if (this->is_nil(y->left)) {
					x = y->right;
					this->transplant(y, y->right);
				} else if (this->is_nil(y->right)) {
					x = y->left;
					this->transplant(y, y->left);
				} else {
					node_pointer z = y;
					y = this->tree_min(z->right);
					y_original_is_black = y->is_black;
					x = y->right;
					if (y->parent != z){
						this->transplant(y, y->right);
						y->right = z->right;
						z->right->parent = y;
					}
					this->transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->is_black = z->is_black;
				}
				this->free_node(for_free);
				if (y_original_is_black)
					this->erase_fixup(x);
				this->tree_size--;
				this->nil->parent = 0x0;
				if (this->tree_size == 0)
					this->root = this->header;
				else {
					if (this->tree_size != 1)
						x = tree_max(this->root);
					else
						x = this->root;
					x->right = this->header;
					this->header->parent = x;
				}
			}

			inline size_type erase(const value_type& value) {
				node_pointer ret = search(value, this->root);
				if (ret)
					this->erase(iterator(ret));
				return (ret != 0x0);
			}

			inline void erase(iterator first, iterator last) {
				while (first != last)
					this->erase(first++);
			}

			inline void erase_fixup(node_pointer x) {
				node_pointer brother;
				while (x != this->root && x->is_black) {
					if (x == x->parent->left) {
						brother = x->parent->right;
						if (!brother->is_black) {
							brother->is_black = true;
							x->parent->is_black = false;
							this->_rotate_left(x->parent);
							brother = x->parent->right;
						}
						if (brother->left->is_black && brother->right->is_black) {
							brother->is_black = false;
							x = x->parent;
						} else {
							if (brother->right->is_black){
								brother->left->is_black = true;
								brother->is_black = false;
								this->_rotate_right(brother);
								brother = x->parent->right;
							}
							brother->is_black = x->parent->is_black;
							x->parent->is_black = true;
							brother->right->is_black = true;
							this->_rotate_left(x->parent);
							x = this->root;
						}
					} else {
						brother = x->parent->left;
						if (!brother->is_black) {
							brother->is_black = true;
							x->parent->is_black = false;
							this->_rotate_right(x->parent);
							brother = x->parent->left;
						}
						if (brother->right->is_black && brother->left->is_black) {
							brother->is_black = false;
							x = x->parent;
						} else {
							if (brother->left->is_black){
								brother->right->is_black = true;
								brother->is_black = false;
								this->_rotate_left(brother);
								brother = x->parent->left;
							}
							brother->is_black = x->parent->is_black;
							x->parent->is_black = true;
							brother->left->is_black = true;
							this->_rotate_right(x->parent);
							x = this->root;
						}
					}
				}
			}

			inline size_type size() const {
				return (this->tree_size);
			}

			inline size_type max_size() const {
				return (this->val_alloc.max_size());
			}
			
			inline bool empty() const {
				return (this->tree_size == 0);
			}

			inline value_compare value_comp() const {
				return (this->compare);
			}
			
			inline void clear() {
				this->clear_node(this->root);
				this->root = this->header;
				this->header->parent = 0x0;
				this->tree_size = 0;
			}
			
			inline size_type count(const value_type& value) const {
				return (this->find(value) != this->end());
			}

			inline iterator lower_bound(const value_type& value) {
				iterator last = this->end();
				for (iterator first = this->begin(); first != last; ++first) {
					if (!this->compare(*first, value))
						return (first);
				}
				return (last);
			}

			inline const_iterator lower_bound(const value_type& value) const{
				const_iterator last = this->end();
				for (const_iterator first = this->begin(); first != last; ++first){
					if (!this->compare(*first, value))
						return (first);
				}
				return (last);
			}

			inline iterator upper_bound(const value_type& value) {
				iterator last = this->end();
				for (iterator first = this->begin(); first != last; ++first){
					if(this->compare(value, *first))
						return (first);
				}
				return (last);
			}

			inline const_iterator upper_bound(const value_type& value) const {
				const_iterator last = this->end();
				for (const_iterator first = this->begin(); first != last; ++first){
					if (this->compare(value, *first))
						return (first);
				}
				return (last);
			}

			inline void swap(RBTree &other) {
				std::swap(this->root, other.root);
				std::swap(this->nil, other.nil);
				std::swap(this->header, other.header);
				std::swap(this->tree_size, other.tree_size);
				std::swap(this->node_alloc, other.node_alloc);
				std::swap(this->val_alloc, other.val_alloc);
				std::swap(this->compare, other.compare);
			}

			inline ft::pair<iterator, iterator> equal_range(const value_type &value) {
				return (ft::make_pair(this->lower_bound(value), this->upper_bound(value)));
			}
			
			inline allocator_type get_allocator() const {
				return (this->val_alloc);
			}

		protected:
			inline node_pointer _tree_min(node_pointer node) const {
				while (node != 0x0 && !is_nil(node->left))
					node = node->left;
				return node;
			}
			
			inline node_pointer _tree_max(node_pointer node) const {
				while (node != NULL && !is_nil(node->right))
					node = node->right;
				return node;
			}
			
			inline void _rotate_right(node_pointer	node) {
				node_pointer y;

				y = node->left;
				node->left = y->right;
				if (!this->is_nil(y->right))
					y->right->parent = node;
				y->parent = node->parent;
				if (node->parent == 0x0)
					this->root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->right = node;
				node->parent = y;
			}

			inline void _rotate_left(node_pointer	node) {
				node_pointer y;

				y = node->right;
				node->right = y->left;
				if (!this->is_nil(y->left))
					y->left->parent = node;
				y->parent = node->parent;
				if (node->parent == 0x0)
					this->root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->left = node;
				node->parent = y;
			}

			inline node_pointer _insert(node_pointer new_node) {
				if (this->root == this->header)
					this->root = new_node;
				else
					this->_insert_to_node(this->root, new_node);
				return new_node;	
			}

			inline node_pointer _insert_to_node(node_pointer root, node_pointer new_node) {
				if (this->compare(*new_node->value, *root->value)) {
					if (!is_nil(root->left))
						return (this->_insert_to_node(root->left, new_node));
					root->left = new_node;
				} else {
					if (!is_nil(root->right))
						return (this->_insert_to_node(root->right, new_node));
					root->right = new_node;
				}
				new_node->parent = root;
				return (new_node);
			}
			
			inline node_pointer _insert_into_tree(node_pointer new_node, node_pointer where) {
				if (this->root == this->header)
					this->root = new_node;
				else
					this->_insert_to_node(where, new_node);
				return (new_node);
			}

			inline void _insert_fixup(node_pointer node) {
				if (node != this->root && node->parent != this->root) {
					while (node != this->root && !node->parent->is_black) {
						if (node->parent == node->parent->parent->left) {
							node_pointer uncle = node->parent->parent->right;
							if (!uncle->is_black) {
								node->parent->is_black = true;
								uncle->is_black = true;
								node->parent->parent->is_black = false;
								node = node->parent->parent;
							} else {
								if (node == node->parent->right) {
									node = node->parent;
									this->_rotate_left(node);
								}
								node->parent->is_black = true;
								node->parent->parent->is_black = false;
								this->_rotate_right(node->parent->parent);
							}
						} else {
							node_pointer uncle = node->parent->parent->left;
							if (!uncle->is_black) {
								node->parent->is_black = true;
								uncle->is_black = true;
								node->parent->parent->is_black = false;
								node = node->parent->parent;
							} else {
								if (node == node->parent->left){
									node = node->parent;
									this->_rotate_right(node);
								}
								node->parent->is_black = true;
								node->parent->parent->is_black = false;
								this->_rotate_left(node->parent->parent);
							}
						}
					}
				}
				this->root->is_black = true;
			}

			inline bool is_nil(node_pointer node) const {
				return node == this->nil || node == this->header;
			}

			inline void clear_node(node_pointer node) {
				if (node && !this->is_nil(node)) {
					this->clear_node(node->right);
					this->clear_node(node->left);
					this->val_alloc.destroy(node->value);
					this->val_alloc.deallocate(node->value, 1);
					this->node_alloc.deallocate(node, 1);
				}
			}
		
			inline void init_nil_head() {
				this->nil = this->node_alloc.allocate(1);
				this->node_alloc.construct(this->nil, Node<T>());
				this->nil->is_black = true;
				this->nil->is_nil = true;
				this->header = this->node_alloc.allocate(1);
				this->node_alloc.construct(this->header, Node<T>());
				this->header->value = this->val_alloc.allocate(1);
				this->val_alloc.construct(this->header->value, T());
				this->header->is_black = true;
			}

			inline void transplant(node_pointer where, node_pointer what) {
				if (where == this->root)
					this->root = what;
				else if (where == where->parent->left)
					where->parent->left = what;
				else
					where->parent->right = what;
				what->parent = where->parent;
			}
			
			inline void free_node(node_pointer node) {
				this->val_alloc.destroy(node->value);
				this->val_alloc.deallocate(node->value, 1);
				this->node_alloc.deallocate(node, 1);
			}
			
		private:
			allocator_type				val_alloc;
			node_allocator				node_alloc;
			value_compare 				compare;
			node_pointer				nil;
			node_pointer				header;
			node_pointer				root;
			size_type					tree_size;
	};

	template<class Content, class Compare, class Alloc> inline void swap(const  RBTree<Content, Compare, Alloc> & lhs, const  RBTree<Content, Compare, Alloc> & rhs) {
		lhs.swap(rhs);
	}
}

#endif