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
    arr_t.setf( [](const text& x, const text& y)->bool { return strcmp(x, y) > 0; } );
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

TEST_F(array_evaluation_p, insert_method)
{
    float values[] = { 10.5f, 10.6f, 10.4f, 10.8f, 10.7f };
    arr_f.insert(values[0], 0);
    arr_f.insert(values[1], 1);
    arr_f.insert(values[2], 0);
    arr_f.insert(values[3], arr_f.getl() + 1);
    arr_f.insert(values[4], 3);

    // array has fixed size
    EXPECT_EXIT(arr_f.insert(100.0f, 0), testing::ExitedWithCode(ERROR_CODE), "no more memory");

    EXPECT_EQ(arr_f[0], values[2]);
    EXPECT_EQ(arr_f[1], values[0]);
    EXPECT_EQ(arr_f[2], values[1]);
    EXPECT_EQ(arr_f[3], values[4]);
    EXPECT_EQ(arr_f[arr_f.getl()], values[3]);

    const char* values_text[] = { "fo", "foo", "fooo", "foooo", "F" };
    arr_t.insert(values_text[0], 0);
    arr_t.insert(values_text[1], 1);
    arr_t.insert(values_text[2], arr_t.getl());
    arr_t.insert(values_text[3], arr_t.getl() + 1);
    arr_t.insert(values_text[4], arr_t.getn() - 1);
    
    EXPECT_EXIT(arr_t.insert("FOO", 0), testing::ExitedWithCode(ERROR_CODE), "no more memory");

    EXPECT_STREQ(arr_t[0], values_text[0]);
    EXPECT_STREQ(arr_t[1], values_text[1]);
    EXPECT_STREQ(arr_t[2], "a");
    EXPECT_STREQ(arr_t[3], "abd");
    
    EXPECT_STREQ(arr_t[arr_t.getl() - 3], values_text[2]);
    EXPECT_STREQ(arr_t[arr_t.getl() - 1], values_text[3]);
    EXPECT_STREQ(arr_t[arr_t.getl()], values_text[4]);
}

TEST_F(array_evaluation_p, remove_method)
{
    arr_f.remove(0);
    EXPECT_EQ(arr_f.getl(), 8);
    EXPECT_EQ(arr_f[0], block_numbers[1]);

    arr_f.remove(2);
    EXPECT_EQ(arr_f[1], block_numbers[2]);
    EXPECT_EQ(arr_f[2], block_numbers[4]);
    EXPECT_NO_THROW(arr_f.remove(arr_f.getl() - 1));    
    
    arr_f.remove(1.01f, true);
    for (auto i : arr_f)
        EXPECT_NE(i, 1.01f);

    arr_t.remove(1);
    EXPECT_EQ(arr_t.getl(), 8);
    EXPECT_STREQ(arr_t[1], block_texts[2]);

    arr_t.remove(3);
    EXPECT_STREQ(arr_t[2], block_texts[3]);
    EXPECT_STREQ(arr_t[3], block_texts[5]);
    EXPECT_NO_THROW(arr_t.remove(arr_t.getl()));

    arr_t.remove("a", false); // there has to be another a
    bit how_many = 0;
    for (auto i : arr_t)
        how_many = strcmp(i, "a") == 0 ? how_many + 1 : how_many;
    EXPECT_STRNE(arr_t[0], "a");
    ASSERT_GE(how_many, 1);
}

TEST_F(array_evaluation_p, query_operations)
{
    // all the numbers bellow are indexes
    size_t index = ULLONG_MAX;
    EXPECT_EQ(index = arr_f.search(-1), 0);
    EXPECT_EQ(index = arr_f.minimum(), 5);
    EXPECT_EQ(index = arr_f.maximum(), 4);
    EXPECT_EQ(index = arr_f.predcessr(1), 8); 
    EXPECT_EQ(index = arr_f.successor(1), 1);

    EXPECT_EQ(index = arr_t.search("b"), ULLONG_MAX);
    EXPECT_EQ(index = arr_t.minimum(), 6);
    EXPECT_EQ(index = arr_t.maximum(), 1);
    EXPECT_EQ(index = arr_t.predcessr("abd"), 3);
    EXPECT_EQ(index = arr_t.successor("aaa"), ULLONG_MAX);
}


TEST(array_p, friend_functions)
{
    array<> first = { 1, 2, 3, 4, 5 };
    array<> secnd = { 5, 6, 7, 8, 9 };

    array<> temp;
    //temp = linking(first, secnd);
    EXPECT_EQ(temp.getn(), 200);
    EXPECT_EQ(temp.getl(), 9);
    //EXPECT_EQ(temp[4], temp[5]);

    //temp = crossng(first, secnd);
    EXPECT_EQ(temp.getn(), 200);
    EXPECT_EQ(temp.getl(), 0);

    //ejectin(first, secnd);
    EXPECT_EQ(first.getl(), 3);
}
/*
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
*/