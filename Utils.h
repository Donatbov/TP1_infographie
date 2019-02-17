#ifndef TP1_UTILS_H
#define TP1_UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <math.h>

using std::string;

struct Vecteur {
    float xyz[ 3 ]; // les composantes
    // constructeur
    Vecteur() = default;
    Vecteur( float x, float y, float z ): xyz{x, y, z} {}

    // accesseur en ecriture
    float& operator[]( int i ) {
        return xyz[i];
    }
    // accesseur en lecture
    float operator[]( int i ) const {
        return xyz[i];
    }

    // Retourne le vecteur dont les composantes sont les minima des
    // composantes de soi-même et de other.
    Vecteur inf( const Vecteur& other ) const{
        Vecteur min;
        for(int i = 0 ; i<3 ; i++){
            min.xyz[i] = (this->xyz[i] < other[i]  ? this->xyz[i] : other.xyz[i]) ;
        }
        return min;
    }
    // Retourne le vecteur dont les composantes sont les maxima des
    // composantes de soi-même et de other.
    Vecteur sup( const Vecteur& other ) const{
        Vecteur max;
        for(int i = 0 ; i<3 ; i++){
            max.xyz[i] = (this->xyz[i] > other[i]  ? this->xyz[i] : other.xyz[i]) ;
        }
        return max;
    }

    float norme() const{
        float res = sqrtf(this->xyz[0]*this->xyz[0] + this->xyz[1]*this->xyz[1] + this->xyz[2]*this->xyz[2]);
        return res;
    }

    Vecteur cross( const Vecteur& v ) const{
        Vecteur res = Vecteur();
        res[0] = (this->xyz[1]*v[2])-(this->xyz[2]*v[1]);
        res[1] = (this->xyz[2]*v[0])-(this->xyz[0]*v[2]);
        res[2] = (this->xyz[0]*v[1])-(this->xyz[1]*v[0]);
        return res;
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

    Vecteur normal() const{
        Vecteur s0s1 = Vecteur( this->sommets[0][0]-this->sommets[1][0],
                                this->sommets[0][1]-this->sommets[1][1],
                                this->sommets[0][2]-this->sommets[1][2]);
        Vecteur s0s2 = Vecteur( this->sommets[0][0]-this->sommets[2][0],
                                this->sommets[0][1]-this->sommets[2][1],
                                this->sommets[0][2]-this->sommets[2][2]);
        Vecteur n = s0s1.cross(s0s2);
        float norme = n.norme();
        for (int i = 0; i < 3 ; i++) {
            n[i] /= norme;
        }
        return n;
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

    void boundingBox( Vecteur& low, Vecteur& up) const{
        //initialize low & up
        float infinity = std::numeric_limits<float>::max();
        for(int i = 0 ; i < 3 ; i++){
            low[i] = infinity;
            up[i] = -infinity;
        }
        //then create the bounding box
        for(Triangle t : triangles){
            low = low.inf((t[0].inf(t[1].inf(t[2]))));
            up = low.sup((t[0].sup(t[1].sup(t[2]))));
        }
    }
};

/// Définit un index sur 3 entiers. Toutes les opérations usuelles
/// sont surchargées (accès, comparaisons, égalité).
struct Index {
    int idx[ 3 ];
    Index() = default;
    Index( int i0, int i1, int i2 ): idx{i0, i1, i2} {}
    Index( int indices[] ): idx{indices[0], indices[1], indices[2]} {}

    int  operator[]( int i ) const { return idx[ i ]; }
    int& operator[]( int i )       { return idx[ i ]; }
    bool operator<( const Index& other ) const
    {
        return ( idx[ 0 ] < other.idx[ 0 ] )
               || ( ( idx[ 0 ] == other.idx[ 0 ] )
                    && ( ( idx[ 1 ] < other.idx[ 1 ] )
                         || ( ( idx[ 1 ] == other.idx[ 1 ] )
                              && ( idx[ 2 ] < other.idx[ 2 ] ) ) ) );
    }

    bool operator==( const Index& other ) const
    {
        return ( idx[ 0 ] == other.idx[ 0 ]
                &&  idx[ 1 ] == other.idx[ 1 ]
                &&  idx[ 2 ] == other.idx[ 2 ]);
    }

    bool operator!=( const Index& other ) const
    {
        return ! (*this == other);
    }

};


struct TriangleSoupZipper {
    Vecteur cellSize;
    Vecteur low, up;

    // Construit le zipper avec une soupe de triangle en entrée \a
    // anInput, une soupe de triangle en sortie \a anOutput, et un index \a size
    // qui est le nombre de cellules de la boîte découpée selon les 3 directions.
    TriangleSoupZipper( const TriangleSoup& anInput, TriangleSoup& anOuput, Index size ){
        // Calcul de la boite englobante
        low = Vecteur();
        up = Vecteur();
        anInput.boundingBox(low,up);

        // Calcul de la taille d'une cellule
        float boundingBoxSizeX = up[0] - low[0];
        float boundingBoxSizeY = up[1] - low[1];
        float boundingBoxSizeZ = up[2] - low[2];
        cellSize[0] = boundingBoxSizeX / size[0];
        cellSize[1] = boundingBoxSizeY / size[1];
        cellSize[2] = boundingBoxSizeZ / size[2];

        zip(anInput, anOuput);
    }

    void zip(const TriangleSoup& anInput, TriangleSoup& anOuput){
        //pour chaque triangle de la soupe
        for(Triangle t : anInput.triangles){
            // on vérifie si tous ses sommets un index différent
            if (areInDifferentsCell(t[0], t[1], t[2])){
                // si oui, on crée un triangle aux centre de la cellule
                anOuput.triangles.emplace_back(centroid(index(t[0])), centroid(index(t[1])), centroid(index(t[2])));
            }// Sinon, on ne l'ajoute pas
        }
    }

    /// @return l'index de la cellule dans laquelle tombe \a p.
    Index index( const Vecteur& p ) const{
        return {(int)((p[0]-low[0])/cellSize[0]), (int)((p[1]-low[1])/cellSize[1]), (int)((p[2]-low[2])/cellSize[2])};
    }

    /// @return le centroïde de la cellule d'index \a idx (son "centre").
    Vecteur centroid( const Index& idx ) const{
        return {(float)(cellSize[0]*(idx[0]+ 0.5) + low[0]), (float)(cellSize[1]*(idx[1]+ 0.5) + low[1]), (float)(cellSize[2]*(idx[2]+ 0.5) + low[2])};
    }

    bool areInDifferentsCell(const Vecteur& u, const Vecteur& v, const Vecteur& w) const {
        return (index(u) != index(v) && index(u) != index(w) && index(v) != index(w));
    }
};


#endif //TP1_UTILS_H
