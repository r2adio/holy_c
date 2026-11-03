#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i8 b8;
typedef i32 b32;

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

#define MIN(a, b)           (((a) < (b)) ? (a) : (b))
#define MAX(a, b)           (((a) > (b)) ? (a) : (b))
#define ALIGN_UP_POW2(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) - 1)))

#define ARENA_BASE_POS (sizeof(mem_arena)) // pointer to arena itself, as the start of the buffer
#define ARENA_ALIGN    (sizeof(void *))    // size of void pointer changes on system arch, 64-bit

typedef struct {
  u64 capacity;
  u64 pos;
} mem_arena;

mem_arena *arena_create(u64 capacity);
void arena_destroy(mem_arena *arena);
void *arena_push(mem_arena *arena, u64 size, b32 non_zero); // pushing mem to arena
void arena_pop(mem_arena *arena, u64 size);
void arena_pop_to(mem_arena *arena, u64 pos); // pop to a specific location in arena
void arena_clear(mem_arena *arena);           // clear all mem in arena

// helpful macros to push to arena
#define PUSH_STRUCT(arena, T)      (T *)arena_push((arena), sizeof(T), false) // zero the mem
#define PUSH_STRUCT_NZ(arena, T)   (T *)arena_push((arena), sizeof(T), true)  // leave mem empty
#define PUSH_ARRAY(arena, T, n)    (T *)arena_push((arena), sizeof(T) * (n), false)
#define PUSH_ARRAY_NZ(arena, T, n) (T *)arena_push((arena), sizeof(T) * (n), true)

int main(void) {
  mem_arena *perm_arena = arena_create(MiB(1));
  // foo *bar = PUSH_STRUCT(perm_arena, foo);

  arena_destroy(perm_arena);
  return EXIT_SUCCESS;
}

mem_arena *arena_create(u64 capacity) {
  mem_arena *arena = (mem_arena *)malloc(capacity);
  arena->capacity = capacity;
  arena->pos = ARENA_BASE_POS;
  return arena;
}

void arena_destroy(mem_arena *arena) {
  free(arena);
}

void *arena_push(mem_arena *arena, u64 size, b32 non_zero) {
  u64 pos_aligned = ALIGN_UP_POW2(arena->pos, ARENA_ALIGN);
  u64 new_pos = pos_aligned + size;

  if (new_pos > arena->capacity) return NULL;
  arena->pos = new_pos;
  u8 *out = (u8 *)arena + pos_aligned;

  if (!non_zero) memset(out, 0, size);
  return out;
}

void arena_pop(mem_arena *arena, u64 size) {
  size = MIN(size, arena->pos - ARENA_BASE_POS);
  arena->pos -= size;
}

void arena_pop_to(mem_arena *arena, u64 pos) {
  u64 size = pos < arena->pos ? arena->pos - pos : 0;
  arena_pop(arena, size);
}

void arena_clear(mem_arena *arena) {
  arena_pop_to(arena, ARENA_BASE_POS);
}
