//
//  vec.h
//
//  Created by Mashpoe on 2/26/19.
//

#ifndef vec_h
#define vec_h

#include <stdbool.h>
#include <stdlib.h>

typedef void* cvector; // you can't use this to store vectors, it's just used
		      // internally as a generic type
typedef size_t vec_size_t;	  // stores the number of elements
typedef unsigned char vec_type_t; // stores the number of bytes for a type

typedef int* vec_int;
typedef char* vec_char;

#ifndef _MSC_VER

// shortcut defines

// vec_addr is a vector* (aka type**)
#define vector_add_asg(vec_addr)                                               \
	((typeof(*vec_addr))(                                                  \
	    _vector_add((cvector*)vec_addr, sizeof(**vec_addr))))
#define vector_insert_asg(vec_addr, pos)                                       \
	((typeof(*vec_addr))(                                                  \
	    _vector_insert((cvector*)vec_addr, sizeof(**vec_addr), pos)))

#define vector_add(vec_addr, value) (*vector_add_asg(vec_addr) = value)
#define vector_insert(vec_addr, pos, value)                                    \
	(*vector_insert_asg(vec_addr, pos) = value)

#else

#define vector_add_asg(vec_addr, type)                                         \
	((type*)_vector_add((cvector*)vec_addr, sizeof(type)))
#define vector_insert_asg(vec_addr, type, pos)                                 \
	((type*)_vector_insert((cvector*)vec_addr, sizeof(type), pos))

#define vector_add(vec_addr, type, value)                                      \
	(*vector_add_asg(vec_addr, type) = value)
#define vector_insert(vec_addr, type, pos, value)                              \
	(*vector_insert_asg(vec_addr, type, pos) = value)

#endif

// vec is a vector (aka type*)
#define vector_erase(vec, pos, len)                                            \
	(_vector_erase((cvector*)vec, sizeof(*vec), pos, len))
#define vector_remove(vec, pos)                                                \
	(_vector_remove((cvector*)vec, sizeof(*vec), pos))

#define vector_copy(vec) (_vector_copy((cvector*)vec, sizeof(*vec)))

cvector vector_create(void);

void vector_free(cvector vec);

cvector _vector_add(cvector* vec_addr, vec_type_t type_size);

cvector _vector_insert(cvector* vec_addr, vec_type_t type_size, vec_size_t pos);

void _vector_erase(cvector* vec_addr, vec_type_t type_size, vec_size_t pos,
		   vec_size_t len);

void _vector_remove(cvector* vec_addr, vec_type_t type_size, vec_size_t pos);

void vector_pop(cvector vec);

cvector _vector_copy(cvector vec, vec_type_t type_size);

vec_size_t vector_size(cvector vec);

vec_size_t vector_get_alloc(cvector vec);

#endif /* vec_h */

