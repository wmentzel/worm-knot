#ifndef PLAYERMETHODS_H
#define PLAYERMETHODS_H

tagPlayer::tagPlayer()
{
	Snake.pParent = this;
}
int tagPlayer::GetPressedKey()
{
	return iPressedKey;
}
void tagPlayer::SetPressedKey(int iCurKey)
{
	iPressedKey = iCurKey;
}

void tagPlayer::SetLost(bool bLooser)
{
	bLost = bLooser;
}

bool tagPlayer::isLost()
{
	return bLost;
}

void tagPlayer::SetDefinedKeys(int iLeft, int iRight, int iUp, int iDown)
{
	iKeys[LEFT] = iLeft;
	iKeys[RIGHT] = iRight;
	iKeys[UP] = iUp;
	iKeys[DOWN] = iDown;
}

bool tagPlayer::isPlayerKey (int iCurKey)
{
	for(int i = 0; i < 4; i++)
	{
		if(iKeys[i] == iCurKey)
		{
			if(iPressedKey == iKeys[0] && iCurKey != iKeys[1] ||
				iPressedKey == iKeys[1] && iCurKey != iKeys[0] ||
				iPressedKey == iKeys[2] && iCurKey != iKeys[3] ||
				iPressedKey == iKeys[3] && iCurKey != iKeys[2])
			{
				iPressedKey = iCurKey;
			}
			return TRUE;
		}
			
	}
	return FALSE;
}

#endif