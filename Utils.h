#ifndef TP1_UTILS_H
#define TP1_UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::string;

struct Vecteur {
    float xyz[ 3 ]; // les composantes
    // constructeur
    Vecteur() = default;;
    Vecteur( float x, float y, float z ): xyz{x, y, z} {}

    // accesseur en ecriture
    float& operator[]( int i ) {
        return xyz[i];
    }
    // accesseur en lecture
    float operator[]( int i ) const {
        return xyz[i];
    }
};

inline
std::ostream& operator<<( std::ostream& out, Vecteur v )
{ out << "{" << v[ 0 ] << " " << v[ 1 ] << " " << v[ 2 ] << "}";
    return out;}
inline
std::istream& operator>>( std::istream& in, Vecteur& v )
{ in >> v[ 0 ] >> v[ 1 ] >> v[ 2 ];
    return in;}

struct Triangle{
    Vecteur sommets[3]; // les sommets des triangles
    // constructeur
    Triangle(Vecteur s1, Vecteur s2, Vecteur s3): sommets{s1, s2, s3}{}

    // accesseur en ecriture
    Vecteur& operator[]( int i ) {
        return sommets[i];
    }
    // accesseur en lecture
    Vecteur operator[]( int i ) const {
        return sommets[i];
    }
};

inline
std::ostream& operator<<( std::ostream& out, Triangle t )
{ out << "triangle: " << t[ 0 ] << " " << t[ 1 ] << " " << t[ 2 ];
    return out;}
inline
std::istream& operator>>( std::istream& in, Triangle& t )
{ in >> t[ 0 ] >> t[ 1 ] >> t[ 2 ];
    return in;}

struct TriangleSoup {
    std::vector<Triangle> triangles; // les triangles
    TriangleSoup() = default;
    void read( std::istream& in ) {
        string inputLine;

        // lecture de chaque ligne
        while(getline(in,inputLine)) {
            if (!inputLine.empty() && inputLine[0] != '#') {
                std::istringstream ss(inputLine);
                Vecteur v1{}, v2{}, v3{};
                ss >> v1 >> v2 >> v3;
                Triangle t(v1, v2, v3);
                triangles.push_back(t);
            }
        }
    }
};


#endif //TP1_UTILS_H
