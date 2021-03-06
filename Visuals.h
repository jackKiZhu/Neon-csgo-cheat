#pragma once

extern QAngle g_RealAngle;
extern QAngle g_FakeAngle;

std::vector<int> getcolor(int iHealth) {
	if (iHealth <= 10) return { 51, 14, 0 };
	if (iHealth <= 30) return { 255, 72, 0 };
	if (iHealth <= 60) return { 255, 136, 0 };
	if (iHealth <= 80) return { 255, 234, 0 };
	if (iHealth <= 100) return { 0, 255, 0 };
	
	
	
}
namespace CVisuals
{
	const float flAlphaSpeed = 600.f;
	int iPlayersAlpha[128];

	void W2S_Line( Vector3 vecFirst, Vector3 vecSecond, Color clrColor ) {
		// TODO: Remove this usseless shit
		/*Vector3 vecFirstScreen;
		Vector3 vecSecondScreen;
		if (!Math::WorldToScreen(Vector3(vecFirst.x, vecFirst.y, vecFirst.z), vecFirstScreen))
			return;
		if (!Math::WorldToScreen(Vector3(vecSecond.x, vecSecond.y, vecSecond.z), vecSecondScreen))
			return;*/

		D::Line( ( int )vecFirst.x, ( int )vecFirst.y, ( int )vecSecond.x, ( int )vecSecond.y, clrColor, 1, false );
	} // TODO: Refactor

	void Box3D( Vector3 vecLower, float flSize, Color clrColor, float flAlpha, int i, int playeridx) {
		
		clrColor[3] = iPlayersAlpha[i];
		if (i > 0 && Options::Visuals::ESP::playerlist::whitelist[i - 1] && clrColor.a() > 230)
			clrColor = Options::Visuals::ESP::DaunColor;
		Vector3 mins = Vector3( vecLower.x - 20, vecLower.y - 20, vecLower.z );
		Vector3 maxs = Vector3( vecLower.x + 20, vecLower.y + 20, vecLower.z + flSize );

		Vector3 firstDown = Vector3( mins.x, mins.y, mins.z );
		Vector3 secondDown = Vector3( mins.x, maxs.y, mins.z );
		Vector3 thirdDown = Vector3( maxs.x, maxs.y, mins.z );
		Vector3 fourthDown = Vector3( maxs.x, mins.y, mins.z );

		Vector3 firstUp = Vector3( mins.x, mins.y, maxs.z );
		Vector3 secondUp = Vector3( mins.x, maxs.y, maxs.z );
		Vector3 thirdUp = Vector3( maxs.x, maxs.y, maxs.z );
		Vector3 fourthUp = Vector3( maxs.x, mins.y, maxs.z );

		if( !Math::WorldToScreen( firstDown, firstDown ) ) return;
		if( !Math::WorldToScreen( secondDown, secondDown ) ) return;
		if( !Math::WorldToScreen( thirdDown, thirdDown ) ) return;
		if( !Math::WorldToScreen( fourthDown, fourthDown ) ) return;

		if( !Math::WorldToScreen( firstUp, firstUp ) ) return;
		if( !Math::WorldToScreen( secondUp, secondUp ) ) return;
		if( !Math::WorldToScreen( thirdUp, thirdUp ) ) return;
		if( !Math::WorldToScreen( fourthUp, fourthUp ) ) return;

		W2S_Line( firstDown, secondDown, clrColor );
		W2S_Line( secondDown, thirdDown, clrColor );
		W2S_Line( thirdDown, fourthDown, clrColor );
		W2S_Line( fourthDown, firstDown, clrColor );

		W2S_Line( firstUp, secondUp, clrColor );
		W2S_Line( secondUp, thirdUp, clrColor );
		W2S_Line( thirdUp, fourthUp, clrColor );
		W2S_Line( fourthUp, firstUp, clrColor );

		W2S_Line( firstDown, firstUp, clrColor );
		W2S_Line( secondDown, secondUp, clrColor );
		W2S_Line( thirdDown, thirdUp, clrColor );
		W2S_Line( fourthDown, fourthUp, clrColor );

		if( flAlpha > 0 ) {
			clrColor[3] = flAlpha;
			if( iPlayersAlpha[i] < clrColor[3] ) clrColor[3] = iPlayersAlpha[i];
			D::m_pDrawList->AddQuadFilled( { firstDown.x, firstDown.y }, { firstUp.x, firstUp.y }, { secondUp.x, secondUp.y }, { secondDown.x, secondDown.y }, D::GetImColor( clrColor ) );
			D::m_pDrawList->AddQuadFilled( { secondDown.x, secondDown.y }, { secondUp.x, secondUp.y }, { thirdUp.x, thirdUp.y }, { thirdDown.x, thirdDown.y }, D::GetImColor( clrColor ) );
			D::m_pDrawList->AddQuadFilled( { thirdDown.x, thirdDown.y }, { thirdUp.x, thirdUp.y }, { fourthUp.x, fourthUp.y }, { fourthDown.x, fourthDown.y }, D::GetImColor( clrColor ) );
			D::m_pDrawList->AddQuadFilled( { fourthDown.x, fourthDown.y }, { fourthUp.x, fourthUp.y }, { firstUp.x, firstUp.y }, { firstDown.x, firstDown.y }, D::GetImColor( clrColor ) );
			D::m_pDrawList->AddQuadFilled( { firstUp.x, firstUp.y }, { secondUp.x, secondUp.y }, { thirdUp.x, thirdUp.y }, { fourthUp.x, fourthUp.y }, D::GetImColor( clrColor ) );
			D::m_pDrawList->AddQuadFilled( { firstDown.x, firstDown.y }, { secondDown.x, secondDown.y }, { thirdDown.x, thirdDown.y }, { fourthDown.x, fourthDown.y }, D::GetImColor( clrColor ) );
		}
	}
	//пошли мм тестить.
	//мне тоже выдай длл и акк,если есть.

	void DrawEspBox( Vector3 leftUpCorn, Vector3 rightDownCorn, Color clr, float w , int playeridx) {
		if (playeridx > 0 && Options::Visuals::ESP::playerlist::whitelist[playeridx - 1] && clr.a() > 230)
			clr = Options::Visuals::ESP::DaunColor;
		
		leftUpCorn.x = ( int )leftUpCorn.x;
		leftUpCorn.y = ( int )leftUpCorn.y;
		rightDownCorn.x = ( int )rightDownCorn.x;
		rightDownCorn.y = ( int )rightDownCorn.y;
		/*
		D::Line( leftUpCorn.x, leftUpCorn.y, leftUpCorn.x, rightDownCorn.y, clr, w, false );
		D::Line( leftUpCorn.x, rightDownCorn.y, rightDownCorn.x, rightDownCorn.y, clr, w, false );
		D::Line( rightDownCorn.x, rightDownCorn.y, rightDownCorn.x, leftUpCorn.y, clr, w, false );
		D::Line( rightDownCorn.x, leftUpCorn.y, leftUpCorn.x, leftUpCorn.y, clr, w, false );
		*/
		//D::RectFilled(leftUpCorn.x, leftUpCorn.y,
			//rightDownCorn.x - leftUpCorn.x, rightDownCorn.y - leftUpCorn.y, clr, false, false);
		D::Rect(leftUpCorn.x, leftUpCorn.y,
			rightDownCorn.x - leftUpCorn.x, rightDownCorn.y - leftUpCorn.y, w, clr, true, false, false);
	}
	
	void DrawCorner(const Vector3 leftUpCorn, const Vector3 rightUpCorn, const Vector3 leftDownCorn, const Vector3 rightDownCorn, Color clr, float width, int playeridx) {

		if (playeridx > 0 && Options::Visuals::ESP::playerlist::whitelist[playeridx - 1] && clr.a() > 230)
			clr = Options::Visuals::ESP::DaunColor;

		int edge = (rightUpCorn.x - leftUpCorn.x) / Options::Visuals::ESP::CornerOffsets;

		D::Line(rightUpCorn.x, rightUpCorn.y, rightUpCorn.x, rightUpCorn.y + edge, clr, width, false);
		D::Line(rightUpCorn.x, rightUpCorn.y, rightUpCorn.x - edge, rightUpCorn.y, clr, width, false);
		D::Line(leftUpCorn.x, leftUpCorn.y, leftUpCorn.x, leftUpCorn.y + edge, clr, width, false);
		D::Line(leftUpCorn.x, leftUpCorn.y, leftUpCorn.x + edge, leftUpCorn.y, clr, width, false);
		D::Line(rightDownCorn.x, rightDownCorn.y, rightDownCorn.x, rightDownCorn.y - edge, clr, width, false);
		D::Line(rightDownCorn.x, rightDownCorn.y, rightDownCorn.x - edge, rightDownCorn.y, clr, width, false);
		D::Line(leftDownCorn.x, leftDownCorn.y, leftDownCorn.x, leftDownCorn.y - edge, clr, width, false);
		D::Line(leftDownCorn.x, leftDownCorn.y, leftDownCorn.x + edge, leftDownCorn.y, clr, width, false);
	}

	void DrawEsp( C_BasePlayer* pBaseEntity, bool isEnemy, bool isVisibled, bool isVisibledSmoke, bool isLocal, int i ) {
		if( !pBaseEntity )
			return;

		if( Options::Visuals::ESP::EnemyOnly && !isEnemy && !isLocal )
			return;

		if( Options::Visuals::ESP::VisibleOnly && !isVisibled )
			return;

		if( Options::Visuals::ESP::SmokeCheck && !isVisibledSmoke )
			return;

		if (Options::Visuals::ESP::playerlist::no_esp[i - 1])
			return;
		// SKELETON

		/*studiohdr_t* pStudioModel = g_pModelInfo->GetStudioModel(pBaseEntity->GetPlayerModel());
		if (pStudioModel)
		{
			static matrix3x4 pBoneToWorldOut[128];
			if (pBaseEntity->SetupBones(pBoneToWorldOut, 128, 256, g_pGlobals->curtime))
			{
				for (int i = 0; i < pStudioModel->numbones; i++)
				{
					mstudiobone_t* pBone = pStudioModel->pBone(i);
					if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
						continue;

					Vector3 vBonePos1;
					if (!Math::WorldToScreen(Vector3(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
						continue;

					Vector3 vBonePos2;
					if (!Math::WorldToScreen(Vector3(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
						continue;

					D::Line(vBonePos1.x, vBonePos1.y, vBonePos2.x, vBonePos2.y, Color::White());
				}
			}
		}*/

		// SKELETON

		Vector3 m_vecFoot = pBaseEntity->GetAbsOrigin( );
		Vector3 m_vecHead;
		Vector3 m_screenFoot;
		Vector3 m_screenHead;

		float flAdjustment = 0;
		if( ( pBaseEntity->Flags( ) & FL_DUCKING ) )
			flAdjustment += 50.f;
		else flAdjustment += 70.f;

		//m_vecFoot -= pBaseEntity->Velocity() * g_pGlobals->interval_per_tick;
		//m_vecHead -= pBaseEntity->Velocity() * g_pGlobals->interval_per_tick;
		m_vecFoot.z -= Options::Visuals::ESP::BoxSize;
		flAdjustment += Options::Visuals::ESP::BoxSize * 2;
		m_vecHead = m_vecFoot + Vector3( 0, 0, flAdjustment );

		if( Math::WorldToScreen( m_vecFoot, m_screenFoot ) &&
			Math::WorldToScreen( m_vecHead, m_screenHead ) ) {
			m_screenFoot.x = ( int )m_screenFoot.x;
			m_screenFoot.y = ( int )m_screenFoot.y;

			float lineHeight = ( m_screenFoot.y - m_screenHead.y );
			int edgeWidth = lineHeight / 4;
			int lineWidth = edgeWidth;
			edgeWidth /= 1.5f;

			const float OUTLINE_WIDTH = 3;
			const float LINE_WIDTH = 1;

			Vector3 leftUpCorn = Vector3( m_screenFoot.x - lineWidth, m_screenHead.y, 0.f );
			Vector3 rightUpCorn = Vector3( m_screenFoot.x + lineWidth, m_screenHead.y, 0.f );
			Vector3 leftDownCorn = Vector3( m_screenFoot.x - lineWidth, m_screenFoot.y, 0.f );
			Vector3 rightDownCorn = Vector3( m_screenFoot.x + lineWidth, m_screenFoot.y, 0.f );
			int iHealth = pBaseEntity->Health();
			std::vector<int> vcolor = getcolor(iHealth);
			if( Options::Visuals::ESP::Box ) {
				//Color col = isVisibled ? Color(0, 255, 0) : Color::Blue();
				Color col = isEnemy ? ( isVisibled ? Options::Visuals::ESP::VisibleColor : Options::Visuals::ESP::InvisibleColor ) : Options::Visuals::ESP::TeammmateColor;
				col[3] = iPlayersAlpha[i];

				switch( Options::Visuals::ESP::Style ) {
				case 1: // default w\ outline
				{
					/*const matrix3x4& trans = *(matrix3x4*)(pBaseEntity + NetVarManager::GetOffset("DT_BaseEntity", "m_CollisionGroup") - 0x30);

					//Vector3 min = *(Vector3*)(pBaseEntity + NetVarManager::GetOffset("DT_BaseEntity", "m_Collision") + NetVarManager::GetOffset("DT_CollisionProperty", "m_vecMins"));
					//Vector3 max = *(Vector3*)(pBaseEntity + NetVarManager::GetOffset("DT_BaseEntity", "m_Collision") + NetVarManager::GetOffset("DT_CollisionProperty", "m_vecMaxs"));

					Vector3 min;
					Vector3 max;
					pBaseEntity->GetRenderBoundsWorldspace(min, max);
					//min -= pBaseEntity->GetRenderOrigin();
					//max -= pBaseEntity->GetRenderOrigin();

					Vector3 pointList[] =
					{
						Vector3(min.x, min.y, min.z),
						Vector3(min.x, max.y, min.z),
						Vector3(max.x, max.y, min.z),
						Vector3(max.x, min.y, min.z),
						Vector3(max.x, max.y, max.z),
						Vector3(min.x, max.y, max.z),
						Vector3(min.x, min.y, max.z),
						Vector3(max.x, min.y, max.z)
					};

					Vector3 transformed[8];

					for (int i = 0; i < 8; i++)
						Math::VectorTransform(pointList[i], trans, transformed[i]);

					Vector3 flb, brt, blb, frt, frb, brb, blt, flt;

					if (!Math::WorldToScreen(transformed[3], flb) || !Math::WorldToScreen(transformed[5], brt)
						|| !Math::WorldToScreen(transformed[0], blb) || !Math::WorldToScreen(transformed[4], frt)
						|| !Math::WorldToScreen(transformed[2], frb) || !Math::WorldToScreen(transformed[1], brb)
						|| !Math::WorldToScreen(transformed[6], blt) || !Math::WorldToScreen(transformed[7], flt))
						return;

					Vector3 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

					float left = flb.x;
					float top = flb.y;
					float right = flb.x;
					float bottom = flb.y;

					for (int i = 0; i < 8; i++)
					{
						if (left > arr[i].x)
							left = arr[i].x;
						if (top < arr[i].y)
							top = arr[i].y;
						if (right < arr[i].x)
							right = arr[i].x;
						if (bottom > arr[i].y)
							bottom = arr[i].y;
					}

					D::Line(left, bottom, left, top, col, LINE_WIDTH);
					D::Line(left, top, right, top, col, LINE_WIDTH);
					D::Line(right, top, right, bottom, col, LINE_WIDTH);
					D::Line(right, bottom, left, bottom, col, LINE_WIDTH);*/
					
					DrawEspBox( leftUpCorn, rightDownCorn, Color::Black( iPlayersAlpha[i] ), OUTLINE_WIDTH, pBaseEntity->index());
					if( Options::Visuals::ESP::BoxCheckColor ) {
						DrawEspBox( leftUpCorn, rightDownCorn, Color(vcolor[0], vcolor[1], vcolor[2]), Options::Visuals::ESP::BoxWidth, pBaseEntity->index());
						
					}
					if( !Options::Visuals::ESP::BoxCheckColor )DrawEspBox( leftUpCorn, rightDownCorn, col, Options::Visuals::ESP::BoxWidth, pBaseEntity->index());
					break;
				}
				case 2: // corner
				{
					int iHealth = pBaseEntity->Health( );
					if( Options::Visuals::ESP::BoxCheckColor ) {
						DrawCorner( leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, Color(vcolor[0], vcolor[1], vcolor[2]), LINE_WIDTH, pBaseEntity->index());
					
					}
					if( !Options::Visuals::ESP::BoxCheckColor ) DrawCorner( leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, col, LINE_WIDTH, pBaseEntity->index());
					break;
				}
				case 3: // corner w\ outline
				{
					int iHealth = pBaseEntity->Health( );
					DrawCorner( leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, Color::Black( iPlayersAlpha[i] ), OUTLINE_WIDTH, pBaseEntity->index());
					if( Options::Visuals::ESP::BoxCheckColor ) {
						DrawCorner( leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, Color(vcolor[0], vcolor[1], vcolor[2]), LINE_WIDTH, pBaseEntity->index());
					}

					if( !Options::Visuals::ESP::BoxCheckColor )DrawCorner( leftUpCorn, rightUpCorn, leftDownCorn, rightDownCorn, col, LINE_WIDTH, pBaseEntity->index());

					break;
				}
				case 4: // 2d filled
				{
					Color nc = Options::Visuals::ESP::FilledColor;
					nc[3] = Options::Visuals::ESP::Opacity;
					if( iPlayersAlpha[i] < nc[3] ) nc[3] = iPlayersAlpha[i];
					D::RectFilledXY( leftUpCorn.x, leftUpCorn.y, rightDownCorn.x, rightDownCorn.y, nc );
					DrawEspBox( leftUpCorn, rightDownCorn, Color::Black( iPlayersAlpha[i] ), OUTLINE_WIDTH, pBaseEntity->index());
					DrawEspBox( leftUpCorn, rightDownCorn, col, LINE_WIDTH, pBaseEntity->index());
					break;
				}
				case 5: // 3d
				{
					int iHealth = pBaseEntity->Health( );
					if( Options::Visuals::ESP::BoxCheckColor ) {
						Box3D( m_vecFoot, flAdjustment, Color(vcolor[0], vcolor[1], vcolor[2]), 0, i , pBaseEntity->index());
						
					}
					if( !Options::Visuals::ESP::BoxCheckColor )Box3D( m_vecFoot, flAdjustment, col, 0, i, pBaseEntity->index());
					//g_pDebugOverlay->AddBoxOverlay(m_vecFoot, Vector3(-20.f, -20.f, 0), Vector3(20, 20, flAdjustment), Vector3(0, 0, 0), col.r(), col.g(), col.b(), 0, 1);
					break;
				}
				case 6: // 3d filled
				{
					Box3D( m_vecFoot, flAdjustment, col, Options::Visuals::ESP::Opacity, i, pBaseEntity->index());
					//g_pDebugOverlay->AddBoxOverlay(m_vecFoot, Vector3(-20.f, -20.f, 0), Vector3(20, 20, flAdjustment), Vector3(0, 0, 0), col.r(), col.g(), col.b(), Options::Visuals::ESP::Opacity, 1);
					break;
				}
				default: // Default
				{
					int iHealth = pBaseEntity->Health( );
					if( Options::Visuals::ESP::BoxCheckColor ) {
						DrawEspBox( leftUpCorn, rightDownCorn, Color( vcolor[0], vcolor[1], vcolor[2] ), Options::Visuals::ESP::BoxWidth, pBaseEntity->index());
					

					}
					if( !Options::Visuals::ESP::BoxCheckColor )DrawEspBox( leftUpCorn, rightDownCorn, col, Options::Visuals::ESP::BoxWidth, pBaseEntity->index());
					break;
				}
				}
			}

			if( Options::Visuals::ESP::Health ) {
				if( Options::Visuals::ESP::HealthType == 1 ) {
					int iHealth = pBaseEntity->Health( );
					int iMaxHealth = pBaseEntity->MaxHealth( );
					float flPixelPerHP = lineHeight / 100.f;
					int iAdjust = 3;
					float flHealthPos = ( ( flPixelPerHP * ( 100 - iHealth ) ) );

					int iDiff = /*1 +*/ ( Options::Visuals::ESP::Style == 1 || Options::Visuals::ESP::Style == 3 ? 1 : 0 );
					//left
					if( Options::Visuals::ESP::HealthPos == 0 ) {
						D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, Options::Visuals::ESP::HealthWidth + 2, false);
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if (!Options::Visuals::ESP::HealthCheckColor)if (iHealth <= 100) { D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false); }
						if (Options::Visuals::ESP::HealthCheckColor) {
							D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Color(0, 0, 0), Options::Visuals::ESP::HealthWidth + 2, false);
							{ D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]), Options::Visuals::ESP::HealthWidth, false); }
						}
						//D::Text(leftUpCorn.x - iAdjust, leftUpCorn.y + flHealthPos, Color::White(), true, true, Font::Small, "%d", iHealth);
						const int LINES_COUNT = 6;
						const float PIXELS_PER_LINE = lineHeight / LINES_COUNT;
						for (int j = 1; j < LINES_COUNT; j++) {
							int iLineAdjust = PIXELS_PER_LINE * j;
							D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth, leftUpCorn.y + iLineAdjust, leftUpCorn.x - iAdjust, leftUpCorn.y + iLineAdjust, Color::Black(), 1.4, false);
						}
					}
					//right
					if( Options::Visuals::ESP::HealthPos == 1 ) {
						D::Line( rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, 4, false );
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if( !Options::Visuals::ESP::HealthCheckColor ) if( iHealth <= 100 ) { D::Line( rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false ); }
						if( Options::Visuals::ESP::HealthCheckColor ) {
							D::Line( rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Color( 0, 0, 0 ), Options::Visuals::ESP::HealthWidth + 2, false );
							if( iHealth <= 100 ) { D::Line( rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i] ), Options::Visuals::ESP::HealthWidth, false ); }
						}
						D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, Options::Visuals::ESP::HealthWidth + 2, false);
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if (!Options::Visuals::ESP::HealthCheckColor)if (iHealth <= 100) { D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false); }
						if (Options::Visuals::ESP::HealthCheckColor) {
							D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Color(0, 0, 0), Options::Visuals::ESP::HealthWidth + 2, false);
							{ D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]), Options::Visuals::ESP::HealthWidth, false); }
						}
						//D::Text(leftUpCorn.x - iAdjust, leftUpCorn.y + flHealthPos, Color::White(), true, true, Font::Small, "%d", iHealth);
						const int LINES_COUNT = 6;
						const float PIXELS_PER_LINE = lineHeight / LINES_COUNT;
						for (int j = 1; j < LINES_COUNT; j++) {
							int iLineAdjust = PIXELS_PER_LINE * j;
							D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth, leftUpCorn.y + iLineAdjust, leftUpCorn.x - iAdjust, leftUpCorn.y + iLineAdjust, Color::Black(), 1.4, false);
						}
						//D::Text(leftUpCorn.x - iAdjust, leftUpCorn.y + flHealthPos, Color::White(), true, true, Font::Small, "%d", iHealth);
						for( int j = 1; j < LINES_COUNT; j++ ) {
							int iLineAdjust = PIXELS_PER_LINE * j;
							D::Line( rightUpCorn.x - iAdjust + 4.6 , rightUpCorn.y + iLineAdjust, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth, rightUpCorn.y + iLineAdjust, Color::Black( ), 1.4, false );
						}

					}
					//all
					if( Options::Visuals::ESP::HealthPos == 2 ) {
						D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, 4, false);
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if (!Options::Visuals::ESP::HealthCheckColor) if (iHealth <= 100) { D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false); }
						if (Options::Visuals::ESP::HealthCheckColor) {
							D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Color(0, 0, 0), Options::Visuals::ESP::HealthWidth + 2, false);
							if (iHealth <= 100) { D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]), Options::Visuals::ESP::HealthWidth, false); }
						}
						//D::Text(leftUpCorn.x - iAdjust, leftUpCorn.y + flHealthPos, Color::White(), true, true, Font::Small, "%d", iHealth);
						const int LINES_COUNT = 6;
						const float PIXELS_PER_LINE = lineHeight / LINES_COUNT;
						for (int j = 1; j < LINES_COUNT; j++) {
							int iLineAdjust = PIXELS_PER_LINE * j;
							D::Line(rightUpCorn.x - iAdjust + 4.6, rightUpCorn.y + iLineAdjust, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth, rightUpCorn.y + iLineAdjust, Color::Black(), 1.4, false);
						}


					}
					if (Options::Visuals::ESP::HealthPos == 3)
					{
						
						if (Options::Visuals::ESP::HealthCheckColor) {
							
							D::RectFilled(leftUpCorn.x - iAdjust + 3, leftDownCorn.y + 2 - iDiff, (rightUpCorn.x - leftUpCorn.x) * iHealth / 100, iDiff + 2 + Options::Visuals::ESP::HealthWidth, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]));
						}
						else D::RectFilled(leftUpCorn.x - iAdjust + 3, leftDownCorn.y + 2 - iDiff, (rightUpCorn.x - leftUpCorn.x) * iHealth / 100, iDiff + 2 + Options::Visuals::ESP::HealthWidth, Options::Visuals::ESP::HealthFalse); // в следующий раз включай боксы
						for (int i = 1; i < 6; ++i) {
							D::Line(leftUpCorn.x - iAdjust + 3 + (rightUpCorn.x - leftUpCorn.x) * i / 6, leftDownCorn.y + 2 - iDiff, leftUpCorn.x - iAdjust + 3 + (rightUpCorn.x - leftUpCorn.x) * i / 6, leftDownCorn.y - 1 - iDiff + iDiff + 2 + iDiff + 2 + Options::Visuals::ESP::HealthWidth, Color::Black());
						}
						D::Rect(leftUpCorn.x - iAdjust + 3, leftDownCorn.y + 2 - iDiff, rightUpCorn.x - leftUpCorn.x, iDiff + 2 + iDiff + Options::Visuals::ESP::HealthWidth, 1, Color(0, 0, 0));
					}
				} else {
					int iHealth = pBaseEntity->Health( );
					int iMaxHealth = pBaseEntity->MaxHealth( );
					float flPixelPerHP = lineHeight / 100.f;
					int iAdjust = 3;
					float flHealthPos = ( ( flPixelPerHP * ( 100 - iHealth ) ) );

					int iDiff = /*1 +*/ ( Options::Visuals::ESP::Style == 1 || Options::Visuals::ESP::Style == 3 ? 1 : 0 );
					//left
					if (Options::Visuals::ESP::HealthPos == 0) {
						D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, Options::Visuals::ESP::HealthWidth + 2, false);
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if (!Options::Visuals::ESP::HealthCheckColor)if (iHealth <= 100) { D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false); }
						if (Options::Visuals::ESP::HealthCheckColor) {
							D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Color(0, 0, 0), Options::Visuals::ESP::HealthWidth + 2, false);
							{ D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]), Options::Visuals::ESP::HealthWidth, false); }
						}
						//D::Text(leftUpCorn.x - iAdjust, leftUpCorn.y + flHealthPos, Color::White(), true, true, Font::Small, "%d", iHealth);
			
					}
					//right
					if (Options::Visuals::ESP::HealthPos == 1) {
						D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, 4, false);
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if (!Options::Visuals::ESP::HealthCheckColor) if (iHealth <= 100) { D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false); }
						if (Options::Visuals::ESP::HealthCheckColor) {
							D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Color(0, 0, 0), Options::Visuals::ESP::HealthWidth + 2, false);
							if (iHealth <= 100) { D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]), Options::Visuals::ESP::HealthWidth, false); }
						}

					}
					//all
					if( Options::Visuals::ESP::HealthPos == 2 ) {
						D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, 4, false);
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if (!Options::Visuals::ESP::HealthCheckColor) if (iHealth <= 100) { D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false); }
						if (Options::Visuals::ESP::HealthCheckColor) {
							D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - 1 - iDiff, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + 1 + iDiff, Color(0, 0, 0), Options::Visuals::ESP::HealthWidth + 2, false);
							if (iHealth <= 100) { D::Line(rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, rightUpCorn.y - iDiff + flHealthPos, rightUpCorn.x - iAdjust + 6 + Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]), Options::Visuals::ESP::HealthWidth, false); }
						}
						D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Options::Visuals::ESP::HealthTrue, Options::Visuals::ESP::HealthWidth + 2, false);
						//D::Line(leftUpCorn.x - iAdjust, leftUpCorn.y, leftUpCorn.x - iAdjust, leftDownCorn.y, Color(255, 0, 0, iPlayersAlpha[i]), 2, false);
						if (!Options::Visuals::ESP::HealthCheckColor)if (iHealth <= 100) { D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + iDiff, Options::Visuals::ESP::HealthFalse, Options::Visuals::ESP::HealthWidth, false); }
						if (Options::Visuals::ESP::HealthCheckColor) {
							D::Line(leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - 1 - iDiff, leftUpCorn.x - iAdjust - Options::Visuals::ESP::HealthWidth / 2.f, leftDownCorn.y + 1 + iDiff, Color(0, 0, 0), Options::Visuals::ESP::HealthWidth + 2, false);
							{ D::Line(leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, leftUpCorn.y - iDiff + flHealthPos, leftUpCorn.x - 3 - Options::Visuals::ESP::HealthWidth / 2.f, rightDownCorn.y + iDiff, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]), Options::Visuals::ESP::HealthWidth, false); }
						}
						//D::Text(leftUpCorn.x - iAdjust, leftUpCorn.y + flHealthPos, Color::White(), true, true, Font::Small, "%d", iHealth);
					

					}
					if (Options::Visuals::ESP::HealthPos == 3)
					{

						if (Options::Visuals::ESP::HealthCheckColor) {

							D::RectFilled(leftUpCorn.x - iAdjust + 3, leftDownCorn.y + 2 - iDiff, (rightUpCorn.x - leftUpCorn.x) * iHealth / 100, iDiff + 2 + Options::Visuals::ESP::HealthWidth, Color(vcolor[0], vcolor[1], vcolor[2], iPlayersAlpha[i]));
						}
						else D::RectFilled(leftUpCorn.x - iAdjust + 3, leftDownCorn.y + 2 - iDiff, (rightUpCorn.x - leftUpCorn.x) * iHealth / 100, iDiff + 2 + Options::Visuals::ESP::HealthWidth, Options::Visuals::ESP::HealthFalse); // в следующий раз включай боксы
						
						D::Rect(leftUpCorn.x - iAdjust + 3, leftDownCorn.y + 2 - iDiff, rightUpCorn.x - leftUpCorn.x, iDiff + 2 + iDiff + Options::Visuals::ESP::HealthWidth, 1, Color(0, 0, 0));
					}
				}

			}



			// if (Options::Visuals::ESP::FlashBar)
			{
				/*float flFlashDuration = pBaseEntity->FlashDuration();
				printf("flFlashDuration: %.3f\n", flFlashDuration);
				if (flFlashDuration < g_pGlobals->curtime)
				{
					//printf("flashed\n");
				}*/
			}


			if( Options::Visuals::ESP::Name && Options::Visuals::ESP::NameStyle == 1 ) {
				player_info_t pInfo;
				g_pEngine->GetPlayerInfo( pBaseEntity->GetIndex( ), &pInfo );

				int iBarIndent = 12;
				int iBarSize = 16;
				int iHalftBarSize = iBarSize / 2;
				int iBarAlphaSize = 20;
				Color clrMainColor = Color::Black( 150 );
				ImU32 imMainColor = D::GetImColor( clrMainColor );
				ImU32 imSecondColor = D::GetImColor( Color::Black( 0 ) );
				Vector3 left_up_edge = Vector3( leftUpCorn.x, leftUpCorn.y - iBarIndent, 0 );
				Vector3 right_up_edge = Vector3( rightUpCorn.x, rightUpCorn.y - iBarIndent, 0 );
				left_up_edge.x = ( int )left_up_edge.x;
				left_up_edge.y = ( int )left_up_edge.y;
				right_up_edge.x = ( int )right_up_edge.x;
				right_up_edge.y = ( int )right_up_edge.y;
				int iBarWidth = ( lineWidth * 2 );
				int iNameWidth = D::GetTextSize( pInfo.name, Font::ESP ).right;
				if( iNameWidth > iBarWidth ) {
					int iDiff = ( iNameWidth - iBarWidth ) / 2;
					left_up_edge.x -= iDiff;
					right_up_edge.x += iDiff;
					iBarWidth = iNameWidth;
				}

				D::Line( left_up_edge.x, left_up_edge.y, right_up_edge.x, right_up_edge.y, clrMainColor, iBarSize, false );
				D::m_pDrawList->AddRectFilledMultiColor( { left_up_edge.x - iBarAlphaSize, left_up_edge.y - iHalftBarSize }, { left_up_edge.x , left_up_edge.y + iHalftBarSize }, imSecondColor, imMainColor, imMainColor, imSecondColor );
				D::m_pDrawList->AddRectFilledMultiColor( { right_up_edge.x, right_up_edge.y + iHalftBarSize }, { right_up_edge.x + iBarAlphaSize, right_up_edge.y - iHalftBarSize }, imMainColor, imSecondColor, imSecondColor, imMainColor );
				D::Text( left_up_edge.x + ( iBarWidth / 2 ), left_up_edge.y, Color::White( ), true, true, Font::ESP, pInfo.name );

			}

			string szInfo;
			if( Options::Visuals::ESP::Name && Options::Visuals::ESP::NameStyle == 0 ) {
				player_info_t pInfo;
				g_pEngine->GetPlayerInfo( pBaseEntity->GetIndex( ), &pInfo );

				szInfo += pInfo.name;
				szInfo += "\n";
			}


		/*	char szPing[128] = "";
			sprintf(szPing, "Ping: %i\n", (*g_pPlayerRes)->GetPlayerPing(pBaseEntity->GetIndex()));

			szInfo += szPing;*/

			if( Options::Visuals::ESP::Money ) {
				char szString[128] = "";
				sprintf( szString, "%d$\n", pBaseEntity->Money( ) );

				szInfo += szString;
			}


			C_BaseWeapon* pBaseWeapon = pBaseEntity->Weapon( );
			if( pBaseWeapon ) {
				if( Options::Visuals::ESP::Weapon ) {
					const char* szWeaponName = U::GetWeaponNameById( pBaseWeapon->GetItemDefinitionIndex( ) );
					char szString[128] = "";
					if( Options::Visuals::ESP::WeaponAmmo )
						sprintf( szString, "%s (%d)\n", szWeaponName, pBaseWeapon->ClipAmmo( ) );
					else
						sprintf( szString, "%s\n", szWeaponName );

					szInfo += szString;

					/*CCSWeaponInfo_t* data = pBaseWeapon->GetWpnData();
					if (data)
					{
						char szString[128] = "";
						if (Options::Visuals::ESP::WeaponAmmo)
							sprintf(szString, "%s (%d)\n", &(data->m_szWeaponName[7]), pBaseWeapon->ClipAmmo());
						else
							sprintf(szString, "%s\n", &(data->m_szWeaponName[7]));

						szInfo += szString;
					}*/
				}

				if( Options::Visuals::ESP::WeaponIcon ) {
					/*int* pWeapons = pBaseEntity->Weapons();
					if (!pWeapons)
						return;

					std::vector<wchar_t> weapons;
					for (int i = 0; pWeapons[i] != INVALID_EHANDLE_INDEX; i++)
					{
						C_BaseAttributableItem* pWeapon = g_pEntityList->GetClientEntity<C_BaseAttributableItem>(pWeapons[i] & 0xFFF);
						if (!pWeapon)
							continue;
						int weapon_id = *pWeapon->GetItemDefinitionIndex();
						int correct_id = 0xE000 + U::GetCorrectIconID(weapon_id);
						if (U::IsWeaponKnife(weapon_id))
							continue;

						if (U::IsWeaponPistol(weapon_id))
							weapons[1] = correct_id;
						else if (U::IsWeaponBomb(weapon_id) ||
								 U::IsWeaponGrenade(weapon_id) ||
								 U::IsWeaponTaser(weapon_id))
							weapons.emplace(weapons.begin() + 2, correct_id);
						else
							weapons[0] = correct_id;
						//weapons.push_back(correct_id);
					}

					if (weapons.size() > 0)
					{
						weapons.push_back('\0'); // null terminator
						weapons.push_back('\0');

						wchar_t* wIcons = weapons.data();*/
					wchar_t wIcons[3] = { (wchar_t)( 0xE000 + U::GetCorrectIconID( pBaseWeapon->GetItemDefinitionIndex( ) ) ), 0, 0 };
					RECT textRect = D::GetTextSize( szInfo.c_str( ), Font::ESP );
					RECT iconRect = D::GetTextSize( wIcons, Font::Icons );
					int iX = 0;
					int iY = 0;
					if( Options::Visuals::ESP::WeaponIconPos == 0 )//right
					{
						iX = rightUpCorn.x + 4;
						iY = rightUpCorn.y + ( textRect.bottom - textRect.top ) + 5;
					} else if( Options::Visuals::ESP::WeaponIconPos == 1 )//left
					{
						iX = leftUpCorn.x - 25;
						iY = leftUpCorn.y + ( textRect.bottom + textRect.top ) + 5;
					} else if( Options::Visuals::ESP::WeaponIconPos == 2 )//up
					{
						iX = m_screenFoot.x - ( ( iconRect.right - iconRect.left ) / 2 );
						iY = m_screenHead.y - iconRect.bottom;
						if( Options::Visuals::ESP::Name && Options::Visuals::ESP::NameStyle == 1 )
							iY -= 24;
					} else if( Options::Visuals::ESP::WeaponIconPos == 3 )//down
					{
						iX = m_screenFoot.x - ( ( iconRect.right - iconRect.left ) / 2 );
						iY = m_screenFoot.y + iconRect.bottom - 10;
					}

					//Font::Icons->DrawTextW(NULL, icon, 32, &Pos, DT_NOCLIP, D3DCOLOR_RGBA(255, 255, 255, iPlayersAlpha[i]));
					D::Text( iX, iY, Options::Visuals::ESP::WeaponIconColor, false, false, Font::Icons, wIcons );
				/*}

				// release stuff
				//delete wIcons;
				weapons.clear();*/
				}
			}

			szInfo += '\n';
			szInfo += CRagebot::PlayerInfo[i].info;

			D::Text( rightUpCorn.x + 4, rightUpCorn.y, Color::White( iPlayersAlpha[i] ), false, false, Font::ESP, szInfo.c_str( ) );
			//D::Text(rightUpCorn.x + 4, rightUpCorn.y, szInfo.c_str());
		}
	}

	void DrawBonesList( C_BasePlayer* pBaseEntity ) {
		if( !pBaseEntity )
			return;

		for( int i = 0; i < 128; i++ ) {
			Vector3 bonePos = pBaseEntity->BonePosition( i );
			if( bonePos.x == 0 )
				continue;

			Vector3 screenPos;
			if( Math::WorldToScreen( bonePos, screenPos ) )
				D::Text( screenPos.x, screenPos.y, Color::White( ), true, true, Font::ESP, "%d", i );
		}
	}//Options::Visuals::Misc::glow_alpha

	void DrawPlayers( C_BasePlayer* pLocalEntity ) {
		Vector3 LocalPosition = pLocalEntity->EyePosition( );
		for( int i = 1; i < 64; i++ ) {
			C_BasePlayer* pBaseEntity = g_pEntityList->GetClientEntity<C_BasePlayer>( i );

			if( !pBaseEntity )
				continue;

			if( pBaseEntity->Health( ) < 1 )
				continue;

			if( pBaseEntity == pLocalEntity && !Options::Visuals::Misc::ThirdPerson )
				continue;

			if( pBaseEntity->Dormant( ) ) {
				if( iPlayersAlpha[i] > 0 ) {
					iPlayersAlpha[i] -= g_pGlobals->frametime * flAlphaSpeed;
					if( iPlayersAlpha[i] < 0 ) iPlayersAlpha[i] = 0;
				} else continue;
			} else {
				if( iPlayersAlpha[i] < 255 ) {
					iPlayersAlpha[i] += g_pGlobals->frametime * flAlphaSpeed;
					if( iPlayersAlpha[i] > 255 ) iPlayersAlpha[i] = 255;
				}
			}

			bool isEnemy = 1 ? pLocalEntity->Team( ) != pBaseEntity->Team( ) : 1;
			bool isVisibled = G::VisibledPlayers[i] == 1;// U::IsVisible(LocalPosition, pBaseEntity->EyePosition(), pLocalEntity, pBaseEntity, false); // CRASHING
			bool isVisibledSmoke = G::VisibledPlayersSmoke[i] == !U::LineGoesThroughSmoke( LocalPosition, pBaseEntity->EyePosition( ) );

			if( Options::Visuals::ESP::Enabled ) DrawEsp( pBaseEntity, isEnemy, isVisibled, isVisibledSmoke, false, i );
		}
	}

	void DrawCrosshairs( C_BasePlayer* pLocalPlayer ) {
		if( Options::Visuals::Misc::StreamMode ) {
			Options::Visuals::Misc::FovChanger = false;
		}

		C_BaseWeapon* pLocalWeapon = pLocalPlayer->Weapon( );
		if( !pLocalWeapon )
			return;

		auto m_nWeaponID = pLocalWeapon->GetItemDefinitionIndex( );
		auto iWeapon = pLocalWeapon->GetItemDefinitionIndex( );
		float flGameFOV = ( Options::Visuals::Misc::FovChanger ? Options::Visuals::Misc::FovChangerValue : pLocalPlayer->FOV( ) ); if( flGameFOV == 0 ) flGameFOV = pLocalPlayer->DefaultFOV( );
		int dx = g_iScreenWidth / flGameFOV;
		int dy = g_iScreenHeight / flGameFOV;
		Vector3 angle = pLocalPlayer->PunchAngles( );
		if( Options::Legitbot::DrawFov && m_nWeaponID.IsAimable( ) && g_Weapons[m_nWeaponID].Enabled ) {
			Vector3 punchAngle = (angle / 2) * Vector3(g_Weapons[iWeapon].RcsX / 50.f, g_Weapons[iWeapon].RcsY / 50.f, 0);
			int posX = g_iScreenCenterX - (dx*(punchAngle.y));
			int posY = g_iScreenCenterY + (dy*(punchAngle.x));
			float flFOV = g_Weapons[iWeapon].Fov;

			int m_iShotsFired = pLocalPlayer->ShotsFired();
			if (m_iShotsFired > 1 && g_Weapons[m_nWeaponID].RcsCustomFov)
				flFOV = g_Weapons[m_nWeaponID].RcsFovValue;

			if (flFOV > Options::Legitbot::MaxFov)
				flFOV = Options::Legitbot::MaxFov;


			float silentfov = g_Weapons[iWeapon].pSilentFov;

			float flRadius = dy * flFOV;
			float silentflRadius = dy * silentfov;
			D::Circle(posX, posY, flRadius, 25, 1, Options::Visuals::ESP::DrawFovColor); // вижуалка ебнутак вот определение она его не видит кусок говна
			if (g_Weapons[iWeapon].pSilent) D::Circle(posX, posY, silentflRadius, 25, 1, { 255, 255, 255, 255 }); // вижуалка ебнутак вот определение она его не видит кусок говна

		}

		if( !iWeapon.IsSniperRifle( ) && Options::Misc::RecoilCrosshair ) {
			int posX = g_iScreenCenterX - ( dx*( angle.y / 2 ) );
			int posY = g_iScreenCenterY + ( dy*( angle.x ) );

			int h = 2;
			D::RectFilled( posX, posY, h, h, Color::Red( ) );
		}
	}

	void DrawSpreadCrosshair( C_BasePlayer* pLocalPlayer ) {
		if( !Options::Visuals::Misc::SpreadCircle )
			return;

		if( pLocalPlayer->Health( ) <= 0 )
			return;

		C_BaseWeapon* pWeapon = pLocalPlayer->Weapon( );
		if( !pWeapon )
			return;

		int xs = g_iScreenWidth / 2;
		int ys = g_iScreenHeight / 2;

		auto accuracy = pWeapon->GetAccuracyPenalty( ) * 550.f; //3000
		if( !accuracy )
			return;

		// TODO: 32 segments
		D::CircleFilled( xs, ys, accuracy, Color( 255, 0, 0, 50 ) );
		D::Circle( xs, ys, accuracy, 12, 1, Color( 255, 0, 0, 150 ) );
		//Render::DrawFilledCircle(Vector2D(xs, ys), Color(24, 24, 24, 124), accuracy, 60);
	}

	char pszWeaponName[128] = "";
	bool DropName( char* szName ) {
		if( !szName )
			return false;

		if( strstr( szName, "CWeapon" ) ) {
			s_strcpy( pszWeaponName, &( szName[7] ) );
			return true;
		}
		if( !s_strcmp( szName, "CDEagle" ) ) {
			s_strcpy( pszWeaponName, "Deagle" );
			return true;
		}
		if( !s_strcmp( szName, "CAK47" ) ||
			!s_strcmp( szName, "CKnife" ) ||
			!s_strcmp( szName, "CC4" ) ) {
			s_strcpy( pszWeaponName, &( szName[1] ) );
			return true;
		}

		return false;
	}

	inline void DropESP( IClientEntity* pBaseEntity, Vector3 vPos ) {
		if( !pBaseEntity )
			return;

		if( pBaseEntity->IsDormant( ) )
			return;

		ClientClass* pClientClass = pBaseEntity->GetClientClass( );
		if( !pClientClass )
			return;

		if( !DropName( pClientClass->szName ) )
			return;

		if( *( int* )( ( DWORD )pBaseEntity + 0x00003210 ) != -1 ) // hOwner
			return;

		C_BaseWeapon* pBaseWeapon = ( C_BaseWeapon* )pBaseEntity;
		int iCorrectID = U::GetCorrectIconID( pBaseWeapon->GetItemDefinitionIndex( ) );
		//TrueRadar::OnItem(vPos, iCorrectID);
		if( Options::Visuals::Misc::DropESP ) {
			Vector3 screenPos;
			if( Math::WorldToScreen( vPos, screenPos ) ) {
				if( Options::Visuals::Misc::DropESPStyle == 0 ) {
					D::Text( screenPos.x, screenPos.y, Color::White( ), true, true, Font::ESP, "%s (%d/%d)",
						pszWeaponName,
						pBaseWeapon->ClipAmmo( ),
						pBaseWeapon->PrimaryReserveAmmoCount( ) );
				} else {
					wchar_t wIcon[3] = { (wchar_t)( 0xE000 + iCorrectID ), 0, 0 };
					D::Text( screenPos.x + 1, screenPos.y + 1, Color::Black( ), true, true, Font::Icons, wIcon );
					D::Text( screenPos.x, screenPos.y, Options::Visuals::ESP::WeaponIconDropColor, true, true, Font::Icons, wIcon );
				}

			}
		}
	}

	inline void BombESP( IClientEntity* pLocalEntity, IClientEntity* pBaseEntity, Vector3 vPos ) {
		if( !pBaseEntity )
			return;

		if( pBaseEntity->IsDormant( ) )
			return;

		if( pBaseEntity->GetClientClass( )->iClassID != CPlantedC4 )
			return;

		static auto m_flC4Blow = NetVarManager::GetOffset( "DT_PlantedC4", "m_flC4Blow" );
		float flTimeLeft = *( float* )( ( DWORD )pBaseEntity + m_flC4Blow ) - g_pGlobals->curtime;
		if( flTimeLeft <= 0 )
			return;

		//TrueRadar::OnItem(vPos, 0xE031);
		if( Options::Visuals::Misc::BombTimer ) {
			int BTT = Options::Visuals::Misc::BombTimerType;
			if( BTT == 0 || BTT == 2 ) {
				Vector3 screenPos;
				if( Math::WorldToScreen( vPos, screenPos ) ) {
					wchar_t wIcon[3] = { 0xE031, 0, 0 };
					RECT iconRect = D::GetTextSize( wIcon, Font::IconsBig );
					D::Text( screenPos.x, screenPos.y, Options::Visuals::ESP::BombColor, true, true, Font::IconsBig, wIcon );
					D::Text( screenPos.x, screenPos.y + ( ( ( iconRect.bottom - iconRect.top ) / 2 ) + 4 ), Color::White( ), true, false, Font::ESP, "%.1f left", flTimeLeft );
				}
			}
			if( BTT == 1 || BTT == 2 ) {
				C_BasePlayer* pLocalPlayer = ( C_BasePlayer* )pLocalEntity;
				float flHealthLeft = max( ( pLocalPlayer->Health( ) ) - Math::CalcBombDamage( pLocalPlayer->EyePosition( ), vPos, pLocalPlayer->Armor( ) ), 0 );
				if( flHealthLeft == 99 ) flHealthLeft = 100;
				D::Text( 20, g_iScreenHeight / 2, ( flHealthLeft <= 10 || flTimeLeft <= 5 ) ? Color::Red( ) : ( flTimeLeft <= 10 ) ? Color::Yellow( ) : Color::White( ), false, true, Font::ESP, "Bomb info:\nTime left: %.1f\nHealth left: ~%.0f", flTimeLeft, flHealthLeft );
			}
		}
	}

	inline void GrenadeESP( IClientEntity* pLocalEntity, IClientEntity* pBaseEntity, Vector3 vPos ) {
		if( !pBaseEntity )
			return;
	#if 0
		auto is_grenade = [] ( int classid ) {
			return classid == 9 || classid == 46 || classid == 111 ||
				classid == 98 || classid == 153;
		};

		if( !is_grenade( pBaseEntity->GetClientClass( )->iClassID ) )
			return;
	#endif

		if( !strstr( pBaseEntity->GetClientClass( )->szName, "Projectile" ) )
			return;

		model_t* pModel = pBaseEntity->GetModel( );

		if( !pModel )
			return;

		studiohdr_t* pHDR = g_pModelInfo->GetStudioModel( pModel );
		if( !pHDR )
			return;

		if( !strstr( pHDR->name, "thrown" ) && !strstr( pHDR->name, "dropped" ) )
			return;

		Color cColor = Color( 0, 0, 0, 0 );
		std::string szName = "";
		DWORD dwIcon = 0;

		/*
					float GrenadeColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float DecoyColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float SmokeColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float MolotovColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float FlashColor[4] = { 0.0f,1.0f,0.0f,1.0f };
		*/

		if( strstr( pHDR->name, "fraggrenade" ) ) {
			szName = "HE grenade";
			cColor = Options::Visuals::ESP::GrenadeColor;
			dwIcon = 0xE02C;
		} else if( strstr( pHDR->name, "flash" ) ) {
			szName = "Flashbang";
			cColor = Options::Visuals::ESP::FlashColor;
			dwIcon = 0xE02B;
		} else if( strstr( pHDR->name, "incendiarygrenade" ) ) {
			szName = "CT Molotov";
			cColor = Options::Visuals::ESP::MolotovColor;
			dwIcon = 0xE030;
		} else if( strstr( pHDR->name, "molotov" ) ) {
			szName = "Molotov";
			cColor = Options::Visuals::ESP::MolotovColor;
			dwIcon = 0xE02E;
		} else if( strstr( pHDR->name, "smoke" ) ) {
			szName = "Smoke";
			cColor = Options::Visuals::ESP::SmokeColor;
			dwIcon = 0xE02D;
		} else if( strstr( pHDR->name, "decoy" ) ) {
			szName = "Decoy";
			cColor = Options::Visuals::ESP::DecoyColor;
			dwIcon = 0xE02F;
		} else
			return;

		Vector3 vScreenPos;
		if( Math::WorldToScreen( vPos, vScreenPos ) ) {
			wchar_t wIcon[3] = { (wchar_t)dwIcon, 0, 0 };
			//TrueRadar::OnItem(vPos, dwIcon);
			if( Options::Visuals::Misc::GrenadeESP )
				D::Text( vScreenPos.x, vScreenPos.y, cColor, true, true, Font::IconsBig, wIcon );
		}
	}

	float flTimeLeft;
	float CSGO_Armor( float flDamage, int ArmorValue ) {
		float flArmorRatio = 0.5f;
		float flArmorBonus = 0.5f;
		if( ArmorValue > 0 ) {
			float flNew = flDamage * flArmorRatio;
			float flArmor = ( flDamage - flNew ) * flArmorBonus;

			if( flArmor > static_cast< float >( ArmorValue ) ) {
				flArmor = static_cast< float >( ArmorValue ) * ( 1.f / flArmorBonus );
				flNew = flDamage - flArmor;
			}

			flDamage = flNew;
		}
		return flDamage;
	}

	void DrawBombTimer( C_BasePlayer* loc, IClientEntity* ent ) {
		if( !ent ) return;
		static ConVar* flC4_time = g_pCvar->FindVar( "mp_c4timer" );

		if( strstr( ent->GetClientClass( )->szName, "PlantedC4" ) ) {
			static auto m_flC4Blow = NetVarManager::GetOffset( "DT_PlantedC4", "m_flC4Blow" );
			flTimeLeft = *( float* )( ( DWORD )ent + m_flC4Blow ) - g_pGlobals->curtime;
			if( flTimeLeft <= 0 ) return;

			int ttt = G::ScreenH / flC4_time->GetInt( );

			int temp = ttt * flTimeLeft;

			int height = G::ScreenH - temp;

			int temp_green = 6 * flTimeLeft;

			int temp_red = 255 - temp_green;

			/*static int temp_alpha = 255;
			if (timer_bomb <= 15)
			{
				if (temp_alpha >= 255)
					temp_alpha--;
				else if (temp_alpha <= 50)
					temp_alpha++;

			}*/

			D::RectFilled( 0, 0, 15, G::ScreenH, Color( 66, 66, 66, 155 ) );
			D::Text( 0, height - 16, Color( 0, 255, 0, 255 ), false, false, Font::ESP, "%i", ( int )flTimeLeft );
			D::RectFilled( 0, height, 15, G::ScreenH, Color( temp_red, temp_green, 0, 255 ) );

			float flDistance = loc->GetAbsOrigin( ).DistTo( ent->GetAbsOrigin( ) );
			float a = 450.7f;
			float b = 75.68f;
			float c = 789.2f;
			float d = ( ( flDistance - b ) / c );
			float flDamage = a * exp( -d * d );
			int damage = max( ( int )ceilf( CSGO_Armor( flDamage, loc->Armor( ) ) ), 0 );

			if( damage >= loc->Health( ) )
				D::Text( 30, 21, Color( 244, 67, 54 ), false, false, Font::MenuTitle, "FATAL" );
			else
				D::Text( 30, 21, Color( 124, 179, 66 ), false, false, Font::MenuTitle, "Bomb damage: %i", damage );
		}
	}

	void DrawOther( C_BasePlayer* pLocalEntity ) {
		for( int i = g_pGlobals->maxclients; i < g_pEntityList->GetHighestEntityIndex( ); i++ ) {
			IClientEntity* pBaseEntity = g_pEntityList->GetClientEntity<IClientEntity>( i );
			if( !pBaseEntity )
				continue;
			Vector3 vPos = pBaseEntity->GetOrigin( );
			if( vPos.IsZero( ) )
				continue;

			//DrawBombTimer( pLocalEntity, pBaseEntity );
			DropESP( pBaseEntity, vPos );
			BombESP( pLocalEntity, pBaseEntity, vPos );
			GrenadeESP( pLocalEntity, pBaseEntity, vPos );
		}
	}

	void DrawCircle3D( Vector3 pos, float points, float radius, ImU32 color, float thickness ) {

		auto step = static_cast< float >( M_PI * 2.0f / points );
		std::vector<Vector3> points3d;
		for( float a = 0; a < ( M_PI * 2.0f ); a += step ) {
			Vector3 start( radius * cosf( a ) + pos.x, radius * sinf( a ) + pos.y, pos.z );
			Vector3 end( radius * cosf( a + step ) + pos.x, radius * sinf( a + step ) + pos.y, pos.z );
			Vector3 start2d, end2d;
			if( !Math::WorldToScreen( start, start2d ) || !Math::WorldToScreen( end, end2d ) )
				return;
			D::RectFilledXY( start2d.x - thickness, start2d.y - thickness, start2d.x, start2d.y, Options::Visuals::ESP::SoundESP );
		}

	}

	void DrawSoundESP( ) {
		if( Options::Misc::SoundESP ) {
			for( int i = 0; i < G::Footsteps.size( ); i++ ) {
				if( G::Footsteps[i].m_flTime > g_pGlobals->curtime ) {
					Vector3 vecScreenPos;
					if( Math::WorldToScreen( G::Footsteps[i].m_vecPos, vecScreenPos ) ) {
						vecScreenPos.x = ( int )vecScreenPos.x;
						vecScreenPos.y = ( int )vecScreenPos.y;

						auto diff = G::Footsteps[i].m_flTime - g_pGlobals->curtime;
						auto circleRadius = fabs( diff - 1.f ) * 15.f;
						auto points = circleRadius * 1.0f;
						DrawCircle3D( G::Footsteps[i].m_vecPos, points, circleRadius, 0, 1.5 );
					}
				} else {
					G::Footsteps.erase( G::Footsteps.begin( ) + i );
					i--;
				}
			}
		} else return;
	}

	void DrawShit( C_BasePlayer* pLocalEntity ) {
		for( int i = 0; i < 13; i++ ) {
			typedef int( __thiscall* GetSequenceActivityFn )( C_BasePlayer*, int );
			typedef AnimationLayer*( __thiscall* GetAnimOverlayFn )( C_BasePlayer*, int, bool );
			static auto GetSequenceActivity = ( GetSequenceActivityFn )U::FindPattern( "client_panorama.dll", "GetSequenceActivity", "55 8B EC 53 8B 5D 08 56 8B F1 83" );
			auto current_layer = ( *( AnimationLayer** )( ( DWORD )pLocalEntity + 0x2980 ) )[i];
			int sequence_activity = GetSequenceActivity( pLocalEntity, current_layer.m_nSequence );

			string szString = to_string( i ) + ": " + to_string( sequence_activity ) + ",\tm_flCycle: " + to_string( current_layer.m_flCycle ) + ",\tm_flWeight" + to_string( current_layer.m_flWeight ) + "\n";
			D::Text( 10, g_iScreenCenterY + ( i * 20 ), Color::White( ), false, true, Font::ESP, szString.c_str( ) );
		}
	}


	void Render( ) {
		if( Options::Misc::Watermark )
			D::Text( 20, 5, Color( 64, 177, 214 ), false, false, Font::Watermark, U::AnimateSkreamex( HACK_FULL_NAME, true ).c_str( ) );

		if( g_pEngine->IsInGame( ) && g_pEngine->IsConnected( ) && !g_pEngine->IsTakingScreenshot( ) ) {
			C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
			if( pLocalPlayer ) {


				auto drawAngleLine = [&](const Vector3& origin, const Vector3& w2sOrigin, const float& angle, const char* text, Color clr) {
					Vector3 forward;
					Math::AngleVectors(QAngle(0.0f, angle, 0.0f), &forward,NULL,NULL);
					float AngleLinesLength = 30.0f;

					Vector3 w2sReal;
					if (Math::WorldToScreen(origin + forward * AngleLinesLength, w2sReal)) {	
						D::Line(w2sOrigin.x, w2sOrigin.y, w2sReal.x, w2sReal.y, clr, 1.0f);
						D::CircleFilled(w2sReal.x, w2sReal.y, 5,clr);
						D::Text(w2sReal.x, w2sReal.y - 10.0f, clr, false, false, Font::ESP, "%s", text);
					}
				};
		
				if (Options::Misc::desync_visual) {
					Vector3 w2sOrigin;
					if (Math::WorldToScreen(pLocalPlayer->GetOrigin(), w2sOrigin)) {
						drawAngleLine(pLocalPlayer->GetOrigin(), w2sOrigin, g_FakeAngle.y, "Fake", Color(255, 0, 0, 255));
						drawAngleLine(pLocalPlayer->GetOrigin(), w2sOrigin, pLocalPlayer->LowerBodyYaw(), "lby", Color(0, 0, 255, 255));
						drawAngleLine(pLocalPlayer->GetOrigin(), w2sOrigin, g_RealAngle.y, "Real", Color(0, 255, 0, 255));
					}
				}

			
				DrawPlayers( pLocalPlayer );
				DrawCrosshairs( pLocalPlayer );
				DrawSpreadCrosshair( pLocalPlayer );
				DrawOther( pLocalPlayer );
				//GrenadeHelper::Draw(pLocalPlayer, g_iScreenCenterX, g_iScreenCenterY);
				DrawSoundESP( );
				//DrawShit(pLocalPlayer);
				
			//	if( Options::Visuals::Misc::GrenadeHelper ) {
			//		GrenadePrediction::draw( );
			//	}

				/*if (pLocalPlayer->Scoped() && Options::Visuals::Misc::NoScope)
				{
					D::Line(g_iScreenWidth / 2, 0, g_iScreenWidth / 2, g_iScreenHeight, Color::Black(), 1, true);
					D::Line(0, g_iScreenHeight / 2, g_iScreenWidth, g_iScreenHeight / 2, Color::Black(), 1, true);
				}*/

				// hit info
				if( Options::Misc::HitInfo && G::flHurtTime + 1.3f >= g_pGlobals->curtime )
					D::Text( g_iScreenWidth / 2, g_iScreenHeight / 3, Options::Visuals::ESP::HitInfo, true, true, Font::MenuItem, "-%d", G::iHurtDamage );
			}
		}
	}
};
