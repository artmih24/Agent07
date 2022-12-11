#include "pch.h"

#pragma pack(8)

#define ELFPATH "C:\\Users\\User\\workspace\\Test\\Release\\Test"
#define SENDPACK 100000

void serialwrite(NMBoard* nm_board, float* pc, unsigned ddr, unsigned num) {
	if (num<SENDPACK)
		nm_board->WriteMemBlock(0, (void*)pc, ddr, num);
	else {
		while (num >= SENDPACK) {
			nm_board->WriteMemBlock(0, (void*)pc, ddr, SENDPACK);
			pc += SENDPACK;
			ddr += SENDPACK;
			num -= SENDPACK;
		}
		if (num > 0)
			nm_board->WriteMemBlock(0, (void*)pc, ddr, num);
	}
}

void serialread(NMBoard* nm_board, float* pc, unsigned ddr, unsigned num) {
	if (num<SENDPACK)
		nm_board->ReadMemBlock(0, (void*)pc, ddr, num);
	else {
		while (num >= SENDPACK) {
			nm_board->ReadMemBlock(0, (void*)pc, ddr, SENDPACK);
			pc += SENDPACK;
			ddr += SENDPACK;
			num -= SENDPACK;
		}
		if (num > 0)
			nm_board->ReadMemBlock(0, (void*)pc, ddr, num);
	}
}

/*
Адреса в 07:
C0_IMU0:	  0000h -   7fffh
C0_IMU1:	  8000h -   ffffh
C0_IMU2:	1 0000h - 1 7fffh
C0_IMU3:	1 8000h - 1 ffffh
C0_IMU4:	2 0000h - 2 7fffh
C0_IMU5:	2 8000h - 2 ffffh
C0_IMU6:	3 0000h - 3 7fffh
C0_IMU7:	3 8000h - 3 ffffh

C0_IMU0:	4 0000h - 4 7fffh
C0_IMU7:	7 8000h - 7 ffffh

C1_IMU0:	8 0000h - 8 7fffh
C1_IMU3:	9 8000h - 9 ffffh

SHMEM0:		a 0000h - a ffffh
SHMEM1:		b 0000h - b ffffh

DDR2:		2000 0000h - 3FFF FFFFh
*/

void test_dwc() {
	NMBoard nm_board;
	if (nm_board.Reset(0) != NM_OK) {
		printf("Can't reset board\n");
		return;
	}
	if (nm_board.Load(0, 1000, ELFPATH, 0) != NM_OK) {
		printf("Error Load MC121.01\n");
		return;
	}
	srand(time(NULL));

	const int L = 64, 
			  X = 256,
			  size = 1024;
	assert(L * X <= 32768);

	float *in = new float[3 * L * X],
		  *ws = new float[9 * L],
		  *out = new float[L * X],
		  *arr = new float[size],
		  *arr2 = new float[size];
	for (int i = 0; i < 3 * L*X; i++)
		in[i] = 0.001 * rand();
	for (int i = 0; i < 9 * L; i++)
		ws[i] = 0.001 * rand();
	for (int i = 0; i < L * X; i++)
		out[i] = 0;
	for (int i = 0; i < size; i++) {
		arr[i] = i * 1.0;
		arr2[i] = 0;
	}

	//          дескр      массив          адрес    размер
	serialwrite(&nm_board, arr,			   0x18000, size);
	serialwrite(&nm_board, arr2,		   0x20000, size);
	
	/*serialwrite(&nm_board, ws,             0x18000, 9 * L);
	serialwrite(&nm_board, in,             0x20000, L * X);
	serialwrite(&nm_board, in + L * X,     0x28000, L * X);
	serialwrite(&nm_board, in + 2 * L * X, 0x30000, L * X);
	serialwrite(&nm_board, out,            0x38000, L * X);*/
	

	const int l = 0;

	int ret_val = 0, 
		rub;
	//printf("Random number: %d\n", (int)(rand() * 10));
	nm_board.Sync(0, 0, &rub);
	Sleep(1000);
	nm_board.Sync(0, 0, &ret_val);
	const int ops = 9 * L * (X - 2);
	//printf("FLOPS: %f\n", (double)ops / ret_val);

	/*serialread(&nm_board, out, 0x38000, L * X);*/

	serialread(&nm_board, arr2, 0x20000, size);

	/*for (int x = 0; x < X - 2; x++) {
		float res = 0;
		for (int i = 0; i < 3; i++) {
			res += ws[l + L * i + L * 3 * 0] * in[l + L * (i + x) + L * X * 0];
			res += ws[l + L * i + L * 3 * 1] * in[l + L * (i + x) + L * X * 1];
			res += ws[l + L * i + L * 3 * 2] * in[l + L * (i + x) + L * X * 2];
		}
		printf("%03d: %7.2f\t%7.2f\t%10.3g\n", x, res, out[l + x * L], res - out[l + x * L]);
	}*/
	for (int i = 0; i < size; i++) {
		printf("%i\t inp = %f \t out = %f", i, arr[i], arr2[i]);
	}
	printf("\n\n");
	printf("TACTS: %d\n", ret_val);
	printf("TIME: %f us\n", ret_val / (500 * 1e6) * 1e6);
	printf("\n\n");


	delete[] in;
	delete[] ws;
	delete[] out;
	delete[] arr;
	delete[] arr2;
}

int main() {
	test_dwc();
}

