/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:45:42 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/09 11:48:26 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator_traits.hpp>

namespace ft{
	template<class Iter> class reverse_iterator {
		public:
			typedef typename Iter									iterator_type;
			typedef ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef ft::iterator_traits<Iter>::value_type			value_type;
			typedef ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef ft::iterator_traits<Iter>::pointer				pointer;
			typedef	ft::iterator_traits<Iter>::reference			reference;

			reverse_iterator(): current() { };
			
			explicit reverse_iterator(iterator_type x): current(x) { };

			template<class U> reverse_iterator(const reverse_iterator<U> & other) : current(other.current);

			template<clase U> reverse_iterator & operator=(const reverse_iterator<U> & other) {
				current = other.current;
				return (*this);
			};

			iterator_type base() const {
				return (current);
			};

			reference operator*() const {
				Iter	tmp = current;
				return *--tmp;
			}

			pointer	operator->() const;
			
			auto operator[](difference_type n) const {
				return *(*this + n);
			}

			reverse_iterator & operator++() {
				current--;
				return (*this);
			}

			reverse_iterator & operator--() {
				current++;
				return (*this);
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				current--;
				return (tmp);
			}
			
			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				current++;
				return (tmp);
			}

			reverse_iterator operator+(difference_type n) const {
				return(reverse_iterator(current - n));
			}

			reverse_iterator operator-(difference_type n) const {
				return(reverse_iterator(current + n));
			}

			reverse_iterator & operator+=(difference_type n) {
				current -= n;
				return (*this);
			}

			reverse_iterator & operator-=(difference_type n) {
				current += n;
				return (*this);
			}
		protected:
			iterator_type	current;
	};

	template<class Iterator1, class Iterator2> bool operator==(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() == rhs.base());
	}

	template<class Iterator1, class Iterator2> bool operator!=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() != rhs.base());
	}

	template<class Iterator1, class Iterator2> bool operator<(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() < rhs.base());
	}

	template<class Iterator1, class Iterator2> bool operator<=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() <= rhs.base());
	}

	template<class Iterator1, class Iterator2> bool operator>(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() > rhs.base());
	}

	template<class Iterator1, class Iterator2> bool operator>=(const ft::reverse_iterator<Iterator1> & lhs, const ft::reverse_iterator<Iterator2> & rhs) {
		return (lhs.base() >= rhs.base());
	}

	template<class Iter> reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> & it) {
		return (reverse_iterator(it.base() - n));
	}

	template<class Iterator> typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs) {
		return (rhs.base() - lhs.base());
	}
}

#endif