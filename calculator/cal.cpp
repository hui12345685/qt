
#include "cal.h"
#include <stack>
#include <unordered_map>

bool Cal::CheckValid(std::string& exp) {
    return true;
}

int Cal::CalExpression(std::string& exp) {
    // 先将exp转换为逆波兰式 ，然后再执行逆波兰式求值
    std::list<std::string> convert = Convert(exp);
    return CalExpressionWithConvert(convert);
}

/* 遇到操作数时，放到list
 * 遇到右括号")“时，依此弹出栈并压入list，直到遇到左括号”)"为止，此时丢掉一对括号；
 * 遇到运算符时：
       1）如果栈为空或栈顶为左括号"("，则压入到栈；
       2）不满足1），则和栈顶运算符比较优先级，高于，则压入栈；
       3）不满足1）和2），弹出栈顶运算符并压入到list，继续循环）。
 */
std::list<std::string> Cal::Convert(std::string& exp) {
    static std::unordered_map<char, int> pri =
        {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 3}};
    std::stack<char> stk;
    std::list<std::string> result;
    std::string num;
    for (auto ch : exp) {
        if (isdigit(ch)) {
            num += ch;
        } else {
            if (!num.empty()) {
                result.push_back(num);
                num.clear();
            }
            if (ch == ')') {
                while (!stk.empty()) {
                    if (stk.top() == '(') {
                        stk.pop(); //左括号也出来
                        break;
                    }
                    std::string op = std::string(1, stk.top());
                    result.push_back(op);
                    stk.pop();
                }
            } else {
                // 非数字就涉及到优先级了
                if (stk.empty() || stk.top() == '(') {
                    stk.push(ch);
                } else {
                    char op = stk.top();
                    // 把栈中优先级大于等于当前操作符的都出栈加到result上
                    while (!stk.empty() && pri[ch] <= pri[op]) {
                        if (stk.top() == '(') {
                            break;
                        }
                        op = stk.top();
                        std::string str_op = std::string(1, op);
                        result.push_back(str_op);
                        stk.pop();
                    }
                    // 再把当前操作符入栈
                    stk.push(ch);
                }
            }
        }
    }
    if (!num.empty()) {
        result.push_back(num);
    }
    while (!stk.empty()) {
        result.push_back(std::string(1, stk.top()));
        stk.pop();
    }
    return result;
}

int Cal::CalExpressionWithConvert(std::list<std::string>& convert) {
    std::stack<int> stk;
    // 默认一定格式合法的逆波兰式, 所以省去了一些不必要的判断
    for (auto str : convert) {
        if (str == "+" || str == "-" || str == "*" || str == "/") {
            int num2 = stk.top();
            stk.pop();
            int num1 = stk.top();
            stk.pop();
            int tmp;
            switch(str[0]) {
            case '+' :
                tmp = num1 + num2;
                break;
            case '-' :
                tmp = num1 - num2;
                break;
            case '*' :
                tmp = num1 * num2;
                break;
            case '/' :
                tmp = num1 / num2;
                break;
            default :
                break;
            }
            stk.push(tmp);
        } else {
            // 数字
            stk.push(atoi(str.c_str()));
        }
    }
    return stk.top();
}
