static inline void Complementary_Filter(float cfk, float dt)
{
    //
    // Attitude estimation with Complementary Filter (CF)
    //
    float pi = 3.14159265359f;


    // Body rates measured by the gyroscopes
    float p = g_SensBurst[1];
    float q = g_SensBurst[2];
    float r = g_SensBurst[3];

    // Precalculating trigonometrics to speed up computations, CLA math needs angles in rads.
    float sin_phi = CLAsin(g_Attitude[0]*pi/180);
    float cos_phi = CLAcos(g_Attitude[0]*pi/180);
    float sin_theta = CLAsin(g_Attitude[1]*pi/180);
    float cos_theta = CLAcos(g_Attitude[1]*pi/180);
    float tan_theta = CLAdiv(sin_theta,cos_theta);
    float sec_theta = CLAdiv(1,cos_theta);

    //
    // ZYX Euler kinematics for the body rates from the Body Frame (B) to Inertial frame (I)
    // w_I = E*w_B
    // E: Euler kinematics (not a rotation matrix it is actually singular when theta (pitch angle) is 90 degrees-> for ZYX Euler).
    // w_I = [phi_dot, theta_dot, psi_dot]
    // w_B = [p, q, r]
    //
    float phi_dot = (p+q*sin_phi*tan_theta+r*cos_phi*tan_theta);
    float theta_dot = (q*cos_phi-r*sin_theta);
    float psi_dot = (p+q*sin_phi*sec_theta+r*cos_phi*sec_theta);

    //
    // Zero linear acceleration assumption (Accelerometer only measures the generalized gravity vector)
    // G: Generalized gravity vector
    // g: Gravity vector in the inertial frame = [0 0 -1]
    // R_BI: Rotation matrix from Body frame (B) to Inertial frame (I)
    // G = R_BI*g
    //
    float rollAcc = CLAatan(CLAdiv(g_SensBurst[5], g_SensBurst[6])) * 180 / pi;
    float pitchAcc = CLAatan(CLAdiv(-g_SensBurst[4],sin_phi*g_SensBurst[5]+cos_phi*g_SensBurst[6]))* 180 / pi;

    //
    // Simple Euler integration with Complementary filter sensor fusion.
    // x_est = k*integral(w_I)+(1-k)*x_a
    // x_a = [rollAcc, pitchAcc] : The angles of the generalized gravity vector measured by the accelerometer with the above assumption
    // cfk: Weight factor for the Low pass filter(gyro) and 1-k for the High pass filter(accelerometer).
    //
    g_Attitude[0] = cfk*(g_Attitude[0]+dt*phi_dot)+(1-cfk)*rollAcc;
    g_Attitude[1] = cfk*(g_Attitude[1]+dt*theta_dot)+(1-cfk)*pitchAcc;
    g_Attitude[2] = g_Attitude[2]+dt*psi_dot;
}
