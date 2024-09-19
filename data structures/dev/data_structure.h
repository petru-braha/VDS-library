#pragma once

template <typename modifier_m, typename specific_m, typename constant_m, typename query_m, typename instance_m, typename iterator_m>
class data_structure :	public modifier_m, public specific_m, 
						public constant_m, public query_m, 
						public instance_m, public iterator_m 
{};

// comments:
// "_m" stands for methods
