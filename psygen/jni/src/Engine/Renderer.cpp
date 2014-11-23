#include "Engine/Renderer.hpp"

#include "Engine/Attribute.hpp"
#include "Engine/Geometry.hpp"
#include "Engine/Node.hpp"

namespace psy {



Renderer::~Renderer()
{
    // TODO Auto-generated destructor stub
}

Renderer::Renderer()
{
    // TODO Auto-generated constructor stub
}

void Renderer::visit(Visitable* visitable)
{
    Node* node = reinterpret_cast<Node*>(visitable);

    for ( Attribute* attr : node->get_attributes_list() ) attr->enable();

    for ( Geometry* geom : node->get_geometries_list() ) geom->draw();

    for ( Node* child : node->get_nodes_list() ) child->accept(this);

    for ( Attribute* attr : node->get_attributes_list() ) attr->disable();
}



} /* namespace psy */
