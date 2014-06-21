#include <iostream>
#include <cstdio>
#include <vector>

#define NUM_BUFFERS 20

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


class ksample
	{
	private:
	unsigned k0;
	unsigned k1;

	public:
	void fetch( void )
		{
		k0 = fetch_k0();
		k1 = fetch_k1();
		}

	ksample( void )
		{
		fetch();
		}

	bool operator!=(const ksample & other)
		{
		return k0 != other.k0 || k1 != other.k1;
		}

	friend std::ostream& operator<<(std::ostream& os, const ksample & k);
	};

std::ostream& operator<<(std::ostream& os, const ksample & sample)
{
char buf[128];
snprintf( buf, sizeof(buf), "k0:%08x k1:%08x", sample.k0, sample.k1 );
os << buf;
return os;
}


int main( void )
{
std::vector<ksample> samples;
samples.reserve(NUM_BUFFERS);//up front to try to avoid catching registers from mmap/setbrk
ksample first;
samples.push_back( first );
while( samples.size() < NUM_BUFFERS )
	{
	ksample sample;
	if( samples.back() != sample )
		{
		samples.push_back( sample );
		}
	}

for (std::vector<ksample>::iterator it = samples.begin() ; it != samples.end(); ++it)
	std::cout << *it << std::endl;

return 0;
}
