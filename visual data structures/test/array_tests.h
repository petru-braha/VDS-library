#pragma once
#include "convoluted.h"
#include "array.h"
#include "trial_test_values.h"
#include <cstring>

class array_evaluation_p : public testing::Test
{
protected:
    array<float> arr_f;
    array<const char*> arr_t;

    ~array_evaluation_p() = default;
    array_evaluation_p();
};


//------------------------------------------------
// constructors:

array_evaluation_p::array_evaluation_p() :
    arr_f(list_numbers, maximum_size),
    arr_t(list_texts, maximum_size)
{
    arr_f = array<float>(block_numbers, classic_size, maximum_size);
    arr_t = array<const char*>(block_texts, classic_size, maximum_size);
};

//------------------------------------------------
// tests:

TEST_F(array_evaluation_p, clear_method)
{
    arr_f.clear();
    EXPECT_EQ(arr_f.empty(), true);

    arr_t.clear();
    EXPECT_EQ(arr_t.empty(), true);
}

TEST_F(array_evaluation_p, sort)
{
    for(bit algorithm = bubble_sort;; algorithm++)
    {
        arr_f.setf([](const float& x, const float& y)->bool { return x < y; });
        EXPECT_NO_THROW(arr_f.sort(algorithm));
        
        FOR(arr_f.getl())
            EXPECT_GE(arr_f[i], arr_f[i]) << "for the " << algorithm << '\n';

        arr_t.setf([](const text& x, const text& y)->bool { return strcmp(x, y) < 0; });
        EXPECT_NO_THROW(arr_t.sort(algorithm));
        
        FOR(arr_t.getl())
            EXPECT_TRUE(strcmp(arr_t[i], arr_t[i + 1]) >= 0)
            << arr_t[i] << "compared with " << arr_t[i + 1] << '\n'
            << "for the " << algorithm << '\n';
        
        // last one
        if (algorithm == insertion_sort)
            break; 
    }
}

TEST_F(array_evaluation_p, insert_remove)
{
    arr_f.insert();
    arr_f.insert(2, 0);
    arr_f.insert(444, 2);
    arr_f.remove();
    
    arr_f.insert(646, 2);
    arr_f.insert(646, 3);
    arr_f.remove();

    arr_f.insert(646, 2);
    arr_f.remove(646);

    EXPECT_EQ(arr_f[0], 2);
    EXPECT_EQ(arr_f[1], 1);
    EXPECT_EQ(arr_f[2], 646);
    EXPECT_EQ(arr_f[3], 646);
    EXPECT_EQ(arr_f[4], 444);


    
    
}


TEST(array_p, defined_errors)
{

}

TEST(array_p, friend_functions)
{

}

//------------------------------------------------
// next class:

class array_evaluation_c : public testing::Test
{
protected:
    array<convoluted> arr_obj;
    void SetUp();
    void TearDown();
};

//------------------------------------------------
// constructors:

void array_evaluation_c::TearDown()
{

}

void array_evaluation_c::SetUp()
{

}

//------------------------------------------------
// tests:

TEST_F(array_evaluation_c, sort)
{

}

TEST_F(array_evaluation_c, insert_delete)
{

}
