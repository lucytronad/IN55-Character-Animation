#include "MyWindow.h"


#include "../shapes/Basis.h"

#include <iostream>

using namespace std;


QPoint lastPos;

Basis* g_Basis;


MyWindow::MyWindow()
{
    setWindowTitle(trUtf8("IN55-MyWindow"));
    g_Basis = new Basis( 10.0 );

    camera = new Camera();
    camera->setAspectRatio(this->width());
    camera->setFOV(45.0f);
    camera->setPlanes(0.1f,100.0f);
    camera->setPosition(0,5,30);
    camera->setOrientation(0,0,0,0);

}


MyWindow::~MyWindow()
{
    delete g_Basis;
    delete camera;
}


bool
MyWindow::initializeObjects()
{
    // Fond gris
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );

    // Chargement des shaders
    createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

    return true;
}

void
MyWindow::resizeGL(int w, int h)
{
    glViewport( 0, 0, w, h );
    camera->setAspectRatio(w / static_cast<GLfloat>(h));
    camera->buildProjectionMatrix();
}


void
MyWindow::render()
{
    // Initialisation de la caméra
    this->transmitMatrices();

    // Rendu des objets
    pushMatrix();
    g_Basis->draw();
    popMatrix();
}


void
MyWindow::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
    case Qt::Key_Escape:
        close();
        break;

    case Qt::Key_Left:
        camera->translateX(1);
        break;

    case Qt::Key_Right:
        camera->translateX(-1);
        break;

    case Qt::Key_Up:
        camera->translateZ(1);
        break;

    case Qt::Key_Down:
        camera->translateZ(-1);
        break;

    /*case Qt::Key_Z:
        camera->rotateX(1);
        break;

    case Qt::Key_S:
        camera->rotateX(-1);
        break;

    case Qt::Key_D:
        camera->rotateY(1);
        break;

    case Qt::Key_Q:
        camera->rotateY(-1);
        break;*/


    }
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyWindow::mouseMoveEvent(QMouseEvent* event) {

    float dx = (event->x() - lastPos.x()) / 10.0f;
    float dy = (event->y() - lastPos.y())/ 10.0f;
    camera->rotate(1,dy,dx,0);
    lastPos = event->pos();

}

void MyWindow::transmitMatrices() {

    GLint var_id_M = glGetUniformLocation( this->getCurrentShaderId(), "M" );
    this->transmitM( var_id_M );

    camera->buildViewMatrix();
    GLint var_id_V = glGetUniformLocation( this->getCurrentShaderId(), "V" );
    glUniformMatrix4fv( var_id_V, 1, GL_TRUE, camera->getViewMatrix().data);

    GLint var_id_P = glGetUniformLocation( this->getCurrentShaderId(), "P" );
    glUniformMatrix4fv( var_id_P, 1, GL_TRUE, camera->getProjectionMatrix().data);


}
