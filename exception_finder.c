#include <stdio.h>

static __inline unsigned fetch_k0( void )
{
unsigned retn;
asm volatile ("move %0, $k0" : "=r" (retn));
return retn;
}

static __inline unsigned fetch_k1( void )
{
unsigned retn;
asm volatile ("move %0, $k1" : "=r" (retn));
return retn;
}

int main( void )
{
unsigned old_k0 = 1,old_k1 = 1;
while(1)
	{
	unsigned k0,k1;
	k0 = fetch_k0();
	k1 = fetch_k1();
	if( old_k0 != k0 || old_k1 != k1 )
		{
		printf("k0:%08x k1:%08x\n",k0,k1);
		old_k0 = k0;
		old_k1 = k1;
		}
	}
return 0;
}
