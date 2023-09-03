#pragma once

class ISerializable
{
public:
	virtual void Serialize() = 0;
	virtual void DeSerialize() = 0;
};