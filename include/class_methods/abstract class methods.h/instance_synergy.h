#pragma once

class instance_synergy 
{
public:
	typedef const instance_synergy& i_type;

	virtual instance_synergy& integrates(i_type structure) = 0;
	virtual instance_synergy& eliminates(i_type structure) = 0;
	virtual instance_synergy& intersects(i_type structure) = 0;
};
