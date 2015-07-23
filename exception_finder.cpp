#include <iostream>
#include <cstdio>
#include <set>

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

	bool operator<(const ksample & other) const
		{
		if( k0 == other.k0 )
			{
			return k1 < other.k1;
			}
		else
			{
			return k0 < other.k0;
			}
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
std::set<ksample> samples;
ksample sample;
samples.insert( sample );
while( 1 )
	{
	sample.fetch();
	if( samples.find( sample ) == samples.end() )
		{
		samples.insert( sample );
		std::cout << sample << std::endl;
		}
	}

return 0;
}
