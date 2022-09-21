/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <student.42nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:39:50 by jrathelo          #+#    #+#             */
/*   Updated: 2022/09/21 17:53:04 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef STD
# define NAMESPACE ft
# include <vector.hpp>
# include <map.hpp>
# include <stack.hpp>
#else
# define NAMESPACE std
# include <vector>
# include <map>
# include <stack>
#endif

template <class Key, class T> void print_map(NAMESPACE::map<Key, T> & map) {
	for (typename NAMESPACE::map<Key, T>::iterator it = map.begin(); it != map.end(); it++)
		std::cout << it->first << " => " << it->second << std::endl;
}

template <class T> void print_vector(NAMESPACE::vector<T> & vector) {
	for (typename NAMESPACE::vector<T>::iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << std::endl;
}

