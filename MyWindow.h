/*
 * MyWindow.h
 *
 *  Created on: 7 но€б. 2019 г.
 *      Author: nito
 */

#ifndef MYWINDOW_H_
#define MYWINDOW_H_

#include "Window.h"
#include "Texture.h"

class MyWindow: public Window
{
protected:
	Texture _madhouse_texture { "dom.png" };
public:
	MyWindow(): Window(800, 600) { setup_gl(); }
	MyWindow(const MyWindow&) = delete;
	virtual ~MyWindow() = default;

	virtual void render();
	virtual void setup_gl();
};




#endif /* MYWINDOW_H_ */
