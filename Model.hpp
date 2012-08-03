#ifndef __MODEL_HPP__
#define __MODEL_HPP__ 1
//#include "Preference.hpp"
//#include "Mesh.hpp"

#include <string>
#include <Eigen/Dense>
#include <QString>

#include "TriangleMesh.hpp"

enum RenderingMode {
        WIRE = 0x01,
        SURFACE = 0x02,
        POINTCLOUD = 0x04
};

class Model
{
private:
    TriangleMesh *mesh;
    float zoom;
    int renderingMode;
public:
        Model ( void ) ;
        virtual ~Model ( void ) ;

        // --- mesh io ---
        bool initMesh ( void );
        bool openMesh ( QString filename);
        bool saveMesh ( const std::string& filename , bool isBinary = false , size_t id = 0 );

        // --- view ---
        void getMesh(TriangleMesh &_mesh);
        void getBoundingBox(Eigen::Vector3f &min, Eigen::Vector3f &max);
        void getDisplayRange(double &near, double &far);
        void setRenderingMode(const int mode);
        int getRenderingMode();
        void toggleWireMode();
        void viewFit ( void );
        void viewInit ( void );
        void setZoom(float zoom);
        float getZoom();

        //void setRenderingMode(const int status);

        // --- color ---
        void getSurfaceColor ( const int id , int &r, int &g, int &b );
        void setSurfaceColor ( const int id, const int r, const int g, const int b );
        void getBackgroundColor ( const int id, int &r, int &g, int &b );
        void setBackgroundColor ( const int id, const int r, const int g, const int b );
        void getWireColor ( const int id, int &r, int &g, int &b );
        void setWireColor ( const int id, const int r, const int g, const int b );
        void getVertexColor( const int id, int &r, int &g, int &b );
        void setVertexColor( const int id, const int r, const int g, const int b );

};
#endif // __MODEL_HPP__
