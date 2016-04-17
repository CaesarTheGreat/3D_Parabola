#include <stdio.h>
#include <string.h>

double magnitude(int number);			//Finds magnitude for mathematical work
double Nx(double Vy, double Wz, double Vz, double Wy);
double Ny(double Vz, double Wx, double Vx, double Wz);
double Nz(double Vx, double Wy, double Vy, double Wx);
double Ax(double Nx, double Ny, double Nz);
double Ay(double Nx, double Ny, double Nz);
double Az(double Nx, double Ny, double Nz);	//All of this is for the formula to determine the normal facet
void triangle(double p_one[][3], double p_two[][3], double p_three[][3], FILE *file);	//Should interpret matrix and write information



															
int main(int argc, char **argv)
{
	char stl[] = ".stl";							//suffix for filename, will be .stl regardless
	char *type = argv[1];						//takes first argument for type(only for testing purposes will be replaced...
											//with file that information will be read from and interpereted from)
	char *file = argv[2];						//takes prefix for filename
	strcat(file, stl);							//combines prefix and suffix for final file name
	FILE *r = fopen(file, "w");					//creates and opens file by the name of the one created before
	char cube[5] = "cube";						//keyword for comparison with type(only for testing purposes)

	if(strcmp(type,cube) == 0)					//Compares argument with keyword(only for testing puposes)
	{
	double p_one[][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,1,0},{0,1,0},{1,0,0},{1,0,0},{0,0,0},{0,0,0},{0,0,1},{0,0,1}};
	double p_two[][3] = {{1,1,0},{0,1,0},{0,1,1},{0,0,1},{1,1,1},{0,1,1},{1,1,0},{1,1,1},{1,0,0},{1,0,1},{1,0,1},{1,1,1}};
	double p_three[][3] = {{1,0,0},{1,1,0},{0,1,0},{0,1,1},{1,1,0},{1,1,1},{1,1,1},{1,0,1},{1,0,1},{0,0,1},{1,1,1},{0,1,1}};
	/*
	These matricies are hard coded and form a cube. The final version should interpret the information given
	and convert it into its own matrix for output purposes. There are three points, as there are only three on a triangle and the
	three didgets per group are the x y and z axes in that order. The format is p_one[][3] as the first box is for the individual 
	numbers in the group (x will always be 0, y will always be 1 and z will always be 2) while the first box is empty since we don't
	know how many triangles there will be in an object. All the points with numbers [x][0-2] will be in the same triangle. 0-2 is just
	the position of the point. Simply in [x][y], x is the number of the triangle and y is the position of the point ex: point one in
	triangle 0 has the position 0-0-0 here.
	*/
	triangle(p_one, p_two, p_three, r);		//will interperet the matrix and write to the file
		
	}
	else
	{
		printf("unknown type\n\nFormat is as follows:\n./stl_test <type> <filename>\nSupported types:\n\ncube\n");
		fclose(r);
		int rem = remove(file);
		//If an unknown type apears, a message is sent to the user and the file is deleted. 
		//In full version this will happen when there is no file to read.
	}
	fclose(r);



	return 0;

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

void triangle(double p_one[][3], double p_two[][3], double p_three[][3], FILE *file)
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


double magnitude(int number)
{
	double first = number * 2;
	double answer = number / 2;
	return answer;
}

