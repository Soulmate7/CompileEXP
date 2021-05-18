#include<iostream>
#include<string.h>
#include<vector>
#include<iomanip>
#include <stack>
#include <map>
#include<stdlib.h>

using namespace std;



//*********************词法分析器******************************//

char SEPARATER[2] = { '(', ')'};    //分隔符

char OPERATOR[5] = { '+', '-', '*', '/', '#' };     //运算符


/**判断是否为分隔符**/

bool IsSeparater(char ch){

    for (int i = 0; i<2; i++){

        if (SEPARATER[i] == ch){

            return true;

        }

    }

    return false;

}



/**判断是否为运算符**/

bool IsOperator(char ch){

    for (int i = 0; i<5; i++){

        if (OPERATOR[i] == ch){

            return true;

        }

    }

    return false;

}

/**判断是否为数字**/

bool IsDigit(char ch){

    if (ch >= '0' && ch <= '9') return true;

    return false;

}



//词法分析主体功能

vector<string> analyse(string expression){

    vector<string> vec;

    char ch = ' ';

    for (int i = 0; i < expression.length(); i++)

    {

        string arr = "";

        ch = expression[i];

        if (IsDigit(ch)){           //判断是否为数字

            while(IsDigit(ch)){

                arr += ch;

                i++;

                ch = expression[i];

            }

            i--;

            vec.push_back(arr);        //把新元素入栈

        }

        else if (IsOperator(ch))

        {

            arr += ch;

            vec.push_back(arr);

        }

        else if (IsSeparater(ch))

        {

            arr += ch;

            vec.push_back(arr);

        }

        else

        {

            cout << "无法识别的字符:" << ch << endl;

            vec.clear();

            return vec;

        }

    }

    return vec;

}

//*******************中间代码生成器******************************//

string InversePolish(string s_text)

{

    string s_words = ""; //创建目标逆波兰表达式

    stack<char> nstk;//创建一个符号栈



    map<char, int> op;//利用map来实现运算符对应其优先级

    op['('] = 0;

    op[')'] = 0;

    op['+'] = 1;

    op['-'] = 1;

    op['*'] = 2;

    op['/'] = 2;

    string::iterator it = s_text.begin();

    //迭代器，遍历并选择序列中的对象，他提供了一种访问一个容器对象的中各个元素，而又不必保留该对象内部细节的方法。

    while (it != s_text.end())

    {

        if (op.count(*it))//判断该元素是否为运算符

        {

            if (*it == ')')//若为’）‘，把栈中的运算符依次加入后缀表达式，直到出现'（'，’（‘出栈，退出该次循环

            {

                while (nstk.top() != '(')

                {

                    s_words += nstk.top();        //取出栈顶元素

                    s_words += " ";

                    nstk.pop();

                }

                nstk.pop();        //弹出栈顶元素

            }

            else if (nstk.empty() || *it == '(' || op[*it]>op[nstk.top()])

                //若为‘（’，入栈 ; 要入栈的运算符优先级大于等于栈顶的运算符的优先级，直接入栈

            {

                nstk.push(*it);    //在栈顶增加元素

            }

            else if (op[*it] <= op[nstk.top()])

                // 入栈的运算符优先级小于等于栈顶的运算符的优先级，栈顶运算符出栈，再次比较，直到出现优先级低的运算符，或者栈为空，退出

            {

                while (op[*it] <= op[nstk.top()] && (!nstk.empty()))

                {

                    s_words += nstk.top();

                    s_words += " ";

                    nstk.pop();

                    if (nstk.empty()) break;

                }

                nstk.push(*it);

            }

        }

        else

        {

            s_words += *it;

            it++;

            if (it != s_text.end() && op.count(*it))

                //count，返回被查找元素个数，返回1/0，有/无；find 返回被查找元素的位置，没有返回map.end()

                s_words += " ";

            it--;

        }

        it++;



        if (it == s_text.end())//当中缀表达式输出完成，所有元素出栈

        {

            while (!nstk.empty())

            {

                s_words += " ";

                s_words += nstk.top();

                nstk.pop();

            }

            break;

        }

    }

    cout <<"后缀表达式："<< s_words << endl;

    return s_words;

}


//*********************后缀表达式计算******************************//
int Operation(int m,char operation,int n)
{
    switch (operation)
    {
        case '+':return m+n; break;
        case '-':return m-n; break;
        case '*':return m*n; break;
        case '/':return m/n; break;
 }
    return 0;
}

int suffix(char *str)
{
 stack<int> s;
 int temp=0;
 int length=strlen(str);
 int result;
 int i=0;

 while (i<length)
 {
  string tstr = "";
  
  for(i;i<length;i++)
  {
   tstr+=str[i];

   if((i == length - 1) || ((str[i]==' ') && (str[i+1]!=' ')))
   {
    char* p=(char*)tstr.data();//创建一个指向字符数组内容的指针
    int num=atoi(tstr.c_str());//将字符串中的数字输出为int类型

    if (IsOperator(*p))//若当前字符为运算符，则将一个数字0压入栈中
     num=0;
    s.push(num);//若当前字符为操作数，则直接压入栈中

    if (IsOperator(*p))
    {
     s.pop();//将数字0弹出
     int a=s.top();
     s.pop();
     int b=s.top();
     s.pop();
     result=Operation(b,*p,a);//进行栈顶两个数的计算
     s.push(result);
    }
    temp=i+1;
    break;
   }
  }
  i=temp;
 }
 return s.top();
}


    

//*********************语法分析器******************************//

//Action表

int action[16][8] = {

{ 0, 0, 0, 0, 4, 0, 5, 0 },//0

{ 6, 7, 0, 0, 0, 0, 0, 100 },//1

{ -3, -3, 8, 9, 0, -3, 0, -3 },//2

{ -6, -6, -6, -6,  0, -6, 0, -6 },//3

{ 0, 0, 0, 0, 4, 0, 5, 0 },//4

{ -8, -8, -8, -8, 0, -8, 0, -8 },//5

{ 0, 0, 0, 0, 4, 0, 5, 0 },//6

{ 0, 0, 0, 0, 4, 0, 5, 0 },//7

{ 0, 0, 0, 0, 4, 0, 5, 0 },//8

{ 0, 0, 0, 0, 4, 0, 5, 0 },//9

{ 6, 7, 0, 0, 0, 15, 0, 0 },//10

{ -1, -1, 8, 9, 0, -1, 0, -1 },//11

{ -2, -2, 8, 9, 0, -2, 0, -2 },//12

{ -4, -4, -4, -4, 0, -4, 0, -4 },//13

{ -5, -5, -5, -5, 0, -5, 0, -5 },//14

{ -7, -7, -7, -7, 0, -7, 0, -7 }//15

};//17

//Goto表

int Goto[16][3] = {

{ 1, 2, 3 },//0

{ 0, 0, 0 },//1

{ 0, 0, 0 },//2

{ 0, 0, 0 },//3

{ 10, 2, 3 },//4

{ 0, 0, 0 },//5

{ 0, 11, 3 },//6

{ 0, 12, 3 },//7

{ 0, 0, 13 },//8

{ 0, 0,14 },//9

{ 0, 0, 0 },//10

{ 0, 0, 0 },//11

{ 0, 0, 0 },//12

{ 0, 0, 0 },//13

{ 0, 0, 0 },//14

{ 0, 0, 0 } };//17

//终结符集合

string endls[8] = { "+", "-", "*", "/", "(", ")","id","#" };

//非终结符集合

string unends[3] = { "E", "T", "F" };

//产生式集合

string grammer[9] = { "E", "E+T", "E-T", "T", "T*F", "T/F", "F", "(E)", "id" };

/*

   E=> T+F | T-F |T

   T=> F*T | F/T |F

   F=> (E) | id

*/



//状态栈

class statestack

{

private:

    int *base;//栈底指针

    int *top;//栈顶指针

    int size;//栈内元素个数

    int stacksize;//栈的大小

public:

    statestack()

    {

        size = 0;

        stacksize = 20;

        base = new int[stacksize];

        top = base;

    }

    int getTop()//获取栈顶的元素。

    {

        if (base == top)

        {

            return -1;

        }

        else

        {

            return *(top - 1);

        }

    }

    bool statePush(int elem)//元素入栈

    {

        ++size;

        (*top) = elem;

        ++top;

        return true;

    }

    void statePop(int time)//元素出栈

    {

        for (int i = 0; i<time; i++)

        {

            --top;

            --size;

        }

    }

    void display_states()//输出栈内的所有元素

    {

        string str = " ";

        int *pre;

        for (pre = base; pre<top; pre++)

        {

            if (*pre>9)   // 栈中保存的10转换成1、0

            {

                char ch1 = (*pre / 10) + 48;

                char ch2 = (*pre % 10) + 48;

                str += ch1;

                str += ch2;

            }

            else

            {

                char ch = *pre + 48;

                str += ch;

            }

        }

        cout << setw(15) << setiosflags(ios_base::left) << str;

    }

};



//符号栈

class symbolstack

{

private:

    string *base;

    string *top;

    int size;

    int stacksize;

public:

    symbolstack()

    {

        size = 0;

        stacksize = 20;

        base = new string[stacksize];

        top = base;

    }

    string getTop()//获取栈顶的元素。

    {

        if (base == top)

        {

            return "";

        }

        else

        {

            return *(top - 1);

        }

    }

    //元素入栈

    bool symbolPush(string elem)

    {

        ++size;

        *top = elem;

        ++top;

        return true;

    }

    //元素出栈

    void symbolPop(int time)

    {

        for (int i = 0; i<time; i++)

        {

            --top;

            --size;

        }

    }

    //输出栈内的所有元素

    void display_symbol()

    {

        string str = "";

        string *pre;

        for (pre = base; pre<top; pre++)

        {

            str += *pre;

        }

        cout << setw(15) << setiosflags(ios_base::left) << str;

    }

};





class analyse_SLR

{

private:

    int step;

    string inputstr;//布尔表达式

    statestack state;//状态栈

    symbolstack symbol;//符号栈

    statestack data;//数据栈


public:

    //构造函数

    analyse_SLR()

    {

        step = 0;

        inputstr = "";

        state = statestack();

        symbol = symbolstack();

    }

    //初始化两个栈

    void initstack()

    {

        state.statePush(0);

        symbol.symbolPush("#");

    }

    //这是一个输出提示函数

    void printInfo(string str)

    {

        cout << str << endl;

    }

    //这是两个输出提示函数的增强版

    void printInfoEX(string str1, string str2, string str3, string str4, string str5)

    {

        cout << setw(6) << setiosflags(ios_base::left) << str1;    // setiosflags(ios_base::left) 左对齐值，用填充字符填充右边

        cout << setw(15) << setiosflags(ios_base::left) << str2;

        cout << setw(15) << setiosflags(ios_base::left) << str3;

        cout << setw(30) << setiosflags(ios_base::left) << str4;

        cout << setw(10) << setiosflags(ios_base::left) << str5 << endl;

    }

    void printfInfoEX(int str1, statestack state, symbolstack symbol, string str4, string str5)

    {

        cout << setw(6) << setiosflags(ios_base::left) << str1;

        state.display_states();

        symbol.display_symbol();

        cout << setw(30) << setiosflags(ios_base::left) << str4;

        cout << setw(10) << setiosflags(ios_base::left) << str5 << endl;

    }

    //将终结符和非终结符转换为action和Goto表中对应的列号

    int symbol2num(string str)

    {

        if (str == "+")

            return 0;

        if (str == "-")

            return 1;

        if (str == "*")

            return 2;

        if (str == "/")

            return 3;

        if (str == "(")

            return 4;

        if (str == ")")

            return 5;

        if (str == "#")

            return 7;

        if (str == "E")

            return 0;

        if (str == "T")

            return 1;

        if (str == "F")

            return 2;

        return 6;

    }

    //判断字符是终结符还是非终结符

    bool judgeSymbol(string str)

    {

        for (int i = 0; i<3; i++)

        {

            if (unends[i] == str)

                return false;

        }

        return true;

    }

    //根据产生式选择非终结符

    int chooseunends(int num)

    {

        if (num == 1 || num == 2 || num == 3)

            return 0;//选择“E”

        if (num == 4 || num == 5 || num == 6)

            return 1;//选择“T”

        return 2;//选择“F”

    }

    //计算字符串中元素的个数

    int calculatenum(string str)

    {

        int num = 0;

        if (str == "id") num = 1;

        else num = str.size();

        return num;

    }

    //将vector容器中的字符串连起来

    string linkVectorstr(vector<string> &vecs, vector<string>::iterator iter)

    {

        string str = "";

        vector<string>::iterator it;

        it = iter;

        for (it; it<vecs.end(); it++)

            str += *it;

        return str;

    }

    void run()

    {

        initstack();//初始化两个栈

        cout<<"\n>>";

        getline(cin, inputstr);
        
        if(inputstr=="quit")
            
            exit(0);

        vector<string> vec = analyse(inputstr);//分开布尔表达式

        if (vec.empty()) {}

        else{

            vector<string>::iterator iter = vec.begin();

            //printInfo("\n---------------------------语法分析----------------------------------");

            //printInfoEX("步骤 ", " 状态栈", "符号栈", "输入串", "操作");

            bool flag;

            for (iter; iter != vec.end(); ++iter)//依次遍历字符

            {

                flag = 1;

                string str1 = linkVectorstr(vec, iter);//将vector容器中的字符串连起来

                actionGoto(*iter, str1, vec,flag);

                if (!flag)

                    return;

            }

            iter--;

            if (*iter != "#")

            {

                flag = 0;

                cout << "请以'#'结束！"<< endl;

            }

            if (flag)

            {

                //cout << "语法分析成功！" << endl;

                //printInfo("\n---------------------------中间代码----------------------------------");

                vector<string>::iterator iter2 = vec.begin();

                string s_mid = linkVectorstr(vec, iter2);   //连接成一个字符串

                s_mid = s_mid.substr(0, s_mid.length() - 1);  //删除最后的#，用substr实现截取功能

                string HZ = InversePolish(s_mid);//转后缀表达式

                //printInfo("\n---------------------------计算结果----------------------------------");

                char* stringofchar = (char*)HZ.data();//加const  或者用char * p=(char*)str.data();的形式

                int Result = suffix(stringofchar);

                cout << "后缀表达式计算结果：" << Result << endl;

            }


        }

    }

    //SLR分析函数

    int actionGoto(string str, string str1,vector<string> vec,bool &flag)

    {

        int x = state.getTop();//当前栈顶状态

        int y = symbol2num(str);//当前将要输入的字符

        if (action[x][y] == 0)

        {

            cout << "语法分析出错！" << endl;

            flag=0;

        }

        if (action[x][y]>0 && judgeSymbol(str) && (str != "#"))//移进

        {

            //printfInfoEX(step, state, symbol, str1, "移入" + str);

            state.statePush(action[x][y]);

            symbol.symbolPush(str);

            ++step;

        }

        if (action[x][y]<0 && judgeSymbol(str))//规约

        {

            int z = -action[x][y];//用-action[x][y]对应的产生式规约

            string lenstr = grammer[z];//生成需要规约的产生式

            int n = calculatenum(lenstr);//计算产生式的长度，进行规约

            int c = chooseunends(z);

            string ch = unends[c];//生成规约后的非终结符

            //printfInfoEX(step, state, symbol, str1, "规约" + unends[c] + "->" + grammer[z]);



            switch (z)

            {

            case 1:

            {

                int a = data.getTop();

                data.statePop(1);

                int b = data.getTop();

                data.statePop(1);

                b += a;

                data.statePush(b);

                break;

            }

            case 2:

            {

                int a = data.getTop();

                data.statePop(1);

                int b = data.getTop();

                data.statePop(1);

                b -= a;

                data.statePush(b);

                break;

            }

            case 4:

            {

                int a = data.getTop();

                data.statePop(1);

                int b = data.getTop();

                data.statePop(1);

                b *= a;

                data.statePush(b);

                break;

            }

            case 5:

            {

                int a = data.getTop();

                if (a == 0)

                {

                    flag = 0;

                    cout << "\n除数为0！" << endl;

                    return flag;

                }

                data.statePop(1);

                int b = data.getTop();

                data.statePop(1);

                b /= a;

                data.statePush(b);

                break;

            }

            case 8:

            {

                string b = symbol.getTop();

                int c = atoi(b.c_str());//将字符转换为所代表的数字

                data.statePush(c);

                break;

            }



            default:

                break;

            }



            state.statePop(n);

            symbol.symbolPop(n);

            int m = state.getTop();//获取规约后的栈顶状态

            if (Goto[m][c]>0)

            {

                int g = Goto[m][c];

                state.statePush(g);

                symbol.symbolPush(ch);

            }

            ++step;

            actionGoto(str, str1,vec,flag);

        }

        if ((action[x][y] == 100) &&(str1=="#"))

        {

            flag = 1;

            //printfInfoEX(step, state, symbol, str1, "分析完成");

            cout << "\n语法分析计算结果："<<data.getTop() << endl;

        }

        else if ((action[x][y] == 100))

        {

            cout << "语法分析失败！" << endl;

            flag = 0;

        }

        return flag;

    }

};





int main()

{

    while (1){

        analyse_SLR slr = analyse_SLR();

        slr.run();

    }
    return 0;

}



 
