#include "mc12101load_nm.h"
#include "nc_int_6407.h"


#define LIGHTINIT *((int*)0x10030c04) = 0x0ff
#define LIGHT(x)	*(int*)0x10030c00 = (x);

typedef unsigned int uint32;
typedef unsigned short int uint16;

extern "C" {
	void Conv1x1(float *inp, float *wts, float *bias, float *out, uint32 Q, uint32 L, uint32 F, uint32 vlen = 32);
	void halt();
}

#define halt halt()
//#define halt asm("halt;\n\t")

void DoConv1x1(float *inp, float *wts, float *bias, float *out, int Q, int L, int F, int vlen = 32) {
	if (!(Q % 2) && !(L % 8) && !(F % 8)) {
		int Qmain = Q - Q % vlen;
		for (int q = 0; q < Qmain; q += vlen)
			for (int f = 0; f < F; f += 8)
				Conv1x1(inp + q * L, wts + f, bias + f, out + q * F + f, Q, L, F, 32);
		if (Q != Qmain)
			for (int f = 0; f < F; f += 8)
				Conv1x1(inp + Qmain * L, wts + f, bias + f, out + Qmain * F + f, Q, L, F, Q - Qmain);
	}
}

void t07_dwc() {
	*((int*)0x40001000) |= 0x10;
	asm(
		"with gr7 = false;\n\t"
		"[40000804h] = gr7;\n\t"
		"gr7 = 0fh;\n\t"
		"[40000806h] = gr7;\n\t"
	);
	int clk;
	ncl_hostSync(0);
	float *inp = (float*)0x20000,
		  *wts = (float*)0x28000,
		  *out = (float*)0x30000,
		  *pQ = wts + 0x7FFD,
		  *pL = wts + 0x7FFE,
		  *pF = wts + 0x7FFF;
	int Q = (int)*pQ,
		L = (int)*pL,
		F = (int)*pF;
	float *bias = wts + (L * F);

	//ncl_hostSync(0);
	clk = clock();
	//Conv1x1(inp, wts, bias, out, Q, L, F, 32);
	DoConv1x1(inp, wts, bias, out, Q, L, F);
	clk = clock() - clk;
	ncl_hostSync(clk);

	//asm("halt;\n\t");
	halt;
}





int main() {
	LIGHTINIT;
	t07_dwc();
	//for (int x = 0;;x = (x + 1) & 255)
	//	LIGHT(x);
}





