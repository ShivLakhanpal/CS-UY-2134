//Shiv Lakhanpal
//Data Structures Fall 2016
//Net ID: svl238
//Homework 4 - Programming Part
#include <vector>
#include <iostream>

using namespace std;

template <typename Object>
class Vector
{
public:
    explicit Vector( int initSize = 0 )
    : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
    { objects = new Object[ theCapacity ]; }

    Vector( const Vector & rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }

    Vector & operator= ( const Vector & rhs )
    {
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    ~Vector( )
    { delete [ ] objects; }

    Vector( Vector && rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    Vector & operator= ( Vector && rhs )
    {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );

        return *this;
    }

    bool empty( ) const
    { return size( ) == 0; }
    int size( ) const
    { return theSize; }
    int capacity( ) const
    { return theCapacity; }

    Object & operator[]( int index )
    {
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
        return objects[ index ];
    }

    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }

    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;

        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );

        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }

    // Stacky stuff
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
    // Stacky stuff
    void push_back( Object && x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }


    // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin( )
    { return &objects[ 0 ]; }
    const_iterator begin( ) const
    { return &objects[ 0 ]; }
    iterator end( )
    { return &objects[ size( ) ]; }
    const_iterator end( ) const
    { return &objects[ size( ) ]; }

    //Programming Part 1
    iterator erase( iterator vectorItr) {
        for (iterator itr = vectorItr; itr != end(); itr++) {
            *itr = *(itr+1);
        }
        resize(size()-1);
        return vectorItr;
    }




    static const int SPARE_CAPACITY = 2;

private:
    int theSize;
    int theCapacity;
    Object * objects;
};
//Programming Part 2
int sumDigits(int n) {
    if (n == 0) {
        return 0;
    }
    else {
        return n % 10 + sumDigits(n / 10);
    }
}

//Programming Part 3
template <class Itr>
int sumRecursive(Itr first, Itr last) {
    if (first + 1 == last) {
        return *first;
    }
    int mid = ((last-first)/2);
    Itr itrMid = first + mid;
    return sumRecursive(first, itrMid) + sumRecursive(itrMid, last);
}

int sumVector(const vector<int> & a) {
    return sumRecursive(a.begin(), a.end());
}

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int>::iterator itr = v.begin() + 1;
    v.erase(itr);
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    cout << "sum of the digits of " << 519 << " is " << sumDigits(519) << endl;
//Part 3

/*vector<int> vec{1, 2, 3};     //Uncomment to print out
cout << sumVector(vec) << endl;
*/
}
