#include "Engine/Node.hpp"

namespace psy {



Node::~Node()
{
    // TODO Auto-generated destructor stub
}



void Node::reparent_to(Node* node)
{
    node->m_nodes_list.push_back(this);
    m_parent = node;
}



void Node::detach()
{
    if (m_parent)
    {
        m_parent->m_nodes_list.remove(this);
        m_parent = 0;
    }
}



} // end namespace psy
