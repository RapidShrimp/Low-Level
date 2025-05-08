
#pragma once

enum E_TeamResponse {
	Neutral = 0,
	Friendly = 1,
	Hostile = 2
};

class ITeamGenerics {

public:
	short int TeamID;
	virtual E_TeamResponse GetResponseToOther(short int MyTeamID, short int OtherTeamID) 
	{
		if (MyTeamID == 0 || OtherTeamID == 0) {
			return Neutral;
		}
		else if (MyTeamID == OtherTeamID) {
			return Friendly;
		}
		else {
			return Hostile;
		}
	}
	virtual int GetTeam() { return TeamID; }
};