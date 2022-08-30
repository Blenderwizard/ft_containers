/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:45:42 by jrathelo          #+#    #+#             */
/*   Updated: 2022/08/30 16:40:05 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template<class Iter> class reverse_iterator {
		public:
			typedef Iter								iterator_type;
			typedef typename Iter::iterator_category	iterator_category;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::pointer				pointer;
			typedef	typename Iter::reference			reference;

			inline reverse_iterator(): current() { }
			
			inline explicit reverse_iterator(iterator_type x): current(x) { }

			template<class U> inline reverse_iterator(const reverse_iterator<U> & other) : current(other.base()) { }

			template<class U> inline reverse_iterator & operator=(const reverse_iterator<U> & other) {
				this->current = other.base();
				return (*this);
			}

			inline operator reverse_iterator<const Iter>() const {
				return (this->current);
			}

			inline iterator_type base() const {
				return (this->current);
			}

			inline reference operator*() const {
				iterator_type tmp = this->current;
				return *--tmp;
			}

			inline pointer	operator->() const {
				return &(operator*());
			}

			inline reverse_iterator & operator++() {
				this->current--;
				return (*this);
			}

			inline reverse_iterator & operator--() {
				this->current++;
				return (*this);
			}

			inline reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				this->current--;
				return (tmp);
			}
			
			inline reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				this->current++;
				return (tmp);
			}

			inline reverse_iterator operator+(const difference_type & n) const {
				return(reverse_iterator(this->current - n));
			}

			inline reverse_iterator operator-(const difference_type & n) const {
				return(reverse_iterator(this->current + n));
			}

			inline reverse_iterator & operator+=(const difference_type & n) {
				this->current -= n;
				return (*this);
			}

			inline reverse_iterator & operator-=(const difference_type & n) {
				this->current += n;
				return (*this);
			}

			inline reference operator[](const difference_type & count) {
				return (*(this->current + count));
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

	template<class Iter> ft::reverse_iterator<Iter> inline operator+(typename ft::reverse_iterator<Iter>::difference_type n, const ft::reverse_iterator<Iter> & it) {
		return reverse_iterator<Iter>(it.base() - n);
	}

	template<class Iter> inline typename ft::reverse_iterator<Iter>::difference_type operator-(const ft::reverse_iterator<Iter> & lhs, const ft::reverse_iterator<Iter> & rhs) {
		return (rhs.base() - lhs.base());
	}

	template<typename T_RAI1, typename T_RAI2> inline typename ft::reverse_iterator<T_RAI1>::difference_type operator-(const ft::reverse_iterator<T_RAI1> rai1, const ft::reverse_iterator<T_RAI2> rai2) {
		return (rai1.base() - rai2.base());
	}
}

#endif