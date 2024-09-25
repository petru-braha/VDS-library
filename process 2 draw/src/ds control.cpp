#include <string>
#include "draw/structure/draw_array.h"

draw_data_structure* assing_ds(const char* structure_name)
{
	return nullptr;
	if (strcmp(structure_name, "array"))
		return new draw_array();
}
