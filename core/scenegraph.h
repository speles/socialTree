#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include <vector>

#include "node.h"
#include "../opengl/RenderTypes.h"
#include "corehandler.h"
#include "tree.h"

#define SQUARE_W 60
#define SQUARE_H 60
#define PADDING_X 20
#define PADDING_Y 100

struct SceneRectangle
{
    Vertex2F center;
    float size;
};

class SceneGraph
{
public:
    static int RootChildren;
    static int FullWidth;

    static void Generator(tree* Tree);
    static std::vector<Line2F> lines;
    static std::vector<SceneRectangle> rectangles;
private:
    static void CheckCollisions(node* leaf);
    static void SetChildCount(node* leaf);
    static void SetOffset(node* leaf, int offset);
    static void SetCoords(node* leaf);
};

#endif // SCENEGRAPH_H
