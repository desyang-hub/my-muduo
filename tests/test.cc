#include <gtest/gtest.h>


int add(int a, int b) {
    return a + b;
}


TEST(MathTest, AdditionWorks) {
    EXPECT_EQ(5, add(3, 2));
}


int main(int argc, char **argv) {
    // 3. 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);
    
    // 4. 运行所有测试并返回结果
    // 如果有测试失败，RUN_ALL_TESTS() 会返回非零值
    return RUN_ALL_TESTS();
}