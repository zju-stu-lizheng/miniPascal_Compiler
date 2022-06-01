#ifndef OPC_GRAPH_VISUAL_HPP
#define OPC_GRAPH_VISUAL_HPP

#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>

class GraphViz
{
private:
    int id_cnt = 0;
    std::stack<int> stk;
    std::vector<std::string> nodes;
    std::vector<std::string> edges;

public:
    GraphViz() = default;

    ~GraphViz() = default;

    //可视化一个节点
    void AddNode(std::string label, int line, int col);
    //可视化一个标识符
    void AddIdentifier(std::string content);
    //可视化一个值(整型/浮点数/布尔值/字符型)
    void AddValue(std::string t, std::string content);
    //将可视化结果输入到文件中
    void Save(std::string path);

    void Pop() { stk.pop(); }
};

#endif