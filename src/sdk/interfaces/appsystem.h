#pragma once

class IAppSystem
{
	IAppSystem() = delete;
	IAppSystem(IAppSystem&&) = delete;
	IAppSystem(const IAppSystem&) = delete;

	virtual bool	Connect(void* pfnFactory) = 0;
	virtual void	Disconnect() = 0;
	virtual void*	QueryInterface(const char* szInterfaceName) const = 0;
	virtual int		Init() = 0;
	virtual void	Shutdown() = 0;
	virtual void	PreShutdown() = 0;
	virtual void*	GetDependencies() const = 0;
	virtual int		GetTier() const = 0;
	virtual void	Reconnect(void* pfnFactory, const char* szInterfaceName) = 0;
	virtual bool	IsSingleton() const = 0;
	virtual int		GetBuildType() const = 0;
};
