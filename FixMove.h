#pragma once

namespace FixMove // pasted from tgf (really nigga)
{
	float m_oldforward, m_oldsidemove;
	QAngle m_oldangle;

	float clamp(float n, float lower, float upper) {
		return max(lower, min(n, upper));
	}

	void Start(CUserCmd* pCmd)
	{
		m_oldangle = pCmd->viewangles;
		m_oldforward = pCmd->forwardmove;
		m_oldsidemove = pCmd->sidemove;
	}

	void End(CUserCmd* pCmd, bool& send_packet)
	{
	#if 0
		float yaw_delta = pCmd->viewangles.y - m_oldangle.y;
		float f1;
		float f2;

		if (m_oldangle.y < 0.f)
			f1 = 360.0f + m_oldangle.y;
		else
			f1 = m_oldangle.y;

		if (pCmd->viewangles.y < 0.0f)
			f2 = 360.0f + pCmd->viewangles.y;
		else
			f2 = pCmd->viewangles.y;

		if (f2 < f1)
			yaw_delta = abs(f2 - f1);
		else
			yaw_delta = 360.0f - abs(f1 - f2);
		yaw_delta = 360.0f - yaw_delta;

		pCmd->forwardmove = cos(Math::Deg2Rad(yaw_delta)) * m_oldforward + cos(Math::Deg2Rad(yaw_delta + 90.f)) * m_oldsidemove;
		pCmd->sidemove = sin(Math::Deg2Rad(yaw_delta)) * m_oldforward + sin(Math::Deg2Rad(yaw_delta + 90.f)) * m_oldsidemove;
	#else
		Vector3 wish_forward, wish_right, wish_up, cmd_forward, cmd_right, cmd_up;

		auto viewangles = pCmd->viewangles;
		Math::NormalizeAngle(viewangles );

		auto movedata = Vector3(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);

		Math::AngleVectors(m_oldangle, &wish_forward, &wish_right, &wish_up);
		Math::AngleVectors(viewangles, &cmd_forward, &cmd_right, &cmd_up);

		auto v8 = sqrt(wish_forward.x * wish_forward.x + wish_forward.y * wish_forward.y), v10 = sqrt(wish_right.x * wish_right.x + wish_right.y * wish_right.y), v12 = sqrt(wish_up.z * wish_up.z);

		Vector3 wish_forward_norm(1.0f / v8 * wish_forward.x, 1.0f / v8 * wish_forward.y, 0.f),
			wish_right_norm(1.0f / v10 * wish_right.x, 1.0f / v10 * wish_right.y, 0.f),
			wish_up_norm(0.f, 0.f, 1.0f / v12 * wish_up.z);

		auto v14 = sqrt(cmd_forward.x * cmd_forward.x + cmd_forward.y * cmd_forward.y), v16 = sqrt(cmd_right.x * cmd_right.x + cmd_right.y * cmd_right.y), v18 = sqrt(cmd_up.z * cmd_up.z);

		Vector3 cmd_forward_norm(1.0f / v14 * cmd_forward.x, 1.0f / v14 * cmd_forward.y, 1.0f / v14 * 0.0f),
			cmd_right_norm(1.0f / v16 * cmd_right.x, 1.0f / v16 * cmd_right.y, 1.0f / v16 * 0.0f),
			cmd_up_norm(0.f, 0.f, 1.0f / v18 * cmd_up.z);

		auto v22 = wish_forward_norm.x * movedata.x, v26 = wish_forward_norm.y * movedata.x, v28 = wish_forward_norm.z * movedata.x, v24 = wish_right_norm.x * movedata.y, v23 = wish_right_norm.y * movedata.y, v25 = wish_right_norm.z * movedata.y, v30 = wish_up_norm.x * movedata.z, v27 = wish_up_norm.z * movedata.z, v29 = wish_up_norm.y * movedata.z;

		Vector3 correct_movement;
		correct_movement.x = cmd_forward_norm.x * v24 + cmd_forward_norm.y * v23 + cmd_forward_norm.z * v25
			+ (cmd_forward_norm.x * v22 + cmd_forward_norm.y * v26 + cmd_forward_norm.z * v28)
			+ (cmd_forward_norm.y * v30 + cmd_forward_norm.x * v29 + cmd_forward_norm.z * v27);
		correct_movement.y = cmd_right_norm.x * v24 + cmd_right_norm.y * v23 + cmd_right_norm.z * v25
			+ (cmd_right_norm.x * v22 + cmd_right_norm.y * v26 + cmd_right_norm.z * v28)
			+ (cmd_right_norm.x * v29 + cmd_right_norm.y * v30 + cmd_right_norm.z * v27);
		correct_movement.z = cmd_up_norm.x * v23 + cmd_up_norm.y * v24 + cmd_up_norm.z * v25
			+ (cmd_up_norm.x * v26 + cmd_up_norm.y * v22 + cmd_up_norm.z * v28)
			+ (cmd_up_norm.x * v30 + cmd_up_norm.y * v29 + cmd_up_norm.z * v27);

		pCmd->forwardmove = clamp(correct_movement.x, -450.f, 450.f);
		pCmd->sidemove = clamp(correct_movement.y, -450.f, 450.f);
		pCmd->upmove = clamp(correct_movement.z, -320.f, 320.f);

		if (GetAsyncKeyState(Options::Visuals::Misc::SlowmoKey))
		{
			pCmd->sidemove *= 0.08f;
			pCmd->forwardmove *= 0.08f;
			pCmd->buttons |= IN_WALK;
		}

		/*auto client_state = *(uintptr_t*)(uintptr_t(GetModuleHandle("engine.dll")) + 0x58BCFC);

		if (GetAsyncKeyState(Options::Visuals::Misc::FakeduckKey))
		{
			auto pLocalPlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(g_pEngine->GetLocalPlayer());
			pCmd->buttons |= IN_BULLRUSH;

			if (client_state && pLocalPlayer) {
				int choked_goal = 14 / 2;
				auto cur_fakelag = (*(int*)(client_state + 0x4D28));

				send_packet = (cur_fakelag >= 14);

				bool should_crouch = (cur_fakelag >= choked_goal);

				if (should_crouch)
					pCmd->buttons |= IN_DUCK;
				else
					pCmd->buttons &= ~IN_DUCK;

				static auto eblan = NetVarManager::GetOffset("DT_CSPlayer", "m_flDuckAmount");

				if (Options::Misc::FakeduckDelayshot && (*(float*)(uintptr_t(pLocalPlayer) + eblan)) > 0.2f)
					pCmd->buttons &= ~IN_ATTACK;
			}
		}
		else
		{
			if (GetAsyncKeyState(Options::Visuals::Misc::fakelagKey) && client_state)
			{
				auto cur_fakelag = (*(int*)(client_state + 0x4D28));

				send_packet = (cur_fakelag >= min(Options::Visuals::Misc::fakelag_limit, 14));
			}
		}*/
	#endif
	}
}
