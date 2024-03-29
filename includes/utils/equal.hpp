/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:19:22 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/17 14:10:41 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft {
	template <class InputIt1, class InputIt2> inline bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for(; first1 != last1; first1++, first2++) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	};

	template <class InputIt1, class InputIt2, class BinaryPredicate > inline bool equal(InputIt1 & first1, InputIt1 & last1, InputIt2 & first2, BinaryPredicate p) {
		for(; first1 != last1; first1++, first2++) {
			if (p(first1, first2)) {
				return false;
			}
		}
		return true;
	};
}
#endif