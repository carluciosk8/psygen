#pragma once


#include <list>

#include "Engine/Object.hpp"
#include "Engine/ObjectData.hpp"
#include "Engine/Visitable.hpp"


namespace psy {


class Attribute;
class Geometry;


class Node :
    public Object,
    public ObjectData,
    public Visitable
{
public:
    virtual ~Node();

    void reparent_to(Node* node);
    void detach();

    std::list<Attribute*>& get_attributes_list() { return m_attributes_list; }
    std::list<Geometry*>&  get_geometries_list() { return m_geometries_list; }
    std::list<Node*>&      get_nodes_list()      { return m_nodes_list; }
    Node*                  get_parent()          { return m_parent; }


protected:
    std::list<Attribute*> m_attributes_list;
    std::list<Geometry*> m_geometries_list;
    std::list<Node*> m_nodes_list;
    Node* m_parent;
};



} // end namespace psy
