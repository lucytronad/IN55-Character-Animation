#ifndef MyWindow_h
#define MyWindow_h


#include "../common/GlWindow.h"
#include "../camera/Camera.h"

class MyWindow : public GlWindow
{
	public:
        MyWindow();
        ~MyWindow();

		/*!
		*\brief Initialization des objets.
		*/
		bool initializeObjects();

		/*!
		*\brief Rendu de la scène.
		*/
		void render();

        void resizeGL(int w, int h);

        void transmitMatrices();

		void keyPressEvent(QKeyEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *);

   private:
        Camera* camera;
};


#endif
