#include <stdlib.h>
#include <stdio.h>
#include "../lib/easysdl.h"
#include "physics/raytrace.h"
#include "maths/vec2d.h"
#include "world/world.h"
#include <math.h>

#define ARROW 0x40000000

int main()
{
	int height = 64;
	EZ_creation_fenetre(" ", 256, 64);
	printf("Hello, World!\n");
	Line2D a;
	Line2D b;
	Line2D c;

	a.pos.x = 0;
	a.pos.y = 0;
	a.vec.x = 1;
	a.vec.y = 0;
	a.length = 1;

	b.pos.x = 0;
	b.pos.y = 0;
	b.vec.x = 0;
	b.vec.y = 1;
	b.length = 1;

	c.pos.x = 0;
	c.pos.y = 1;
	c.vec.x = -sqrt(2) / 2;
	c.vec.y = -sqrt(2) / 2;
	c.length = .5;

	MaybePosition2D pos = intersect2D(a, b);

	printf("%s (%lf, %lf)\n", (pos.success ? "true" : "false"), pos.pos.x, pos.pos.y);

	pos = intersect2D(a, c);

	printf("%s (%lf, %lf)\n", (pos.success ? "true" : "false"), pos.pos.x, pos.pos.y);

	pos = intersect2D(c, b);

	printf("%s (%lf, %lf)\n", (pos.success ? "true" : "false"), pos.pos.x, pos.pos.y);

	Lines lines;
	lines.lines = (Line2D*)malloc(sizeof(Line2D) * 3);
	lines.length = 3;
	// copy the values in the allocated memory
	lines.lines[0] = a;
	lines.lines[1] = b;
	lines.lines[2] = c;
	double x = -1;
	double y = 0.5;
	double angle = 0;
	bool exit = false;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool rleft = false;
	bool rright = false;

	bool drag = false;
	int drag_x = 0;

	while (!exit) {
		for (int i = 0; i < 256; i++) {
			double a = angle + ((double)(i + (drag ? -EZ_souris_x() + drag_x : 0)) / 128 - 1) * .5;
			Line2D ray;
			ray.length = 100;
			ray.pos.x = x;
			ray.pos.y = y;
			ray.vec.x = cos(a);
			ray.vec.y = sin(a);
			RayIntersection r = cast_ray(lines, ray);
			int red = (r.index == 0) * 255;
			int green = (r.index == 1) * 255;
			int blue = (r.index == 2) * 255;
			int d = height / dist(ray.pos, r.pos.pos) / 2;
			EZ_trace_rectangle_plein(i, 0, i + 1, 64, 0, 0, 0, 255);
			if (r.pos.success) {
				EZ_trace_rectangle_plein(i, height / 2 - d, i + 1, d * 2, red, green, blue, 255);
			}
		}
		EZ_mise_a_jour();
		int evt = 1;
		while (evt = EZ_recupere_evenement_continu()) {
			if (evt == EZ_EXIT) exit = true;
			if (evt == EZ_TOUCHE_ENFONCEE || evt == EZ_TOUCHE_RELACHEE) {
				bool state = evt == EZ_TOUCHE_ENFONCEE;
				switch (EZ_touche()) {
					case ARROW | 0x52:
					case 'w':
						up = state;
						break;
					case ARROW | 0x50:
						rleft = state;
						break;
					case ARROW | 0x4f:
						rright = state;
						break;
					case ARROW | 0x51:
					case 's':
						down = state;
						break;
					case 'd':
						right = state;
						break;
					case 'a':
						left = state;
						break;
				}
			}
			if (evt == EZ_SOURIS_BOUTON_GAUCHE_ENFONCE) {
				drag_x = EZ_souris_x();
				drag = true;
			}
			else if (evt == EZ_SOURIS_BOUTON_GAUCHE_RELACHE) {
				drag = false;
				angle -= ((double)(EZ_souris_x() - drag_x) / 128) * .5;
			}
		}
		if (up) {
			x += .007 * cos(angle);
			y += .007 * sin(angle);
		}
		if (down) {
			x -= .007 * cos(angle);
			y -= .007 * sin(angle);
		}
		if (right) {
			x -= .005 * sin(angle);
			y += .005 * cos(angle);
		}
		if (left) {
			x += .005 * sin(angle);
			y -= .005 * cos(angle);
		}
		if (rright) angle += .004;
		if (rleft) angle -= .004;
	}

	return 0;
}
