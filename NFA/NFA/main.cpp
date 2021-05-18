#include "Thompson.h"

//÷˜∫Ø ˝
int main()
{
    string Regular_Expression;
    cell NFA_Cell;
    //输入
    input(Regular_Expression);
    //添加“+”，便于转后缀表达式
    Regular_Expression = add_join_symbol(Regular_Expression);
    //中缀转后缀
    Regular_Expression = postfix(Regular_Expression);
    //表达式转NFA
    NFA_Cell = express_2_NFA(Regular_Expression);
    //显示
    Display(NFA_Cell);

    return 0;
}
