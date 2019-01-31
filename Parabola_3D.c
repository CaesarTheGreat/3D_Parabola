#include <stdio.h>
#include <string.h>
#include <math.h>

int intersect_check();
void cube(double p_one[][3], double p_two[][3], double p_three[][3], FILE *file);
double magnitude(double number);			//Finds magnitude for mathematical work
double Nx(double Vy, double Wz, double Vz, double Wy);
double Ny(double Vz, double Wx, double Vx, double Wz);
double Nz(double Vx, double Wy, double Vy, double Wx);
double Ax(double Nx, double Ny, double Nz);
double Ay(double Nx, double Ny, double Nz);
double Az(double Nx, double Ny, double Nz);	//All of this is for the formula to determine the normal facet
double point_distance();
double parabola_y(double z);
//double parabola_x(double z);
double y_neg(double z);
double y_pos(double z);
double tri_y_pos(double z, double angle);
double tri_x_pos(double z, double angle);
double tri_x_neg(double z, double angle);
double real_distance(double Ax, double Ay, double Bx, double By);

		double a;
		double b;
		double c;
		double m;
		double d;
		double cut;
		double tri_angle;
		int cuts[11];
		int cut_num;
		int resolution;

void triangle_print(FILE *file);
void rectangular_print(FILE *file);
void square_print(FILE *file);

int main(int argc, char **argv)
{
	char stl[] = ".stl";
	char type[20];	
	char file[101];					//suffix for filename, will be .stl regardless
	printf("please enter the name of the type of shape you would like to create:\n\trectangular\n\ttriangular\n\tsquare\n");
	scanf("%19s", type);
	printf("please enter the name of the file to make: (exclude any extensions such as .stl\n");
	scanf("%50s", file);

	strcat(file, stl);										//with file that information will be read from and interpereted from)
											//combines prefix and suffix for final file name
	FILE *r = fopen(file, "w");		//creates and opens file by the name of the one created before
	char cube_test[20] = "cube";
	char rectangular_test[20] = "rectangular";
	char triangle_test[20] = "triangular";
	char square_test[20] = "square";

	if(strcmp(type,rectangular_test) == 0)
	{
		//get parabola information and interpolate that into a square matrix for writing to .stl
		
		printf("Parabola: y = ax^2 + bx + c\nPlease enter your value for a:\n");
		scanf("%lf", &a);
		printf("\nPlease enter your value for b:\n");
		scanf("%lf", &b);
		printf("\nPlease enter your value for c:\n");
		scanf("%lf", &c);
		printf("\nIntersecting Line: y = mx + b\nPlease enter your value for m: \n(currently only slope 0 compatable)\n");
		scanf("%lf", &m);
		printf("\nPlease enter your value for b:\n");
		scanf("%lf", &d);
		printf("\nPlease enter the resolution you would like:\n(must be above 20 at least)\n");
		scanf("%d", &resolution);
		if(resolution < 20)
		{
			printf("\nresolution can be no less than 20\n");
			return 1;
		}
		printf("\nPlease enter the number of cuts between 0 and 10 you would like to make:\n");
		scanf("%d", &cut_num);
		if(cut_num > 10 || cut_num < 0)
		{
			printf("\nno more than 10 cuts or less than 0\n");
			return 1;
		}
		int i;
		for(i = 0; i < cut_num; i++)
		{
			int print = i + 1;
			printf("\nPlease enter the cut for layer %d:\n(enter in order from least to greatest)\n", print);
			scanf("%d", &cuts[i]);
			if(cuts[i] > resolution)
			{
				printf("\ncut larger than resolution\n");
				return 1;
			}
		}
		//Checking for imaginary numbers (lines don't intersect);
		if(intersect_check() == 0)
		{
			printf("error: line does not intersect\n");
			fclose(r);
			int rem = remove(file);
			return 1;
		}
		else if(intersect_check() == 2)
		{
			printf("Sorry, only slope of 0 is compatable at this time\n");
			fclose(r);
			int rem = remove(file);
			return 1;
		}
		rectangular_print(r);
		fclose(r);
		return 0;

	}
	else if(strcmp(type,triangle_test) == 0)
	{
		//get parabola information and interpolate that into a triangular matrix for writing to .stl

		printf("Parabola: y = ax^2 + bx + c\nPlease enter your value for a:\n");
		scanf("%lf", &a);
		printf("\nPlease enter your value for b:\n");
		scanf("%lf", &b);
		printf("\nPlease enter your value for c:\n");
		scanf("%lf", &c);
		printf("\nIntersecting Line: y = mx + b\nPlease enter your value for m: \n(currently only slope 0 compatable)\n");
		scanf("%lf", &m);
		printf("\nPlease enter your value for b:\n");
		scanf("%lf", &d);
		printf("\nPlease enter your value for the angle of the triangle: \n(between 0 and 90)\n");
		scanf("%lf", &tri_angle);
		printf("\nPlease enter the resolution you would like:\n(must be above 20 at least)\n");
		scanf("%d", &resolution);
		if(resolution < 20)
		{
			printf("\nresolution can be no less than 20\n");
			return 1;
		}
		printf("\nPlease enter the number of cuts between 0 and 10 you would like to make:\n");
		scanf("%d", &cut_num);
		if(cut_num > 10 || cut_num < 0)
		{
			printf("\no more than 10 cuts or less than 0\n");
			return 1;
		}
		int i;
		for(i = 0; i < cut_num; i++)
		{
			int print = i + 1;
			printf("\nPlease enter the cut for layer %d:\n(enter in order from least to greatest)\n", print);
			scanf("%d", &cuts[i]);
			if(cuts[i] > resolution)
			{
				printf("\ncut larger than resolution\n");
				return 1;
			}
		}
		//Checking for imaginary numbers(lines don't intersect)
		if(tri_angle >=90 || tri_angle <= 0)
		{
			printf("the angle of the triangle must be between 0 and 90\n");
			fclose(r);
			int rem = remove(file);
			return 1;
		}
		if(intersect_check() == 0)
		{
			printf("error: line does not intersect\n");
			fclose(r);
			int rem = remove(file);
			return 1;
		}
		else if(intersect_check() == 2)
		{
			printf("Sorry, only slope of 0 is compatable at this time\n");
			fclose(r);
			int rem = remove(file);
			return 1;
		}
		triangle_print(r);	//insert print function and close file function here
		fclose(r);
		return 0;
	}
	else if(strcmp(type,cube_test) == 0)
	{
		//Use cube example from previous test
		double p_one[][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,1,0},{0,1,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,1},{0,0,1}};
		double p_two[][3] = {{1,1,0},{0,1,0},{0,1,1},{0,0,1},{1,1,1},{0,1,1},{1,1,0},{1,1,1},{1,0,0},{1,0,1},{1,0,1},{1,1,1}};
		double p_three[][3] = {{1,0,0},{1,1,0},{0,1,0},{0,1,1},{1,1,0},{1,1,1},{1,1,1},{1,0,1},{1,0,1},{0,0,1},{1,1,1},{0,1,1}};
		cube(p_one, p_two, p_three, r);
	}
	else if(strcmp(type,square_test) == 0)
	{
		//get parabola information and interpolate that into a triangular matrix for writing to .stl

		printf("Parabola: y = ax^2 + bx + c\nPlease enter your value for a:\n");
		scanf("%lf", &a);
		printf("\nPlease enter your value for b:\n");
		scanf("%lf", &b);
		printf("\nPlease enter your value for c:\n");
		scanf("%lf", &c);
		printf("\nIntersecting Line: y = mx + b\nPlease enter your value for m: \n(currently only slope 0 compatable)\n");
		scanf("%lf", &m);
		printf("\nPlease enter your value for b:\n");
		scanf("%lf", &d);
		printf("\nPlease enter the resolution you would like:\n(must be above 20 at least)\n");
		scanf("%d", &resolution);
		if(resolution < 20)
		{
			printf("\nresolution can be no less than 20\n");
			return 1;
		}
		printf("\nPlease enter the number of cuts between 0 and 10 you would like to make:\n");
		scanf("%d", &cut_num);
		if(cut_num > 10 || cut_num < 0)
		{
			printf("\nno more than 10 cuts or less than 0\n");
			return 1;
		}
		int i;
		for(i = 0; i < cut_num; i++)
		{
			int printer = i + 1;
			printf("\nPlease enter the cut for layer %d:\n(enter in order from least to greatest)\n", printer);
			scanf("%d", &cuts[i]);
			if(cuts[i] > resolution)
			{
				printf("\ncut larger than resolution\n");
				return 1;
			}
		}
		//Checking for imaginary numbers(lines don't intersect)
		if(intersect_check() == 0)
		{
			printf("error: line does not intersect\n");
			fclose(r);
			int rem = remove(file);
			return 1;
		}
		else if(intersect_check() == 2)
		{
			printf("Sorry, only slope of 0 is compatable at this time\n");
			fclose(r);
			int rem = remove(file);
			return 1;
		}
	//insert print function and close fiile function here
	square_print(r);
	fclose(r);
	return 0;
	}
	else
	{
		printf("type not recognized\n\nrecognized types:\n\trectangular\n\ttriangular\n\tsquare\n");
		fclose(r);
		int rem = remove(file);
		return 1;
	}
	
}

void triangle_print(FILE *file)
{
	double A = a;
	double B = b - m;
	double C = c - d;
	double AC = A * C;
	double ACfour = AC * 4;
	double B_squared = B * B;
	double under_sqrt;
	if(ACfour >= 0)
	{
		under_sqrt = B_squared - ACfour;
	}
	else if(ACfour < 0)
	{
		double four_ac_squared = ACfour * ACfour;
		ACfour = sqrt(four_ac_squared);
		under_sqrt = B_squared + ACfour;
	}
	
	double the_sqrt = sqrt(under_sqrt);
	double negative = -B - the_sqrt;
	double positive = -B + the_sqrt;
	double two_A = A * 2;
	double quad_negative = negative / two_A;
	double quad_positive = positive / two_A;
	
	double Az_end;
	double Bz_end;
	if(quad_positive > quad_negative)
	{
		Az_end = quad_positive;
		Bz_end = quad_negative;
	}
	else if(quad_negative > quad_positive)
	{
		Az_end = quad_negative;
		Bz_end = quad_positive;
		
	}
	
	double Z_spacing = point_distance() / resolution;
	double cut_spacing = point_distance() / 20;
	double cut_spacer = 0;
	double z_space = Az_end;
	double half = point_distance() / 2;
	double middle = Az_end - half;
	double middle_height = y_pos(middle);
	double spacer = 0;	
	int real_resolution = resolution - 1;
	int cut_iteration = 0;

	char solid[] = "solid";
	char new_line[] = "\n";
	char tab[] = "\t";
	char space[] = " ";
	char facet_normal[] = "facet normal";
	char outer_loop[] = "outer loop";
	char vertex[] = "vertex";
	char endloop[] = "endloop";
	char endfacet[] = "endfacet";
	char endsolid[] = "endsolid";
	//fputs for these: fputs(object, filename)
	//fprintf for the points: fprintf(filename, "%f", object)
	int i;
	
	fputs(solid, file);
	fputs(new_line, file);
	
	printf("\nDeveloper Diagnostics:\n\n");
	printf("a = %f\nb = %f\nc = %f\nd = %f\nm = %f\n", a, b, c, d, m);
	printf("\nQuadratic one = %f\nQuadratic two = %f\n", quad_negative, quad_positive);
	printf("\nZ_spacing = %f\nz_space = %f\npoint_distance = %f\n", Z_spacing, z_space, point_distance());
	printf("\ny_neg(z_space + Z_spacing) = %f\ny_pos(z_space + Z_spacing) = %f\nmiddle height = %f\n", y_neg(z_space + Z_spacing), y_pos(z_space + Z_spacing), middle_height);
	printf("\nUnder sqrt = %f\nACfour = %f\n", under_sqrt, ACfour);
	printf("\nAz should be larger: Az = %f Bz = %f\n", Az_end, Bz_end);
	printf("\nA = %f B = %f C = %f 4(A)(C) = %f negative = %f positive = %f\n", A, B, C, ACfour, negative, positive);
	
	for(i = 0; i < resolution; i ++)
	{
		z_space = z_space - Z_spacing;
		double z_start = z_space + Z_spacing;
		if(i == cuts[cut_iteration] && cut_num != 0 && cuts[cut_iteration] != real_resolution)
		{
			cut_iteration++;
			int c;
			for(c = 0; c < 2; c++)
			{
				if(c == 1)
				{
					cut_spacer = cut_spacer + cut_spacing;
				}
				int n;
				for(n = 0; n < 1; n++)
				{
				double points[6][3] = {{tri_x_neg(z_start, tri_angle), 0, z_start - cut_spacer},{0, tri_y_pos(z_start, tri_angle), z_start - cut_spacer},{tri_x_pos(z_start, tri_angle),0,z_start - cut_spacer},{tri_x_neg(z_space, tri_angle), 0, z_space - cut_spacer},{0, tri_y_pos(z_space, tri_angle), z_space - cut_spacer},{tri_x_pos(z_space, tri_angle), 0, z_space - cut_spacer}};
				
				//int rotate[3][8] = {{0,1,1,2,2,3,3,0},{4,0,5,1,6,2,7,3},{5,5,6,6,7,7,4,4}};
				int rotate[2][3][1] = {{{0},{1},{2}},{{0},{2},{1}}};
				double Vx = points[rotate[c][1][n]][0] - points[rotate[c][0][n]][0];
				double Vy = points[rotate[c][1][n]][1] - points[rotate[c][0][n]][1];
				double Vz = points[rotate[c][1][n]][2] - points[rotate[c][0][n]][2];
				double Wx = points[rotate[c][2][n]][0] - points[rotate[c][0][n]][0];
				double Wy = points[rotate[c][2][n]][1] - points[rotate[c][0][n]][1];
				double Wz = points[rotate[c][2][n]][2] - points[rotate[c][0][n]][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][2][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
				}
			}
		}
		//Each row
		if(i == 0)
		{	
			//First Point
			int n;
			for(n = 0; n < 3; n ++)
			{
				double points[4][3] = {{0,0,Az_end}, {tri_x_neg(z_space, tri_angle), 0, z_space}, {0, tri_y_pos(z_space, tri_angle), z_space}, {tri_x_pos(z_space, tri_angle), 0, z_space}};
				
				//int rotate[2][4] = {{1,2,3,4},{2,3,4,1}};
				int rotate[2][3] = {{2,3,1},{1,2,3}};
				double Vx = points[rotate[0][n]][0] - points[0][0];
				double Vy = points[rotate[0][n]][1] - points[0][1];
				double Vz = points[rotate[0][n]][2] - points[0][2];
				double Wx = points[rotate[1][n]][0] - points[0][0];
				double Wy = points[rotate[1][n]][1] - points[0][1];
				double Wz = points[rotate[1][n]][2] - points[0][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[0][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
			continue;
		}
		else if(i == real_resolution)
		{
			if(cut_num != 0)
			{
				cut_spacer = cut_spacing * cut_num;
			}
			//Final point
			int n;
			for(n = 0; n < 3; n ++)
			{
				double points[4][3] = {{0,0,Bz_end - cut_spacer}, {tri_x_neg(z_start, tri_angle), 0, z_start - cut_spacer}, {0, tri_y_pos(z_start, tri_angle), z_start - cut_spacer}, {tri_x_pos(z_start, tri_angle), 0, z_start - cut_spacer}};
				
				//int rotate[2][4] = {{2,3,4,1},{1,2,3,4}};
				int rotate[2][3] = {{1,2,3},{2,3,1}};
				double Vx = points[rotate[0][n]][0] - points[0][0];
				double Vy = points[rotate[0][n]][1] - points[0][1];
				double Vz = points[rotate[0][n]][2] - points[0][2];
				double Wx = points[rotate[1][n]][0] - points[0][0];
				double Wy = points[rotate[1][n]][1] - points[0][1];
				double Wz = points[rotate[1][n]][2] - points[0][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[0][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
		}
		else
		{
			int n;
			for(n = 0; n <6; n++)
			{
				double points[6][3] = {{tri_x_neg(z_start, tri_angle), 0, z_start - cut_spacer},{0, tri_y_pos(z_start, tri_angle), z_start - cut_spacer},{tri_x_pos(z_start, tri_angle),0,z_start - cut_spacer},{tri_x_neg(z_space, tri_angle), 0, z_space - cut_spacer},{0, tri_y_pos(z_space, tri_angle), z_space - cut_spacer},{tri_x_pos(z_space, tri_angle), 0, z_space - cut_spacer}};
				
				//int rotate[3][8] = {{0,1,1,2,2,3,3,0},{4,0,5,1,6,2,7,3},{5,5,6,6,7,7,4,4}};
				int rotate[3][6] = {{0,1,1,2,2,2},{4,4,5,5,0,3},{3,0,4,1,3,5}};
				double Vx = points[rotate[1][n]][0] - points[rotate[0][n]][0];
				double Vy = points[rotate[1][n]][1] - points[rotate[0][n]][1];
				double Vz = points[rotate[1][n]][2] - points[rotate[0][n]][2];
				double Wx = points[rotate[2][n]][0] - points[rotate[0][n]][0];
				double Wy = points[rotate[2][n]][1] - points[rotate[0][n]][1];
				double Wz = points[rotate[2][n]][2] - points[rotate[0][n]][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[2][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
		}
	}
	
	 
	fputs(endsolid, file);
}

void rectangular_print(FILE *file)
{
	//Works with numbers to get the starting and ending points
	double A = a;
	double B = b - m;
	double C = c - d;
	double AC = A * C;
	double ACfour = AC * 4;
	double B_squared = B * B;
	double under_sqrt;
	if(ACfour >= 0)
	{
		under_sqrt = B_squared - ACfour;
	}
	else if(ACfour < 0)
	{
		double four_ac_squared = ACfour * ACfour;
		ACfour = sqrt(four_ac_squared);
		under_sqrt = B_squared + ACfour;
	}
	
	double the_sqrt = sqrt(under_sqrt);
	double negative = -B - the_sqrt;
	double positive = -B + the_sqrt;
	double two_A = A * 2;
	double quad_negative = negative / two_A;
	double quad_positive = positive / two_A;
	
	double Az_end;
	double Bz_end;
	if(quad_positive > quad_negative)
	{
		Az_end = quad_positive;
		Bz_end = quad_negative;
	}
	else if(quad_negative > quad_positive)
	{
		Az_end = quad_negative;
		Bz_end = quad_positive;
		
	}
	
	double Z_spacing = point_distance() / resolution;
	double cut_spacing = point_distance() / 20;
	double cut_spacer = 0;
	double z_space = Az_end;
	double half = point_distance() / 2;
	double middle = Az_end - half;
	double middle_height = y_pos(middle);
	double spacer = 0;	
	int real_resolution = resolution - 1;
	int cut_iteration = 0;
	
	char solid[] = "solid";
	char new_line[] = "\n";
	char tab[] = "\t";
	char space[] = " ";
	char facet_normal[] = "facet normal";
	char outer_loop[] = "outer loop";
	char vertex[] = "vertex";
	char endloop[] = "endloop";
	char endfacet[] = "endfacet";
	char endsolid[] = "endsolid";
	//fputs for these: fputs(object, filename)
	//fprintf for the points: fprintf(filename, "%f", object)
	int i;
	
	fputs(solid, file);
	fputs(new_line, file);
	
	printf("\nDeveloper Diagnostics:\n\n");
	printf("a = %f\nb = %f\nc = %f\nd = %f\nm = %f\n", a, b, c, d, m);
	printf("\nQuadratic one = %f\nQuadratic two = %f\n", quad_negative, quad_positive);
	printf("\nZ_spacing = %f\nz_space = %f\npoint_distance = %f\n", Z_spacing, z_space, point_distance());
	printf("\ny_neg(z_space + Z_spacing) = %f\ny_pos(z_space + Z_spacing) = %f\nmiddle height = %f\n", y_neg(z_space + Z_spacing), y_pos(z_space + Z_spacing), middle_height);
	printf("\nUnder sqrt = %f\nACfour = %f\n", under_sqrt, ACfour);
	printf("\nAz should be larger: Az = %f Bz = %f\n", Az_end, Bz_end);
	printf("\nA = %f B = %f C = %f 4(A)(C) = %f negative = %f positive = %f\n", A, B, C, ACfour, negative, positive);
	
	for(i = 0; i < resolution; i ++)
	{
		z_space = z_space - Z_spacing;
		double z_start = z_space + Z_spacing;
		if(i == cuts[cut_iteration] && cut_num != 0 && cuts[cut_iteration] != real_resolution)
		{
			cut_iteration++;
			int c;
			for(c = 0; c < 2; c++)
			{
				if(c == 1)
				{
					cut_spacer = cut_spacer + cut_spacing;
				}
				int n;
				for(n = 0; n < 2; n++)
				{
				double points[8][3] = {{y_neg(z_start), 0, z_start - cut_spacer},{y_neg(z_start), y_pos(z_start), z_start - cut_spacer},{y_pos(z_start), y_pos(z_start), z_start - cut_spacer},{y_pos(z_start),0,z_start - cut_spacer},{y_neg(z_space), 0, z_space - cut_spacer},{y_neg(z_space), y_pos(z_space), z_space - cut_spacer},{y_pos(z_space), y_pos(z_space), z_space - cut_spacer},{y_pos(z_space), 0, z_space - cut_spacer}};
				
				//int rotate[3][8] = {{0,1,1,2,2,3,3,0},{4,0,5,1,6,2,7,3},{5,5,6,6,7,7,4,4}};
				int rotate[2][3][2] = {{{0,0},{1,2},{2,3}},{{0,0},{2,3},{1,2}}};
				double Vx = points[rotate[c][1][n]][0] - points[rotate[c][0][n]][0];
				double Vy = points[rotate[c][1][n]][1] - points[rotate[c][0][n]][1];
				double Vz = points[rotate[c][1][n]][2] - points[rotate[c][0][n]][2];
				double Wx = points[rotate[c][2][n]][0] - points[rotate[c][0][n]][0];
				double Wy = points[rotate[c][2][n]][1] - points[rotate[c][0][n]][1];
				double Wz = points[rotate[c][2][n]][2] - points[rotate[c][0][n]][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][2][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
				}
			}
		}
		//Each row
		if(i == 0)
		{	
			//First Point
			int n;
			for(n = 0; n < 4; n ++)
			{
				double points[5][3] = {{0,0,Az_end}, {y_neg(z_space), 0, z_space}, {y_neg(z_space), y_pos(z_space), z_space}, {y_pos(z_space), y_pos(z_space), z_space}, {y_pos(z_space), 0, z_space}};
				
				//int rotate[2][4] = {{1,2,3,4},{2,3,4,1}};
				int rotate[2][4] = {{2,3,4,1},{1,2,3,4}};
				double Vx = points[rotate[0][n]][0] - points[0][0];
				double Vy = points[rotate[0][n]][1] - points[0][1];
				double Vz = points[rotate[0][n]][2] - points[0][2];
				double Wx = points[rotate[1][n]][0] - points[0][0];
				double Wy = points[rotate[1][n]][1] - points[0][1];
				double Wz = points[rotate[1][n]][2] - points[0][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[0][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
			continue;
		}
		else if(i == real_resolution)
		{
			if(cut_num != 0)
			{
				cut_spacer = cut_spacing * cut_num;
			}
			//Final point
			int n;
			for(n = 0; n < 4; n ++)
			{
				double points[5][3] = {{0,0,Bz_end - cut_spacer}, {y_neg(z_start), 0, z_start - cut_spacer}, {y_neg(z_start), y_pos(z_start), z_start - cut_spacer}, {y_pos(z_start), y_pos(z_start), z_start - cut_spacer}, {y_pos(z_start), 0, z_start - cut_spacer}};
				
				//int rotate[2][4] = {{1,2,3,4},{2,3,4,1}};
				int rotate[2][4] = {{1,2,3,4},{2,3,4,1}};
				double Vx = points[rotate[0][n]][0] - points[0][0];
				double Vy = points[rotate[0][n]][1] - points[0][1];
				double Vz = points[rotate[0][n]][2] - points[0][2];
				double Wx = points[rotate[1][n]][0] - points[0][0];
				double Wy = points[rotate[1][n]][1] - points[0][1];
				double Wz = points[rotate[1][n]][2] - points[0][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[0][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
		}
		else
		{
			int n;
			for(n = 0; n <8; n++)
			{
				double points[8][3] = {{y_neg(z_start), 0, z_start - cut_spacer},{y_neg(z_start), y_pos(z_start), z_start - cut_spacer},{y_pos(z_start), y_pos(z_start), z_start - cut_spacer},{y_pos(z_start),0,z_start - cut_spacer},{y_neg(z_space), 0, z_space - cut_spacer},{y_neg(z_space), y_pos(z_space), z_space - cut_spacer},{y_pos(z_space), y_pos(z_space), z_space - cut_spacer},{y_pos(z_space), 0, z_space - cut_spacer}};
				
				//int rotate[3][8] = {{0,1,1,2,2,3,3,0},{4,0,5,1,6,2,7,3},{5,5,6,6,7,7,4,4}};
				int rotate[3][8] = {{0,1,1,2,2,3,3,0},{5,5,6,6,7,7,4,4},{4,0,5,1,6,2,7,3}};
				double Vx = points[rotate[1][n]][0] - points[rotate[0][n]][0];
				double Vy = points[rotate[1][n]][1] - points[rotate[0][n]][1];
				double Vz = points[rotate[1][n]][2] - points[rotate[0][n]][2];
				double Wx = points[rotate[2][n]][0] - points[rotate[0][n]][0];
				double Wy = points[rotate[2][n]][1] - points[rotate[0][n]][1];
				double Wz = points[rotate[2][n]][2] - points[rotate[0][n]][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[2][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
		}
	}
	
	 
	fputs(endsolid, file);
}

void square_print(FILE *file)
{
	//Works with numbers to get the starting and ending points
		double A = a;
	double B = b - m;
	double C = c - d;
	double AC = A * C;
	double ACfour = AC * 4;
	double B_squared = B * B;
	double under_sqrt;
	if(ACfour >= 0)
	{
		under_sqrt = B_squared - ACfour;
	}
	else if(ACfour < 0)
	{
		double four_ac_squared = ACfour * ACfour;
		ACfour = sqrt(four_ac_squared);
		under_sqrt = B_squared + ACfour;
	}
	
	double the_sqrt = sqrt(under_sqrt);
	double negative = -B - the_sqrt;
	double positive = -B + the_sqrt;
	double two_A = A * 2;
	double quad_negative = negative / two_A;
	double quad_positive = positive / two_A;
	
	double Az_end;
	double Bz_end;
	if(quad_positive > quad_negative)
	{
		Az_end = quad_positive;
		Bz_end = quad_negative;
	}
	else if(quad_negative > quad_positive)
	{
		Az_end = quad_negative;
		Bz_end = quad_positive;
		
	}
	
	double Z_spacing = point_distance() / resolution;
	double cut_spacing = point_distance() / 20;
	double cut_spacer = 0;
	double z_space = Az_end;
	double half = point_distance() / 2;
	double middle = Az_end - half;
	double middle_height = y_pos(middle);
	double spacer = 0;	
	int real_resolution = resolution - 1;
	int cut_iteration = 0;
	
	char solid[] = "solid";
	char new_line[] = "\n";
	char tab[] = "\t";
	char space[] = " ";
	char facet_normal[] = "facet normal";
	char outer_loop[] = "outer loop";
	char vertex[] = "vertex";
	char endloop[] = "endloop";
	char endfacet[] = "endfacet";
	char endsolid[] = "endsolid";
	//fputs for these: fputs(object, filename)
	//fprintf for the points: fprintf(filename, "%f", object)
	int i;
	
	fputs(solid, file);
	fputs(new_line, file);
	
	printf("\nDeveloper Diagnostics:\n\n");
	printf("a = %f\nb = %f\nc = %f\nd = %f\nm = %f\n", a, b, c, d, m);
	printf("\nQuadratic one = %f\nQuadratic two = %f\n", quad_negative, quad_positive);
	printf("\nZ_spacing = %f\nz_space = %f\npoint_distance = %f\n", Z_spacing, z_space, point_distance());
	printf("\ny_neg(z_space + Z_spacing) = %f\ny_pos(z_space + Z_spacing) = %f\nmiddle height = %f\n", y_neg(z_space + Z_spacing), y_pos(z_space + Z_spacing), middle_height);
	printf("\nUnder sqrt = %f\nACfour = %f\n", under_sqrt, ACfour);
	printf("\nAz should be larger: Az = %f Bz = %f\n", Az_end, Bz_end);
	printf("\nA = %f B = %f C = %f 4(A)(C) = %f negative = %f positive = %f\n", A, B, C, ACfour, negative, positive);
	for(i = 0; i < resolution; i ++)
	{
		z_space = z_space - Z_spacing;
		double z_start = z_space + Z_spacing;
		if(i == cuts[cut_iteration] && cut_num != 0 && cuts[cut_iteration] != real_resolution)
		{
			cut_iteration++;
			int c;
			for(c = 0; c < 2; c++)
			{
				if(c == 1)
				{
					cut_spacer = cut_spacer + cut_spacing;
				}
				int n;
				for(n = 0; n < 2; n++)
				{
				double points[8][3] = {{y_neg(z_start), 0, z_start - cut_spacer},{y_neg(z_start), y_pos(z_start) * 2, z_start - cut_spacer},{y_pos(z_start), y_pos(z_start) * 2, z_start - cut_spacer},{y_pos(z_start),0,z_start - cut_spacer},{y_neg(z_space), 0, z_space - cut_spacer},{y_neg(z_space), y_pos(z_space) * 2, z_space - cut_spacer},{y_pos(z_space), y_pos(z_space) * 2, z_space - cut_spacer},{y_pos(z_space), 0, z_space - cut_spacer}};
				
				//int rotate[3][8] = {{0,1,1,2,2,3,3,0},{4,0,5,1,6,2,7,3},{5,5,6,6,7,7,4,4}};
				int rotate[2][3][2] = {{{0,0},{1,2},{2,3}},{{0,0},{2,3},{1,2}}};
				double Vx = points[rotate[c][1][n]][0] - points[rotate[c][0][n]][0];
				double Vy = points[rotate[c][1][n]][1] - points[rotate[c][0][n]][1];
				double Vz = points[rotate[c][1][n]][2] - points[rotate[c][0][n]][2];
				double Wx = points[rotate[c][2][n]][0] - points[rotate[c][0][n]][0];
				double Wy = points[rotate[c][2][n]][1] - points[rotate[c][0][n]][1];
				double Wz = points[rotate[c][2][n]][2] - points[rotate[c][0][n]][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[c][2][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
				}
			}
		}
		//Each row
		if(i == 0)
		{	
			//First Point
			int n;
			for(n = 0; n < 4; n ++)
			{
				double points[5][3] = {{0,0,Az_end}, {y_neg(z_space), 0, z_space - cut_spacer}, {y_neg(z_space), y_pos(z_space) * 2, z_space - cut_spacer}, {y_pos(z_space), y_pos(z_space) * 2, z_space - cut_spacer}, {y_pos(z_space), 0, z_space - cut_spacer}};
				
				//int rotate[2][4] = {{1,2,3,4},{2,3,4,1}};
				int rotate[2][4] = {{2,3,4,1},{1,2,3,4}};
				double Vx = points[rotate[0][n]][0] - points[0][0];
				double Vy = points[rotate[0][n]][1] - points[0][1];
				double Vz = points[rotate[0][n]][2] - points[0][2];
				double Wx = points[rotate[1][n]][0] - points[0][0];
				double Wy = points[rotate[1][n]][1] - points[0][1];
				double Wz = points[rotate[1][n]][2] - points[0][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[0][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
			continue;
		}
		else if(i == real_resolution)
		{
			if(cut_num != 0)
			{
				cut_spacer = cut_spacing * cut_num;
			}
			//Final point
			int n;
			for(n = 0; n < 4; n ++)
			{
				double points[5][3] = {{0,0,Bz_end - cut_spacer}, {y_neg(z_start), 0, z_start - cut_spacer}, {y_neg(z_start), y_pos(z_start) * 2, z_start - cut_spacer}, {y_pos(z_start), y_pos(z_start) * 2, z_start - cut_spacer}, {y_pos(z_start), 0, z_start - cut_spacer}};
				
				//int rotate[2][4] = {{2,3,4,1},{1,2,3,4}};
				int rotate[2][4] = {{1,2,3,4},{2,3,4,1}};
				double Vx = points[rotate[0][n]][0] - points[0][0];
				double Vy = points[rotate[0][n]][1] - points[0][1];
				double Vz = points[rotate[0][n]][2] - points[0][2];
				double Wx = points[rotate[1][n]][0] - points[0][0];
				double Wy = points[rotate[1][n]][1] - points[0][1];
				double Wz = points[rotate[1][n]][2] - points[0][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[0][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
		}
		else
		{
			int n;
			for(n = 0; n <8; n++)
			{
				double points[8][3] = {{y_neg(z_start), 0, z_start - cut_spacer},{y_neg(z_start), y_pos(z_start) * 2, z_start - cut_spacer},{y_pos(z_start), y_pos(z_start) * 2, z_start - cut_spacer},{y_pos(z_start),0,z_start - cut_spacer},{y_neg(z_space), 0, z_space - cut_spacer},{y_neg(z_space), y_pos(z_space) * 2, z_space - cut_spacer},{y_pos(z_space), y_pos(z_space) * 2, z_space - cut_spacer},{y_pos(z_space), 0, z_space - cut_spacer}};
				
				//int rotate[3][8] = {{0,1,1,2,2,3,3,0},{4,0,5,1,6,2,7,3},{5,5,6,6,7,7,4,4}};
				int rotate[3][8] = {{0,1,1,2,2,3,3,0},{5,5,6,6,7,7,4,4},{4,0,5,1,6,2,7,3}};
				double Vx = points[rotate[1][n]][0] - points[rotate[0][n]][0];
				double Vy = points[rotate[1][n]][1] - points[rotate[0][n]][1];
				double Vz = points[rotate[1][n]][2] - points[rotate[0][n]][2];
				double Wx = points[rotate[2][n]][0] - points[rotate[0][n]][0];
				double Wy = points[rotate[2][n]][1] - points[rotate[0][n]][1];
				double Wz = points[rotate[2][n]][2] - points[rotate[0][n]][2];

				double Nx_final = Nx(Vy, Wz, Vz, Wy);
				double Ny_final = Ny(Vz, Wx, Vx, Wz);
				double Nz_final = Nz(Vx, Wy, Vy, Wx);
				double Ax_final = Ax(Nx_final, Ny_final, Nz_final);
				double Ay_final = Ay(Nx_final, Ny_final, Nz_final);
				double Az_final = Az(Nx_final, Ny_final, Nz_final);
				fputs(tab, file);
				fputs(facet_normal, file);
				fputs(space, file);	
				fprintf(file, "%f", Ax_final);
				fputs(space, file);	
				fprintf(file, "%f", Ay_final);
				fputs(space, file);
				fprintf(file, "%f", Az_final);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(outer_loop, file);
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						int l;
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[0][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[1][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
						fputs(tab, file);
						fputs(vertex, file);
						for(l = 0; l < 3; l++)
						{
							fputs(space, file);
							fprintf(file, "%f", points[rotate[2][n]][l]);
						}
			fputs(new_line, file);
				fputs(tab, file);
					fputs(tab, file);
					fputs(endloop, file);
			fputs(new_line, file);
				fputs(tab, file);
				fputs(endfacet, file);
			fputs(new_line, file);
			}
		}
	}
	
	 
	fputs(endsolid, file);


}
//Includes locations of the points
double point_distance()
{
	double A = a;
	double B = b - m;
	double C = c - d;
	double AC = A * C;
	double ACfour = AC * 4;
	double B_squared = B * B;
	double under_sqrt = B_squared - ACfour;
	double the_sqrt = sqrt(under_sqrt);
	double negative = -B - the_sqrt;
	double positive = -B + the_sqrt;
	double two_A = 2 * A;
	double quad_negative = negative / two_A;
	double quad_positive = positive / two_A;
	
	
	double Ax = quad_positive;
	double Ay = m * Ax + d;
	double Bx = quad_negative;
	double By = m * Bx + d;
	double Xs = Ax - Bx;
	double Ys = Ay - By;
	double X_squared = Xs * Xs;
	double Y_squared = Ys * Ys;
	double X_sqrt = sqrt(X_squared);
	double Y_sqrt = sqrt(Y_squared);
	double distance = X_sqrt + Y_sqrt;
	return distance;
	
}

int intersect_check()
{
	
	if(m != 0)
	{
		return 2;
	}
	double A = a;
	double B = b - m;
	double C = c - d;
	double B_squared = B * B;
	double AC = A * C;
	double four_ac = 4 * AC;
	double under_sqrt;
	
	if(four_ac > 0)
	{
		under_sqrt = B_squared - four_ac;
	}
	else if(four_ac < 0)
	{
		double four_ac_squared = four_ac * four_ac;
		four_ac = sqrt(four_ac_squared);
		under_sqrt = B_squared + four_ac;
	}
	if(under_sqrt < 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
}
void cube(double p_one[][3], double p_two[][3], double p_three[][3], FILE *file)
{
	char solid[] = "solid";
	char new_line[] = "\n";
	char tab[] = "\t";
	char space[] = " ";
	char facet_normal[] = "facet normal";
	char outer_loop[] = "outer loop";
	char vertex[] = "vertex";
	char endloop[] = "endloop";
	char endfacet[] = "endfacet";
	char endsolid[] = "endsolid";
	int x;
	fputs(solid, file);
	fputs(new_line, file);
	
	for(x = 0; ;x++)
	{
		double Vx = p_two[x][0] - p_one[x][0];
		double Vy = p_two[x][1] - p_one[x][1];
		double Vz = p_two[x][2] - p_one[x][2];
		double Wx = p_three[x][0] - p_one[x][0];
		double Wy = p_three[x][1] - p_one[x][1];
		double Wz = p_three[x][2] - p_one[x][2];
		double Nx_final = Nx(Vy, Wz, Vz, Wy);
		double Ny_final = Ny(Vz, Wx, Vx, Wz);
		double Nz_final = Nz(Vx, Wy, Vy, Wx);
		if(x == 12)
		{
			break;
		}
		else
		{	
			fputs(tab, file);					//Facet Normal
			fputs(facet_normal, file);			
			fputs(space, file);
			fprintf(file, "%f", Nx_final);
			fputs(space, file);
			fprintf(file, "%f", Ny_final);
			fputs(space, file);
			fprintf(file, "%f", Nz_final);

			fputs(new_line, file);				//Outer Loop
			fputs(tab, file);
			fputs(tab, file);
			fputs(outer_loop, file);				
			fputs(new_line, file);
			
			fputs(tab, file);					//Vertecies P1
			fputs(tab, file);
			fputs(tab, file);
			fputs(vertex, file);
			fputs(space, file);
			fprintf(file, "%f", p_one[x][0]);
			fputs(space, file);
			fprintf(file, "%f", p_one[x][1]);
			fputs(space, file);
			fprintf(file, "%f", p_one[x][2]);
			fputs(new_line, file);

			fputs(tab, file);					//Vertecies P2
			fputs(tab, file);
			fputs(tab, file);
			fputs(vertex, file);
			fputs(space, file);
			fprintf(file, "%f", p_two[x][0]);
			fputs(space, file);
			fprintf(file, "%f", p_two[x][1]);
			fputs(space, file);
			fprintf(file, "%f", p_two[x][2]);
			fputs(new_line, file);

			fputs(tab, file);					//Vertecies P3
			fputs(tab, file);
			fputs(tab, file);
			fputs(vertex, file);
			fputs(space, file);
			fprintf(file, "%f", p_three[x][0]);
			fputs(space, file);
			fprintf(file, "%f", p_three[x][1]);
			fputs(space, file);
			fprintf(file, "%f", p_three[x][2]);
			fputs(new_line, file);
			
			fputs(tab, file);					//Endloop
			fputs(tab, file);
			fputs(endloop, file);
			fputs(new_line, file);
			
			fputs(tab, file);					//Endfacet
			fputs(endfacet, file);
			fputs(new_line, file);	
		}
	}
	fputs(endsolid, file);
}
double real_distance(double Ax, double Ay, double Bx, double By)
{
	double Xs = Ax - Bx;
	double Ys = Ay - By;
	double X_squared = Xs * Xs;
	double Y_squared = Ys * Ys;
	double distance = sqrt(X_squared + Y_squared);
	return distance;
}
double Nx(double Vy, double Wz, double Vz, double Wy)
{
	double first = Vy * Wz;
	double second = Vz * Wy;
	double final = first - second;
	return final;
}

double Ny(double Vz, double Wx, double Vx, double Wz)
{
	double first = Vz * Wx;
	double second = Vx * Wz;
	double final = first - second;
	return final;
}

double Nz(double Vx, double Wy, double Vy, double Wx)
{
	double first = Vx * Wy;
	double second = Vy * Wx;
	double final = first - second;
	return final;
}

double Ax(double Nx, double Ny, double Nz)
{
	double denominator = magnitude(Nx) + magnitude(Ny) + magnitude(Nz);
	double numerator = Nx;
	double answer = numerator / denominator;
	return answer;
}

double Ay(double Nx, double Ny, double Nz)
{
	double denominator = magnitude(Nx) + magnitude(Ny) + magnitude(Nz);
	double numerator = Ny;
	double answer = numerator / denominator;
	return answer;
}

double Az(double Nx, double Ny, double Nz)
{
	double denominator = magnitude(Nx) + magnitude(Ny) + magnitude(Nz);
	double numerator = Nz;
	double answer = numerator / denominator;
	return answer;
}

double magnitude(double number)
{
	double first = number * number;
	double answer = sqrt(first);
	return answer;
}
double parabola_y(double z)
{	
	double bz = b*z;
	double z_squared = z * z;
	double az_squared = a * z_squared;
	double y_before = az_squared + bz + c;
	
	double slope = m * z;
	double y_slope = slope + d;
	y_before -= y_slope;

	
	double y_squared = y_before * y_before;
	double y = sqrt(y_squared);


	/*
	double A = a;
	double B = b - m;
	double C = c - d;
	double AC = A * C;
	double ACfour = AC * 4;
	double B_squared = B * B;
	double under_sqrt;
	if(ACfour >= 0)
	{
		under_sqrt = B_squared - ACfour;
	}
	else if(ACfour < 0)
	{
		double four_ac_squared = ACfour * ACfour;
		ACfour = sqrt(four_ac_squared);
		under_sqrt = B_squared + ACfour;
	}
	
	double the_sqrt = sqrt(under_sqrt);
	double negative = -B - the_sqrt;
	double positive = -B + the_sqrt;
	double quad_negative = negative / 2 * A;
	double quad_positive = positive / 2 * A;
	
	
	double Ax = quad_positive;
	double Ay = m * Ax + d;
	double Bx = quad_negative;
	double By = m * Bx + d;
	double Xs = Ax - Bx;
	double Ys = Ay - By;
	double X_squared = Xs * Xs;
	double Y_squared = Ys * Ys;
	double distance = sqrt(X_squared + Y_squared);
	
	double start;
	double pi = 3.141592;
	double degree = 180/pi;
	double angle = atan(m) * degree;
	double subtraction = angle * angle;
	double angle_subtraction = sqrt(subtraction);
	if(m != 0)
	{
		if(Ax > Bx)
		{
			start = Ax;
		}
		else
		{
			start = Bx;
		}

		double section_distance = real_distance(start, 0, z, y);
		double width = real_distance(start, 0, z, 0);
		double height = real_distance(z, 0, z, y);
		double big_angle = atan(height/width);
		double small_angle = big_angle - angle_subtraction;
		double sine = sin(small_angle) * degree;
		double new_y = sine * section_distance;
		return new_y;
	}
	else
	{
	return y;
	}*/
	return y;
}
/* double parabola_x(double z)
{	
	double bz = b*z;
	double z_squared = z * z;
	double az_squared = a * z_squared;
	double y_before = az_squared + bz + c;
	
	double slope = m * z;
	double y_slope = slope + d;
	if(d >= 0)
	{
		y_before = y_before - y_slope;
	}
	else if(d <= 0)
	{
		y_before = y_before - y_slope;
	}

	
	double y_squared = y_before * y_before;
	double y = sqrt(y_squared);


	
	double A = a;
	double B = b - m;
	double C = c - d;
	double AC = A * C;
	double ACfour = AC * 4;
	double B_squared = B * B;
	double under_sqrt;
	if(ACfour >= 0)
	{
		under_sqrt = B_squared - ACfour;
	}
	else if(ACfour < 0)
	{
		double four_ac_squared = ACfour * ACfour;
		ACfour = sqrt(four_ac_squared);
		under_sqrt = B_squared + ACfour;
	}
	
	double the_sqrt = sqrt(under_sqrt);
	double negative = -B - the_sqrt;
	double positive = -B + the_sqrt;
	double quad_negative = negative / 2 * A;
	double quad_positive = positive / 2 * A;
	
	
	double Ax = quad_positive;
	double Ay = m * Ax + d;
	double Bx = quad_negative;
	double By = m * Bx + d;
	double Xs = Ax - Bx;
	double Ys = Ay - By;
	double X_squared = Xs * Xs;
	double Y_squared = Ys * Ys;
	double distance = sqrt(X_squared + Y_squared);
	
	double start;
	double pi = 3.141592;
	double degree = 180/pi;
	double angle = atan(m) * degree;
	double subtraction = angle * angle;
	double angle_subtraction = sqrt(subtraction);
	if(m != 0)
	{
		if(Ax > Bx)
		{
			start = Ax;
		}
		else
		{
			start = Bx;
		}

		double section_distance = real_distance(start, 0, z, y);
		double width = real_distance(start, 0, z, 0);
		double height = real_distance(z, 0, z, y);
		double big_angle = atan(height/width);
		double small_angle = big_angle - angle_subtraction;
		double sine = sin(small_angle) * degree;
		double new_y = sine * section_distance;
		return new_y;
	}
	else
	{
	return z;
	}

	
	
}*/
double tri_y_pos(double z, double angle)
{
	double pi = 3.1415926535;
	double rad_convert = pi/180;
	double parabola = parabola_y(z);
	double first = tan(angle * rad_convert);
	double second = sin(angle * rad_convert) * parabola;
	double third = cos(angle * rad_convert) * parabola;
	double first_second = first * second;
	double final = first_second + third;
	double final_final = magnitude(final);
	return final_final;
	
}
double tri_x_pos(double z, double angle)
{
	double pi = 3.1415926535;
	double rad_convert = pi/180;
	double second_angle = 90 - angle;
	double parabola = parabola_y(z);
	double first = sin(angle * rad_convert) * parabola;
	double second = tan(second_angle * rad_convert);
	double third = cos(angle * rad_convert) * parabola;
	double second_third = second * third;
	double final = first + second_third;
	double final_final = magnitude(final);
	return final_final;
}
double tri_x_neg(double z, double angle)
{
	double answer = -1 * tri_x_pos(z, angle);
	return answer;
	
}

double shifter(double z)
{
	//y = mx + b
	double mx = m * z;
	double y = mx + b;
	return y;
}
double y_neg(double z)
{
	double y = -1 * parabola_y(z);
	return y;
}
double y_pos(double z)
{
	double y = parabola_y(z);
	return y;
}

