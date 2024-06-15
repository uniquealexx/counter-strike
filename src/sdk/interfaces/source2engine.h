#pragma once

class ISource2Engine : public IAppSystem
{
	ISource2Engine() = delete;
	ISource2Engine(ISource2Engine&&) = delete;
	ISource2Engine(const ISource2Engine&) = delete;

	virtual bool	IsPaused() const = 0;
	virtual float	GetTimescale() const = 0;
};