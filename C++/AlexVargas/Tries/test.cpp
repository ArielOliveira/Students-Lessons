#include <iostream>
#include "CTrie.h"
#include "TTrie.h"

using std::cout;
using std::endl;

int main(void) {
    CTrie* root = new CTrie();

    //*root += "cat";
    //*root += "cap";
    //*root += "cater";
    //*root += "set";
    //*root += "send";
    *root += "hello";
    *root += "help";

    cout << *root << endl;



    TTrie<int> genericRoot;

    std::vector<std::string> v = {"cat", "cap", "cater", "set", "send"};    
    
    std::vector<int> iseq1({8, 6, 7, 5, 3, 0, 9});
    std::vector<int> iseq2({8, 6, 7, 101});
    std::vector<int> iseq3({8, 6, 7, 101, 3, 4, 5});
    std::vector<int> iseq4({90125});
    std::vector<int> iseq5({8, 6, 7, 101, 2});
    std::vector<int> iseq6({8, 6, 7});

    genericRoot += iseq1;
    genericRoot += iseq2;
    genericRoot += iseq3;
    genericRoot += iseq4;
    genericRoot += iseq5;
    

    TTrie<int> genericRoot2;

    genericRoot2 += iseq1;
    genericRoot2 += iseq2;
    genericRoot2 += iseq3;
    genericRoot2 += iseq4;
    genericRoot2 += iseq5;
    //genericRoot += iseq6;
    
    cout << genericRoot << endl;   
    cout << genericRoot2 << endl;
    cout << endl;
    cout << (genericRoot == genericRoot2) << endl;
    cout << (genericRoot2 == genericRoot) << endl << endl;

    TTrie<char> st1;
    std::vector<char> hello({'h', 'e', 'l', 'l', 'o'});
    std::vector<char> hell({'h', 'e', 'l', 'l'});
    std::vector<char> help({'h', 'e', 'l', 'p'});
    std::vector<char> johns({'j', 'o', 'h', 'n', 's'});
    std::vector<char> johnson({'j', 'o', 'h', 'n', 's', 'o', 'n'});
    std::vector<char> joanna({'j', 'o', 'a', 'n', 'n', 'a'});

    //(st1 += hello) += help;

    st1 += hello;
    cout << "Added hello" << endl; 
    st1 += help;
    cout << "Added help" << endl;
    //st1 += johns;
    //st1 += johnson;
    //st1 += joanna;

    //TTrie<char> st2(st1);

    /*st2 += sseq1;
    st2 += sseq2;
    st2 += sseq3;
    st2 += sseq4;
    st2 += sseq5;
    st2 += sseq6;*/

    cout << (st1 ^ hell) << endl;
    cout << " printed ^ from st1" << endl;
    cout << (*root ^ "hell") << endl;
    cout << " printed ^ from root" << endl;
    //cout << (st1 ^ joanna) << endl; 

    cout << st1 << endl;

    //st2 = st1;

    //cout << st2 << endl;

    TTrie<std::string> st5;
    std::vector<std::string> sseq1({"spam", "spam", "spam", "baked beans", "spam"});
    std::vector<std::string> sseq2({"spam", "spam", "spam"});
    std::vector<std::string> sseq3({"avocado", "egg"});
    std::vector<std::string> sseq4({"avocado", "marmalade"});
    std::vector<std::string> sseq5({"potato"});
    std::vector<std::string> sseq6({"avocado", "toast"});

    st5 += sseq1;
    st5 += sseq2;
    st5 += sseq3;
    st5 += sseq4;
    st5 += sseq5;
    st5 += sseq6;

    cout << st5 << endl;


   

    delete root;
    //delete genericRoot;

    return 0;
}