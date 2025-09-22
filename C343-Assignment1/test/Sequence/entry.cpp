
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    /** Test Naming Requirements:
   *  - Unique Name
   *  - Name describes what it is testing
   */

    TEST(Sequence_Entry, Test1_Int) {
        //Setup
        auto seq = std::make_unique<Sequence<int>>();
        //Test
        EXPECT_EQ(std::nullopt,seq->entry(0));
    }


    TEST(Sequence_Entry, Test1_String) {
        //Setup
        auto seq = std::make_unique<Sequence<std::string>>();
        //Test
        EXPECT_EQ(std::nullopt,seq->entry(0));
    }
    TEST(Sequence_Entry, Test1_NonEmptyBoolWith1Elem) {
        //Setup
        auto seq = std::make_unique<Sequence<bool>>();
        bool value1 = false;
        seq-> add(value1, 0);
        //Test
        EXPECT_EQ(false,seq->entry(0));
    }

    TEST(Sequence_Entry, Test1_NonEmptySequenceWith2Elems) {
        //Setup
        auto seq = std::make_unique<Sequence<bool>>();
        bool value1 = false;
        bool value2 = true;
        seq-> add(value1, 0);
        seq -> add(value2, 1);
        //Test
        EXPECT_EQ(true,seq->entry(1));
    }

}