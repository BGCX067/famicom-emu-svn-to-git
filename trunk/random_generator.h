#ifndef RANDOM_GENERATOR_HDR
#define RANDOM_GENERATOR_HDR

#ifndef RANDOM
#define RANDOM(x) (x * (rand() / (RAND_MAX + 1.0)));
#else
#error RANDOM(x) was already defined
#endif

#endif
