// BlackJack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h>
using namespace std;
const int maxcards = 13;
string Cards[maxcards] = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

struct Players
{
	int Points = 0;
	bool winner = false ;
	bool hit = true;
};

int cardvalue(int i)
{
	if (i == 10 || i == 11 || i == 12 || i == 13)
	{
		i = 10;
	}
	else { i++; }
	return i;
}

Players setpoints(Players player, string Playername)
{
	int i = rand() % 13;
	cout << Playername<<" has = " << Cards[i] << endl;
	i = cardvalue(i);
	player.Points += i;
	cout << Playername<<" points " << player.Points << endl;
	if (player.Points > 21)
	{
		player.hit = false;
		player.winner = false;
	}
	else if ((player.Points > 17) && (player.Points < 22))
	{
		player.hit = false;
	}
	else if (player.Points == 21)
	{
		player.winner = true;
	}
	cout << "  " << endl;
	return player;
}

int subtractpoints(Players player)
{
	int points;
	if (player.Points < 21) { points = 21 - player.Points; }
	else if (player.Points > 21) { points = player.Points - 21; }
	return points;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Players Human, Computer;
	srand(time(NULL));
	while (((Human.winner == false) && (Computer.winner == false)) &&(( Human.hit == true) || (Computer.hit == true)))
	{		
		if (Computer.hit == true)
		{	
			Computer = setpoints(Computer,"Computer");	
		}
		if (Human.hit == true)
		{	
			Human = setpoints(Human, "Human");
		}	
	}
	if ((Computer.winner == false) && (Human.winner == false))
	{
		int comp = subtractpoints(Computer);
		int pla = subtractpoints(Human);

		if (comp > pla) { cout << "Human has won" << endl; Human.winner = true; }
		else if (comp < pla) { cout << "Computer has won" << endl; Computer.winner = true; }
		else { cout << "Both players have won" << endl; Computer.winner = true; Human.winner = true; }
	}
	
	return 0;
}

