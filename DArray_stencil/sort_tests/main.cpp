#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.h"
#include "darray.h"
#include "sort.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

void printInts(const DArray<int> &ints )
{
    for( size_t i = 0; i < ints.size(); i++ )
    {
        std::cout << ints[i] << ", ";
    }
    std::cout << std::endl;
}

void random_fill_ints(DArray<int> &ints)
{
    int size = ints.size();
    for(int i = 0; i < size; i++ )
    {
        ints[ i ] = rand() % size;
    }
}

template<class T>
bool isSorted( DArray<T> &data )
{
    if( data.size() <= 1 )
        return true;

    for(size_t i = 1; i < data.size(); i++ )
    {
        if( data[ i - 1 ] > data[ i ] )
        {
            std::cout << "Error - Integers not sorted:" << std::endl;
            printInts( data );
            return false;
        }
    }
    return true;
}

TEST_CASE( "Small sorts work", "[ctor]" )
{
    srand((unsigned)time(0));

    SECTION("No values")
    {
        DArray<int> ints(0);
        sort(ints);
        REQUIRE( isSorted( ints ) );
    }
    SECTION("One value")
    {
        DArray<int> ints(1);
        random_fill_ints(ints);
        sort(ints);
        REQUIRE( isSorted( ints ) );
    }
    SECTION("Two values")
    {
        DArray<int> ints(2);
        random_fill_ints(ints);
        sort(ints);
        REQUIRE( isSorted( ints ) );
    }
    SECTION("Three values")
    {
        DArray<int> ints(3);
        random_fill_ints(ints);
        sort(ints);
        REQUIRE( isSorted( ints ) );
    }
    SECTION("Four values")
    {
        DArray<int> ints(4);
        random_fill_ints(ints);
        sort(ints);
        REQUIRE( isSorted( ints ) );
    }
    SECTION("Five values")
    {
        DArray<int> ints(5);
        random_fill_ints(ints);
        sort(ints);
        REQUIRE( isSorted( ints ) );
    }
}


TEST_CASE( "Moderate number of values " )
{
    SECTION("8 values")
    {
        DArray<int> ints(8);
        random_fill_ints( ints );
        sort(ints);
        REQUIRE( isSorted(ints ) );
    }
    SECTION("17 values")
    {
        DArray<int> ints(17);
        random_fill_ints( ints );
        sort(ints);
        REQUIRE( isSorted(ints ) );
    }
    SECTION("88 values")
    {
        DArray<int> ints(88);
        random_fill_ints( ints );
        sort(ints);
        REQUIRE( isSorted(ints ) );
    }
    SECTION("117 values")
    {
        DArray<int> ints(117);
        random_fill_ints( ints );
        sort(ints);
        REQUIRE( isSorted(ints ) );
    }
}

TEST_CASE( "Many values " )
{
    SECTION("1001 values")
    {
        DArray<int> ints(1001);
        random_fill_ints( ints );
        sort(ints);
        REQUIRE( isSorted(ints ) );
    }
    SECTION("10101 values")
    {
        DArray<int> ints(10101);
        random_fill_ints( ints );
        sort(ints);
        REQUIRE( isSorted(ints ) );
    }
}
