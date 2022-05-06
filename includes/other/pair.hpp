/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:07:10 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/06 12:29:13 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
	template<class T1, class T2> struct pair {
		public:
			typedef first_type	T1;
			typedef second_type	T2;

			T1	first;
			T2	second;

			pair(): first(), second() { }
			pair(const T1 & x, const T2 & y) {
				this->first = x;
				this->second = y;
			}

			template<class U1, class U2> pair(const pair<U1, U2> & p) {
				this->first = p.first;
				this->second = p.second;
			}

			pair & operator=(const pair & other) {
				this->first = other.first;
				this->second = other.second;
				return (*this);
			}
	};

	template<class T1, class T2> inline bool operator==(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}

	template<class T1, class T2> inline bool operator!=(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return !(p1 == p2);
	}

	template<class T1, class T2> inline bool operator<(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return p1.first < p2.first || (!(p2.first < p1.first) && p1.second < p2.second);
	}

	template<class T1, class T2> inline bool operator<=(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return !(p2 < p1);
	}

	template<class T1, class T2> inline bool operator>(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return p2 < p1;
	}

	template<class T1, class T2> inline bool operator>=(const pair<T1, T2> & p1, const pair<T1, T2> & p2) {
		return !(p1 < p2);
	}
	
}

#endif