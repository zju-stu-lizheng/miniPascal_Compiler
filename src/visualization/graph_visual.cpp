#include "graph_visual.hpp"

void GraphViz::AddNode(std::string label, int line, int col)
{
    int id = id_cnt++;
    std::stringstream ostr("");
    ostr << "node_" << id << "[";
    ostr << "label=\"" << label << "\\n";
    ostr << "[" << line << ", " << col << "]";
    ostr << "\"];";
    std::string node_str = ostr.str();
    nodes.push_back(node_str);
    std::stringstream ostr1("");
    ostr1.clear();
    if (id != 0)
    {
        ostr1 << "node_" << stk.top() << "->"
              << "node_" << id << ";";
        std::string edge_str = ostr1.str();
        edges.push_back(edge_str);
    }
    stk.push(id);
}

void GraphViz::AddIdentifier(std::string content)
{
    int id = id_cnt++;
    std::stringstream ostr("");
    ostr << "node_" << id << "[";
    ostr << "label=\"<ID>" << content << "\"";
    ostr << "];";
    std::string node_str = ostr.str();
    nodes.push_back(node_str);
    std::stringstream ostr1("");
    ostr1.clear();
    if (id != 0)
    {
        ostr1 << "node_" << stk.top() << "->"
              << "node_" << id << ";";
        std::string edge_str = ostr1.str();
        edges.push_back(edge_str);
    }
}

void GraphViz::AddValue(std::string t, std::string content)
{
    int id = id_cnt++;
    std::stringstream ostr("");
    ostr << "node_" << id << "[";
    ostr << "label=\"<" << t << ">" << content << "\"";
    ostr << "];";
    std::string node_str = ostr.str();
    nodes.push_back(node_str);
    std::stringstream ostr1("");
    if (id != 0)
    {
        ostr1 << "node_" << stk.top() << "->"
              << "node_" << id << ";";
        std::string edge_str = ostr1.str();
        edges.push_back(edge_str);
    }
}

void GraphViz::Save(std::string path)
{
    std::ofstream f(path);
    f << "digraph g {" << std::endl;
    for (auto e : edges)
        f << "\t" << e << std::endl;
    for (auto n : nodes)
        f << "\t" << n << std::endl;
    f << "}";
    f.close();
}
