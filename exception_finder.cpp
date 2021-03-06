#include <iostream>
#include <cstdio>
#include <set>

class ksample
	{
	private:
	unsigned k0;
	unsigned k1;

	public:

	ksample( void )
		{
		asm volatile ("move %0, $k0" : "=r" (k0));
		asm volatile ("move %0, $k1" : "=r" (k1));
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
return os << buf;
}


int main( void )
{
std::set<ksample> samples;
while( 1 )
	{
	ksample sample;
	if( samples.find( sample ) == samples.end() )
		{
		samples.insert( sample );
		std::cout << sample << std::endl;
		}
	}

return 0;
}
