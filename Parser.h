#pragma once


class ParsedItem_t
{
public:
	int iID = 0;
	string szName = "";

	bool operator < (const ParsedItem_t& other) const { return (szName < other.szName); } // TODO: do in correct way
};

class ParsedSkin_t : public ParsedItem_t
{
public:
	string szSkinName = "";
	int iRarity = 0;
};

template <typename T>
class Parsed
{
public:
	vector<T> List;
	string szLabel = "";
};
struct skinInfo
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};

namespace Parser
{
	VDF::Document EnglishDoc;
	VDF::Document ItemsDoc;

	unordered_map<string, string> Translates;
	Parsed<ParsedItem_t> Weapons;
	Parsed<ParsedItem_t> MusicKits;
	Parsed<ParsedSkin_t> Skins[MAX_WEAPONS];
	Parsed<ParsedItem_t> Stickers;
	Parsed<ParsedItem_t> Coins;
	Parsed<Parsed<ParsedItem_t>> Gloves;
	std::unordered_map<std::string, std::set<std::string>> weaponSkins;
	std::unordered_map<std::string, skinInfo> skinMap;
	std::unordered_map<std::string, std::string> skinNames;
	
	


	bool ParseTranslates()
	{
		DEVMSG(/*> > Parsing translates...*/XorStr<0x44, 26, 0x6A027C3F>("\x7A\x65\x78\x67\x18\x28\x38\x38\x25\x23\x29\x6F\x24\x23\x33\x3D\x27\x39\x37\x23\x3D\x2A\x74\x75\x72" + 0x6A027C3F).s);
		auto Tokens = EnglishDoc.BreadthFirstSearch("Tokens");
		for (auto child : Tokens->children)
		{
			auto pValue = child->ToKeyValue();
			if (!pValue)
				continue;

			Translates[pValue->Key.toString()] = pValue->Value.toString();
		}
		return true;
	}

	bool ParseWeapons()
	{
		DEVMSG("> > Parsing weapons...");

		ParsedItem_t DefaultItem;
		DefaultItem.iID = 0;
		DefaultItem.szName = "-";
		Weapons.List.push_back(DefaultItem);
		Weapons.szLabel += DefaultItem.szName;
		Weapons.szLabel.push_back('\0');

		auto Items = ItemsDoc.BreadthFirstSearchMultiple("items");
		for (auto Child : Items)
		{
			auto pChildObject = Child->ToObject();
			if (!pChildObject)
				continue;

			for (auto Item : pChildObject->children)
			{
				auto pObject = Item->ToObject();
				if (!pObject)
					continue;

				ParsedItem_t Item;
				Item.iID = pObject->name.toInt();
				Item.szName = U::GetWeaponNameById(Item.iID);
				if (Item.szName == "NONE" ||
					Item.iID == 0 ||
					Item.iID >= 874)
					continue;

				Weapons.List.push_back(Item);
				Weapons.szLabel += Item.szName;
				Weapons.szLabel.push_back('\0');
			}
		}
		return true;
	}
	int ParseSkins2()
	{
		VDF::Document EnglishDoc;
		VDF::Document ItemsDoc;
		auto r = ItemsDoc.Load(".\\csgo\\scripts\\items\\items_game.txt", VDF::ENCODING::UTF8);
		if (!r)
			return 1;


		r = EnglishDoc.Load(".\\csgo\\resource\\csgo_english.txt", VDF::ENCODING::UTF16_LE);
		if (!r)
			return 2;

		auto weaponSkinCombo = ItemsDoc.BreadthFirstSearch("weapon_icons");
		if (!weaponSkinCombo || !weaponSkinCombo->ToObject())
			return 3;

		auto skinDataVec = ItemsDoc.BreadthFirstSearchMultiple("paint_kits");
		if (!skinDataVec.size())
			return 4;

		auto PaintKitNames = EnglishDoc.BreadthFirstSearch("Tokens");
		if (!PaintKitNames || !PaintKitNames->ToObject())
			return 5;


		std::vector<std::string> weaponNames = {
			"deagle",
			"elite",
			"fiveseven",
			"glock",
			"ak47",
			"aug",
			"awp",
			"famas",
			"g3sg1",
			"galilar",
			"m249",
			"m4a1_silencer", //needs to be before m4a1 else silencer doesnt get filtered out :D
			"m4a1",
			"mac10",
			"p90",
			"ump45",
			"xm1014",
			"bizon",
			"mag7",
			"negev",
			"sawedoff",
			"tec9",
			"hkp2000",
			"mp7",
			"mp9",
			"nova",
			"p250",
			"scar20",
			"sg556",
			"ssg08",
			"usp_silencer",
			"cz75a",
			"revolver",
			"knife_m9_bayonet", //needs to be before bayonet else knife_m9_bayonet doesnt get filtered out :D
			"bayonet",
			"knife_flip",
			"knife_gut",
			"knife_karambit",
			"knife_tactical",
			"knife_falchion",
			"knife_survival_bowie",
			"knife_butterfly",
			"knife_css",
			"knife_push",
			"knife_gypsy_jackknife",
			"knife_stiletto",
			"knife_ursus",
			"knife_widowmaker",
			"knife_cord",
			"knife_canis",
			"knife_outdoor",
			"knife_skeleton"


		};

		//populate G::weaponSkins
		for (auto child : weaponSkinCombo->children)
		{
			if (child->ToObject())
			{
				for (auto weapon : weaponNames)
				{
					auto skinName = child->ToObject()->GetKeyByName("icon_path")->ToKeyValue()->Value.toString();
					auto pos = skinName.find(weapon);
					//filter out the skinname
					if (pos != std::string::npos)
					{
						auto pos2 = skinName.find_last_of('_');
						weaponSkins[weapon].insert(
							skinName.substr(pos + weapon.length() + 1,
								pos2 - pos - weapon.length() - 1)
						);
						break;
					}
				}
			}
		}

		//populate skinData
		for (auto skinData : skinDataVec)
		{
			if (skinData->ToObject())
			{
				for (auto skin : skinData->children)
				{
					if (skin->ToObject())
					{
						skinInfo si;
						si.paintkit = skin->ToObject()->name.toInt();

						auto skinName = skin->ToObject()->GetKeyByName("name")->ToKeyValue()->Value.toString();
						auto tagNode = skin->ToObject()->GetKeyByName("description_tag");
						if (tagNode)
						{
							std::string tag = tagNode->ToKeyValue()->Value.toString();
							tag = tag.substr(1, std::string::npos); //skip #
							std::transform(tag.begin(), tag.end(), tag.begin(), towlower);
							si.tagName = tag;
						}

						auto keyVal = skin->ToObject()->GetKeyByName("seed");
						if (keyVal != nullptr)
							si.seed = keyVal->ToKeyValue()->Value.toInt();

						skinMap[skinName] = si;
					}
				}
			}
		}

		//populate G::skinNames
		for (auto child : PaintKitNames->children)
		{
			if (child->ToKeyValue())
			{
				std::string key = child->ToKeyValue()->Key.toString();
				std::transform(key.begin(), key.end(), key.begin(), towlower);
				if (key.find("paintkit") != std::string::npos &&
					key.find("tag") != std::string::npos)
				{
					skinNames[key] = child->ToKeyValue()->Value.toString();
				}
			}
		}

		return 0;
	}
	bool ParseSkins()
	{
		// Warning: a lot of shit code in this zone
		DEVMSG(/*> > Parsing skins...*/XorStr<0x6E, 21, 0x09CC2048>("\x50\x4F\x4E\x51\x22\x12\x06\x06\x1F\x19\x1F\x59\x09\x10\x15\x13\x0D\x51\xAE\xAF" + 0x09CC2048).s);

		unordered_map<string, set<string>> weaponSkins;
		unordered_map<string, ParsedSkin_t> skinMap;
		unordered_map<string, int> rarityMap;
		vector<string> weaponNames = {
			"deagle",
			"elite",
			"fiveseven",
			"glock",
			"ak47",
			"aug",
			"awp",
			"famas",
			"g3sg1",
			"galilar",
			"m249",
			"m4a1_silencer", //needs to be before m4a1 else silencer doesnt get filtered out :D
			"m4a1",
			"mac10",
			"p90",
			"ump45",
			"xm1014",
			"bizon",
			"mag7",
			"negev",
			"sawedoff",
			"tec9",
			"hkp2000",
			"mp7",
			"mp9",
			"nova",
			"p250",
			"scar20",
			"sg556",
			"ssg08",
			"usp_silencer",
			"cz75a",
			"revolver",
			"knife_m9_bayonet", //needs to be before bayonet else knife_m9_bayonet doesnt get filtered out :D
			"bayonet",
			"knife_flip",
			"knife_gut",
			"knife_karambit",
			"knife_tactical",
			"knife_falchion",
			"knife_survival_bowie",
			"knife_butterfly",
			"knife_push",
			"knife_gypsy_jackknife",
			"knife_stiletto",
			"knife_ursus",
			"knife_widowmaker",
			"knife_css",
			"knife_cord",
			"knife_canis",
			"knife_outdoor",
			"knife_skeleton"
			

		};
		
		// Populate weaponSkins
		auto Icons = ItemsDoc.BreadthFirstSearch("weapon_icons");
		for (auto child : Icons->children)
		{
			auto pObject = child->ToObject();
			if (!pObject)
				continue;

			for (auto weapon : weaponNames)
			{
				auto skinName = pObject->GetKeyByName("icon_path")->ToKeyValue()->Value.toString();
				auto pos = skinName.find(weapon);
				//filter out the skinname
				if (pos != string::npos)
				{
					auto pos2 = skinName.find_last_of('_');

					weaponSkins[weapon].insert(
						skinName.substr(pos + weapon.length() + 1,
							pos2 - pos - weapon.length() - 1)
					);
					break;
				}
			}
		}

		// Populate skinMap
		auto skinDataVec = ItemsDoc.BreadthFirstSearchMultiple("paint_kits");
		for (auto skinData : skinDataVec)
		{
			if (skinData->ToObject())
			{
				for (auto skin : skinData->children)
				{
					if (skin->ToObject())
					{
						ParsedSkin_t Item;
						Item.iID = skin->ToObject()->name.toInt();
						if (Item.iID == 0)
							continue;

						auto skinName = skin->ToObject()->GetKeyByName("name")->ToKeyValue()->Value.toString();
						Item.szSkinName = skinName;

						auto tagNode = skin->ToObject()->GetKeyByName("description_tag");
						if (tagNode)
						{
							string tag = tagNode->ToKeyValue()->Value.toString();
							tag = tag.substr(1, string::npos); //skip #
							//transform(tag.begin(), tag.end(), tag.begin(), towlower);
							Item.szName = Translates[tag];
						}

						skinMap[skinName] = Item;
					}
				}
			}
		}

		// Populate rarity
		auto paintKitsRarityVec = ItemsDoc.BreadthFirstSearchMultiple("paint_kits_rarity");
		for (auto paintKitsRarity : paintKitsRarityVec)
		{
			for (auto skin : paintKitsRarity->children)
			{
				if (skin->ToKeyValue())
				{
					string rarityStr = skin->ToKeyValue()->Value.toString();
					int rarity = 0;
					if (rarityStr == "common")
						rarity = 2;
					else if (rarityStr == "uncommon")
						rarity = 3;
					else if (rarityStr == "rare")
						rarity = 4;
					else if (rarityStr == "mythical")
						rarity = 5;
					else if (rarityStr == "legendary")
						rarity = 6;
					else if (rarityStr == "ancient")
						rarity = 7;

					skinMap[skin->ToKeyValue()->Key.toString()].iRarity = rarity;
				}
			}
		}

		// Format string
		for (int i = 0; i < MAX_WEAPONS; i++)
		{
			string skinName = U::GetParsableWeaponName(i);
			if (skinName.compare("") == 0) // TODO: Wtf? Use == here
				continue;

			for (auto skin : weaponSkins[skinName])
			{
				Skins[i].List.push_back(skinMap[skin]);

				Skins[i].szLabel += skinMap[skin].szName;
				Skins[i].szLabel.push_back('\0');
			}
			Skins[i].szLabel.push_back('\0');
		}

		return true;
	}

	bool ParseStickers()
	{
		DEVMSG(/*> > Parsing stickers...*/XorStr<0xC3, 24, 0xC78C7B37>("\xFD\xE4\xFB\xE6\x97\xA9\xBB\xB9\xA2\xA2\xAA\xEE\xBC\xA4\xB8\xB1\xB8\xB1\xA7\xA5\xF9\xF6\xF7" + 0xC78C7B37).s);
		auto StickerKits = ItemsDoc.BreadthFirstSearchMultiple("sticker_kits");
		for (auto Kit : StickerKits)
		{
			auto pObject = Kit->ToObject();
			if (!pObject)
				continue;

			for (auto sticker : pObject->children)
			{
				if (sticker->ToObject())
				{
					ParsedItem_t Item;
					Item.iID = sticker->ToObject()->name.toInt();
					string szName = sticker->ToObject()->GetKeyByName("item_name")->ToKeyValue()->Value.toString().substr(1, string::npos);
					Item.szName = Item.iID == 0 ? "-" : Translates[szName];
					if (Item.szName == "" ||
						szName == "")
						continue;
					if (szName.find("StickerKit") == std::string::npos)
						continue;

					Stickers.List.push_back(Item);
					Stickers.szLabel += Item.szName;
					Stickers.szLabel.push_back('\0');
				}
			}
		}

		return true;
	}

	bool ParseMusicKits()
	{
		DEVMSG(/*> > Parsing music kits...*/XorStr<0x60, 26, 0x566BB92C>("\x5E\x41\x5C\x43\x34\x04\x14\x14\x01\x07\x0D\x4B\x01\x18\x1D\x06\x13\x51\x19\x1A\x00\x06\x58\x59\x56" + 0x566BB92C).s);

		ParsedItem_t DefaultItem;
		DefaultItem.iID = 0;
		DefaultItem.szName = "-";
		MusicKits.List.push_back(DefaultItem);
		MusicKits.szLabel += DefaultItem.szName;
		MusicKits.szLabel.push_back('\0');

		auto Kits = ItemsDoc.BreadthFirstSearchMultiple("music_definitions");
		for (auto Child : Kits)
		{
			auto pChildObject = Child->ToObject();
			if (!pChildObject)
				continue;

			for (auto Kit : pChildObject->children)
			{
				auto pObject = Kit->ToObject();
				if (!pObject)
					continue;

				ParsedItem_t Item;
				Item.iID = pObject->name.toInt();
				Item.szName = Translates[pObject->GetKeyByName("loc_name")->ToKeyValue()->Value.toString().substr(1, string::npos)];
				if (Item.szName == "" ||
					Item.iID == 1)
					continue;

				int iComma = Item.szName.find(',');
				if (iComma != std::string::npos) Item.szName = Item.szName.substr(iComma + 1);
				MusicKits.List.push_back(Item);
				MusicKits.szLabel += Item.szName;
				MusicKits.szLabel.push_back('\0');
			}
		}
		return true;
	}

	bool ParseCoins()
	{
		DEVMSG(/*> > Parsing coins...*/XorStr<0x8A, 21, 0x8D732D55>("\xB4\xAB\xB2\xAD\xDE\xEE\xE2\xE2\xFB\xFD\xF3\xB5\xF5\xF8\xF1\xF7\xE9\xB5\xB2\xB3" + 0x8D732D55).s);

		ParsedItem_t DefaultItem;
		DefaultItem.iID = 0;
		DefaultItem.szName = "-";
		Coins.List.push_back(DefaultItem);
		Coins.szLabel += DefaultItem.szName;
		Coins.szLabel.push_back('\0');

		auto Items = ItemsDoc.BreadthFirstSearchMultiple("items");
		for (auto Child : Items)
		{
			auto pChildObject = Child->ToObject();
			if (!pChildObject)
				continue;

			for (auto Item : pChildObject->children)
			{
				auto pItem = Item->ToObject();
				if (!pItem)
					continue;

				auto pName = pItem->GetKeyByName("item_name");
				if (!pName)
					continue;

				auto szName = pName->ToKeyValue()->Value.toString();
				if (szName.find("#CSGO_CollectibleCoin") == std::string::npos)
					continue; // Not a coin

				ParsedItem_t ParsedItem;
				ParsedItem.iID = pItem->name.toInt();
				ParsedItem.szName = pItem->GetKeyByName("name")->ToKeyValue()->Value.toString();
				
				Coins.List.push_back(ParsedItem);
				Coins.szLabel += ParsedItem.szName;
				Coins.szLabel.push_back('\0');
			}
		}

		return true;
	}

	bool Parse()
	{
		DEVMSG(/*> > Loading "csgo_english.txt"...*/XorStr<0x75, 34, 0x1B9C8F34>("\x4B\x56\x49\x58\x35\x15\x1A\x18\x14\x10\x18\xA0\xA3\xE1\xF0\xE3\xEA\xD9\xE2\xE6\xEE\xE6\xE2\xFF\xE5\xA0\xFB\xE8\xE5\xB0\xBD\xBA\xBB" + 0x1B9C8F34).s);
		if (!EnglishDoc.Load(".\\csgo\\resource\\csgo_english.txt", VDF::ENCODING::UTF16_LE))
			return false;
		DEVMSG(/*> > Loading "items_game.txt"...*/XorStr<0x1A, 32, 0x5CC46EEC>("\x24\x3B\x22\x3D\x52\x70\x41\x45\x4B\x4D\x43\x05\x04\x4E\x5C\x4C\x47\x58\x73\x4A\x4F\x42\x55\x1F\x46\x4B\x40\x17\x18\x19\x16" + 0x5CC46EEC).s);
		if (!ItemsDoc.Load(".\\csgo\\scripts\\items\\items_game.txt", VDF::ENCODING::UTF8))
			return false;
	

		ParseTranslates();
		ParseWeapons();

		ParseSkins();
		ParseStickers();
		ParseMusicKits();
		ParseCoins();
		return true;
	}
}