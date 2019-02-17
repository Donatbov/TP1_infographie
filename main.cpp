#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <complex>
#include "Viewer.h"
#include "Utils.h"

using namespace std;
/*int main(int argc, char** argv) {
    std::ifstream input( argv[1] );
    TriangleSoup ts;
    TriangleSoup zippedTs;

    ts.read(input);

    TriangleSoupZipper(ts, zippedTs, Index(50,50,50));

    cout << ts.triangles.size() << endl;
    cout << zippedTs.triangles.size() << endl;


    // Read command lines arguments.
    QApplication application(argc,argv);
    // Instantiate the viewer.
    Viewer viewer(&zippedTs);
    // Give a name
    viewer.setWindowTitle("Viewer triangle soup");
    // Make the viewer window visible on screen.
    viewer.show();
    // Run main loop.
    application.exec();
    return 0;

}*/


int main(int argc, char** argv) {

    if ( argc != 2 ){
        std::cerr << "Nombre d'arguments incorrect. Usage: ./viewer <inputFile>" << std::endl;
        return 0;
    }

    std::ifstream input( argv[1] );
    TriangleSoup ts;

    ts.read(input);

    cout << "Nombre de triangles en entrée : " << ts.triangles.size() << endl;


    // Read command lines arguments.
    QApplication application(argc,argv);
    // Instantiate the viewer.
    Viewer viewer(&ts);
    // Give a name
    viewer.setWindowTitle("Viewer triangle soup");
    // Make the viewer window visible on screen.
    viewer.show();
    // Run main loop.
    application.exec();
    return 0;

}



/*int main(int argc, char** argv) {

    if ( argc != 6 ) {
        std::cerr << "Nombre d'arguments incorrect. Usage: ./compresseur <inputFile> <outputFile> <decoupageX> <decoupageY> <decoupageZ>" << std::endl;
        return 0;
    }

    std::ifstream input( argv[1] );
    std::ofstream output( argv[2] );

    TriangleSoup ts;
    TriangleSoup zippedTs;

    ts.read(input);
    cout << "Nombre de triangles en entrée : " << ts.triangles.size() << endl;

    TriangleSoupZipper(ts, zippedTs, Index(atoi(argv[3]), atoi(argv[4]), atoi(argv[5])));

    zippedTs.write(output);
    cout << "Nombre de triangles en sortie : " << zippedTs.triangles.size() << endl;

    output.close();

    return 0;

}*/


