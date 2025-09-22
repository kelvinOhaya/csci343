
#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {

    TEST(Sequence_Operator, Test1_Int) {
        auto seq = new Sequence<int>();
        auto seq2 = new Sequence<int>();
        int value = 33;
        int value2 = 23;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->add(value, 0);
        *seq = *seq2;
        //Test
        EXPECT_EQ("33", seq->outputSequence());
    }

    TEST(Sequence_Operator, Test2_Int) {
        auto seq = new Sequence<int>();
        auto seq2 = new Sequence<int>();
        int value = 12;
        int value2 = 10;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->add(value, 0);
        seq2->add(value2, 1);
        seq2->add(value, 2);
        *seq2 = *seq;
        //Test
        EXPECT_EQ("12, 10", seq2->outputSequence());
    }

    TEST(Sequence_Operator, Test3_Int) {
        auto seq = new Sequence<int>();
        auto seq2 = new Sequence<int>();
        int value = 33;
        int value2 = 23;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->add(value, 0);
        seq2->add(value2, 1);
        seq2->add(value, 2);
        *seq = *seq2;
        //Test bv
        EXPECT_EQ("33, 23, 33", seq->outputSequence());
    }

    TEST(Sequence_Operator, Test1_String) {
        auto seq = new Sequence<std::string>();
        auto seq2 = new Sequence<std::string>();
        std::string value = "fish";
        std::string value2 = "cat";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        *seq = *seq2;
        //Test
        EXPECT_EQ(0, seq->length());
    }


    TEST(Sequence_Operator, Test2_String) {
        auto seq = new Sequence<std::string>();
        auto seq2 = new Sequence<std::string>();
        std::string value = "green";
        std::string value2 = "purple";
        //Process
        seq2->add(value, 0);
        seq2->add(value2, 1);
        *seq2 = *seq;
        //Test
        EXPECT_EQ(0, seq2->length());
    }


    TEST(Sequence_Operator, Test3_String) {
        auto seq = new Sequence<std::string>();
        auto seq2 = new Sequence<std::string>();
        std::string value = "fish";
        std::string value2 = "cat";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->add(value, 0);
        seq2->add(value2, 1);
        seq2->add(value, 2);
        *seq = *seq2;
        //Test
        EXPECT_EQ("fish, cat, fish", seq->outputSequence());
    }





}