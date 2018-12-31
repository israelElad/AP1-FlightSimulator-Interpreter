//
// Created by root on 31/12/18.
//

#ifndef AP3_TEXTANALYZER_H
#define AP3_TEXTANALYZER_H

#include <vector>
#include <string>

using namespace std;

class TextAnalyzer {
public:
    static vector<string> lexer(string &toSeparate);
    static void parse(vector<string> &separated, bool &shouldStop);
    static unsigned long findMinIndexToSeparate(const string &str);
    static unsigned long findOperator(string &toSeparate, short &opLen);
    static void addSpaces(string &toSeparate);
};


#endif //AP3_TEXTANALYZER_H
