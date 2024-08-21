#pragma once

template <typename modifier_m, typename specific_m, typename constant_m, typename query_m, typename instance_m, typename iterator_m>
class data_structure : public modifier_m, specific_m, constant_m, query_m, instance_m, iterator_m {};

// comments:
// "_m" stands for methods
