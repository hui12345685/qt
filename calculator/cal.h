#ifndef CAL_H
#define CAL_H

#include <string>
#include <list>

class Cal {
public:
    // 计算表达式的值
    int CalExpression(std::string& exp);
    // 检查表达式是否合法
    bool CheckValid(std::string& exp);
private:
    // 将表达式转换为逆波兰式
    std::list<std::string> Convert(std::string& exp);

    int CalExpressionWithConvert(std::list<std::string>& convert);
};

#endif // CAL_H
