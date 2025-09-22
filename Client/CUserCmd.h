#pragma once 
// from r2_internal { https://github.com/jz0/r2-internal/blob/main/R2SDK/CUserCmd.hpp }

class CUserCmd
{
public:
	int32_t command_number;        // 0x00
	int32_t tick_count;           // 0x04
	int32_t command_time;         // 0x08
	Vector worldViewAngles;       // 0x0C (12 bytes: 3 floats)
	BYTE gap18[4];               // 0x18 (4 bytes padding)
	Vector localViewAngles;      // 0x1C (12 bytes: 3 floats)
	Vector attackangles;         // 0x28 (12 bytes: 3 floats)
	Vector move;                 // 0x34 (12 bytes: 3 floats)
	int buttons;                 // 0x40
	BYTE impulse;                // 0x44
	short weaponselect;          // 0x45
	int meleetarget;             // 0x47
	BYTE gap4C[24];              // 0x4B (24 bytes padding)
	char headoffset;             // 0x63
	BYTE gap65[11];              // 0x64 (11 bytes padding)
	Vector cameraPos;            // 0x6F (12 bytes: 3 floats)
	Vector cameraAngles;         // 0x7B (12 bytes: 3 floats)
	BYTE gap88[4];               // 0x87 (4 bytes padding)
	int tickSomething;           // 0x8B
	int dword90;                 // 0x8F
	int predictedServerEventAck; // 0x93
	int dword98;                 // 0x97
	float frameTime;             // 0x9B
};    
