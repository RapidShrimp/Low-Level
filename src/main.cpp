#include <iostream>
#include "Engine/Core/GameInstance.h"
#include "main.h"

using namespace std;

int main()
{
	InitialiseEngine();
	return 0;
}

void InitialiseEngine() 
{
	cout << "Initialise Sinistar" << endl;
	
	//Create Game Instance;
	GameInstance GI = GameInstance();

	//Lock Engine 
	/*while (GI != NULL) {

	}*/

}


