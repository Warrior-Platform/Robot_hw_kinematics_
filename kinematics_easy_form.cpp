#include <stdio.h>
#include <math.h>
#define DEGREE2RAD 0.017453292
#define RAD2DEGREE 57.29577951


extern void multiply_matrix_4x4(double  first[][4], double  second[][4], double  result[][4]);		// 4X4 ��� ���� ����.
extern void copy_matrix_A2B_4x4(double A[][4], double B[][4]);										// 4X4 ��� ��Ʈ���� ī��
extern void print_matrix_4x4(double matrix[][4]);													// 4X4 ��� ���
extern void init_matrix_4x4(double matrix[][4]);													// 4X4 ��� �ʱ�ȭ.
void kinematics_matrix_DH_notation(double theta, double d, double alpha, double a, double matrix[][4]) // input : DH parameters & 4x4 matrix for memorized output
{
	double tmp[4][4]
		= { {cos(theta)	,-1 * sin(theta) * cos(alpha)	,sin(theta) * sin(alpha)		,a * cos(alpha)	},
			{sin(theta)	,cos(theta) * cos(alpha)		,-1 * cos(theta) * sin(alpha)	,a * sin(alpha)	},
			{0			,sin(alpha)						, cos(alpha)					,d				},
			{0			,0								,0								,1				} };


	//matrix copy
	copy_matrix_A2B_4x4(tmp, matrix);

}

void PUMA_kinematics_easy()
{
	double T[6][4][4] = { '\0', };
	double theta[6]	  = { 0,0,-90,0,0,0 };
	double d[6] = { 1,1,0,1,0,1 };
	double alpha[6] = { 90,0,-90,90,-90,0 };
	double a[6] = { 0,1,0,0,0,0 };


	double tmp[4][4] = { '\0', };
	double result[4][4] = { '\0', };
	for (int i = 0; i < 6; i++)
	{
		kinematics_matrix_DH_notation(DEGREE2RAD *theta[i], d[i], DEGREE2RAD * alpha[i], a[i], T[i]);
	}
	multiply_matrix_4x4(T[0], T[1], tmp);
	for (int i = 1; i < 5; i++)
	{
		multiply_matrix_4x4(tmp, T[i + 1], result);
		copy_matrix_A2B_4x4(result, tmp);
		init_matrix_4x4(result);
	}

	printf("Kinematics! (easy form) !!!\n\n");
	printf("n \t\to \t\ta \t\tp \n");
	print_matrix_4x4(tmp);

}