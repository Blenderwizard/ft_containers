/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:21:49 by jrathelo          #+#    #+#             */
/*   Updated: 2022/08/28 13:34:44 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

namespace ft {
	template <class T> class RBtree {
		public:
			RBtree();
			RBtree(T& value);
			RBtree(const RBtree<T> & other);
			RBtree & operator=(const RBtree<T> & other);

			~RBtree();
		private:
			enum color_t { BLACK, RED };

			class RBnode {
				public:
					
				private:
					RBnode* parent;
					RBnode* child[2];
					enum color_t color;
					int key;
			};

			RBnode* root;
	};
}

#endif