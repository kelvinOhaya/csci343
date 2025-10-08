
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    /** Test Naming Requirements:
   *  - Unique Name
   *  - Name describes what it is testing
   */

    //tests if integer types work with add
    TEST(Sequence_Add, Test1_Int) {
        //Setup
        auto seq = std::make_unique<Sequence<int>>();
        int value = 37;
        //Process
        seq->add(value, 0);
        //Test
        EXPECT_EQ(37, seq->entry(0));
    }

    //tests if string types work with add
    TEST(Sequence_Add, Test1_String) {
        //Setup
        auto seq = std::make_unique<Sequence<std::string>>();
        std::string value = "cat";
        std::string value2 = "dog";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        //Test
        EXPECT_EQ("cat", seq->entry(0));
    }

    //Test if boolean types work with add
    TEST(Sequence_Add, Test1_Bool) {
        //Setup
        auto seq = std::make_unique<Sequence<bool>>();
        bool value = false;
        bool value2 = true;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        //Test
        EXPECT_EQ(0, seq->entry(0));
    }

}