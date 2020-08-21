#pragma once
#include "Command.h"

class Player;

class CommandMoveRight : public Command
{
public:
	CommandMoveRight(Player* player) : m_pPlayer(player){}
private:
	Player* m_pPlayer;
	void OnPressed() override;
	void Released() override;
};

class CommandMoveUp : public Command
{
public:
	CommandMoveUp(Player* player) : m_pPlayer(player){}
private:
	Player* m_pPlayer;
	void OnPressed() override;
	void Released() override;
};

class CommandMoveLeft : public Command
{
public:
	CommandMoveLeft(Player* player) : m_pPlayer(player){}
private:
	Player* m_pPlayer;
	void OnPressed() override;
	void Released() override;
};

class CommandMoveDown : public Command
{
public:
	CommandMoveDown(Player* player) : m_pPlayer(player){}
private:
	Player* m_pPlayer;
	void OnPressed() override;
	void Released() override;
};