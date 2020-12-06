#include "math_utils.h"

size_t nearest_even_ceil_size_t(size_t x) { return (x % 2) ? x + 1 : x; }
size_t nearest_even_floor_size_t(size_t x) { return (x % 2) ? x - 1 : x; }
size_t nearest_odd_ceil_size_t(size_t x) { return (x % 2) ? x : x + 1; }
size_t nearest_odd_floor_size_t(size_t x) { return (x % 2) ? x : x - 1; }

uint32_t nearest_even_ceil_uint32_t(uint32_t x) { return (x % 2) ? x + 1 : x; }
uint32_t nearest_even_floor_uint32_t(uint32_t x) { return (x % 2) ? x - 1 : x; }
int32_t nearest_even_ceil_int32_t(int32_t x) { return (x % 2) ? x + 1 : x; }
int32_t nearest_even_floor_int32_t(int32_t x) { return (x % 2) ? x - 1 : x; }
uint32_t nearest_odd_ceil_uint32_t(uint32_t x) { return (x % 2) ? x : x + 1; }
uint32_t nearest_odd_floor_uint32_t(uint32_t x) { return (x % 2) ? x : x - 1; }
int32_t nearest_odd_ceil_int32_t(int32_t x) { return (x % 2) ? x : x + 1; }
int32_t nearest_odd_floor_int32_t(int32_t x) { return (x % 2) ? x : x - 1; }

uint8_t nearest_even_ceil_uint8_t(uint8_t x) { return (x % 2) ? x + 1 : x; }
uint8_t nearest_even_floor_uint8_t(uint8_t x) { return (x % 2) ? x - 1 : x; }
int8_t nearest_even_ceil_int8_t(int8_t x) { return (x % 2) ? x + 1 : x; }
int8_t nearest_even_floor_int8_t(int8_t x) { return (x % 2) ? x - 1 : x; }
uint8_t nearest_odd_ceil_uint8_t(uint8_t x) { return (x % 2) ? x : x + 1; }
uint8_t nearest_odd_floor_uint8_t(uint8_t x) { return (x % 2) ? x : x - 1; }
int8_t nearest_odd_ceil_int8_t(int8_t x) { return (x % 2) ? x : x + 1; }
int8_t nearest_odd_floor_int8_t(int8_t x) { return (x % 2) ? x : x - 1; }
