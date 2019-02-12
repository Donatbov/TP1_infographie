#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "Utils.h"

using namespace std;
int main(int argc, char** argv) {

   // Read command lines arguments.
   QApplication application(argc,argv);
   Vecteur u1 ( 0.0, 0.0, 0.0 );
   Vecteur u2 ( 1.0, 0.0, 0.0 );
   Vecteur u3 ( 0.0, 1.0, 0.0 );

   Triangle t (u1, u2, u3);

   cout << t ;

   // Instantiate the viewer.
   Viewer viewer;
   // Give a name
   viewer.setWindowTitle("Viewer triangle soup");
   // Make the viewer window visible on screen.
   viewer.show();
   // Run main loop.
   application.exec();
   return 0;
}