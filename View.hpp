#ifndef __VIEW_HPP__
#define __VIEW_HPP__ 1
#include "Model.hpp"
#include <qgl.h>
#if defined(Q_WS_MAC)
# include <OpenGL/glu.h>
#else
# include <GL/glu.h>
#endif

typedef std::pair<GLuint , GLuint> RenderPair;

class View
{
private:
        Model& _model;
        ::GLuint _drawMesh;

public:
        View ( Model& model );
        virtual ~View ( void );
        void init ( void );
        void render ( void );
        void resize ( const int width, const int height );

private:
        void render_mesh ( void );

};
#endif // __VIEW_HPP__
