#ifndef PLAYERKEYS_H
#define PLAYERKEYS_H

class
{
	public:
		int iLeft;
		int iRight;
		int iUp;
		int iDown;
} PlayerKeys [] =
{
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	// a, d, w, s
	0x41, 0x44, 0x57, 0x53,
	// j, l, i, k
	0x4A, 0x4C, 0x49, 0x4B,
	// NUM BLOCK 1 3 5 2
	0x61, 0x63, 0x65, 0x62
};

#endif