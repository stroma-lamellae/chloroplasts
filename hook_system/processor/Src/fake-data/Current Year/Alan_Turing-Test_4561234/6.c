#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	double x;	//X position
	double y;	//Y position
}point_t;

typedef struct
{
	point_t p;	//Point data
	double m;	//Mass
}node_t;

int get_tree_size(int recursion_level)
{
	int t = 3, n = 2, c = 2;
	if (recursion_level == 0)
	{
		t = 1;
	}
	else if (recursion_level == 1)
	{
		t = 3;
	}
	else
	{
		for (n = 2; n <= recursion_level; n++)
		{
			t += n*c;
			c *= n;
		}
	}
	return t;
}

int get_tree_depth(int size)
{
	int t = 3, n = 2, c = 2, d = 0;
	if (size <=1)
	{
		d = 0;
	}
	else if (size <= 3)
		d = 1;
	else
	{
		d = 1;
		while (t < size)
		{
			t += n*c;
			c *= n;
			n++;
			d++;
		}
	}
	return d;
}
point_t centre_of_mass(node_t *nodes, int num)
{
	int i = 0;
	double  m = 0, x = 0, y = 0;
	point_t c;
	c.x = 0.0;
	c.y = 0.0;
	for (i = 0; i<num; i++)
	{
		m += (nodes+i)->m;
		x = (nodes + i)->p.x;
		y = (nodes + i)->p.y;
		c.x += ((nodes+i)->m)*x;
		c.y += ((nodes+i)->m)*y;
	}
	c.x = c.x / m;
	c.y = c.y / m;
	return c;
}

int get_level_offset(int recursion_level)
{
	int o = 0, n = 2, c = 2;
	if (recursion_level == 0)
	{
		o = 0;
	}
	else if (recursion_level == 1)
	{
		o = 1;
	}
	else if (recursion_level == 2)
	{
		o = 3;
	}
	else
	{
		o = 3;
		for (n = 2;n < recursion_level;n++)
		{
			o += n * c;
			c *= n;
			n++;
		}
	}
	return o;
}

void calc_position(node_t *nodes, int child_number, int recursion_depth, int recursion_level, double mount_theta)
{
	int i = 0,n = 0, offset = 0;
	double theta_spacing = 0.0, parent_theta = 0.0, child_theta = 0.0;
	node_t *self;
	parent_theta = mount_theta + M_PI;			//Adjust mount_theta perspective from that of the parent to that of the child
	if (parent_theta > 2 * M_PI)
	{
		parent_theta -= 2*M_PI;				//Angle wraps around
	}
	n = recursion_level + 2;
	theta_spacing = (2 * M_PI) / n;
	offset = get_level_offset(recursion_level+1) + child_number*(n-1);	//Location to start placing children
	self = (nodes + get_level_offset(recursion_level) + child_number);
	for (i = 0; i < n-1; i++)				//n-1 children per node
	{
		child_theta = parent_theta + ((i+1) * theta_spacing);
		(nodes + offset + i)->p.x = self->p.x + cos(child_theta);
		(nodes + offset + i)->p.y = self->p.y + sin(child_theta);
		if (recursion_level < recursion_depth - 1)
		{
			if (child_theta > 2*M_PI)
				child_theta -= 2*M_PI;
			calc_position(nodes,child_number * (n-1) + i,recursion_depth,recursion_level+1,child_theta);
		}
	}
	return;
}

int main(int argc, char** argv)
{
	int i= 0, num = 0, size = 0, depth = 0;
	point_t com;
	node_t *nodes;
	fscanf(stdin,"%d",&num);
	depth = get_tree_depth(num);			//Calculate the depth of a tree with num nodes
	size = get_tree_size(depth);			//Calculate the size of a tree with num nodes
	nodes = malloc(sizeof(node_t) * size);		//Create a full tree of the necessary depth
	memset(nodes,0,sizeof(node_t) * size);		//Zero out the tree (this is important to avoid potential errors because not all elements are explicitly initialized)
	for (i = 0; i < num; i++)
	{
		fscanf(stdin,"%lf",&((nodes + i)->m));	//Scan in the masses. If the addressing was setup properly, they can be scanned in linearly
	}
	(nodes + 1)->p.x = cos(0);			//Initialize the positions of the first two children
	(nodes + 1)->p.y = sin(0);
	(nodes + 2)->p.x = cos(M_PI);
	(nodes + 2)->p.y = sin(M_PI);
	calc_position(nodes,0,depth,1,0);		//Start the recursive algorithm on both halves of the tree
	calc_position(nodes,1,depth,1,M_PI);
	com = centre_of_mass(nodes,size);		//Calculate the center of mass of the tree
	printf("%.3lf %.3lf",com.x,com.y);
	return 0;
}