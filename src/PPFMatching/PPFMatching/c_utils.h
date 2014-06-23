
#ifndef __UTILS_H_
#define __UTILS_H_

#define EPS		1.192092896e-07F        /* smallest such that 1.0+FLT_EPSILON != 1.0 */

#define T_OPENMP // define this if OpenMP is desired

#ifndef PI
#ifdef  M_PI
#define PI               M_PI
#define PI_F             3.1415926535897932384626433832795f
#else
#define PI               3.1415926535897932384626433832795
#define PI_F             3.1415926535897932384626433832795f
#endif
#endif

#ifndef M_PI
#define M_PI             PI
#endif

// Useful Macros
#define TNorm3(v) (sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]))

#define TNormalize3(v)\
double normTemp=TNorm3(v);\
if (normTemp>0)\
{\
v[0]/=normTemp;\
v[1]/=normTemp;\
v[2]/=normTemp;\
}

#define TCross(a, b, c) c[0] = (a[1])*(b[2])-(a[2])*(b[1]); c[1] = (a[2])*(b[0])-(a[0])*(b[2]); c[2] = (a[0])*(b[1])-(a[1])*(b[0]);

#define TDot3(a,b) ((a[0])*(b[0])+(a[1])*(b[1])+(a[2])*(b[2]))

#define TAngle3(a, b, c, f) {\
	TCross(a,b,c);\
	f = (atan2(TNorm3(c), TDot3(a, b)));\
}


#if defined (__cplusplus)
extern "C" {
#endif 

	void matrix_cross4(const double *u, const double *v, const double *w, double *x);
	void matrix_cross_matrix(double *v, double *v_cross) ;
	
	void matrix_to_axis_angle(double *R, double *axis, double *angle);
	void axis_angle_to_matrix(double *axis, double angle, double *R);
	void matrix_to_quaternion(double *R, double *q);
	void quaternion_to_matrix(double *q, double *R);

	static __inline void matrix_product33(double *A, double *B, double *R)
	{
		R[0] = A[0] * B[0] + A[1] * B[3] + A[2] * B[6];
		R[1] = A[0] * B[1] + A[1] * B[4] + A[2] * B[7];
		R[2] = A[0] * B[2] + A[1] * B[5] + A[2] * B[8];    

		R[3] = A[3] * B[0] + A[4] * B[3] + A[5] * B[6];
		R[4] = A[3] * B[1] + A[4] * B[4] + A[5] * B[7];
		R[5] = A[3] * B[2] + A[4] * B[5] + A[5] * B[8];    

		R[6] = A[6] * B[0] + A[7] * B[3] + A[8] * B[6];
		R[7] = A[6] * B[1] + A[7] * B[4] + A[8] * B[7];
		R[8] = A[6] * B[2] + A[7] * B[5] + A[8] * B[8];            
	}

	// A is a vector
	static __inline void matrix_product133(double *A, double *B, double *R)
	{
		R[0] = A[0] * B[0] + A[1] * B[3] + A[2] * B[6];
		R[1] = A[0] * B[1] + A[1] * B[4] + A[2] * B[7];
		R[2] = A[0] * B[2] + A[1] * B[5] + A[2] * B[8];            
	}

	static __inline void matrix_product331(const double A[9], const double b[3], double r[3])
	{
		r[0] = A[0] * b[0] + A[1] * b[1] + A[2] * b[2];
		r[1] = A[3] * b[0] + A[4] * b[1] + A[5] * b[2];
		r[2] = A[6] * b[0] + A[7] * b[1] + A[8] * b[2];
	}

	static __inline void matrix_transpose33(double *A, double *At)
	{
		At[0] = A[0]; At[4] = A[4]; At[8] = A[8];
		At[1] = A[3]; At[2] = A[6]; 
		At[3] = A[1]; At[5] = A[7]; 
		At[6] = A[2]; At[7] = A[5]; 
	}

	static __inline void matrix_product44(const double A[16], const double B[16], double R[16])
	{
		R[0] = A[0] * B[0] + A[1] * B[4] + A[2] * B[8] + A[3] * B[12];
		R[1] = A[0] * B[1] + A[1] * B[5] + A[2] * B[9] + A[3] * B[13];
		R[2] = A[0] * B[2] + A[1] * B[6] + A[2] * B[10] + A[3] * B[14];
		R[3] = A[0] * B[3] + A[1] * B[7] + A[2] * B[11] + A[3] * B[15];

		R[4] = A[4] * B[0] + A[5] * B[4] + A[6] * B[8] + A[7] * B[12];
		R[5] = A[4] * B[1] + A[5] * B[5] + A[6] * B[9] + A[7] * B[13];
		R[6] = A[4] * B[2] + A[5] * B[6] + A[6] * B[10] + A[7] * B[14];
		R[7] = A[4] * B[3] + A[5] * B[7] + A[6] * B[11] + A[7] * B[15];

		R[8] = A[8] * B[0] + A[9] * B[4] + A[10] * B[8] + A[11] * B[12];
		R[9] = A[8] * B[1] + A[9] * B[5] + A[10] * B[9] + A[11] * B[13];
		R[10] = A[8] * B[2] + A[9] * B[6] + A[10] * B[10] + A[11] * B[14];
		R[11] = A[8] * B[3] + A[9] * B[7] + A[10] * B[11] + A[11] * B[15];

		R[12] = A[12] * B[0] + A[13] * B[4] + A[14] * B[8] + A[15] * B[12];
		R[13] = A[12] * B[1] + A[13] * B[5] + A[14] * B[9] + A[15] * B[13];
		R[14] = A[12] * B[2] + A[13] * B[6] + A[14] * B[10] + A[15] * B[14];
		R[15] = A[12] * B[3] + A[13] * B[7] + A[14] * B[11] + A[15] * B[15];
	}


	/*static __inline int next_power_of_two(int x)
	{
		return (int)pow(2.0, ceil(log((double)x)/log(2.0)));;
	}*/


	static __inline void compute_axis_angle_yz(double angle, const double r[3], double row2[3], double row3[3])
	{
		const double sinA=sin(angle);
		const double cosA=cos(angle);
		const double cos1A=(1-cosA);

		row2[0] =  0.f;  row2[1] = cosA; row2[2] =  0.f; 
		row3[0] =  0.f;  row3[1] =  0.f; row3[2] = cosA; 

		row2[0] +=  r[2] * sinA; 
		row2[2] += -r[0] * sinA; 
		row3[0] += -r[1] * sinA; 
		row3[1] +=  r[0] * sinA;

		row2[0] += r[1] * r[0] * cos1A;  row2[1] += r[1] * r[1] * cos1A; row2[2] += r[1] * r[2] * cos1A;
		row3[0] += r[2] * r[0] * cos1A;  row3[1] += r[2] * r[1] * cos1A; row3[2] += r[2] * r[2] * cos1A;
	}

	static __inline void compute_axis_angle(double angle, const double r[3], double R[9])
	{
		const double sinA=sin(angle);
		const double cosA=cos(angle);
		const double cos1A=(1-cosA);
		double *row1 = &R[0];
		double *row2 = &R[3];
		double *row3 = &R[6];

		row1[0] =  cosA;  row1[1] = 0.0f; row1[2] =  0.f; 
		row2[0] =  0.f;  row2[1] = cosA; row2[2] =  0.f; 
		row3[0] =  0.f;  row3[1] =  0.f; row3[2] = cosA; 

		row1[1] += -r[2] * sinA;
		row1[2] +=  r[1] * sinA;
		row2[0] +=  r[2] * sinA;
		row2[2] += -r[0] * sinA;
		row3[0] += -r[1] * sinA;
		row3[1] +=  r[0] * sinA;

		row1[0] += r[0] * r[0] * cos1A;  row1[1] += r[0] * r[1] * cos1A; row1[2] += r[0] * r[2] * cos1A;
		row2[0] += r[1] * r[0] * cos1A;  row2[1] += r[1] * r[1] * cos1A; row2[2] += r[1] * r[2] * cos1A;
		row3[0] += r[2] * r[0] * cos1A;  row3[1] += r[2] * r[1] * cos1A; row3[2] += r[2] * r[2] * cos1A;
	}

	static __inline void get_unit_x_rotation(double angle, double R[9])
	{
		const double sinA=sin(angle);
		const double cosA=cos(angle);
		const double cos1A=(1-cosA);
		double *row1 = &R[0];
		double *row2 = &R[3];
		double *row3 = &R[6];

		row1[0] =  cosA;  row1[1] = 0.0f; row1[2] =  0.f; 
		row2[0] =  0.f;  row2[1] = cosA; row2[2] =  0.f; 
		row3[0] =  0.f;  row3[1] =  0.f; row3[2] = cosA; 

		row2[2] += -sinA;
		row3[1] +=  sinA;

		row1[0] += cos1A;
	}

	static __inline void get_unit_x_rotation_44(double angle, double T[16])
	{
		const double sinA=sin(angle);
		const double cosA=cos(angle);
		const double cos1A=(1-cosA);
		double *row1 = &T[0];
		double *row2 = &T[4];
		double *row3 = &T[8];

		row1[0] =  cosA;  row1[1] = 0.0f; row1[2] =  0.f; 
		row2[0] =  0.f;  row2[1] = cosA; row2[2] =  0.f; 
		row3[0] =  0.f;  row3[1] =  0.f; row3[2] = cosA; 

		row2[2] += -sinA;
		row3[1] +=  sinA;

		row1[0] += cos1A;

		T[15] = 1;
	}

	static __inline void compute_transform_rt_yz(const double p1[4], const double n1[4], double row2[3], double row3[3], double t[3])
	{
		double angle=acos( n1[0] );
		double axis[3]={0, n1[2], -n1[1]};
		double axisNorm;

		// we try to project on the ground plane but it's already parallel
		if (n1[1]==0 && n1[2]==0)
		{
			axis[0]=0; axis[1]=1; axis[2]=0;
		}
		else
		{	
			axisNorm=sqrt(axis[2]*axis[2]+axis[1]*axis[1]);

			if (axisNorm>EPS)
			{
				axis[1]/=axisNorm;
				axis[2]/=axisNorm;
			}
		}

		compute_axis_angle_yz(angle, axis, row2, row3);

		t[1] = row2[0] * (-p1[0]) + row2[1] * (-p1[1]) + row2[2] * (-p1[2]);
		t[2] = row3[0] * (-p1[0]) + row3[1] * (-p1[1]) + row3[2] * (-p1[2]);
	}

	static __inline void compute_transform_rt(const double p1[4], const double n1[4], double R[9], double t[3])
	{
		double angle=acos( n1[0] );
		double axis[3]={0, n1[2], -n1[1]};
		double axisNorm;
		double *row1, *row2, *row3;

		// we try to project on the ground plane but it's already parallel
		if (n1[1]==0 && n1[2]==0)
		{
			axis[0]=0; axis[1]=1; axis[2]=0;
		}
		else
		{	
			axisNorm=sqrt(axis[2]*axis[2]+axis[1]*axis[1]);

			if (axisNorm>EPS)
			{
				axis[1]/=axisNorm;
				axis[2]/=axisNorm;
			}
		}

		compute_axis_angle(angle, axis, R);
		row1 = &R[0];
		row2 = &R[3];
		row3 = &R[6];

		t[0] = row1[0] * (-p1[0]) + row1[1] * (-p1[1]) + row1[2] * (-p1[2]);
		t[1] = row2[0] * (-p1[0]) + row2[1] * (-p1[1]) + row2[2] * (-p1[2]);
		t[2] = row3[0] * (-p1[0]) + row3[1] * (-p1[1]) + row3[2] * (-p1[2]);
	}


#if defined (__cplusplus)
}
#endif 

#endif