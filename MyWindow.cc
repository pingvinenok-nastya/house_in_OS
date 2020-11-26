/*
 * MyWindow.cc
 *
 *  Created on: 7 нояб. 2019 г.
 *      Author: nito
 */
#include "MyWindow.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <algorithm>
#include <vector>

static constexpr double Pi = acos(-1);

using VertexVector = std::vector<std::vector<GLdouble>>;
using NormalVector = std::vector<std::vector<GLdouble>>;
using FaceVector = std::vector<std::vector<int>>;
using TexCoordVector = std::vector<std::vector<std::vector<GLdouble>>>;

struct Model {
	VertexVector vertices;
	FaceVector faces;
	NormalVector normals;
	TexCoordVector texcoords;
};

static const VertexVector madhouse_vertices {
	/*{ -1., 0., 2.5 },//1
		{ 1., 0., 2.5 },//2
		{ -1., -1., 2. },//3
		{ -1., 1., 2. },//4
		{ 1., 1., 2. },//5
		{ 1., -1., 2. },//6
		{ -1., -1., 0. },//7
		{ -1., 1., 0. },//8
		{ 1., 1., 0. },//9
		{ 1., -1., 0. },//10*/

		//стена с дв
		{ 1., 1., 2},//0
		{ 1., 1., 1.25},//1
		{ 1., 0.5, 1.25},//2
		{ 1., -0.5, 1.25},//3
		{ 1., -1., 1.25},//4
		{ 1., -1., 2.},//5
		{ 1., 1., 0.},//6
		{ 1., 0.5, 0.},//7
		{ 1., -0.5, 0.},//8
		{ 1., -1., 0.},//9
		//

		//стена с окном
		{ -1., 1., 2.},//10
		{ -1., 1., 1.25},//11
		{ -1., 1., 0.},//12
		{ -0.5, 1., 0.},//13
		{ -0.5, 1., 0.5},//14
		{ -0.5, 1., 1.25},//15
		{ 0.5, 1., 1.25},//16
		{ 0.5, 1., 0.5},//17
		{ 0.5, 1., 0.},//18

		//3stena
		{ -1., -1., 2},//19
		{ -1., -1., 0},//20

		//крыша
		{ 0., 0., 3},//21
		{ 1.3, 1.3, 2},//22
		{ 1.3, -1.3, 2},//23
		{ -1.3, 1.3, 2},//24
		{ -1.3, -1.3, 2},//25
};

static const FaceVector madhouse_faces {
	/*{ 1, 4, 8, 9, 5 },
		{ 0, 2, 6, 7, 3 },
		{ 4, 3, 7, 8 },
		{ 2, 5, 9, 6 },
		{ 7, 6, 9, 8 },
		{ 1, 0, 3, 4 },
		{ 0, 1, 5, 2 },*/
		/*{0, 3, 2, 1},//1
		{4, 5, 3, 0},//2
		{6, 7, 5, 4},//3
		{1, 2, 7, 6},//4*/

		{0, 1, 4, 5},
		{1, 6, 7, 2},
		{3, 8, 9, 4},//дверь

		{10, 11, 1, 0},
		{11, 12, 13, 15},
		{16, 18, 6, 1},
		{14, 13, 18,17},//окно

		{19, 20, 12, 10},//

		{5, 9, 20, 19},//


		//cryha
		{ 21, 22, 23},//1
		{ 21, 24, 22},//2
		{ 21, 25, 24},//3
		{ 21, 25, 23},//4
	};

static const NormalVector madhouse_normals {
	{ 1., 0., 0. },//первые три это стена с дверью
		{ 1., 0., 0. },
		{ 1., 0., 0. },

		{ 0., 1., 0. },//следующие четыре это стена с окном
		{ 0., 1., 0. },
		{ 0., 1., 0. },
		{ 0., 1., 0. },

		{ -1., 0., 0. },//третья стена

		{ 0., -1., 0. },//четвертая стена

		{ 1., 0., 0. },//крыша над дверью
		{ 0., 1., 0. },//крыша над окном
		{ -1., 0., 0. },//крыша третья
		{ 0., -1., 0. },//крыша четвертая
};

static const TexCoordVector madhouse_tc {
		{ {0., 0.}, {0.45, 0.}, {0.45, 0.45}, {0., 0.45} },
		{ {0., 0.}, {0.45, 0.}, {0.45, 0.45}, {0., 0.45} },
		{ {0., 0.}, {0.45, 0.}, {0.45, 0.45}, {0., 0.45} },
		{ {0., 0.}, {0.45, 0.}, {0.45, 0.45}, {0., 0.45} },
		{ {0., 0.}, {0.45, 0.}, {0.45, 0.45}, {0., 0.45} },
		{ {0., 0.}, {0.45, 0.}, {0.45, 0.45}, {0., 0.45} },
		{ {0., 0.}, {0.45, 0.}, {0.45, 0.45}, {0., 0.45} },

		//sten pusto
		{ {0., 0.}, {0.5, 0.}, {0.5, 0.5}, {0., 0.5} },
		{ {0., 0.}, {0.5, 0.}, {0.5, 0.5}, {0., 0.5} },
		//должна быть крыша
		{ {0.75, 0.}, {1., 0.5}, {0.5, 0.5} },
		{ {0.75, 0.}, {1., 0.5}, {0.5, 0.5} },
		{ {0.75, 0.}, {1., 0.5}, {0.5, 0.5} },
		{ {0.75, 0.}, {1., 0.5}, {0.5, 0.5} },
		/*{{0.333, 0.2}, {0.667, 0.2}, {0.667, 0.5}, {0.333, 0.5} },
		{{0.333, 0.2}, {0.667, 0.2}, {0.667, 0.5}, {0.333, 0.5} },
		{{0.333, 0.2}, {0.667, 0.2}, {0.667, 0.5}, {0.333, 0.5} },
		{{0.333, 0.2}, {0.667, 0.2}, {0.667, 0.5}, {0.333, 0.5} },*/
	};

static const Model madhouse_model {
	madhouse_vertices,
	madhouse_faces,
	madhouse_normals,
	madhouse_tc
};

void draw_model(const Model& m)
{
	for (size_t face = 0; face < m.faces.size(); face++) {
		size_t nv = m.faces[face].size();
		if (nv == 3) glBegin(GL_TRIANGLES);
		else if (nv == 4) glBegin(GL_QUADS);
		else glBegin(GL_TRIANGLE_FAN);
		glNormal3dv(&m.normals[face][0]);
		for (size_t v = 0; v < nv; v++) {
			size_t vi = m.faces[face][v];
			glTexCoord2dv(&m.texcoords[face][v][0]);
			glVertex3dv(&m.vertices[vi][0]);
		}

		glEnd();
	}
}

void MyWindow::setup_gl()
{
//	glClearColor(0.2f, 0.1f, 0.8f, 1.0f);
	glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 800./600., 0.1, 120.0);
	glMatrixMode(GL_MODELVIEW);
}

void MyWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(10, 15, 6, 0, 0, 1, 0, 0, 1);

	static double a = 0;
	a += 0.1;

	glRotated(a, 0., 0., 1.0);

	glEnable(GL_TEXTURE_2D);
	_madhouse_texture.bind();

	glBegin(GL_QUADS);
	glNormal3d(0., 0., 1.);
	glTexCoord2d(0.333, 0.5); glVertex3d(-30., -30., 0.);
	glTexCoord2d(0.667, 0.5);glVertex3d(30., -30., 0.);
	glTexCoord2d(0.667, 0.7); glVertex3d(30., 30., 0.);
	glTexCoord2d(0.333, 0.7); glVertex3d(-30., 30., 0.);
	glEnd();
	glPushMatrix();

	glTranslated(0., 0., 0.);

	draw_model(madhouse_model);
	glPopMatrix();

	/*for (int i = -4; i <= 4; i++)
		for (int j = -4; j <= 4; j++) {
			glPushMatrix();

			glTranslated(5.3 * i, 5.3 * j, 0.);

			draw_model(madhouse_model);
			glPopMatrix();
		}*/

}



