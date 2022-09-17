/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:07:10 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/17 11:35:02 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
	template <class T1, class T2> struct pair {
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			inline pair(): first(), second() { }

			inline pair(const first_type & x, const second_type & y): first(x), second(y) {	}

			template <class U1, class U2> inline pair(const pair<U1, U2> & p): first(p.first), second(p.second) { }

			inline pair(const pair & p): first(p.first), second(p.second) { }

			inline pair & operator=(const pair & p) {
				this->first = p.first;
				this->second = p.second;
				return (*this);
			}

			// operator pair<const T1, T2>() const {
			// 	return(pair<const T1, T2>(first, second));
			// }
	};

	template <class T1, class T2> inline bool operator==(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}

	template <class T1, class T2> inline bool operator!=(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return !(p1 == p2);
	}

	template <class T1, class T2> inline bool operator<(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return p1.first < p2.first || (!(p2.first < p1.first) && p1.second < p2.second);
	}

	template <class T1, class T2> inline bool operator<=(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return !(p2 < p1);
	}

	template <class T1, class T2> inline bool operator>(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return p2 < p1;
	}

	template <class T1, class T2> inline bool operator>=(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return !(p1 < p2);
	}

	template <class T1, class T2> inline pair<T1,T2> make_pair(T1 t, T2 u) {
		return (pair<T1, T2>(t, u));
	}
	
}

#endif