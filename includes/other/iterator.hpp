/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:33:09 by jrathelo          #+#    #+#             */
/*   Updated: 2022/05/09 15:20:19 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iterator_traits.hpp>

namespace ft {
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> class iterator {
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
    };

	class random_access_iterator_tag {};

	template <typename T> class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef T*																				pointer;
			typedef T&																				reference;
            
			random_access_iterator() : current(0x0) {}

			random_access_iterator(pointer x): current(x) {}

			random_access_iterator(const random_access_iterator& rai): current(rai.current) {}
		
			random_access_iterator & operator=(const random_access_iterator & rai) {
				if (this != &rai)
					this->current = rai.current;
				return (*this);
			}
			
			virtual ~random_access_iterator() {}

			pointer base() const {
				return (this->current);
			}

			reference operator*() const {
				return *(this->current);
			}

			pointer operator->() {
				return &(this->operator*());
			}

			random_access_iterator & operator++() {
				this->current++;
				return (*this);
			}

			random_access_iterator operator++(int) {
				random_access_iterator ret(*this);
				operator++();
				return (ret);
			}

			random_access_iterator & operator--() {
				this->current--;
				return (*this);
			}

			random_access_iterator operator--(int) {
				random_access_iterator ret(*this);
				operator--();
				return (ret);
			}

			random_access_iterator operator+(difference_type count) const {
				return (this->current + count);
			}

			random_access_iterator operator-(difference_type count) const {
				return (this->current - count);
			}

			random_access_iterator operator+=(difference_type count) {
				this->current += count;
				return (*this);
			}

			reference operator[](difference_type count) {
				return (*(operator + (count)));
			}

			// operator random_access_iterator<const T> const {
			// 	return (random_access_iterator<const T>(this->current));
			// }
		
		private:
			pointer current;
	};

	// Out of class random acess iterator defs
	
	template <typename T> typename ft::random_access_iterator<T>::difference_type operator==(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() == rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator==(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() == rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator!=(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() != rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator!=(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() != rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator<(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() < rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator<(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() < rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator>(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() > rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator>(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() > rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator<=(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() <= rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator<=(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() <= rai2.base());
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator>=(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() >= rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator>=(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() >= rai2.base());
	}

	template<typename T> ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type count, typename ft::random_access_iterator<T> & rai) {
		return (&(*rai) + count);
	}

	template <typename T> typename ft::random_access_iterator<T>::difference_type operator-(const ft::random_access_iterator<T> rai1, const ft::random_access_iterator<T> rai2) {
		return (rai1.base() - rai2.base());
	}

	template<typename T_RAI1, typename T_RAI2> typename ft::random_access_iterator<T_RAI1>::difference_type operator-(const ft::random_access_iterator<T_RAI1> rai1, const ft::random_access_iterator<T_RAI2> rai2) {
		return (rai1.base() - rai2.base());
	}


    template <bool is_valid, typename T> struct valid_tag {
		typedef T type;
		const static bool value = is_valid;
	};

	template <typename T> struct check_iterator_tagged_ft : public valid_tag<false, T> { };
	template <> struct check_iterator_tagged_ft<ft::random_access_iterator_tag> : public valid_tag<true, ft::random_access_iterator_tag> { };
}

#endif