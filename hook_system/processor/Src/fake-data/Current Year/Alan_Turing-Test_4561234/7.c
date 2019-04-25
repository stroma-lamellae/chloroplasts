#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	double x;
	double y;
	double z;
} point_t;

typedef struct
{
	point_t p0;
	point_t p1;
	point_t p2;
} plane_t;

double det_2x2(double matrix[2][2])
{
	return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

double det_3x3(double matrix[3][3])
{
	double a[2][2],b[2][2],c[2][2];
	a[0][0]=matrix[1][1];
	a[0][1]=matrix[1][2];
	a[1][0]=matrix[2][1];
	a[1][1]=matrix[2][2];
	b[0][0]=matrix[1][0];
	b[0][1]=matrix[1][2];
	b[1][0]=matrix[2][0];
	b[1][1]=matrix[2][2];
	c[0][0]=matrix[1][0];
	c[0][1]=matrix[1][1];
	c[1][0]=matrix[2][0];
	c[1][1]=matrix[2][1];
	return matrix[0][0]*det_2x2(a) - matrix[0][1]*det_2x2(b) + matrix[0][2]*det_2x2(c);
}

double det_4x4(double matrix[4][4])
{
	double a[3][3],b[3][3],c[3][3],d[3][3];
	a[0][0] = matrix[1][1];
	a[0][1] = matrix[1][2];
	a[0][2] = matrix[1][3];
	a[1][0] = matrix[2][1];
	a[1][1] = matrix[2][2];
	a[1][2] = matrix[2][3];
	a[2][0] = matrix[3][1];
	a[2][1] = matrix[3][2];
	a[2][2] = matrix[3][3];
        b[0][0] = matrix[1][0];
        b[0][1] = matrix[1][2];
        b[0][2] = matrix[1][3];
        b[1][0] = matrix[2][0];
        b[1][1] = matrix[2][2];
        b[1][2] = matrix[2][3];
        b[2][0] = matrix[3][0];
        b[2][1] = matrix[3][2];
        b[2][2] = matrix[3][3];
        c[0][0] = matrix[1][0];
        c[0][1] = matrix[1][1];
        c[0][2] = matrix[1][3];
        c[1][0] = matrix[2][0];
        c[1][1] = matrix[2][1];
        c[1][2] = matrix[2][3];
        c[2][0] = matrix[3][0];
        c[2][1] = matrix[3][1];
        c[2][2] = matrix[3][3];
        d[0][0] = matrix[1][0];
        d[0][1] = matrix[1][1];
        d[0][2] = matrix[1][2];
        d[1][0] = matrix[2][0];
        d[1][1] = matrix[2][1];
        d[1][2] = matrix[2][2];
        d[2][0] = matrix[3][0];
        d[2][1] = matrix[3][1];
        d[2][2] = matrix[3][2];
	return matrix[0][0]*det_3x3(a) - matrix[0][1]*det_3x3(b) + matrix[0][2]*det_3x3(c) - matrix[0][3]*det_3x3(d);
}

point_t plane_line_intersect(plane_t *plane, point_t *x0, point_t *x1)
{
	double num[4][4];
	double den[4][4];
	double i,j,t;
	point_t intersection;
	num[0][0] = 1;
	num[0][1] = 1;
	num[0][2] = 1;
	num[0][3] = 1;
	num[1][0] = plane->p0.x;
	num[1][1] = plane->p1.x;
	num[1][2] = plane->p2.x;
	num[1][3] = x0->x;
	num[2][0] = plane->p0.y;
	num[2][1] = plane->p1.y;
	num[2][2] = plane->p2.y;
	num[2][3] = x0->y;
	num[3][0] = plane->p0.z;
	num[3][1] = plane->p1.z;
	num[3][2] = plane->p2.z;
	num[3][3] = x0->z;
	den[0][0] = 1;
	den[0][1] = 1;
	den[0][2] = 1;
	den[0][3] = 0;
	den[1][0] = plane->p0.x;
	den[1][1] = plane->p1.x;
	den[1][2] = plane->p2.x;
	den[1][3] = x1->x - x0->x;
	den[2][0] = plane->p0.y;
	den[2][1] = plane->p1.y;
	den[2][2] = plane->p2.y;
	den[2][3] = x1->y - x0->y;
	den[3][0] = plane->p0.z;
	den[3][1] = plane->p1.z;
	den[3][2] = plane->p2.z;
	den[3][3] = x1->z - x0->z;
	i = det_4x4(num);
	j = det_4x4(den);
	if (j == 0)			//No intersection (line is parallel to the plane)
	{
		intersection.x = INFINITY;
		intersection.y = INFINITY;
		intersection.z = INFINITY;
	}
	else
	{
		t = (i / j)*(-1);
		intersection.x = x0->x + (x1->x - x0->x)*t;
		intersection.y = x0->y + (x1->y - x0->y)*t;
		intersection.z = x0->z + (x1->z - x0->z)*t;
	}
	return intersection;
}

double dot(point_t *a, point_t *b)
{
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

point_t cross(point_t *a, point_t *b)
{
	point_t cross;
	cross.x = (a->y * b->z) - (a->z * b->y);
	cross.y = (a->z * b->x) - (a->x * b->z);
	cross.z = (a->x * b->y) - (a->y * b->x);
	return cross;
}

double norm2(point_t *a)
{
	point_t n;
	n.x = (a->x)*(a->x);
	n.y = (a->y)*(a->y);
	n.z = (a->z)*(a->z);
	return sqrt(n.x + n.y + n.z);
}

point_t difference(point_t *a, point_t *b)
{
	point_t diff;
	diff.x = b->x - a->x;
	diff.y = b->y - a->y;
	diff.z = b->z - a->z;
	return diff;
}

point_t midpoint(point_t *a, point_t *b)
{
	point_t mid;
	mid.x = (a->x + b->x)/2;
	mid.y = (a->y + b->y)/2;
	mid.z = (a->z + b->z)/2;
	return mid;
}

double surface_area(point_t *a, point_t *b, point_t *c)
{
	point_t ab,ac,bh;
	double s;
	ab = difference(a,b);
	ac = difference(a,c);
	bh = cross(&ab,&ac);
	s = norm2(&bh)/2;
	return s;
}

int main(int argc, char** argv)
{
	point_t light;
	point_t tri_a, tri_b, tri_c;
	plane_t plane;
	point_t pro_a, pro_b, pro_c;
	double area;
	fscanf(stdin,"%lf %lf %lf",&light.x,&light.y,&light.z);
	fscanf(stdin,"%lf %lf %lf",&tri_a.x,&tri_a.y,&tri_a.z);
	fscanf(stdin,"%lf %lf %lf",&tri_b.x,&tri_b.y,&tri_b.z);
	fscanf(stdin,"%lf %lf %lf",&tri_c.x,&tri_c.y,&tri_c.z);
	fscanf(stdin,"%lf %lf %lf",&plane.p0.x,&plane.p0.y,&plane.p0.z);
        fscanf(stdin,"%lf %lf %lf",&plane.p1.x,&plane.p1.y,&plane.p1.z);
        fscanf(stdin,"%lf %lf %lf",&plane.p2.x,&plane.p2.y,&plane.p2.z);
	pro_a = plane_line_intersect(&plane,&light,&tri_a);
	pro_b = plane_line_intersect(&plane,&light,&tri_b);
	pro_c = plane_line_intersect(&plane,&light,&tri_c);
	area = surface_area(&pro_a,&pro_b,&pro_c);
	fprintf(stdout,"%.3lf",area);
	return 0;
}