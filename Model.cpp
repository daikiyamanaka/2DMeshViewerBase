#include "Model.hpp"
#include "Color3f.hpp"
#include <iostream>
#include <QtGui>

Model::Model ( void )
{
    mesh = new TriangleMesh();
    zoom = 1;
    renderingMode = 0x00;
    return;

}

Model::~Model( void )
{
        return;
}

bool
Model::initMesh ( void )
{
        //this->_mesh.clear();
        return true;
}

bool Model::openMesh(QString filename){
    QString extension = QFileInfo(filename).completeSuffix();
    if(extension.toStdString() == "ctm"){
        std::cout << "file is ctm." << std::endl;
        mesh->readCTM(filename.toStdString());
    }
    return true;
}

void Model::getMesh(TriangleMesh &_mesh){
    _mesh = *mesh;
}

void Model::getBoundingBox(Eigen::Vector3f &min, Eigen::Vector3f &max){
    Eigen::Vector3f v;
    for(int i=0; i<mesh->get_number_of_vertices(); i++){
        mesh->getVertex(i, v);
        for(int j=0; j<3; j++){
            if(v[j] > max[j]){
                max[j] = v[j];
            }
            else if(v[j] < min[j]){
                min[j] = v[j];
            }
        }
    }
}

void Model::setRenderingMode(const int mode){
    renderingMode = mode;
}

int Model::getRenderingMode(){
    return renderingMode;
}

void Model::toggleWireMode(){
    //std::cout << "toggle wire mode" << std::endl;
    //std::cout << "mode : " << getRenderingMode() << std::endl;
    //std::cout << "mode & WIRE : " << (getRenderingMode() & WIRE) << std::endl;
    setRenderingMode(getRenderingMode() ^ WIRE);
}

void Model::getDisplayRange(double &near, double &far){
    //Eigen::Vector3f min, max;
    //getBoundingBox(min, max);

}

void Model::setZoom(float _zoom){
    zoom = _zoom;
}

float Model::getZoom(){
    return zoom;
}

/*
bool
Model::openMesh ( const std::string& filename )
{
    ImporterMesh *importer = NULL;
    Tokenizer tok(filename, ".");
    std::string ext = tok.get( tok.size() - 1);
    Mesh mesh;
    if( ext == std::string("stl") ){
        importer = new ImporterMeshStlBinary(mesh);
        ImporterMeshStlBinary impb(mesh);
        if(!impb.check(filename) ) importer = new ImporterStlAscii(mesh);
    }
    else if ( ext == std::string("obj") ){
        importer = new ImporterMeshObj(mesh);
    }
    else if(ext == std::string("pcd") ){
        importer = new ImporterPointsCloudPcdAscii(mesh);
    }
    else {
        return false;
    }

    mesh.clear();

    //this->initMesh();
    bool result = importer->read ( filename );
    this->_mesh.push_back(mesh);
    this->_checked.push_back(true);
    if( this->_mesh.size() > 1 ) this->_Preferences.push_back( Preference() );

    Eigen::Vector3f bmin, bmax;
    //this->_mesh.getBoundingBox ( bmin, bmax );
    mesh.getBoundingBox ( bmin, bmax );

    const Eigen::Vector3f center = 0.5 * ( bmin + bmax );
    const float radius = 1.25 * 0.5 * ( bmax - bmin ).norm();
    const Eigen::Quaternionf q ( 1,0,0,0 );
    Camera camera;
    camera.fitPosition(center , radius , q);
    this->_cameraList.assign(1, camera );
    this->_NowCameraId = 0;
    this->_activeMeshId = this->_mesh.size() - 1;
    this->viewInit();
    delete importer;

    return result;
}
bool
Model::saveMesh ( const std::string& filename, bool isBinary, size_t id )
{
    ExporterMesh *exporter = NULL;
    Tokenizer tok(filename, ".");
    std::string ext = tok.get( tok.size() - 1);
    if( id > this->_mesh.size() - 1 ) return false;
    Mesh mesh = this->_mesh[id];
    if( ext == std::string("stl") ){
        if( isBinary ) exporter = new ExporterStlBinary(mesh);
        else exporter = new ExporterStlAscii(mesh);
    }
    else if ( ext == std::string("obj") ){
        exporter = new ExporterObj(mesh);
    }
    else {
        return false;
    }

    bool result = exporter->write(filename);
    delete exporter;
    return result;
}
*/

/*
void
Model::setRenderingMode ( const RenderingMode mode )
{
        this->_preference.setRenderingMode ( mode );
        return;
}
*/
/*
void
Model::viewFit ( void )
{
        Eigen::Vector3f bmin, bmax;


        this->_mesh[getActiveMeshIndex()].getBoundingBox ( bmin, bmax );

        Eigen::Vector3f center;
        center = ( bmax+bmin )/2;

        //const Eigen::Vector3f center = this->_camera.getCenter();
        const float radius = 1.25 * std::min ( ( bmax - center ).norm(), ( bmin - center ).norm() );
        const Eigen::Quaternionf q = this->getCamera().getRotation();
        this->addNowCameraToList();
        this->_cameraList.at(this->_NowCameraId).fitPosition ( center, radius, q );
        this->_light.setPosition ( this->getCamera().getEye() );
        return;
}
void
Model::viewInit ( void )
{
        Eigen::Vector3f bmin, bmax;
        this->_mesh[getActiveMeshIndex()].getBoundingBox ( bmin, bmax );

        const Eigen::Vector3f center = 0.5 * ( bmin + bmax );
        const float radius = 1.25 * 0.5 * ( bmax - bmin ).norm();
        const Eigen::Quaternionf q ( 1,0,0,0 );
        this->addNowCameraToList();
        this->_cameraList.at(this->_NowCameraId).fitPosition ( center, radius, q );

        this->setLightPosition();

        Eigen::Vector3f keyamb(0.1, 0.1, 0.1);
        Eigen::Vector3f keydif = 8.0*keyamb;
        this->_keylight.setAmbient(keyamb);
        this->_keylight.setDiffuse(keydif);
        this->_keylight.setSpecular(keyamb);

        this->_filllight.setAmbient( 0.5*keyamb);
        this->_filllight.setDiffuse(0.5*keydif);
        this->_filllight.setSpecular(0.0*keyamb);

        this->_backlight.setAmbient(0.50*keyamb);
        this->_backlight.setDiffuse(0.50*keydif);
        this->_backlight.setSpecular(0.0*keyamb);
        return;
}
*/
void
Model::getSurfaceColor (const int id, int &r, int &g, int &b )
{
    //const Color3f c = this->getPreference().getSurfaceColor();
    //const Color3f c = this->_Preferences.at(id).getSurfaceColor();
    //r = static_cast<int> ( 255 * c.x() );
    //g = static_cast<int> ( 255 * c.y() );
    //b = static_cast<int> ( 255 * c.z() );

}
void
Model::setSurfaceColor ( const int id, const int r, const int g, const int b )
{
	Color3f c;
    //c.x() = r * 1.0 / 255;
    //c.y() = g * 1.0 / 255;
    //c.z() = b * 1.0 / 255;
    //this->_Preferences.at(id).setSurfaceColor( c );
}

void
Model::getBackgroundColor (const int id , int &r, int &g, int &b )

{

    //const Color3f c = this->getPreference().getBackgroundColor();
    //const Color3f c = this->_Preferences.at(id).getBackgroundColor();
    //r = static_cast<int> ( 255 * c.x() );
    //g = static_cast<int> ( 255 * c.y() );
    //b = static_cast<int> ( 255 * c.z() );

}
void
Model::setBackgroundColor ( const int id ,  const int r, const int g, const int b )
{
    Color3f c;
    //c.x() = r * 1.0 / 255;
    //c.y() = g * 1.0 / 255;
    //c.z() = b * 1.0 / 255;
    //this->_preference.setBackgroundColor ( c );
    //this->_Preferences.at(id).setBackgroundColor( c );
}
void
Model::getWireColor ( const int id, int &r, int &g, int &b )
{
    //const Color3f c = this->getPreference().getWireColor();
    //const Color3f c = this->_Preferences.at(id).getWireColor();
    //r = static_cast<int> ( 255 * c.x() );
    //g = static_cast<int> ( 255 * c.y() );
    //b = static_cast<int> ( 255 * c.z() );

}

void
Model::setWireColor ( const int id, const int r, const int g, const int b )
{
    /*
    Color3f c;
    c.x() = r * 1.0 / 255;
    c.y() = g * 1.0 / 255;
    c.z() = b * 1.0 / 255;
    this->_Preferences.at(id).setWireColor(  c );
    */
}

void
Model::getVertexColor ( const int id ,  int &r, int &g, int &b )
{
    /*
    const Color3f c = this->_Preferences.at(id).getVertexColor();
    r = static_cast<int> ( 255 * c.x() );
    g = static_cast<int> ( 255 * c.y() );
    b = static_cast<int> ( 255 * c.z() );
    */
}

/*void
Model::setWireColor ( const int id, const int r, const int g, const int b )
{
    Color3f c;
    c.x() = r * 1.0 / 255;
    c.y() = g * 1.0 / 255;
    c.z() = b * 1.0 / 255;
    //this->_preference.setWireColor ( c );
    this->_Preferences.at(id).setWireColor(  c );
}*/

/*void
Model::getVertexColor ( const int id ,  int &r, int &g, int &b )
{
    //const Color3f c = this->getPreference().getVertexColor();
    const Color3f c = this->_Preferences.at(id).getVertexColor();
    r = static_cast<int> ( 255 * c.x() );
    g = static_cast<int> ( 255 * c.y() );
    b = static_cast<int> ( 255 * c.z() );

}*/

void
Model::setVertexColor ( const int id,  const int r, const int g, const int b )
{
    /*
    Color3f c;
    c.x() = r * 1.0 / 255;
    c.y() = g * 1.0 / 255;
    c.z() = b * 1.0 / 255;
    this->_Preferences.at(id).setVertexColor( c );
    */
}
