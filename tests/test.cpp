// Copyright 2021 GNDavydov

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

#include <unique_ptr.hpp>

using namespace my_unique_ptr;


TEST(Optional, Init) {
    unique_ptr<int> ptr_1;
    unique_ptr<int> ptr_2(new int(5));
    unique_ptr<int> ptr_3(nullptr);

    EXPECT_FALSE(ptr_1.operator bool());
    EXPECT_TRUE(ptr_2.operator bool());
    EXPECT_FALSE(ptr_3.operator bool());

    unique_ptr<int> ptr_4(std::move(ptr_2));
    EXPECT_FALSE(ptr_2.operator bool());
    EXPECT_TRUE(ptr_4.operator bool());
}

TEST(Optional, Equality) {
    unique_ptr<int> ptr_1;
    unique_ptr<int> ptr_2(new int(5));

    EXPECT_FALSE(ptr_1.operator bool());
    EXPECT_TRUE(ptr_2.operator bool());

    ptr_1 = std::move(ptr_2);
    EXPECT_FALSE(ptr_2.operator bool());
    EXPECT_TRUE(ptr_1.operator bool());
}

TEST(Optional, Access) {
    unique_ptr<std::string> ptr_1;
    unique_ptr<std::string> ptr_2(new std::string("Qwerty"));

    EXPECT_EQ(ptr_1.operator->(), nullptr);
    EXPECT_EQ(*ptr_2, "Qwerty");

    ptr_1 = std::move(ptr_2);
    EXPECT_EQ(ptr_2.operator->(), nullptr);
    EXPECT_EQ(*ptr_1, "Qwerty");

    *ptr_1 = "12345";
    EXPECT_EQ(*ptr_1, "12345");

    ptr_1->erase(2, 1);
    EXPECT_EQ(*ptr_1, "1245");
}

TEST(Optional, Reset) {
    int* a = new int(10);
    int* b = new int(100);

    unique_ptr<int> ptr_1;

    ptr_1.reset(a);
    EXPECT_EQ(*ptr_1, 10);

    ptr_1.reset(b);
    EXPECT_EQ(*ptr_1, 100);
}

TEST(Optional, Release) {
    unique_ptr<int> ptr_1(new int(30));
    unique_ptr<int> ptr_2(ptr_1.release());

    EXPECT_EQ(*ptr_2, 30);
}

TEST(Optional, Swap) {
    unique_ptr<int> ptr_1(new int(30));
    unique_ptr<int> ptr_2(new int(50));

    ptr_2.swap(ptr_1);

    EXPECT_EQ(*ptr_1, 50);
    EXPECT_EQ(*ptr_2, 30);
}

TEST(Optional, Get) {
    unique_ptr<int> ptr_1;
    unique_ptr<int> ptr_2(new int(50));

    EXPECT_EQ(ptr_1.get(), nullptr);
    EXPECT_EQ(*(ptr_2.get()), 50);

    *(ptr_2.get()) = 100;
    EXPECT_EQ(*(ptr_2.get()), 100);
}
