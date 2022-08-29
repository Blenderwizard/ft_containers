/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:45:42 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/09 14:52:55 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator_traits.hpp>

namespace ft {
	template<class Iter> class reverse_iterator {
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef	typename ft::iterator_traits<Iter>::reference			reference;

			inline reverse_iterator(): current() { };
			
			inline explicit reverse_iterator(iterator_type x): current(x) { };

			template<class U> inline reverse_iterator(const reverse_iterator<U> & other) : current(other.current) { };

			template<class U> inline reverse_iterator & operator=(const reverse_iterator<U> & other) {
				current = other.current;
				return (*this);
			};

			inline iterator_type base() const {
				return (current);
			};

			inline reference operator*() const {
				Iter	tmp = current;
				return *--tmp;
			}

			inline pointer	operator->() const {
				return &(operator*());
			}

			inline reverse_iterator & operator++() {
				current--;
				return (*this);
			}

			inline reverse_iterator & operator--() {
				current++;
				return (*this);
			}

			inline reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				current--;
				return (tmp);
			}
			
			inline reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				current++;
				return (tmp);
			}

			inline reverse_iterator operator+(difference_type n) const {
				return(reverse_iterator(current - n));
			}

			inline reverse_iterator operator-(difference_type n) const {
				return(reverse_iterator(current + n));
			}

			inline reverse_iterator & operator+=(difference_type n) {
				current -= n;
				return (*this);
			}

			inline reverse_iterator & operator-=(difference_type n) {
				current += n;
				return (*this);
			}
		protected:
			iterator_type	current;
	};

	template<class Iterator1, class Iterator2> inline bool operator==(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template<class Iterator1, class Iterator2> inline bool operator!=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() != rhs.base());
	}

	template<class Iterator1, class Iterator2> inline bool operator<(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() < rhs.base());
	}

	template<class Iterator1, class Iterator2> inline bool operator<=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() <= rhs.base());
	}

	template<class Iterator1, class Iterator2> inline bool operator>(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() > rhs.base());
	}

	template<class Iterator1, class Iterator2> inline bool operator>=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() >= rhs.base());
	}

	template<class Iter> reverse_iterator<Iter> inline operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> & it) {
		return reverse_iterator<Iter>(it.base() - n);
	}

	template<class Iterator> inline typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) {
		return (rhs.base() - lhs.base());
	}
}

#endif