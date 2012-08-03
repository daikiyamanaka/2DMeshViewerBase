#include "View.hpp"
#include "Model.hpp"
#include "Color3f.hpp"
#include <iostream>

View::View ( Model& model ) : _model ( model )
{
        return;
}

View::~View ( void )
{
        return;
}

void
View::init ( void )
{
        ::glEnable( GL_CULL_FACE );
        ::glEnable ( GL_DEPTH_TEST );
        ::glEnable ( GL_LIGHT0 );
    ::glEnable( GL_LIGHT1 );
    ::glEnable( GL_LIGHT2 );
        ::glShadeModel ( GL_FLAT );
        ::glShadeModel ( GL_SMOOTH );
        //const Color3f bg = this->_model.getPreferences().at(0).getBackgroundColor();
        //::glClearColor ( bg.x(), bg.y(), bg.z(), 1 );
    ::glClearColor(1, 1, 1, 1);
        return;
}

void View::render(void){
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ::glLoadIdentity();
    float zoom = this->_model.getZoom();
    ::glScalef(zoom, zoom, zoom);

    ::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    TriangleMesh mesh;
    this->_model.getMesh(mesh);
    ::glEnable(GL_POLYGON_OFFSET_FILL);
    ::glPolygonOffset(5.0, 5.0);
    for(int i=0; i<mesh.get_number_of_faces(); i++){
        ::glBegin(GL_POLYGON);
            ::glColor3f(mesh.scalars[i], mesh.scalars[i], mesh.scalars[i]);
            ::glVertex2f(mesh.points[mesh.facets[i][0]][0], mesh.points[mesh.facets[i][0]][1]);
            ::glVertex2f(mesh.points[mesh.facets[i][1]][0], mesh.points[mesh.facets[i][1]][1]);
            ::glVertex2f(mesh.points[mesh.facets[i][2]][0], mesh.points[mesh.facets[i][2]][1]);
        ::glEnd();
    }
    ::glDisable(GL_POLYGON_OFFSET_FILL);
    ::glDisable(GL_CULL_FACE);
    int mode = this->_model.getRenderingMode();
    if(mode & WIRE){
        ::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        ::glColor3f(0, 1, 1);
        for(int i=0; i<mesh.get_number_of_faces(); i++){
            ::glBegin(GL_POLYGON);
                ::glVertex2f(mesh.points[mesh.facets[i][0]][0], mesh.points[mesh.facets[i][0]][1]);
                ::glVertex2f(mesh.points[mesh.facets[i][1]][0], mesh.points[mesh.facets[i][1]][1]);
                ::glVertex2f(mesh.points[mesh.facets[i][2]][0], mesh.points[mesh.facets[i][2]][1]);
            ::glEnd();
        }
    }
}

/*
void
View::render ( void )
{
        //const Color3f bg = this->_model.getPreferences().at(0).getBackgroundColor();
        //::glClearColor(bg.x(), bg.y(), bg.z(), 1);
        ::glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        ::glLoadIdentity();

        //const double zNear = 0.001;
        //const double zFar  = 100000.0;
        double zNear , zFar;
        //this->_model.getDisplayRange(zNear , zFar);
        //const double fov = this->_model.getCamera().getFieldOfViewAngle();

        // model view.

        const Camera& camera = this->_model.getCamera();
        Eigen::Vector3f eye = camera.getEye();
        Eigen::Vector3f center = camera.getCenter();
        Eigen::Vector3f up = camera.getUpVector();
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();
        int viewport[4];
        ::glGetIntegerv ( GL_VIEWPORT, viewport );
        ::gluPerspective ( fov, viewport[2] * 1.0 / viewport[3],  zNear, zFar );
        ::gluLookAt ( eye.x(), eye.y(), eye.z(),
                      center.x(), center.y(), center.z(),
                      up.x(), up.y(), up.z() );

        //light
        //const Color3f lg = this->_model.getLight(-1).getColor();
        //Eigen::Vector3f color;
        //color[0] = lg.x();
        //color[1] = lg.y();
        //color[2] = lg.z();


        //this->setLightColor(light1, GL_LIGHT0, color);
        //this->setLightColor(light2, GL_LIGHT1, color);
        //this->setLightColor(light3, GL_LIGHT2, color);

        //draw mesh

        //RenderingMode mode = this->_model.getPreference().getRenderingMode() ;

        for( int i = 0 ; i < this->_drawMeshList.size() ; i++){
            if( !this->_model.getMeshCheckState().at(i) ) continue;

            int mode = this->_model.getPreferences().at(i).getRenderingMode();
            GLuint drawlist;
            ShadingMode shading = this->_model.getPreferences().at(i).getShadingMode();
            if( shading == FLAT ) drawlist = this->_drawMeshList[i].first;
            else drawlist = this->_drawMeshList[i].second;

            //std::cerr<< i <<":";

            if ( mode & SURFACE ) {
                //std::cerr<<"Surface";
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
                glEnable(GL_POLYGON_OFFSET_FILL);
                glPolygonOffset(1.0, 1.0);
                glCallList(drawlist);
                glDisable(GL_POLYGON_OFFSET_FILL);
                glDisable(GL_CULL_FACE);
                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
                ::glEnable ( GL_LIGHTING );
                const Color3f fg = this->_model.getPreferences().at(i).getSurfaceColor();

                //::glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
                GLfloat mat_ambient[4] = {fg.x(), fg.y(), fg.z(), 1.0};
                GLfloat mat_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                GLfloat mat_specular[4] = {0.2, 0.2, 0.2, 1.0};
                GLfloat mat_shininess[1] = {100.0f};

                ::glMaterialfv ( GL_FRONT, GL_AMBIENT,  mat_ambient );
                ::glMaterialfv ( GL_FRONT, GL_DIFFUSE,  mat_diffuse );
                ::glMaterialfv ( GL_FRONT, GL_SPECULAR, mat_specular );
                ::glMaterialfv ( GL_FRONT, GL_SHININESS,mat_shininess );

                GLfloat mat2_ambient[4] = {1-fg.x(), 1-fg.y(), 1-fg.z(), 1.0};
                GLfloat mat2_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                GLfloat mat2_specular[4] = {0.2, 0.2, 0.2, 1.0};
                GLfloat mat2_shininess[1] = {100.0f};
                ::glMaterialfv ( GL_BACK, GL_AMBIENT,  mat2_ambient );
                ::glMaterialfv ( GL_BACK, GL_DIFFUSE,  mat2_diffuse );
                ::glMaterialfv ( GL_BACK, GL_SPECULAR, mat2_specular );
                ::glMaterialfv ( GL_BACK, GL_SHININESS,mat2_shininess );
                ::glCallList(drawlist);
            }
            if ( mode & WIRE ) {
                //std::cerr<<"Wire";
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                ::glDisable ( GL_LIGHTING );
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
                const Color3f fg = this->_model.getPreferences().at(i).getWireColor();
                ::glColor3f ( fg.x(), fg.y(), fg.z() );
                int width = this->_model.getWireWidth();
                ::glLineWidth(width);
                ::glCallList(drawlist);
            }
            if( mode & POINTCLOUD ){
                //std::cerr<<"Vertex";
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                ::glDisable ( GL_LIGHTING );
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
                const Color3f fg = this->_model.getPreferences().at(i).getVertexColor();
                ::glColor3f ( fg.x(), fg.y(), fg.z() );
                int radius = this->_model.getPreferences().at(i).getPointRadius();///edit after
                ::glLineWidth(radius);
                //this->render_mesh();
                ::glCallList(drawlist);
            }
            //std::cerr<<std::endl;
        }


        return;
}
*/
void
View::resize ( const int width, const int height )
{
        ::glViewport ( 0, 0, width, height );
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();

        if (width <= height)
            glOrtho(-1.2, 1.2, //左右
              -1.2*height/width, 1.2*height/width, //下上
              -1, 1 //手前奥
              );
        else
            glOrtho(-1.2*width/height, 1.2*width/height, //左右
              -1.2, 1.2, //下上
              -1, 1 //手前奥
              );

        glMatrixMode(GL_MODELVIEW);

    /*
        const double zNear = 0.001;
        const double zFar  = 100000.0;
        //const double fov = this->_model.getCamera().getFieldOfViewAngle();
        double fov = 10;
        // Camera
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();
        int viewport[4];
        ::glGetIntegerv ( GL_VIEWPORT, viewport );
        ::gluPerspective ( fov, viewport[2] * 1.0 / viewport[3],  zNear, zFar );
        ::glMatrixMode ( GL_MODELVIEW );
        */
        return;
}

void
View::render_mesh ( void )
{
    //const std::vector<Mesh>& meshes = this->_model.getMesh();
    //std::vector<bool> checkState= this->_model.getMeshCheckState();
   // std::cout << checkState.size() <<std::endl;
/*
    for(int k=0; k<meshes.size(); k++){

    //for(int k=0; k<checkState.size(); k++){
        if(!checkState[k]){
            continue;
        }
        const Mesh& mesh = meshes[k];
        bool index_data = mesh.IndexDataExists();
        bool vnormal_data = mesh.VNormalDataExists();

        if( index_data ){
            ::glBegin ( GL_TRIANGLES );
            for ( int i = 0 ; i < mesh.getNumFaces() ; i++ ) {

                ShadingMode shading = this->_model.getPreferences().at(i).getShadingMode();
                if(shading == FLAT){
                    const Eigen::Vector3f nrm = mesh.getNormal ( i );
                    ::glNormal3f ( nrm.x(),nrm.y(),nrm.z() );
                }

                    const std::vector<int> index = mesh.getIndex(i);
                    for( int j = 0; j < 3; j++){
                        if(shading == SMOOTH){
                            const Eigen::Vector3f n = mesh.getVNormal( index[j] );
                            ::glNormal3f ( n.x(),n.y(),n.z() );
                        }
                        const Eigen::Vector3f p = mesh.getPosition ( index[j] );
                        ::glVertex3f ( p.x(), p.y(), p.z() );
                    }
            }
            ::glEnd();
        }else{
            ::glBegin ( GL_POINTS );
            for ( int i = 0 ; i < mesh.getNumVertex() ; i++ ) {
                if( vnormal_data ){
                    const Eigen::Vector3f nrm = mesh.getVNormal(i);
                    ::glNormal3f ( nrm.x(),nrm.y(),nrm.z() );
                }
                const Eigen::Vector3f p = mesh.getPosition(i);
                ::glVertex3f ( p.x(), p.y(), p.z() );
            }
             ::glEnd();
        }
        ::glEnd();


    }
    */
    return;
}

