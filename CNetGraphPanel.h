#pragma once

class CNetGraphPanel {

public:

	float GetFps() {

		return (float)(1.0f / *(float*)(this + 0x131B8));
	}
};
CNetGraphPanel *g_pNetGraphPanel;


