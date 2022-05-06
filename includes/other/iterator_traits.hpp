/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:45:23 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/06 13:56:45 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft {
	template< class Iter > struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter*						pointer;
		typedef typename Iter&						reference;
		typedef typename Iter::iterator_category	iterator_category;
	};
	template< class T > struct iterator_traits<T*> {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter*						pointer;
		typedef typename Iter&						reference;
		typedef typename Iter::iterator_category	iterator_category;
	};
};

#endif