#include "global_declare.h"

#include "moka_base.h"

using namespace testing;

class User {
public:
    User() {};
    ~User() {};
public:
    // ��¼
    virtual bool Login(const std::string& username, const std::string& password) = 0;
    // ֧��
    virtual bool Pay(int money) = 0;
    // �Ƿ��¼
    virtual bool Online() = 0;
};

class Biz {
public:
    void SetUser(User* user) {
        _user = user;
    }

    std::string pay(const std::string& username, const std::string& password, int money) {
        std::string ret;
        if (!_user) {
            ret = "pointer is null.";
            return ret;
        }
        
        if (!_user->Online()) {
            ret = "logout status.";
            // ��δ��¼��Ҫ���¼
            if (!_user->Login(username, password)) {
                // ��¼ʧ��
                ret += "login error.";
                return ret;
            } else {
                // ��¼�ɹ�
                ret += "login success.";
            }
        } else {
            // �ѵ�¼
            ret = "login.status";
        }

        if (!_user->Pay(money)) {
            ret += "pay error.";
        } else {
            ret += "pay success.";
        }

        return ret;
    }

private:
    User* _user;
};

class TestUser : public User {
public:
    MOCK_METHOD2(Login, bool(const std::string&, const std::string&));
    MOCK_METHOD1(Pay, bool(int));
    MOCK_METHOD0(Online, bool());
};

void test_moka1() {
    TestUser test_user;
    EXPECT_CALL(test_user, Online()).WillOnce(testing::Return(true));
    EXPECT_CALL(test_user, Login(_,_)).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(test_user, Pay(_)).WillRepeatedly(testing::Return(true));

    Biz biz;
    biz.SetUser(&test_user);
    std::string admin_ret = biz.pay("user", "", 1);
    admin_ret = biz.pay("user", "", 1);
}

void test_moka2() {
    TestUser test_user;
    EXPECT_CALL(test_user, Online()).WillOnce(testing::Return(false));
    EXPECT_CALL(test_user, Login("admin",testing::_)).WillRepeatedly(testing::Return(false));

    Biz biz;
    biz.SetUser(&test_user);
    std::string admin_ret = biz.pay("admin", "", 1);
}

void test_moka3() {
    TestUser test_user;
    EXPECT_CALL(test_user, Online()).WillOnce(testing::Return(false));
    EXPECT_CALL(test_user, Login(StrNe("admin"),_)).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(test_user, Pay(_)).Times(5).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillRepeatedly(testing::Return(false));

    Biz biz;
    biz.SetUser(&test_user);
    std::string user_ret = biz.pay("user", "", 1);
    user_ret = biz.pay("user", "", 1);
    user_ret = biz.pay("user", "", 1);
}

void TestMokaBase() {
    // test_moka1();
    // test_moka2();
    // test_moka3();
}