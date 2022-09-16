/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:45:23 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/16 11:27:53 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft {
	template <class Iter> class iterator_traits {
		public:
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef Iter*								pointer;
			typedef Iter&								reference;
			typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T> class iterator_traits<T*> {
		public:
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};

	template <class T> class iterator_traits<const T *> {
		public:
			typedef std::ptrdiff_t						difference_type;
			typedef const T								value_type;
			typedef const T *							pointer;
			typedef const T &							reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};
};

#endif