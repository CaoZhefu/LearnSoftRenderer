#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "mesh.h"

mesh::mesh(const string& filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if(in.fail()) return;
    std::string line;
    while(!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            vec3 v;
            for(int i = 0; i < 3; ++i) iss >> v[i];
            vertexs.push_back(v);
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            vec3 n;
            for(int i = 0; i < 3; ++i) iss >> n[i];
            n.normalize();
            normals.push_back(n);
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            vec2 uv;
            iss >> uv.x >> uv.y;
            texcoords.push_back(uv);
        }
        else if (!line.compare(0, 2, "f ")) {
            int f, t, n;
            iss >> trash;
            int cnt = 0;
            while(iss >> f >> trash >> t >> trash >> n) {
                facet_vert.push_back(--f);
                facet_texcoord.push_back(--t);
                facet_norm.push_back(--n);
                ++cnt;
            }
            if(cnt != 3) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                in.close();
                return;
            }
        }
    }

    in.close();
    std::cerr << "mesh " << filename << " load finished" << std::endl; 
    std::cerr << "v# " << vertexs.size() << " f# " << facet_vert.size() / 3 << " vt# " << texcoords.size() << " vn# " << normals.size() << std::endl;
}