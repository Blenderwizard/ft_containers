/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:45:23 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/05 15:50:31 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft {
	template< class Iter > struct iterator_traits {
		public:
			typedef difference_type		Iter::difference_type;
			typedef value_type			Iter::value_type;
			typedef pointer				Iter::pointer;
			typedef reference			Iter::reference;
			typedef iterator_category	Iter::iterator_category;

			
	};
	template< class T > struct iterator_traits<T*> {

	};
};

#endif