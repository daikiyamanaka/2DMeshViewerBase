/*
 * TriangleMesh.cpp
 *
 *  Created on: Jun 26, 2012
 *      Author: daikiyamanaka
 */

#include "TriangleMesh.hpp"
#include <fstream>
#include <string>
#include <iostream>

TriangleMesh::TriangleMesh() {
	// TODO Auto-generated constructor stub

}


TriangleMesh::~TriangleMesh() {
    // TODO Auto-generated destructor stub

}

void TriangleMesh::readCTM(std::string filename){

    std::cout << filename.c_str() << std::endl;

    FILE* in = fopen(filename.c_str(), "r");
    fscanf(in, "%d", &num_of_vertices);
    //ver = new float[verN][2];
    points.resize(num_of_vertices);

    fscanf(in, "%d", &num_of_faces);
    facets.resize(num_of_faces);
    scalars.resize(num_of_faces);

    std::cout << "num_of_vertices : " << num_of_vertices << std::endl;
    std::cout << "num_of_faces : " << num_of_faces << std::endl;

    for(int i=0; i<num_of_vertices; i++){
        float x, y;
      fscanf(in, "%g %g", &x, &y);
      points[i][0] = x;
      points[i][1] = y;
      points[i][2] = 0;
    }

    for(int i=0; i<num_of_faces; i++){
        int p0, p1, p2;
        fscanf(in, "%d %d %d", &p0, &p1, &p2);
        std::vector<int> face(3);
        face[0] = p0;
        face[1] = p1;
        face[2] = p2;
        facets[i] = face;
    }

    for(int i=0; i<num_of_faces; i++){
        float value;
        fscanf(in, "%g", &value);
        scalars[i] = value;
    }

    fclose(in);

    normalizeScalar();
    normalize();

    std::cout << "ctm file readed" << std::endl;

}

void TriangleMesh::add(Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c){

	std::vector<int> face(3);

	if(std::find(points.begin(), points.end(), a) == points.end()){
		points.push_back(a);
	}
	if(std::find(points.begin(), points.end(), b) == points.end()){
		points.push_back(b);
	}
	if(std::find(points.begin(), points.end(), c) == points.end()){
		points.push_back(c);
	}

	face[0] = std::find(points.begin(), points.end(), a) - points.begin();
	face[1] = std::find(points.begin(), points.end(), b) - points.begin();
	face[2] = std::find(points.begin(), points.end(), c) - points.begin();

	facets.push_back(face);

}

void TriangleMesh::getVertex(int index, Eigen::Vector3f &v){
    v = points[index];
}

void TriangleMesh::getFace(int index, std::vector<int> &f){
    f = facets[index];
}

int TriangleMesh::get_number_of_faces(){
//	return facets.size();
    return num_of_faces;
}

int TriangleMesh::get_number_of_vertices(){
    return num_of_vertices;
}

void TriangleMesh::normalizeScalar(){
    float max, min;
    max = min = scalars[0];
    for(int i=0; i<num_of_faces; i++){
        if(scalars[i] > max){
            max = scalars[i];
        }
        else if(scalars[i] < min){
            min = scalars[i];
        }
    }
    for(int i=0; i<num_of_faces; i++){
        scalars[i] = (scalars[i] - min)/(max - min);
    }
}

void TriangleMesh::normalize(){
    float max[3], min[3], mid[3];
    for(int i=0; i<3; i++){
        max[i] = min[i] = points[0][i];
        for(int j=1; j<num_of_vertices; j++){
            float v = points[j][i];
            if(max[i] < v){
                max[i] = v;
            }
            else if(min[i] > v){
                min[i] = v;
            }
        }
        mid[i] = 0.5*(max[i] + min[i]);
    }
    float size = max[0] - min[0];

    for(int i=0; i<num_of_vertices; i++){
        points[i][0] = (points[i][0] - mid[0])/size;
        points[i][1] = (points[i][1] - mid[1])/size;
        points[i][2] = (points[i][2] - mid[2])/size;
    }
}
