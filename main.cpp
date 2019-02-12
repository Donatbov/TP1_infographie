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
    ts.read(input);

    cout << ts.triangles.size() << endl;


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