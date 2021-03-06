//#pragma once
//
//// TODO:
////  Equipted
////  Stickers
//
//struct inv_item_t
//{
//	int Index = 0;
//	int ID = 0;
//	int Skin = 0;
//	char Name[32] = "";
//	int StatTrak = 0;
//	int Seed = 0;
//	float Wear = 0;
//	int Quality = 0;
//	uint64_t Sticker1 = 0;
//	uint64_t Sticker2 = 0;
//	uint64_t Sticker3 = 0;
//	uint64_t Sticker4 = 0;
//	bool EquiptedTT = false;
//	bool EquiptedCT = false;
//	uint64_t UniqueID = 0;
//
//	inv_item_t(int ID, int Skin, char Name[32], int StatTrak, int Seed, float Wear, int Quality, int Sticker1, int Sticker2, int Sticker3, int Sticker4, bool EquiptedTT, bool EquiptedCT)
//	{
//		this->ID = ID;
//		this->Skin = Skin;
//		s_strcpy(this->Name, Name);
//		this->StatTrak = StatTrak;
//		this->Seed = Seed;
//		this->Wear = Wear;
//		this->Quality = Quality;
//		this->Sticker1 = Sticker1;
//		this->Sticker2 = Sticker2;
//		this->Sticker3 = Sticker3;
//		this->Sticker4 = Sticker4;
//		this->EquiptedTT = EquiptedTT;
//		this->EquiptedCT = EquiptedCT;
//	}
//
//	uint64_t BuildItemID()
//	{
//		string szID = "20";
//		szID += to_string(ID);
//		szID += to_string(Skin);
//		szID += to_string(Quality);
//		szID += to_string(Index);
//
//		return std::stoi(szID);
//	}
//};
//
//namespace InventoryChanger
//{
//	std::vector<inv_item_t> m_Items;
//
//	void AddItem(inv_item_t inv)
//	{
//		inv.Index = m_Items.size();
//		inv.UniqueID = inv.BuildItemID();
//		m_Items.push_back(inv);
//	}
//
//	string parseString(string szBefore, string szAfter, string szSource)
//	{
//		if (!szBefore.empty() && !szAfter.empty() && !szSource.empty() && (szSource.find(szBefore) != std::string::npos) && (szSource.find(szAfter) != std::string::npos))
//		{
//			string t = strstr(szSource.c_str(), szBefore.c_str());
//			t.erase(0, szBefore.length());
//			string::size_type loc = t.find(szAfter, 0);
//			t = t.substr(0, loc);
//			return t;
//		}
//		else
//			return "";
//	}
//
//	string HttpGet(string hostaddr, string api)
//	{
//		string request;
//		string response;
//		int resp_leng;
//		char buffer[1024];
//		struct sockaddr_in serveraddr;
//		int sock;
//		WSADATA wsaData;
//
//		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
//			DEVMSG("InventoryChanger: WSAStartup() failed\r\n");
//
//		struct hostent *host;
//		host = gethostbyname(hostaddr.c_str());
//
//		int port = 80;
//		request += "GET " + api + " HTTP/1.0\r\n";
//		request += "Host: " + hostaddr + "\r\n";
//		request += "User-Agent: InventoryChanger [Build: 1.0.0] \r\n";
//		request += "\r\n";
//
//		if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
//			DEVMSG("InventoryChanger: socket() failed\r\n");
//
//		memset(&serveraddr, 0, sizeof(serveraddr));
//		serveraddr.sin_family = AF_INET;
//
//		serveraddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
//
//		serveraddr.sin_port = htons((unsigned short)port);
//
//		struct in_addr **addr_list;
//
//		addr_list = (struct in_addr **) host->h_addr_list;
//
//		response = "";
//
//		if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
//			DEVMSG("InventoryChanger: connect() failed");
//
//		if (send(sock, request.c_str(), request.length(), 0) != request.length())
//			DEVMSG("InventoryChanger: send() sent a different number of BYTEs than expected");
//
//		resp_leng = 1024;
//
//		while (resp_leng > 0)
//		{
//
//			resp_leng = recv(sock, (char*)&buffer, 1024, 0);
//
//			if (resp_leng > 0)
//				response += string(buffer).substr(0, resp_leng);
//		}
//
//		closesocket(sock);
//		WSACleanup();
//		return response;
//	}
//
//	void ParseInventory()
//	{
//		InventoryChanger::m_Items.clear();
//
//		std::string szResponse = HttpGet("yeahnot.ru", "/inventory.php");
//		if (szResponse.empty())
//		{
//			DEVMSG("Failed parsing InventoryChanger api: response is null");
//			MakeNotify("ERROR: Failed initializing InventoryChanger!");
//			return;
//		}
//
//		int i = 0;
//		while (true)
//		{
//			if (szResponse.find("[<id>" + std::to_string(i) + "</id>]") == std::string::npos)
//				break;
//
//			string szParseWeapon = parseString("<weapon>=", "</weapon>", szResponse);
//			string szParseSkin = parseString("<skin>=", "</skin>", szResponse);
//			string szParseName = parseString("<name>=", "</name>", szResponse);
//			string szParseST = parseString("<stattrak>=", "</stattrak>", szResponse);
//
//			string szParseSeed = parseString("<seed>=", "</seed>", szResponse);
//			string szParseWear = parseString("<wear>=", "</wear>", szResponse);
//			string szParseQuality = parseString("<quality>=", "</quality>", szResponse);
//
//			string szParseSticker1 = parseString("<sticker1>=", "</sticker1>", szResponse);
//			string szParseSticker2 = parseString("<sticker2>=", "</sticker2>", szResponse);
//			string szParseSticker3 = parseString("<sticker3>=", "</sticker3>", szResponse);
//			string szParseSticker4 = parseString("<sticker4>=", "</sticker4>", szResponse);
//
//			string szParseACT = parseString("<act>=", "</act>", szResponse);
//			string szParseATT = parseString("<att>=", "</att>", szResponse);
//
//			if (szParseWeapon.empty() || szParseSkin.empty() || szParseST.empty() || szParseSeed.empty() || szParseWear.empty()
//				|| szParseQuality.empty() || szParseSticker1.empty() || szParseSticker2.empty() || szParseSticker3.empty()
//				|| szParseSticker4.empty() || szParseACT.empty() || szParseATT.empty())
//			{
//				i++;
//				continue;
//			}
//
//			if (szParseName.empty())
//				szParseName = "";
//
//			char Name[32];
//			s_strcpy(Name, szParseName.c_str());
//
//			InventoryChanger::AddItem(inv_item_t(atoi(szParseWeapon.c_str()), atoi(szParseSkin.c_str()), Name, atoi(szParseST.c_str()), atoi(szParseSeed.c_str()),
//				atof(szParseWear.c_str()), atoi(szParseQuality.c_str()), atoi(szParseSticker1.c_str()), atoi(szParseSticker2.c_str()), atoi(szParseSticker3.c_str()), atoi(szParseSticker4.c_str()),
//				atoi(szParseACT.c_str()), atoi(szParseATT.c_str())));
//
//			size_t nPos = szResponse.find("</att>");
//			szResponse.erase(0, nPos + 1);
//			i++;
//		}
//	}
//
//	int WeaponIdToItemId(int id)
//	{
//		for (int i = 0; i < Parser::Weapons.List.size(); i++)
//		{
//			auto& item = Parser::Weapons.List[i];
//			if (item.iID == id)
//				return i;
//		}
//
//		return 0;
//	}
//
//	void SetupInv()
//	{
//		//AddItem(inv_item_t(5, 3, "", 1337, 555, 0.5f, 2, 555, 444, 444, 222, false, false)); // ak47
//		//AddItem(inv_item_t(8, 3, "", 1337, 555, 0.5f, 2, 555, 444, 444, 222, false, false)); // awp
//		//AddItem(inv_item_t(3, 3, "", 1337, 555, 0.5f, 2, 555, 444, 444, 222, false, false)); // awp
//		//AddItem(inv_item_t(7, 3, "", 1337, 555, 0.5f, 2, 555, 444, 444, 222, false, false)); // awp
//		//AddItem(inv_item_t(4, 3, "", 1337, 555, 0.5f, 2, 555, 444, 444, 222, false, false)); // awp
//		//AddItem(inv_item_t(2, 3, "", 1337, 555, 0.5f, 2, 555, 444, 444, 222, false, false)); // awp
//		//AddItem(inv_item_t(8, 3, "", 1337, 555, 0.5f, 2, 555, 444, 444, 222, false, false)); // awp
//		//AddItem(inv_item_t(WeaponIdToItemId(WEAPON_USP_SILENCER), 11, "suka blyat", 1335, 555, 0.7f, 2, 555, 444, 444, 222, false, false));
//		CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(ParseInventory), NULL, NULL, NULL);
//	}
//
//	inline ItemDefinitionIndex ItemIdToWeaponId(int id)
//	{
//		return Parser::Weapons.List[id].iID;
//	}
//
//	bool HasWeaponCustomSkin(int id)
//	{
//		for (auto& item : m_Items)
//			if (Parser::Weapons.List[item.ID].iID == id)
//				return true;
//
//		return false;
//	}
//
//	int GetWeaponSkin(int id)
//	{
//		for (auto& item : m_Items)
//			if (Parser::Weapons.List[item.ID].iID == id)
//				return item.Skin;
//
//		return -1;
//	}
//
//	void SetupSkins()
//	{
//		for (auto item : m_Items)
//		{
//			if (item.EquiptedCT || item.EquiptedTT)
//			{
//				auto DefIndex = ItemIdToWeaponId(item.ID);
//
//				g_Weapons[DefIndex].ChangerEnabled = true;
//				g_Weapons[DefIndex].StickersEnabled = true;
//
//				// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
//
//				if (item.EquiptedCT)
//				{
//					if (DefIndex.IsKnife())
//					{
//						Options::SkinChanger::EnabledKnife = true;
//						if (DefIndex == WEAPON_KNIFE_BAYONET) Options::SkinChanger::KnifeCT = 0;
//						else if (DefIndex == WEAPON_KNIFE_FLIP) Options::SkinChanger::KnifeCT = 1;
//						else if (DefIndex == WEAPON_KNIFE_GUT) Options::SkinChanger::KnifeCT = 2;
//						else if (DefIndex == WEAPON_KNIFE_KARAMBIT) Options::SkinChanger::KnifeCT = 3;
//						else if (DefIndex == WEAPON_KNIFE_M9_BAYONET) Options::SkinChanger::KnifeCT = 4;
//						else if (DefIndex == WEAPON_KNIFE_TACTICAL) Options::SkinChanger::KnifeCT = 5;
//						else if (DefIndex == WEAPON_KNIFE_FALCHION) Options::SkinChanger::KnifeCT = 6;
//						else if (DefIndex == WEAPON_KNIFE_SURVIVAL_BOWIE) Options::SkinChanger::KnifeCT = 7;
//						else if (DefIndex == WEAPON_KNIFE_BUTTERFLY) Options::SkinChanger::KnifeCT = 8;
//						else if (DefIndex == WEAPON_KNIFE_PUSH) Options::SkinChanger::KnifeCT = 9;
//
//						Options::SkinChanger::EnabledKnife = true;
//
//						/*Options::SkinChanger::KnifeCTSkin = item.Skin;
//						Options::SkinChanger::KnifeCTWear = item.Wear;
//						Options::SkinChanger::KnifeCTSeed = item.Seed;
//						Options::SkinChanger::KnifeCTST = item.StatTrak;*/
//					}
//
//					g_Weapons[DefIndex].ChangerSkinCT = item.Skin;
//					g_Weapons[DefIndex].ChangerWearCT = item.Wear;
//					g_Weapons[DefIndex].ChangerSeedCT = item.Seed;
//					g_Weapons[DefIndex].ChangerStatTrakCT = item.StatTrak;
//					s_strcpy(g_Weapons[DefIndex].ChangerNameCT, item.Name);
//
//					g_Weapons[DefIndex].Stickers[0].iID = item.Sticker1;
//					g_Weapons[DefIndex].Stickers[1].iID = item.Sticker2;
//					g_Weapons[DefIndex].Stickers[2].iID = item.Sticker3;
//					g_Weapons[DefIndex].Stickers[3].iID = item.Sticker4;
//				}
//
//				if (item.EquiptedTT)
//				{
//					if (DefIndex.IsKnife())
//					{
//						Options::SkinChanger::EnabledKnife = true;
//						if (DefIndex == WEAPON_KNIFE_BAYONET) Options::SkinChanger::KnifeTT = 0;
//						else if (DefIndex == WEAPON_KNIFE_FLIP) Options::SkinChanger::KnifeTT = 1;
//						else if (DefIndex == WEAPON_KNIFE_GUT) Options::SkinChanger::KnifeTT = 2;
//						else if (DefIndex == WEAPON_KNIFE_KARAMBIT) Options::SkinChanger::KnifeTT = 3;
//						else if (DefIndex == WEAPON_KNIFE_M9_BAYONET) Options::SkinChanger::KnifeTT = 4;
//						else if (DefIndex == WEAPON_KNIFE_TACTICAL) Options::SkinChanger::KnifeTT = 5;
//						else if (DefIndex == WEAPON_KNIFE_FALCHION) Options::SkinChanger::KnifeTT = 6;
//						else if (DefIndex == WEAPON_KNIFE_SURVIVAL_BOWIE) Options::SkinChanger::KnifeTT = 7;
//						else if (DefIndex == WEAPON_KNIFE_BUTTERFLY) Options::SkinChanger::KnifeTT = 8;
//						else if (DefIndex == WEAPON_KNIFE_PUSH) Options::SkinChanger::KnifeTT = 9;
//
//						//Options::SkinChanger::KnifeTTSkin = item.Skin;
//						//Options::SkinChanger::KnifeTTWear = item.Wear;
//						//Options::SkinChanger::KnifeTTSeed = item.Seed;
//						//Options::SkinChanger::KnifeTTST = item.StatTrak;
//					}
//
//					g_Weapons[DefIndex].ChangerSkinTT = item.Skin;
//					g_Weapons[DefIndex].ChangerWearTT = item.Wear;
//					g_Weapons[DefIndex].ChangerSeedTT = item.Seed;
//					g_Weapons[DefIndex].ChangerStatTrakTT = item.StatTrak;
//					s_strcpy(g_Weapons[DefIndex].ChangerNameTT, item.Name);
//
//					g_Weapons[DefIndex].Stickers[0].iID = item.Sticker1;
//					g_Weapons[DefIndex].Stickers[1].iID = item.Sticker2;
//					g_Weapons[DefIndex].Stickers[2].iID = item.Sticker3;
//					g_Weapons[DefIndex].Stickers[3].iID = item.Sticker4;
//				}
//			}
//		}
//	}
//
//	void ReEquip(int DefIndex, int WeaponIndex, bool CT, bool TT)
//	{
//		for (auto item : m_Items)
//		{
//			if (DefIndex == (int)ItemIdToWeaponId(item.ID))
//			{
//				if (item.EquiptedCT || item.EquiptedTT)
//				{
//					if (WeaponIndex == item.Index)
//						continue;
//
//					if (CT)
//						m_Items[item.Index].EquiptedCT = false;
//
//					if (TT)
//						m_Items[item.Index].EquiptedTT = false;
//				}
//			}
//		}
//	}
//
//	string GetGunsString()
//	{
//		string str;
//
//		for (auto& item : m_Items)
//		{
//			if (item.ID == 0)
//				str += "None";
//			else if (!s_strcmp(item.Name, ""))
//				str += Parser::Weapons.List[item.ID].szName;
//			else
//			{
//				str.push_back('\"');
//				str += item.Name;
//				str.push_back('\"');
//			}
//
//			str.push_back('\0');
//		}
//
//		str.push_back('\0');
//		str.push_back('\0');
//		return str;
//	}
//
//	void PostRetrieveMessage(uint32_t MsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
//	{
//		CMsgClientWelcome Message;
//
//		if (!Message.ParsePartialFromArray((void*)((DWORD)pubDest + 8), *pcubMsgSize - 8))
//			return;
//
//		if (Message.outofdate_subscribed_caches_size() <= 0)
//			return;
//
//		CMsgSOCacheSubscribed* Cache = Message.mutable_outofdate_subscribed_caches(0);
//
//		for (int i = 0; i < Cache->objects_size(); i++)
//		{
//			CMsgSOCacheSubscribed::SubscribedType* Object = Cache->mutable_objects(i);
//
//			if (!Object->has_type_id())
//				continue;
//
//			if (Object->type_id() != 1) // Inventory
//				continue;
//
//			for (int j = 0; j < Object->object_data_size(); j++)
//			{
//				string* ObjectData = Object->mutable_object_data(j);
//				CSOEconItem Item;
//				if (!Item.ParseFromArray((void*)const_cast<char*>(ObjectData->data()), ObjectData->size()))
//					continue;
//				if (Item.equipped_state_size() <= 0)
//					continue;
//
//				for (int k = 0; k < Item.equipped_state_size(); k++)
//				{
//					CSOEconItemEquipped* EquippedState = Item.mutable_equipped_state(k);
//					auto c = EquippedState->new_class();
//
//					for (auto& item : m_Items)
//					{
//						if (ItemIdToWeaponId(item.ID) == Item.def_index())
//						{
//							if (item.EquiptedCT && c == CS_TEAM_CT)
//							{
//								EquippedState->set_new_class(0);
//								EquippedState->set_new_slot(0);
//							}
//
//							if (item.EquiptedTT && c == CS_TEAM_TT)
//							{
//								EquippedState->set_new_class(0);
//								EquippedState->set_new_slot(0);
//							}
//
//							SetupSkins();
//						}
//					}
//				}
//
//				ObjectData->resize(Item.ByteSize());
//				Item.SerializeToArray((void*)const_cast<char*>(ObjectData->data()), Item.ByteSize());
//			}
//
//			CSteamID LocalSteamID = g_pSteamUser->GetSteamID();
//
//			int j = 1;
//
//			for (auto& item : m_Items)
//			{
//				if (item.ID == 0)
//					continue;
//
//				auto def_index = ItemIdToWeaponId(item.ID);
//				auto paint_kit = Parser::Skins[def_index].List[item.Skin].iID;
//
//				CSOEconItem Skin;
//				Skin.set_id(item.BuildItemID());
//				Skin.set_account_id(LocalSteamID.GetAccountID());
//				Skin.set_def_index(def_index);
//				Skin.set_inventory(20000 + j);
//				Skin.set_origin(24);
//				Skin.set_quantity(1);
//				Skin.set_level(1);
//				Skin.set_style(0);
//				Skin.set_flags(0);
//				Skin.set_in_use(false);
//				Skin.set_original_id(0);
//
//				// Custom name
//				if (s_strcmp(item.Name, ""))
//					Skin.set_custom_name(item.Name);
//
//				// Rarity & quality
//				if (def_index.IsKnife())
//				{
//					Skin.set_rarity(6);
//					Skin.set_quality(3);
//				}
//				else
//				{
//					if (item.Quality > 0)
//					{
//						int quality = item.Quality;
//						if (quality > 2) quality += 2;
//						if (quality > 8) quality += 1;
//						if (quality > 10) quality += 1;
//
//						Skin.set_quality(quality);
//					}
//					Skin.set_rarity(Parser::Skins[def_index].List[item.Skin].iRarity);
//				}
//
//				CSOEconItemEquipped* EquippedState = Skin.add_equipped_state();
//
//				if (item.EquiptedCT)
//				{
//					EquippedState->set_new_class(CS_TEAM_CT);
//					EquippedState->set_new_slot(item.ID);
//					SetupSkins();
//				}
//
//				if (item.EquiptedTT)
//				{
//					EquippedState->set_new_class(CS_TEAM_TT);
//					EquippedState->set_new_slot(item.ID);
//					SetupSkins();
//				}
//
//				CSOEconItemAttribute* PaintKitAttribute = Skin.add_attribute();
//				float PaintKitAttributeValue = paint_kit;
//				PaintKitAttribute->set_def_index(6);
//				PaintKitAttribute->set_value_BYTEs(&PaintKitAttributeValue, 4);
//
//				CSOEconItemAttribute* SeedAttribute = Skin.add_attribute();
//				float SeedAttributeValue = item.Seed;
//				SeedAttribute->set_def_index(7);
//				SeedAttribute->set_value_BYTEs(&SeedAttributeValue, 4);
//
//				CSOEconItemAttribute* WearAttribute = Skin.add_attribute();
//				float WearAttributeValue = item.Wear;
//				WearAttribute->set_def_index(8);
//				WearAttribute->set_value_BYTEs(&WearAttributeValue, 4);
//
//				if (item.StatTrak > 0)
//				{
//					CSOEconItemAttribute* StatTrakAttribute = Skin.add_attribute();
//					uint32_t StatTrakAttributeValue = 0;
//					StatTrakAttribute->set_def_index(81);
//					StatTrakAttribute->set_value_BYTEs(&StatTrakAttributeValue, 4);
//
//					CSOEconItemAttribute* StatTrakCountAttribute = Skin.add_attribute();
//					uint32_t StatTrakCountAttributeValue = item.StatTrak;
//					StatTrakCountAttribute->set_def_index(80);
//					StatTrakCountAttribute->set_value_BYTEs(&StatTrakCountAttributeValue, 4);
//
//					Skin.set_quality(9);
//				}
//
//				// Sticker Kit
//				CSOEconItemAttribute* StickerKitAttribute1 = Skin.add_attribute();
//				CSOEconItemAttribute* StickerKitAttribute2 = Skin.add_attribute();
//				CSOEconItemAttribute* StickerKitAttribute3 = Skin.add_attribute();
//				CSOEconItemAttribute* StickerKitAttribute4 = Skin.add_attribute();
//
//				StickerKitAttribute1->set_def_index(113 + 4 * 0);
//				StickerKitAttribute1->set_value_BYTEs(&Parser::Stickers.List[item.Sticker1].iID, 4);
//
//				StickerKitAttribute2->set_def_index(113 + 4 * 1);
//				StickerKitAttribute2->set_value_BYTEs(&Parser::Stickers.List[item.Sticker2].iID, 4);
//
//				StickerKitAttribute3->set_def_index(113 + 4 * 2);
//				StickerKitAttribute3->set_value_BYTEs(&Parser::Stickers.List[item.Sticker3].iID, 4);
//
//				StickerKitAttribute4->set_def_index(113 + 4 * 3);
//				StickerKitAttribute4->set_value_BYTEs(&Parser::Stickers.List[item.Sticker4].iID, 4);
//
//				for (int m = 0; m < 4; m++)
//				{
//					// Sticker Wear
//					CSOEconItemAttribute* StickerWearAttribute = Skin.add_attribute();
//					float StickerWearAttributeValue = 0.001f;
//					StickerWearAttribute->set_def_index(114 + 4 * m);
//					StickerWearAttribute->set_value_BYTEs(&StickerWearAttributeValue, 4);
//
//					// Sticker Scale
//					CSOEconItemAttribute* StickerScaleAttribute = Skin.add_attribute();
//					float StickerScaleAttributeValue = 1.f;
//					StickerScaleAttribute->set_def_index(115 + 4 * m);
//					StickerScaleAttribute->set_value_BYTEs(&StickerScaleAttributeValue, 4);
//
//					// Sticker Rotation
//					CSOEconItemAttribute* StickerRotationAttribute = Skin.add_attribute();
//					float StickerRotationAttributeValue = 0.f;
//					StickerRotationAttribute->set_def_index(116 + 4 * m);
//					StickerRotationAttribute->set_value_BYTEs(&StickerRotationAttributeValue, 4);
//				}
//
//				Object->add_object_data(Skin.SerializeAsString());
//				j++;
//			}
//		}
//
//		if ((uint32_t)Message.ByteSize() <= cubDest - 8)
//		{
//			Message.SerializeToArray((void*)((DWORD)pubDest + 8), Message.ByteSize());
//
//			*pcubMsgSize = Message.ByteSize() + 8;
//		}
//	}
//
//	bool PreSendMessage(void* pubData, uint32_t &cubData)
//	{
//		CMsgAdjustItemEquippedState Message;
//		if (!Message.ParsePartialFromArray((void*)((DWORD)pubData + 8), cubData - 8))
//			return false;
//
//		if (!Message.has_item_id()
//			|| !Message.has_new_class()
//			|| !Message.has_new_slot())
//			return false;
//
//		auto itemID = (uint32_t)Message.item_id();
//
//		for (auto item : m_Items)
//		{
//			if (itemID != item.UniqueID)
//				continue;
//
//			if (Message.new_class() == CS_TEAM_CT)
//			{
//				m_Items[item.Index].EquiptedCT = true;
//				ReEquip(ItemIdToWeaponId(item.ID), item.Index, true, false);
//			}
//
//			if (Message.new_class() == CS_TEAM_TT)
//			{
//				m_Items[item.Index].EquiptedTT = true;
//				ReEquip(ItemIdToWeaponId(item.ID), item.Index, false, true);
//			}
//
//			SetupSkins();
//			U::FullUpdate();
//		}
//		return true;
//	}
//}
