//*****************************************************************************
//
// Main Program
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//          (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "MyWindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    MyWindow win;
    win.show();
    return app.exec();
}
