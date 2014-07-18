#include "tree.h"
#include "../request/request.h"
#include <QVector>
#include "node.h"

tree::tree() {
    root = NULL;
}

tree::~tree() {
    destroy_tree();
}

void tree::destroy_tree(node *leaf){
    if(leaf!=NULL){
        for (int i = 0; i < (*leaf).nodes.size(); i++)
            destroy_tree((*leaf).nodes[i]);
        delete leaf;
    }
}

void tree::insert(QString name, node *leaf)
{
      (*leaf).nodes.push_back(new node(name));
}

node *tree::search(QString name, node *leaf)
{
  if(leaf!=NULL)
  {
      if ((*leaf).name == name)
          return leaf;
      node* tmpNode;
      for (int i = 0; i < (*leaf).nodes.size(); i++)
      {
          tmpNode = search(name, (*leaf).nodes[i]);
          if (tmpNode != NULL)
          {
              return tmpNode;
          }
      }
      return NULL;
  }
  else
      return NULL;
}

node *tree::searchParent(QString name, node *leaf)
{
  if(leaf!=NULL)
  {
      node* tmpNode;
      for (int i = 0; i < (*leaf).nodes.size(); i++)
          if ((*leaf).nodes[i]->name == name)
              return leaf;
      for (int i = 0; i < (*leaf).nodes.size(); i++)
      {
          tmpNode = searchParent(name, (*leaf).nodes[i]);
          if (tmpNode != NULL)
          {
              return tmpNode;
          }
      }
      return NULL;
  }
  else
      return NULL;
}

node *tree::search(QString name)
{
  return search(name, root);
}

void tree::insertRoot(QString name)
{
    root=new node(name);
}

void tree::deleteNode(QString name)
{
    node* nodeForDel = search(name);
    node* nodeForDel_Parent = searchParent(name, root);
    for (int i = 0; i < nodeForDel_Parent->nodes.size(); i++)
        if (nodeForDel == nodeForDel_Parent->nodes[i])
            nodeForDel_Parent->nodes.erase(
                        nodeForDel_Parent->nodes.begin() + i);
    destroy_tree(nodeForDel);
}

void tree::destroy_tree()
{
  destroy_tree(root);
}
