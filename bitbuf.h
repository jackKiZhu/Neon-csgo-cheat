#pragma once

class bf_read
{
public:
	uintptr_t base_address;
	uintptr_t cur_offset;

	bf_read(uintptr_t addr)
	{
		base_address = addr;
		cur_offset = 0;
	}

	void SetOffset(uintptr_t offset)
	{
		cur_offset = offset;
	}

	void Skip(uintptr_t length)
	{
		cur_offset += length;
	}

	int ReadByte()
	{
		auto val = *reinterpret_cast<char*>(base_address + cur_offset);
		++cur_offset;
		//cur_offset += 4;
		return val;
	}

	bool ReadBool()
	{
		auto val = *reinterpret_cast<bool*>(base_address + cur_offset);
		++cur_offset;
		return val;
	}

	string ReadString()
	{
		char buffer[256];
		auto str_length = *reinterpret_cast<char*>(base_address + cur_offset);
		++cur_offset;
 		std::memcpy(buffer, reinterpret_cast<void*>(base_address + cur_offset), str_length > 255 ? 255 : str_length);
		buffer[str_length > 255 ? 255 : str_length] = '\0';
		cur_offset += str_length + 1;
		return string(buffer);
	}
};