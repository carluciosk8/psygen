#include "Engine/Renderer.hpp"

#include "Engine/Effect.hpp"
#include "Engine/Geometry.hpp"
#include "Engine/Node.hpp"


namespace psy {



Renderer::~Renderer()
{
}


Renderer::Renderer()
{
}


void Renderer::visit(Visitable* visitable)
{
    Node* node = reinterpret_cast<Node*>(visitable);

    for ( Effect* attr : node->get_attributes_list() ) attr->enable();

    for ( Geometry* geom : node->get_geometries_list() ) geom->draw();

    for ( Node* child : node->get_nodes_list() ) child->accept(this);

    for ( Effect* attr : node->get_attributes_list() ) attr->disable();
}



} // end namespace psy
