#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.h"
#include "darray.h"

#include <string>

TEST_CASE( "Empty Constructors", "[ctor]" )
{
    SECTION("Basic Constructors")
    {
        DArray<int> dInt;
        DArray<float> dFloat;
        DArray<std::string> dString;
    }
}

TEST_CASE( "Size Constructors", "[ctor_size]" )
{
    SECTION( "Small Constructors" )
    {
        DArray<int> dInt1(1);
        DArray<int> dInt4(4);
        DArray<int> dInt15(15);
        DArray<int> dInt16(16);
        DArray<int> dInt17(17);
    }

    SECTION( "Big Constructors" )
    {
        DArray<int> dInt5000(5000);
        DArray<int> dInt123456(123456);
    }
}

TEST_CASE( "Initializer List Constructors", "[ctor_ilist]" )
{
    DArray<float> dFloat1 = {42.0f};
    DArray<float> dFloat3 = {1.0f, 4.0f, 5.0f};

    SECTION( "Data accessibility" )
    {
        REQUIRE( dFloat1[0] == 42.0f );
        REQUIRE( dFloat3[0] == 1.0f );
        REQUIRE( dFloat3[1] == 4.0f );
        REQUIRE( dFloat3[2] == 5.0f );
    }

    SECTION( "Meta-data correctness" )
    {
        REQUIRE( dFloat1.size() == 1 );
        REQUIRE( dFloat1.capacity() >= 1 );

        REQUIRE( dFloat3.size() == 3 );
        REQUIRE( dFloat3.capacity() >= 3 );
    }
}

TEST_CASE( "Copy constructor", "[copy_ops]" )
{
    DArray<int> dInt1 = {1, 2, 3, 4};
    DArray<int> dInt2(dInt1);

    SECTION( "Copy constructor all values")
    {
        REQUIRE( dInt1.size() == dInt2.size() );
        REQUIRE( dInt1.capacity() == dInt2.capacity() );

        for(size_t i = 0;i < dInt1.size(); i++ )
        {
            REQUIRE( dInt1[i] == dInt2[i] );
        }
    }
    SECTION( "Copy constructor makes deep copy")
    {
        REQUIRE( &dInt1[0] != &dInt2[0] );
    }

}

TEST_CASE( "Copy assignment operator", "[copy_ops]" )
{
    DArray<int> dInt1 = {1, 2, 3, 4};
    DArray<int> dInt2 = {395, 3490, 123098};
    dInt2 = dInt1;

    SECTION( "Copy assignment operator copies all values")
    {
        REQUIRE( dInt1.size() == dInt2.size() );
        REQUIRE( dInt1.capacity() == dInt2.capacity() );

        for(size_t i = 0;i < dInt1.size(); i++ )
        {
            REQUIRE( dInt1[i] == dInt2[i] );
        }
    }
    SECTION( "Copy assignment operator makes deep copy")
    {
        REQUIRE( &dInt1[0] != &dInt2[0] );
    }
    SECTION( "Copy assignment operator doesn't do anything if copying to itself" )
    {
        static int value = 1;
        struct ValRef
        {
            ValRef() : ref(value){}
            ValRef(int& x) :
                ref(x)
            {}
            ValRef(const ValRef& other) :
                ref(other.ref)
            {}
            ValRef& operator=(const ValRef& other)
            {
                ref = other.ref;
                return *this;
            }

            ~ValRef()
            {
                ref--;
            }

            int& ref;
        };
        ValRef canary(value);
        DArray<ValRef> dVR;
        dVR.push_back( canary );
        auto startPtr = &dVR[0];
        DArray<ValRef>& other = dVR;
        dVR = other;
        auto endPtr = &dVR[0];
        REQUIRE( startPtr == endPtr );
        REQUIRE( value == 1 );
    }
}

TEST_CASE( "Resize", "[resize]" )
{
    DArray<int> v( 15 );

    REQUIRE( v.size() == 15 );
    REQUIRE( v.capacity() >= 15 );

    SECTION( "Resizing bigger changes size and capacity" )
    {
        v.resize( 100 );

        REQUIRE( v.size() == 100 );
        REQUIRE( v.capacity() >= 100 );
    }
    SECTION( "Resizing smaller changes size but not capacity" )
    {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 15 );
    }
}

TEST_CASE( "Reserve", "[reserve]" )
{
    DArray<int> v( 15 );

    REQUIRE( v.size() == 15 );
    REQUIRE( v.capacity() >= 15 );

    SECTION( "Reserving bigger changes capacity but not size" )
    {
        v.reserve( 100 );

        REQUIRE( v.size() == 15 );
        REQUIRE( v.capacity() >= 100 );
    }
    SECTION( "Reserving smaller does not change size or capacity" )
    {
        v.reserve( 0 );

        REQUIRE( v.size() == 15 );
        REQUIRE( v.capacity() >= 15 );
    }
}

TEST_CASE( "Pop_back", "[pop_back]")
{
    SECTION( "Popping back reduces size by 1 but capacity remains unchanged" )
    {
        DArray<int> v(32);

        REQUIRE( v.size() == 32 );
        REQUIRE( v.capacity() >= 32 );

        v.pop_back();

        REQUIRE( v.size() == 31 );
        REQUIRE( v.capacity() >= 32 );
    }

    SECTION( "Popping back when size is 0 is idempotent" )
    {
        DArray<int> v(1);

        v.pop_back();

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 1 );

        v.pop_back();

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 1);
    }

    SECTION( "Popping back calls destructor of object")
    {
        static int value = 1;
        struct ValRef
        {
            ValRef() : ref(value){}
            ValRef(int& x) :
                ref(x)
            {}
            ValRef(const ValRef& other) :
                ref(other.ref)
            {}
            ValRef& operator=(const ValRef& other)
            {
                ref = other.ref;
                return *this;
            }

            ~ValRef()
            {
                ref--;
            }

            int& ref;
        };
        ValRef canary(value);
        DArray<ValRef> v;
        v.push_back(canary);
        v.pop_back();
        REQUIRE( value == 0 );
    }
}

TEST_CASE( "Push_back", "[push_back]" )
{
    SECTION( "Pushing back works on empty array" )
    {
        DArray<float> dF;
        dF.push_back(12.3f);
        REQUIRE( dF[0] == 12.3f );
        REQUIRE( dF.size() == 1);
        REQUIRE( dF.capacity() >= 1);
    }
    SECTION( "Pushing back works on an array with size but no values")
    {
        DArray<double> dD(2);
        dD.push_back(10.0);
        REQUIRE( dD[2] == 10.0 );
        REQUIRE( dD.size() == 3 );
        REQUIRE( dD.capacity() >= 2 );
        dD.push_back(20.0);
        REQUIRE( dD[3] == 20.0 );
        REQUIRE( dD.size() == 4 );
        REQUIRE( dD.capacity() >= 2 );
        dD.push_back(30.0);
        REQUIRE( dD[4] == 30.0 );
        REQUIRE( dD.size() == 5 );
        REQUIRE( dD.capacity() >= 3 );
        dD.push_back(40.0);
        REQUIRE( dD[5] == 40.0 );
        REQUIRE( dD.size() == 6 );
        REQUIRE( dD.capacity() >= 4 );
        dD.push_back(50.0);
        REQUIRE( dD[6] == 50.0 );
        REQUIRE( dD.size() == 7 );
        REQUIRE( dD.capacity() >= 5 );
    }
    SECTION( "Pushing back does not clobber values")
    {
        DArray<int> dI;
        for( int i = 0; i < 10; i++)
        {
            dI.push_back(i);
            for(int j = 0; j <= i; j++)
            {
                REQUIRE( dI[j] == j );
            }
        }
    }
}
