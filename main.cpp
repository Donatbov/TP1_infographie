#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <complex>
#include "Viewer.h"
#include "Utils.h"

using namespace std;
int main(int argc, char** argv) {
    std::ifstream input( argv[1] );
    TriangleSoup ts;
    TriangleSoup zippedTs;

    ts.read(input);

    TriangleSoupZipper(ts, zippedTs, Index(50,50,50));

    cout << ts.triangles.size() << endl;
    cout << zippedTs.triangles.size() << endl;

    /*
    // tests inf & max :
    Vecteur v1(1,1,1);
    Vecteur v2(2,0,1);
    cout << "min :" << v1.inf(v2) << "\n";
    cout << "max :" << v1.sup(v2) << "\n";
    */


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
}
