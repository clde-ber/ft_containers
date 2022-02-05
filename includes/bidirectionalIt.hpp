#ifndef BIDIRECTIONALITER_H
#define BIDIRECTIONALITER_H

#include <iostream>

namespace ft
{
    template< typename T >
    class biIter
    {
        private:
            T _it;
        public:
            typedef typename iterator_traits<T>::value_type			value_type;
            typedef typename iterator_traits<T>::difference_type	difference_type;
            typedef typename iterator_traits<T>::pointer			pointer;
            typedef typename iterator_traits<T>::reference			reference;
            typedef typename iterator_traits<T>::iterator_category	iterator_category;
            typedef T iterator_type;
            typedef const value_type *			const_iterator_type;

            biIter() : _it(T()) {}
            biIter(iterator_type x) : _it(x) {}
            template< class U >
            biIter(U & other) : _it(&(*other)) {}
            template< class U >
            biIter& operator=(U & other) {_it = &(*other); return *this;}
            virtual ~biIter() {}
            biIter& operator++()
            {
                T current = this->_it;
                if (current->right != NULL){
                    current = current->right;
                    while (current->left != NULL)
                        current = current->left;
                    this->_it = current;
                }
                else{
                    T temp = current;
                    current = current->parent;
                    while (current->left != temp){
                        temp = current;
                        current = current->parent;
                    }
                    this->_it = current;
                }
                return *this;
            }
            biIter operator++(int)
            {
                std::cout << "VALUE ->" << _it->val << std::endl;
                T tmp = 0;
                if (_it->left)
                {
                    std::cout << "la3" << std::endl;
                    while (_it->left)
                        _it = _it->left;
                    tmp = _it;
                    return tmp;
                }
                if (_it->right && _it->right->right)
                {
                    std::cout << "la1" << std::endl;
                    _it = _it->right;
                    tmp = _it;
                    return tmp;
                }
                if (_it->parent)
                {
                    std::cout << "la2" << std::endl;
                    while (_it->parent)
                        _it = _it->parent;
                    tmp = _it;
                }
                    std::cout << "it val" << _it->val << std::endl;
                    if (!_it->right->right->right && _it->right->right)
                        _it = _it->right->right;
                    std::cout << "tmp->right val" << tmp->right->val << std::endl;
                    return tmp;
                std::cout << "it val" << _it->right->val << std::endl;
                std::cout << "la4" << std::endl;
                return _it;
            }
            biIter& operator--()
            {
                T current = this->_it;
                if (current->left != NULL){
                    current = current->left;
                    while (current->right != NULL)
                        current = current->right;
                    this->_it = current;
                }
                else{
                    current = current->parent;
                    this->_it = current;
                }
                return *this;
            }
            biIter operator--(int)
            {
                T temp = this->_it;
                T current = this->_it;
                if (current->left != NULL){
                    current = current->left;
                    while (current->right != NULL)
                        current = current->right;
                    this->_it = current;
                }
                else{
                    current = current->parent;
                    this->_it = current;
                }
                return temp;
            }
            pointer operator->() const {return &operator*();}
            reference operator*() const {return *_it;}
            iterator_type base() const {return _it;}

            operator biIter<const_iterator_type>()
            {
                return (biIter<const_iterator_type>(const_cast<const iterator_type>(_it)));
            }
    };
    template< typename T >
    class biReviter
    {
        private:
            T _it;
        public:
            typedef	typename iterator_traits<T>::difference_type		difference_type;
            typedef	typename iterator_traits<T>::value_type			value_type;
            typedef	typename iterator_traits<T>::pointer				pointer;
            typedef	typename iterator_traits<T>::reference			reference;
            typedef	typename iterator_traits<T>::iterator_category	iterator_category;
            typedef T iterator_type;
            typedef const value_type *			const_iterator_type;
            biReviter() : _it(T()) {}
            biReviter(iterator_type x) : _it(x) {}
            template< class U >
            biReviter(U & other) : _it(other.base()) {}
            template< class U >
            biReviter& operator=(U & other) {_it = other.base(); return *this;}
            virtual ~biReviter() {}
            biReviter& operator--()
            {
                if (_it->right)
                    _it = _it->right;
                else if (_it->parent)
                    _it = _it->parent;
                else if (_it->left)
                    _it = _it->left;
                else
                    _it = _it.getLast();
                return *this;
            }
            biReviter operator--(int)
            {
                T ret = _it;
                --_it;
                return ret;
            }
            biReviter& operator++()
            {
                if (_it->left)
                    _it = _it->left;
                else if (_it->parent)
                    _it = _it->parent;
                else if (_it->right)
                    _it = _it->right;
                else
                    _it = _it.getLast();
                return *this;
            }
            biReviter operator++(int)
            {
               T ret = _it;
                ++_it;
                return ret;
            }
            pointer operator->() const {return &operator*();}
            reference operator*() const {T tmp(_it); return *--tmp;}
            iterator_type base() const {return _it;}

            operator biReviter<biIter<const_iterator_type> >()
            {
                return (biReviter<biIter<const_iterator_type> >(biIter<const_iterator_type>(_it)));
            }
    };

    template< class Iter>
    biIter<Iter> operator+( typename biIter<Iter>::difference_type n, const biIter<Iter>& it )
    {
        return biIter<Iter>(it.base() + n);
    }
    template< class Iterator, class U >
    typename biIter<Iterator>::difference_type operator-( const biIter<Iterator>& lhs, const biIter<U>& rhs )
    {
        return lhs.base() - rhs.base();
    }

    template< class Iter >
    biReviter<Iter> operator+( typename biReviter<Iter>::difference_type n, const biReviter<Iter>& it )
    {
        return biReviter<Iter>(it.base() - n);
    }
    template< class Iterator, class U >
    typename biReviter<Iterator>::difference_type operator-( const biReviter<Iterator>& lhs, const biReviter<U>& rhs )
    {
        return rhs.base() - lhs.base();
    }

    template<typename Iterator1, typename Iterator2>
	bool			operator==(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(biIter<Iterator1> const &lhs, biIter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}

    template<typename Iterator1, typename Iterator2>
	bool			operator==(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(biReviter<Iterator1> const &lhs, biReviter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
}

#endif