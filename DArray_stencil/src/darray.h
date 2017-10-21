#ifndef DARRAY_H
#define DARRAY_H


#include <initializer_list>

template<typename T>
class DArray
{
public:
    DArray();
    DArray( size_t count );
    DArray( std::initializer_list<T> initList );
    DArray( const DArray& other);
    DArray& operator=(const DArray &other);

    T& at( size_t pos );
    const T& at( size_t pos ) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void clear();
    void pop_back();
    void push_back( const T& ayy);
    void resize( size_t count );
    bool empty() const;
    size_t size() const;
    void reserve( size_t new_cap );
    size_t capacity() const;

    T& operator[]( size_t pos );
    const T& operator[]( size_t pos ) const;

private:
    unsigned int sizeOfD;
    unsigned int cap;
    T* buffer;

};


template<class T>
DArray<T>::DArray()
{
    sizeOfD = 0;
    cap = 0;
    buffer = new T [cap];
}

template<class T>
DArray<T>::DArray( size_t count ){
    sizeOfD = count;
    cap = count + 5;
    buffer = new T [cap];
}

template<class T>
DArray<T>::DArray( std::initializer_list<T> initList ) {
    sizeOfD = initList.size();
    cap = initList.size()+5;
    buffer = new T [cap];
    unsigned int a = 0;
    for (auto i = initList.begin(); i != initList.end(); i++) {
        buffer[a] = *i;
        a++;
    }
    //We can do std::copy(initList.begin(), initList.end(), buffer); like how there's std::move

}

template<class T>
DArray<T>::DArray( const DArray& other){
    sizeOfD = other.size();
    cap = other.capacity();
    buffer = new T [cap];
    for (unsigned int i = 0; i < sizeOfD; i++) {
        buffer[i] = other.buffer[i];
    }
}

template<class T>
DArray<T> &DArray<T>::operator = (const DArray &other)
{
    if (buffer == other.buffer){
    } else {
        delete[] buffer;
        sizeOfD = other.size();
        cap = other.capacity();
        buffer = new T [cap];
        for (int i = 0; i < cap; i++){
            buffer[i] = other.buffer[i];
        }
        return *this;
    }

}

template<class T>
T& DArray<T> ::at( size_t pos ){
    if (pos <= cap) {
        return *buffer[pos];
    }
}

template<class T>
const T& DArray<T>::at( size_t pos ) const{
    if (pos <= cap) {
        return (const)*buffer[pos];
    }
}

template<class T>
T& DArray<T>::front(){
    return *buffer[0];
}

template<class T>
const T& DArray<T>::front() const{
    return *buffer[0];
}

template<class T>
T& DArray<T>::back(){
    if (sizeOfD > 0){
        return *buffer[sizeOfD - 1];
    } else {
        return NULL;
    }
}

template<class T>
const T& DArray<T>::back() const{
    if (sizeOfD > 0){
        return (const)*buffer[sizeOfD - 1];
    } else {
        return NULL;
    }
}

template<class T>
void DArray<T>::clear(){
    while (sizeOfD != 0){
        pop_back();
    }
}

template<class T>
void DArray<T>::pop_back(){
    if (sizeOfD > 0) {
        buffer[sizeOfD - 1].~T();
        sizeOfD--;
    }

}

template<class T>
void DArray<T>::push_back( const T& ayy){
    if (sizeOfD == cap){
        reserve(cap+5);
        buffer[sizeOfD] = ayy;
        sizeOfD++;
    } else {
        buffer[sizeOfD] = ayy;
        sizeOfD++;
    }
}

template<class T>
void DArray<T>::resize(size_t count) {
    if (count > sizeOfD){
        if (count > cap){
            cap = count + 5;
        }
        T * newBuffer = new T [cap];

        for (int i = 0; i < count; i++){
            newBuffer[i] = buffer[i];
        }

        sizeOfD = count;
        buffer = newBuffer;

    } else {
        T * newBuffer = new T [cap];

        sizeOfD = count;
        for (int i = 0; i < count; i++){
            newBuffer[i] = buffer[i];
        }

        buffer = newBuffer;
    }
}

template<class T>
bool DArray<T>::empty() const {
    if (sizeOfD == 0){
        return 1;
    }
    return 0;
}

template <class T>
size_t DArray<T>::size() const{
    return sizeOfD;
}

template<class T>
void DArray<T>::reserve( size_t new_cap ) {
    if (new_cap > cap) {
        cap = new_cap;
    }
    T * newBuffer = new T [cap];
    for (int i = 0; i < sizeOfD; i++){
        newBuffer[i] = buffer[i];
    }
    buffer = newBuffer;
}

template <class T>
size_t DArray<T>::capacity() const{
    return cap;
}

template <class T>
T& DArray<T>::operator[]( size_t pos ){
    return buffer[pos];
}

template <class T>
const T& DArray<T>::operator[]( size_t pos ) const {
    return buffer[pos];
}


#endif // DARRAY_H
