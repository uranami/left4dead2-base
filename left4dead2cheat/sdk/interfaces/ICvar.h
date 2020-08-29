#pragma once
#include"..\convar\convar.h"
#include "..\other\Misc.h"
class ConVar;
class IConVar;
class CCommand;
class ConCommand;
class ConCommandBase;
typedef void(*FnChangeCallback_t)(IConVar* var, const char* pOldValue, float flOldValue);
enum InitReturnVal_t
{
	INIT_FAILED = 0,
	INIT_OK,
	INIT_LAST_VAL,
};
class IAppSystem
{
public:
	virtual bool			Connect(create_interface_fn Factory) = 0;
	virtual void			Disconnect() = 0;
	virtual void* QueryInterface(const char* pInterfaceName) = 0;
	virtual InitReturnVal_t Init() = 0;
	virtual void			Shutdown() = 0;
};

class Color;

class IConsoleDisplayFunc
{
public:
	virtual void ColorPrint(const Color& clr, const char* pMessage) = 0;
	virtual void Print(const char* pMessage) = 0;
	virtual void DPrint(const char* pMessage) = 0;
};
typedef int CVarDLLIdentifier_t;

class ICvar : public IAppSystem
{
public:
	virtual CVarDLLIdentifier_t        AllocateDLLIdentifier() = 0;
	virtual void                       RegisterConCommand(ConCommandBase *pCommandBase) = 0; 
	virtual void                       UnregisterConCommand(ConCommandBase *pCommandBase) = 0;
	virtual void                       UnregisterConCommands(CVarDLLIdentifier_t id) = 0;
	virtual const char*                GetCommandLineValue(const char *pVariableName) = 0; 
	virtual ConCommandBase*            FindCommandBase(const char *name) = 0; 
	virtual ConVar*                    FindVar(const char *var_name) = 0;
	virtual const ConVar*              FindVar(const char *var_name) const = 0;
	virtual ConCommand*                FindCommand(const char *name) = 0;
	virtual const ConCommand*          FindCommand(const char *name) const = 0; 
	virtual void                       InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void                       RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void                       CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) = 0;
	virtual void                       InstallConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
	virtual void                       RemoveConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
	virtual void                       ConsoleColorPrintf(const Color& clr, const char *pFormat, ...) const = 0;
	virtual void                       ConsolePrintf(const char *pFormat, ...) const = 0;
	virtual void                       ConsoleDPrintf(const char *pFormat, ...) const = 0;
	virtual void                       RevertFlaggedConVars(int nFlag) = 0;

	// Method allowing the engine ICvarQuery interface to take over
	// A little hacky, owing to the fact the engine is loaded
	// well after ICVar, so we can't use the standard connect pattern
	virtual void			InstallCVarQuery(void* pQuery) = 0;

#if defined( _X360 )
	virtual void			PublishToVXConsole() = 0;
#endif
	virtual bool			IsMaterialThreadSetAllowed() const = 0;
	virtual void			QueueMaterialThreadSetValue(ConVar* pConVar, const char* pValue) = 0;
	virtual void			QueueMaterialThreadSetValue(ConVar* pConVar, int nValue) = 0;
	virtual void			QueueMaterialThreadSetValue(ConVar* pConVar, float flValue) = 0;
	virtual bool			HasQueuedMaterialThreadConVarSets() const = 0;
	virtual int				ProcessQueuedMaterialThreadConVarSets() = 0;

protected:	class ICVarIteratorInternal;
public:
	/// Iteration over all cvars.
	/// (THIS IS A SLOW OPERATION AND YOU SHOULD AVOID IT.)
	/// usage:
	/// { ICVar::Iterator iter(g_pCVar);
	///   for ( iter.SetFirst() ; iter.IsValid() ; iter.Next() )
	///   {
	///       ConCommandBase *cmd = iter.Get();
	///   }
	/// }
	/// The Iterator class actually wraps the internal factory methods
	/// so you don't need to worry about new/delete -- scope takes care
	//  of it.
	/// We need an iterator like this because we can't simply return a
	/// pointer to the internal data type that contains the cvars --
	/// it's a custom, protected class with unusual semantics and is
	/// prone to change.
	class Iterator
	{
	public:
		inline Iterator(ICvar* icvar);
		inline ~Iterator(void);
		inline void		SetFirst(void);
		inline void		Next(void);
		inline bool		IsValid(void);
		inline ConCommandBase* Get(void);
	private:
		ICVarIteratorInternal* m_pIter;
	};

protected:
	// internals for  ICVarIterator
	class ICVarIteratorInternal
	{
	public:
		// warning: delete called on 'ICvar::ICVarIteratorInternal' that is abstract but has non-virtual destructor [-Wdelete-non-virtual-dtor]
		virtual ~ICVarIteratorInternal()
		{
		}
		virtual void		SetFirst(void) = 0;
		virtual void		Next(void) = 0;
		virtual	bool		IsValid(void) = 0;
		virtual ConCommandBase* Get(void) = 0;
	};

	virtual ICVarIteratorInternal* FactoryInternalIterator(void) = 0;
	friend class Iterator;
};
