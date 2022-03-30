static inline void matmul(m_elem Pxx_[M], m_elem Jfx[][N], m_elem Q[M], m_elem Pxx[M])
{
	Pxx[0] = Q[0] + Jfx[0][0]*(Pxx_[0]*Jfx[0][0]+Pxx_[1]*Jfx[0][1]+Pxx_[2]*Jfx[0][2])+Jfx[0][1]*(Pxx_[1]*Jfx[0][0]+Pxx_[3]*Jfx[0][1]+Pxx_[4]*Jfx[0][2])+Jfx[0][2]*(Pxx_[2]*Jfx[0][0]+Pxx_[4]*Jfx[0][1]+Pxx_[5]*Jfx[0][2]);
	Pxx[1] = Q[1] + Jfx[0][0]*(Pxx_[0]*Jfx[1][0]+Pxx_[1]*Jfx[1][1]+Pxx_[2]*Jfx[1][2])+Jfx[0][1]*(Pxx_[1]*Jfx[1][0]+Pxx_[3]*Jfx[1][1]+Pxx_[4]*Jfx[1][2])+Jfx[0][2]*(Pxx_[2]*Jfx[1][0]+Pxx_[4]*Jfx[1][1]+Pxx_[5]*Jfx[1][2]);
	Pxx[2] = Q[2] + Jfx[0][0]*(Pxx_[0]*Jfx[2][0]+Pxx_[1]*Jfx[2][1]+Pxx_[2]*Jfx[2][2])+Jfx[0][1]*(Pxx_[1]*Jfx[2][0]+Pxx_[3]*Jfx[2][1]+Pxx_[4]*Jfx[2][2])+Jfx[0][2]*(Pxx_[2]*Jfx[2][0]+Pxx_[4]*Jfx[2][1]+Pxx_[5]*Jfx[2][2]);
	Pxx[3] = Q[3] + Jfx[1][0]*(Pxx_[0]*Jfx[1][0]+Pxx_[1]*Jfx[1][1]+Pxx_[2]*Jfx[1][2])+Jfx[1][1]*(Pxx_[1]*Jfx[1][0]+Pxx_[3]*Jfx[1][1]+Pxx_[4]*Jfx[1][2])+Jfx[1][2]*(Pxx_[2]*Jfx[1][0]+Pxx_[4]*Jfx[1][1]+Pxx_[5]*Jfx[1][2]);
	Pxx[4] = Q[4] + Jfx[1][0]*(Pxx_[0]*Jfx[2][0]+Pxx_[1]*Jfx[2][1]+Pxx_[2]*Jfx[2][2])+Jfx[1][1]*(Pxx_[1]*Jfx[2][0]+Pxx_[3]*Jfx[2][1]+Pxx_[4]*Jfx[2][2])+Jfx[1][2]*(Pxx_[2]*Jfx[2][0]+Pxx_[4]*Jfx[2][1]+Pxx_[5]*Jfx[2][2]);
	Pxx[5] = Q[5] + Jfx[2][0]*(Pxx_[0]*Jfx[2][0]+Pxx_[1]*Jfx[2][1]+Pxx_[2]*Jfx[2][2])+Jfx[2][1]*(Pxx_[1]*Jfx[2][0]+Pxx_[3]*Jfx[2][1]+Pxx_[4]*Jfx[2][2])+Jfx[2][2]*(Pxx_[2]*Jfx[2][0]+Pxx_[4]*Jfx[2][1]+Pxx_[5]*Jfx[2][2]);
}
