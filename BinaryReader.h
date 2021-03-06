#pragma once

class BinaryReader
{
private:
	BYTE * _DataPtr;

public:
	BinaryReader(BYTE* DataPtr)
	{
		_DataPtr = DataPtr;
	}

	BYTE ReadByte()
	{
		BYTE b = _DataPtr[0];
		_DataPtr += sizeof(BYTE);
		return b;
	}

	int Read7BitEncodedInt()
	{
		int num = 0;
		int num2 = 0;
		BYTE b;
		do
		{
			if (num2 == 35)
			{
				DEVMSG("ERROR: Bad7BitInt32");
				return 0;
				//throw new FormatException(Environment.GetResourceString("Format_Bad7BitInt32"));
			}
			b = ReadByte();
			num |= (b & 0x7F) << num2;
			num2 += 7;
		} while ((b & 0x80) != 0);
		return num;
	}

	int32_t ReadInt32()
	{
		// can't we just (int32)_DataPtr ?
		return (int)_DataPtr[0] | (int)_DataPtr[1] << 8 | (int)_DataPtr[2] << 16 | (int)_DataPtr[3] << 24;
	}

	uint16_t ReadUInt16()
	{
		auto i = (uint16_t)((int)_DataPtr[0] | (int)_DataPtr[1] << 8);
		_DataPtr += sizeof(uint16_t);
		return i;
	}

	uint32_t ReadUInt32()
	{
		auto i = (uint32_t)((int)_DataPtr[0] | (int)_DataPtr[1] << 8 | (int)_DataPtr[2] << 16 | (int)_DataPtr[3] << 24);
		_DataPtr += sizeof(uint32_t);
		return i;
	}

	uint64_t ReadUInt64()
	{
		uint32_t num = (uint32_t)((int)_DataPtr[0] | (int)_DataPtr[1] << 8 | (int)_DataPtr[2] << 16 | (int)_DataPtr[3] << 24);
		uint32_t num2 = (uint32_t)((int)_DataPtr[4] | (int)_DataPtr[5] << 8 | (int)_DataPtr[6] << 16 | (int)_DataPtr[7] << 24);
		auto i = (uint64_t)num2 << 32 | (uint64_t)num;
		_DataPtr += sizeof(uint64_t);
		return i;
	}

	string ReadString()
	{
		auto size = ReadByte();
		//auto size = Read7BitEncodedInt();
		auto str = string((const char*)_DataPtr, size);
		_DataPtr += size;
		return str;
	}
};