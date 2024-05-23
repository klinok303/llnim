#ifndef EASINGS_H
#define EASINGS_H

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif

#define EASE_IN_SINE(x) (1 - cosf(((x) * M_PI) / 2))
#define EASE_OUT_SINE(x) (sinf(((x) * M_PI) / 2))
#define EASE_IN_OUT_SINE(x) (-(cosf(M_PI * (x)) - 1) / 2)
#define EASE_IN_QUAD(x) ((x) * (x))
#define EASE_OUT_QUAD(x) (1 - (1 - (x)) * (1 + (x)))
#define EASE_IN_OUT_QUAD(x) ((x) < 0.5) ? (2 * (x) * (x)) : \
    (1 - pow(-2 * (x) + 2, 2) / 2)

#endif // EASINGS