/* P2 bits for paddle buttons */

#define LeftSw BIT2
#define DownSw BIT3
#define UpSw BIT4

#if LCD1202_VERSION == 3
#define RightSw BIT1
#elif LCD1202_VERSION == 1 || LCD1202_VERSION == 2 || LCD1202_VERSION == 4
#define RightSw BIT5
#else
#error +++++
#error +++++ LCD1202_VERSION not (properly) defined.  See note in Makefile.
#error +++++
#endif
