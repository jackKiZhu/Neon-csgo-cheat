#pragma once

class BinaryWriter
{
private:
	string _Bytes;

public:
	BinaryWriter()
	{

	}

	void WriteByte(BYTE b)
	{
		_Bytes.push_back(b);
	}

	void WriteInt(int i)
	{
		_Bytes.push_back(i);
		_Bytes.push_back(i >> 8);
		_Bytes.push_back(i >> 16);
		_Bytes.push_back(i >> 24);
	}

	void WriteUInt16(uint16_t i)
	{
		_Bytes.push_back(i);
		_Bytes.push_back(i >> 8);
	}

	void WriteUInt32(uint32_t i)
	{
		_Bytes.push_back(i);
		_Bytes.push_back(i >> 8);
		_Bytes.push_back(i >> 16);
		_Bytes.push_back(i >> 24);
	}

	void WriteUInt64(uint64_t i)
	{
		_Bytes.push_back(i);
		_Bytes.push_back(i >> 8);
		_Bytes.push_back(i >> 16);
		_Bytes.push_back(i >> 24);
		_Bytes.push_back(i >> 32);
		_Bytes.push_back(i >> 40);
		_Bytes.push_back(i >> 48);
		_Bytes.push_back(i >> 56);
	}

	void WriteString(string str)
	{
		WriteByte(str.size());
		//WriteInt(str.size());
		_Bytes += str;
	}

	const char* Bytes()
	{
		return _Bytes.c_str();
	}

	size_t Size()
	{
		return _Bytes.size();
	}
};