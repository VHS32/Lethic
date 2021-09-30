/*
Instead of using rand WinAPI function, use Mulberry32 or Xorshift32 / 64 randomize algorithum.
You may face problem with Xorshift32/64 since rand seed is different than Xorshift or Mulberry,
but for fast response you shouldn't use rand WinAPI for this works.
*/


// fast_rand source: https://stackoverflow.com/questions/26237419/faster-than-rand

static unsigned int seed;
int rng(void) {
    seed = (214013 * seed + 2531011);
    return (seed >> 16) & 0x7fff;
}


// Mulberry32 source: https://gist.github.com/tommyettinger/46a874533244883189143505d203312c
// Taken from Magnetar (by Nathan) source: https://github.com/IOCTL0x7F/Magnetar

int rng(void)
{
	DWORD state;
	DWORD z = (state += 0x6D2B79F5UL);
	z = (z ^ (z >> 15)) * (z | 1UL);
	z ^= z + (z ^ (z >> 7)) * (z | 61UL);
	return z ^ (z >> 14);
}
