#include "global_declare.h"

class TestCase {
    public:

    TestCase() {}

    int Func1(int n1) {
        int local_n2 = 10;
        n1 = n1 + local_n2;
        if (n1 > 100) {
            m_value1++;
            m_value2++;
        }
        return n1;
    }

    private:
        int m_value1;
        int m_value2;
        int m_value3;

    public:
    int Func2(int value) {
        int local_n = 100;
        value += Cal1(local_n);
        m_value3 += value;
        return value;
    }

    int Cal1(int n2) {
        return n2*2;
    }

    int Func3(int value) {
        m_value1 += value;
        if (m_value1 > 100) {
            // �˴νӿڵĵ����ǿɲ��,m_value1 ���߼��жϺ���ⲿ�ӿڵ��ú�һֱδ�䣬�ڽӿڵ��ý�����������ⲿУ��;
            PrintImportantInfo(m_value1); 
        }

        int condition1 = m_value1 + m_value2;
        if (condition1 < 0) {
            // �˴νӿڵĵ��ò��ɲ⣬condition1 �Ǿֲ���������ʱ���ڴ˴ε��ú󲻸ı䣬Ҳ�޷����ⲿ��ȡ;
            PrintImportantInfo(condition1); 
            return condition1;
        }

        m_value2 += condition1;
        if (m_value2 > 10) {
            // �˴νӿڵĵ��ò��ɲ⣬m_value2 �ǷǾֲ����������Ա��ⲿ��ȡ��
            // �������ڴ˴ε��ú�仯��, ����仯�Ĺ��̲�һ���ǿ���ģ�Fun3() ִ�������У��m_value2 ��ֵû������;
            PrintImportantInfo(m_value2);
        }
        m_value2 /= (m_value2 + m_value1 + 100); // �����仯;

        m_value3 -= m_value2;
        m_value3 *= 99 + m_value2*m_value1 + value * 1331;
        if (m_value3 < -1) { // ��Ҫ���߼��ж�
            m_value3 =  (m_value2 / m_value1 + value % 100) / 7;
            // �˴νӿڵ�����Ը���, ��Ϊ���㿼��
            // �ӿڵĵ��ò����ǿɲ�ģ�m_value3 �ڴ˴ε��ú�δ�ı䣬�����Ƕ���ɵõ�;
            // �ӿڵĵ���ʱ���ǲ��ɲ��, m_value3 ����Ϊ�߼��ж��������־����˸��ӵı仯;
            //  ������Func3()������,��Ϊ�ж�������m_value3 ��ֵ�ǲ��ɸ�ԭ�ġ�
            // ���Դ˴��ⲿ�ӿڵĵ��ô����������ǲ��ɲ�ġ�
            PrintImportantInfo(m_value3); 
        }
        return m_value3 - m_value2;
    }

    // ����ȫ��Ӱ�����Ľӿ�;
    void PrintImportantInfo(int value) {
        printf("%d", value);
    }
};
