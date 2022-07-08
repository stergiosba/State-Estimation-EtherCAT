#ifndef CLA_APP_KF_H_
#define CLA_APP_KF_H_


void Quat_product(float a, float p[4], float q[4], float r[4])
{
    r[0] = a*(p[0]*q[0] - p[1]*q[1] - p[2]*q[2] - p[3]*q[3]);
    r[1] = a*(p[0]*q[1] + p[1]*q[0] + p[2]*q[3] - p[3]*q[2]);
    r[2] = a*(p[0]*q[2] - p[1]*q[3] + p[2]*q[0] + p[3]*q[1]);
    r[3] = a*(p[0]*q[3] + p[1]*q[2] - p[2]*q[1] + p[3]*q[0]);
}

void Quat_product_inplace(float a, float p[4], float q[4])
{
    float q0 = a*(p[0]*q[0] - p[1]*q[1] - p[2]*q[2] - p[3]*q[3]);
    float q1 = a*(p[0]*q[1] + p[1]*q[0] + p[2]*q[3] - p[3]*q[2]);
    float q2 = a*(p[0]*q[2] - p[1]*q[3] + p[2]*q[0] + p[3]*q[1]);
    float q3 = a*(p[0]*q[3] + p[1]*q[2] - p[2]*q[1] + p[3]*q[0]);

    p[0] = q0;
    p[1] = q1;
    p[2] = q2;
    p[3] = q3;
}

void Quat_normalize(float p[4])
{
    float norm = CLAsqrt(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]+p[3]*p[3]);
    p[0] = CLAdiv(p[0],norm);
    p[1] = CLAdiv(p[1],norm);
    p[2] = CLAdiv(p[2],norm);
    p[3] = CLAdiv(p[3],norm);
}

void integrate(float p[4], float q[4], float dt)
{
    p[0] += dt*q[0];
    p[1] += dt*q[1];
    p[2] += dt*q[2];
    p[3] += dt*q[3];
}

float sign(float x){
    return (x >= 0) - (x < 0);
}

void rotated_acc(float ra[3])
{
    ra[0] = (2*(QGL[0]*QGL[0]+QGL[1]*QGL[1])-1)*g_SensBurst[4] + (2*(QGL[1]*QGL[2]-QGL[0]*QGL[3]))*g_SensBurst[5] + (2*(QGL[1]*QGL[3]+QGL[0]*QGL[2]))*g_SensBurst[6];
    ra[1] = (2*(QGL[1]*QGL[2]+QGL[0]*QGL[3]))*g_SensBurst[4] + (2*(QGL[0]*QGL[0]+QGL[2]*QGL[2])-1)*g_SensBurst[5] + (2*(QGL[2]*QGL[3]-QGL[0]*QGL[1]))*g_SensBurst[6];
    ra[2] = (2*(QGL[1]*QGL[3]-QGL[0]*QGL[2]))*g_SensBurst[4] + (2*(QGL[2]*QGL[3]+QGL[0]*QGL[1]))*g_SensBurst[5] + (2*(QGL[0]*QGL[0]+QGL[3]*QGL[3])-1)*g_SensBurst[6];
}


static inline void Q_Complementary_Filter(float cfk, float dt)
{
    //
    // Attitude estimation with Complementary Filter (CF)
    //

    // Body rates measured by the gyroscopes stored as a pure quaternion.
    float Qw[4] = {0, g_SensBurst[1], g_SensBurst[2], g_SensBurst[3]};
    float ra[3] = {0};
    rotated_acc(ra);
    float q0 = CLAsqrt(0.5*(1-ra[2]));
    float Qa[4] = {(1-cfk)+(cfk)*q0, -(cfk)*CLAdiv(ra[1],2*q0), (cfk)*CLAdiv(ra[0],2*q0), 0};
    float QGL_dot[4]={0};

    Quat_product(0.5,QGL,Qw,QGL_dot);
    //
    integrate(QGL, QGL_dot, dt);
    Quat_normalize(Qa);
    Quat_product_inplace(1,QGL,Qa);
    Quat_normalize(QGL);
    p_s=CLAsqrt(QGL[0]*QGL[0]+QGL[1]*QGL[1]+QGL[2]*QGL[2]+QGL[3]*QGL[3]);

    float sinr_cosp = 2 * (QGL[0] * QGL[1] + QGL[2] * QGL[3]);
    float cosr_cosp = 1 - 2 * (QGL[1] * QGL[1] + QGL[2] * QGL[2]);
    g_Attitude[0] = CLAatan2(sinr_cosp, cosr_cosp)*180.0f/CLAMATH_PI;

    // pitch (y-axis rotation)
    float sinp = 2 * (QGL[0] * QGL[2] - QGL[3] * QGL[1]);
    g_Attitude[1] = CLAasin(sinp)*180.0f/CLAMATH_PI;

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (QGL[0] * QGL[3] + QGL[1] * QGL[2]);
    float cosy_cosp = 1 - 2 * (QGL[2] * QGL[2] + QGL[3] * QGL[3]);

    g_Attitude[2] = CLAatan2(siny_cosp, cosy_cosp)*180.0f/CLAMATH_PI;
}



#endif /* CLA_APP_KF_H_ */
