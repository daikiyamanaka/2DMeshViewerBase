/*
 * TriangleMesh.h
 *
 *  Created on: Jun 26, 2012
 *      Author: daikiyamanaka
 */

#ifndef TRIANGLEMESH_H_
#define TRIANGLEMESH_H_

#include <vector>

#include <Eigen/Dense>

class TriangleMesh {
public:
	TriangleMesh();
	virtual ~TriangleMesh();

	void read(std::string file_name);
	void write(std::string file_name);
    void readCTM(std::string filename);
    void normalizeScalar();
    void normalize();

	void add(Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c);

    void getVertex(int index, Eigen::Vector3f &v);
    void getFace(int index, std::vector<int> &f);

    int get_number_of_faces();
    int get_number_of_vertices();


	std::vector<Eigen::Vector3f> points;
	std::vector<std::vector<int> > facets;
    std::vector<float> scalars;
private:
    int num_of_vertices;
    int num_of_faces;

};

#endif /* TRIANGLEMESH_H_ */
