#include <gtest.h>

#include "array_list.h"

TEST(List, can_create_list){
	ASSERT_NO_THROW(List list(3));
}

TEST(List, throws_when_create_list_with_negative_size_of_buffer_memory){
	ASSERT_ANY_THROW(List list(-1));
}
