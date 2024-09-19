#pragma once

template <typename argument>
class instance_synergy 
{
public:
	virtual instance_synergy& integrates(const argument& structure) = 0;
	virtual instance_synergy& eliminates(const argument& structure) = 0;
	virtual instance_synergy& intersects(const argument& structure) = 0;
};
