#ifndef INPUT_H
#define INPUT_H
#include <stddef.h>

// Keep the input retrieval process safe and robust
// by using getnstr, which prevents the user from entering
// more than the specified number of characters.
size_t get_size_t(void);

#endif
