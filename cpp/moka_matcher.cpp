#include "moka_matcher.h"

TEST(TestMockPrivate, TestPrivate) {

    MockFoo foo;

    //GetTimeOut��private���ε�

    EXPECT_CALL(foo, GetTimeOut()).WillOnce(Return(1));

    cout << "test private GetTimeOut:" << foo.GetTimeOut() << endl; //1
}

// //�������ط���

TEST(TestMockOverload, TestOverload) {
    MockFoo foo;
    EXPECT_CALL(foo, Add(_))
        .Times(1)
        .WillOnce(Return(1));
    cout << "test TestOverload Add:" << foo.Add('c') << endl; //1
}

//����������ͬ�����Ͳ�ͬ�������

// virtual int Add(int x,int y) = 0;

// virtual int Add(int times, char x) = 0;

TEST(TestMockOverload, TestSameNumArg) {

    MockFoo foo;

    //��������int

    EXPECT_CALL(foo, Add(An<int>(), An<int>()))
        .Times(1)
        .WillOnce(Return(8));

    int c = foo.Add(3, 5);

    cout << "test TestOverload Add:" <<c<< endl; //8

     

    EXPECT_CALL(foo, Add(Matcher<int>(Lt(10)), TypedEq<char>('c')))
        .Times(1)
        .WillOnce(Return(7));
    c = foo.Add(2, 'c');
    cout << "test TestOverload Add:" << c << endl; //7
}

//����������ͬ�����Ͳ�ͬ�������

TEST(TestMockOverload, TestSameNumArg2) {

   MockFoo foo;

   EXPECT_CALL(foo, Add(Matcher<int>(Lt(5)), An<int>()))
        .Times(1)
        .WillOnce(Return(7));

    int c = foo.Add(2, 5);

    cout << "test TestOverload Add:" << c << endl; //7

    //��һ������С��5��,�ڶ���������'d'

    EXPECT_CALL(foo, Add(Matcher<int>(Lt(5)), Matcher<char>('d')))
        .Times(1)
        .WillOnce(Return(10));

    c = foo.Add(2, 'd'); //10

    cout << "test TestOverload Add:" << c << endl; //10
}