#ifndef FRAMEXFORM_H
#define FRAMEXFORM_H
#include <string.h> 

class FrameXform
{
public:
	double m[16];

	FrameXform( double* mIn = NULL )
	{
		if( mIn )
			set( mIn );
		else
			memset( m, 0, sizeof(double)*16 );
	}

	void set(double* glMatrix)
	{
		memcpy( m, glMatrix, sizeof(double)*16 );
	}

	double* matrix()
	{
		return m;
	}      

	FrameXform inverse()
	{
		FrameXform ret;

		if ((m[3] != 0) || (m[7] != 0) || (m[11] != 0) || (m[15] != 1))
		{
			printf("ERROR: Matrix is not Affine\n");
			return ret;
		}

		double i11 = m[5]*m[10] - m[6]*m[9];
		double i21 = m[6]*m[8]  - m[4]*m[10];
		double i31 = m[4]*m[9]  - m[5]*m[8];
		double det = i11*m[0] + i21*m[1] + i31*m[2];

		if (det == 0)
		{
			printf( "ERROR: Matrix is singular\n" );
			return ret;
		}
		else
			det = 1/double(det);

		double i12 = m[2]*m[9]  - m[1]*m[10];
		double i22 = m[0]*m[10] - m[2]*m[8];
		double i32 = m[1]*m[8]  - m[0]*m[9];

		double i13 = m[1]*m[6] - m[2]*m[5];
		double i23 = m[2]*m[4] - m[0]*m[6];
		double i33 = m[0]*m[5] - m[1]*m[4];

		double i41 = -(i11*m[12] + i21*m[13] + i31*m[14]);
		double i42 = -(i12*m[12] + i22*m[13] + i32*m[14]);
		double i43 = -(i13*m[12] + i23*m[13] + i33*m[14]);

		double inv[16] = 
		{
			det*i11, det*i12, det*i13, 0,    
			det*i21, det*i22, det*i23, 0,    
			det*i31, det*i32, det*i33, 0,    
			det*i41, det*i42, det*i43, 1
		};
		ret.set( inv );

		return ret;
	}
};
#endif // FRAMEXFORM_H
