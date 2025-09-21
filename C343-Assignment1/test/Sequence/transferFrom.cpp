

#include "gtest/gtest.h"
#include "../../src/Sequence/Sequence.cpp"

namespace {
    TEST(Sequence_TranferFrom, Test1_Int) {
        auto seq = std::make_unique<Sequence<int>>();
        auto seq2 = std::make_unique<Sequence<int>>();
        int value = 55;
        int value2 = 45;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->transferFrom(*seq);
        //Test
        EXPECT_EQ("55, 45", seq2->outputSequence());

    }

    TEST(Sequence_TranferFrom, Test2_Int) {
        auto seq = std::make_unique<Sequence<int>>();
        auto seq2 = std::make_unique<Sequence<int>>();
        int value = 5;
        int value2 = 4;
        int value3 = 6;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq->add(value3, 2);
        seq2->transferFrom(*seq);
        //Test
        EXPECT_EQ("5, 4, 6", seq2->outputSequence());

    }

    TEST(Sequence_TranferFrom, Test3_Int) {
        auto seq = std::make_unique<Sequence<int>>();
        auto seq2 = std::make_unique<Sequence<int>>();
        int value = 55;
        int value2 = 45;
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->transferFrom(*seq);
        //Test
        EXPECT_EQ(0, seq->length());

    }

    TEST(Sequence_TranferFrom, Test1_String) {
        auto seq = std::make_unique<Sequence<std::string>>();
        auto seq2 = std::make_unique<Sequence<std::string>>();
        std::string value = "fish";
        std::string value2 = "cat";
        std::string value3 = "flower";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->add(value3, 0);
        seq2->transferFrom(*seq);
        //Test
        EXPECT_EQ("fish, cat", seq2->outputSequence());

    }

    TEST(Sequence_TranferFrom, Test2_String) {
        auto seq = std::make_unique<Sequence<std::string>>();
        auto seq2 = std::make_unique<Sequence<std::string>>();
        std::string value = "sun";
        std::string value2 = "dog";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->transferFrom(*seq);
        //Test
        EXPECT_EQ("sun, dog", seq2->outputSequence());

    }

    TEST(Sequence_TranferFrom, Test3_String) {
        auto seq = std::make_unique<Sequence<std::string>>();
        auto seq2 = std::make_unique<Sequence<std::string>>();
        std::string value = "purple";
        std::string value2 = "red";
        std::string value3 = "flower";
        //Process
        seq->add(value, 0);
        seq->add(value2, 1);
        seq2->add(value3, 0);
        seq2->transferFrom(*seq);
        //Test
        EXPECT_EQ("purple, red", seq2->outputSequence());

    }

}