global ctor : label;
global dtor : label;
//nmc-g++; -c -std=c++11 -mmas -O2 -Wall
global _dwc3x1v1: label;
global _dwc3x3_load_filters: label;
global _dwc3x3: label;

global _Conv1x1: label;
_Conv1x1_AddBiases: label;
_Conv1x1_AddBiasesEnd: label;
_Conv1x1_AddBiasesF: label;
_Conv1x1_AddBiasesFEnd: label;
_Conv1x1_Div_by_vlen: label;
_Conv1x1_Div_by_vlen_End: label;
_Conv1x1_LoopQ: label;
_Conv1x1_LoopQEnd: label;
_Conv1x1_LoopL: label;
_Conv1x1_LoopLEnd: label;
_Conv1x1_LoopLEndTail10: label;
_Conv1x1_LoopLEndTail8: label;
_Conv1x1_LoopLEndTail6: label;
_Conv1x1_LoopLEndTail4: label;
_Conv1x1_LoopLEndTail2: label;
_Conv1x1_LoopLEndTail0: label;
_Conv1x1_LoopLEndTailEnd: label;
_Conv1x1_LoopF: label;
_Conv1x1_LoopFEnd: label;

global _halt: label;

begin ".text"

<ctor>
<dtor>
return;

<_halt>
	halt;

//void Conv1x1(float *inp, float *wts, float *bias, float *out, int Q, int L, int F, int vlen);
<_Conv1x1>
	push ar0, gr0;
	push ar1, gr1;
	push ar2, gr2;
	push ar3, gr3;
	push ar4, gr4;
	push ar5, gr5;
	push ar6, gr6;
	push ar7, gr7;
	ar0 = [ar7 - 19];	// inp
	ar1 = [ar7 - 20];	// wts
	ar2 = [ar7 - 21];	// bias
	ar3 = [ar7 - 22];	// out
	gr0 = [ar7 - 23];	// Q
	gr1 = [ar7 - 24];	// L
	gr2 = [ar7 - 25];	// F
	gr3 = [ar7 - 26];	// vlen
	gr3--;
	vlen = gr3;

	ar4 = ar1;
	fpu 0 rep vlen vreg1 = [ar2];
	ar2 += 2;
	fpu 1 rep vlen vreg1 = [ar2];
	ar2 += 2;
	fpu 2 rep vlen vreg1 = [ar2];
	ar2 += 2;
	fpu 3 rep vlen vreg1 = [ar2];
	ar2 += 2;
	ar5 = ar0;

	// ==========================================================================================
	// ----------- reading input map 1 ------------
	ar6 = ar0			with gr0 = gr1;
	fpu 0 rep vlen vreg5 = [ar0++gr0];
	ar0 = ar6 + 2;
	fpu 1 vreg5 = fpu 0 vreg5;
	fpu 2 vreg5 = fpu 1 vreg5;
	fpu 3 vreg5 = fpu 2 vreg5;
	// ==========================================================================================
	// ----------- reading input map 2 -----------
	//ar6 = ar0			with gr0 = gr1;
	fpu 0 rep vlen vreg6 = [ar0++gr0];
	ar0 = ar6 + 4;//2;
	fpu 1 vreg6 = fpu 0 vreg6;
	fpu 2 vreg6 = fpu 1 vreg6;
	fpu 3 vreg6 = fpu 2 vreg6;
	// ==========================================================================================
	// ----------- reading input map 3 ------------
	//ar6 = ar0			with gr0 = gr1;
	fpu 0 rep vlen vreg7 = [ar0++gr0];
	ar0 = ar6 + 6;//2;
	fpu 1 vreg7 = fpu 0 vreg7;
	fpu 2 vreg7 = fpu 1 vreg7;
	fpu 3 vreg7 = fpu 2 vreg7;
	// ------------ reading weights 1 ------------
	gr6 = gr1;											// L (gr1) -> gr6
	gr1 = gr2;
	fpu 0 rep 1 vreg2 = [ar1++];
	fpu 1 rep 1 vreg2 = [ar1++];
	fpu 2 rep 1 vreg2 = [ar1++];
	fpu 3 rep 1 vreg2 = [ar1++];
	ar1 -= 8;
	ar1 += gr1;
	fpu 0 rep 1 vreg3 = [ar1++];
	fpu 1 rep 1 vreg3 = [ar1++];
	fpu 2 rep 1 vreg3 = [ar1++];
	fpu 3 rep 1 vreg3 = [ar1++];
	ar1 += gr1;
	ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
	// ==========================================================================================
	// ----------- reading input map 4 ------------
	//ar6 = ar0			with gr0 = gr1;
	fpu 0 rep vlen vreg4 = [ar0++gr0];
	ar0 = ar6 + 8;//2;
	fpu 1 vreg4 = fpu 0 vreg4;
	fpu 2 vreg4 = fpu 1 vreg4;
	fpu 3 vreg4 = fpu 2 vreg4;
	// ---------------- muladd 1 ----------------
	fpu 0 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
	fpu 1 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
	fpu 2 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
	fpu 3 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
	// ------------ reading weights 2 ------------
	gr6 = gr1;											// L (gr1) -> gr6
	gr1 = gr2;
	fpu 0 rep 1 vreg2 = [ar1++];
	fpu 1 rep 1 vreg2 = [ar1++];
	fpu 2 rep 1 vreg2 = [ar1++];
	fpu 3 rep 1 vreg2 = [ar1++];
	ar1 -= 8;
	ar1 += gr1;
	fpu 0 rep 1 vreg3 = [ar1++];
	fpu 1 rep 1 vreg3 = [ar1++];
	fpu 2 rep 1 vreg3 = [ar1++];
	fpu 3 rep 1 vreg3 = [ar1++];
	ar1 += gr1;
	ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
	// ==========================================================================================

	gr3 = gr1 >> 3;	// L / 8
	gr3--;
	<_Conv1x1_LoopL>
		gr3 - 1;
		if < skip _Conv1x1_LoopLEnd;

		// ==========================================================================================
		// ----------- reading input map 1 ------------
		ar6 = ar0			with gr0 = gr1;
		fpu 0 rep vlen vreg5 = [ar0++gr0];
		ar0 = ar6 + 2;
		fpu 1 vreg5 = fpu 0 vreg5;
		fpu 2 vreg5 = fpu 1 vreg5;
		fpu 3 vreg5 = fpu 2 vreg5;
		// ---------------- muladd 2 ----------------
		fpu 0 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
		fpu 1 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
		fpu 2 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
		fpu 3 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
		// ------------ reading weights 3 ------------
		gr6 = gr1;											// L (gr1) -> gr6
		gr1 = gr2;
		fpu 0 rep 1 vreg2 = [ar1++];
		fpu 1 rep 1 vreg2 = [ar1++];
		fpu 2 rep 1 vreg2 = [ar1++];
		fpu 3 rep 1 vreg2 = [ar1++];
		ar1 -= 8;
		ar1 += gr1;
		fpu 0 rep 1 vreg3 = [ar1++];
		fpu 1 rep 1 vreg3 = [ar1++];
		fpu 2 rep 1 vreg3 = [ar1++];
		fpu 3 rep 1 vreg3 = [ar1++];
		ar1 += gr1;
		ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
		// ==========================================================================================
		// ----------- reading input map 2 -----------
		//ar6 = ar0			with gr0 = gr1;
		fpu 0 rep vlen vreg6 = [ar0++gr0];
		ar0 = ar6 + 4;//2;
		fpu 1 vreg6 = fpu 0 vreg6;
		fpu 2 vreg6 = fpu 1 vreg6;
		fpu 3 vreg6 = fpu 2 vreg6;
		// ---------------- muladd 3 ----------------
		fpu 0 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
		fpu 1 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
		fpu 2 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
		fpu 3 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
		// ------------ reading weights 4 ------------
		gr6 = gr1;											// L (gr1) -> gr6
		gr1 = gr2;
		fpu 0 rep 1 vreg2 = [ar1++];
		fpu 1 rep 1 vreg2 = [ar1++];
		fpu 2 rep 1 vreg2 = [ar1++];
		fpu 3 rep 1 vreg2 = [ar1++];
		ar1 -= 8;
		ar1 += gr1;
		fpu 0 rep 1 vreg3 = [ar1++];
		fpu 1 rep 1 vreg3 = [ar1++];
		fpu 2 rep 1 vreg3 = [ar1++];
		fpu 3 rep 1 vreg3 = [ar1++];
		ar1 += gr1;
		ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
		// ==========================================================================================
		// ----------- reading input map 3 ------------
		//ar6 = ar0			with gr0 = gr1;
		fpu 0 rep vlen vreg7 = [ar0++gr0];
		ar0 = ar6 + 6;//2;
		fpu 1 vreg7 = fpu 0 vreg7;
		fpu 2 vreg7 = fpu 1 vreg7;
		fpu 3 vreg7 = fpu 2 vreg7;
		// ---------------- muladd 4 ----------------
		fpu 0 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
		fpu 1 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
		fpu 2 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
		fpu 3 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
		// ------------ reading weights 1 ------------
		gr6 = gr1;											// L (gr1) -> gr6
		gr1 = gr2;
		fpu 0 rep 1 vreg2 = [ar1++];
		fpu 1 rep 1 vreg2 = [ar1++];
		fpu 2 rep 1 vreg2 = [ar1++];
		fpu 3 rep 1 vreg2 = [ar1++];
		ar1 -= 8;
		ar1 += gr1;
		fpu 0 rep 1 vreg3 = [ar1++];
		fpu 1 rep 1 vreg3 = [ar1++];
		fpu 2 rep 1 vreg3 = [ar1++];
		fpu 3 rep 1 vreg3 = [ar1++];
		ar1 += gr1;
		ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
		// ==========================================================================================
		// ----------- reading input map 4 ------------
		//ar6 = ar0			with gr0 = gr1;
		fpu 0 rep vlen vreg4 = [ar0++gr0];
		ar0 = ar6 + 8;//2;
		fpu 1 vreg4 = fpu 0 vreg4;
		fpu 2 vreg4 = fpu 1 vreg4;
		fpu 3 vreg4 = fpu 2 vreg4;
		// ---------------- muladd 1 ----------------
		fpu 0 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
		fpu 1 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
		fpu 2 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
		fpu 3 .matrix vreg1 = vreg5 * .retrive(vreg2, vreg3) + vreg1;
		// ------------ reading weights 2 ------------
		gr6 = gr1;											// L (gr1) -> gr6
		gr1 = gr2;
		fpu 0 rep 1 vreg2 = [ar1++];
		fpu 1 rep 1 vreg2 = [ar1++];
		fpu 2 rep 1 vreg2 = [ar1++];
		fpu 3 rep 1 vreg2 = [ar1++];
		ar1 -= 8;
		ar1 += gr1;
		fpu 0 rep 1 vreg3 = [ar1++];
		fpu 1 rep 1 vreg3 = [ar1++];
		fpu 2 rep 1 vreg3 = [ar1++];
		fpu 3 rep 1 vreg3 = [ar1++];
		ar1 += gr1;
		ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
		// ==========================================================================================

		skip _Conv1x1_LoopL	with gr3--;
	<_Conv1x1_LoopLEnd>
	// ==========================================================================================
	// ---------------- muladd 2 ----------------
	fpu 0 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
	fpu 1 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
	fpu 2 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
	fpu 3 .matrix vreg1 = vreg6 * .retrive(vreg2, vreg3) + vreg1;
	// ------------ reading weights 3 ------------
	gr6 = gr1;											// L (gr1) -> gr6
	gr1 = gr2;
	fpu 0 rep 1 vreg2 = [ar1++];
	fpu 1 rep 1 vreg2 = [ar1++];
	fpu 2 rep 1 vreg2 = [ar1++];
	fpu 3 rep 1 vreg2 = [ar1++];
	ar1 -= 8;
	ar1 += gr1;
	fpu 0 rep 1 vreg3 = [ar1++];
	fpu 1 rep 1 vreg3 = [ar1++];
	fpu 2 rep 1 vreg3 = [ar1++];
	fpu 3 rep 1 vreg3 = [ar1++];
	ar1 += gr1;
	ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
	// ==========================================================================================
	// ---------------- muladd 3 ----------------
	fpu 0 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
	fpu 1 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
	fpu 2 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
	fpu 3 .matrix vreg1 = vreg7 * .retrive(vreg2, vreg3) + vreg1;
	// ------------ reading weights 4 ------------
	gr6 = gr1;											// L (gr1) -> gr6
	gr1 = gr2;
	fpu 0 rep 1 vreg2 = [ar1++];
	fpu 1 rep 1 vreg2 = [ar1++];
	fpu 2 rep 1 vreg2 = [ar1++];
	fpu 3 rep 1 vreg2 = [ar1++];
	ar1 -= 8;
	ar1 += gr1;
	fpu 0 rep 1 vreg3 = [ar1++];
	fpu 1 rep 1 vreg3 = [ar1++];
	fpu 2 rep 1 vreg3 = [ar1++];
	fpu 3 rep 1 vreg3 = [ar1++];
	ar1 += gr1;
	ar1 -= 8			with gr1 = gr6;					// L (gr6) -> gr1
	// ==========================================================================================
	// ---------------- muladd 4 ----------------
	fpu 0 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
	fpu 1 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
	fpu 2 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
	fpu 3 .matrix vreg1 = vreg4 * .retrive(vreg2, vreg3) + vreg1;
	// ==========================================================================================

	ar0 = ar5;
	ar1 = ar4;
	ar5 = ar6;
	ar6 = ar3			with gr3 = gr2;
	fpu 0 rep vlen [ar3++gr3] = vreg1;
	ar3 = ar6 + 2;
	fpu 1 rep vlen [ar3++gr3] = vreg1;
	ar3 = ar6 + 4;
	fpu 2 rep vlen [ar3++gr3] = vreg1;
	ar3 = ar6 + 6;
	fpu 3 rep vlen [ar3++gr3] = vreg1;
	ar3 = ar6 + 8;
	ar1 += 8;
	ar6 = ar5;

	pop ar7, gr7;
	pop ar6, gr6;
	pop ar5, gr5;
	pop ar4, gr4;
	pop ar3, gr3;
	pop ar2, gr2;
	pop ar1, gr1;
	pop ar0, gr0;
	return;

end ".text";





