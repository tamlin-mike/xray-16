////////////////////////////////////////////////////////////////////////////
//	Module 		: script_token_list.h
//	Created 	: 21.05.2004
//  Modified 	: 21.05.2004
//	Author		: Dmitriy Iassenev
//	Description : Script token list class
////////////////////////////////////////////////////////////////////////////

#pragma once
#include "xrCommon/xr_vector.h"
#include "xrCore/xr_token.h"

class CScriptTokenList {
protected:
	// XXX: tamlin: See if it's possible to place the vector in an impl.
	typedef xr_vector<xr_token>			TOKEN_LIST;
	typedef TOKEN_LIST::iterator		iterator;
	typedef TOKEN_LIST::const_iterator	const_iterator;

protected:
	struct CTokenPredicateName {
		const char*		m_name;

		constexpr CTokenPredicateName(const char* name) noexcept : m_name(name) { }

		bool operator()(const xr_token &token) const noexcept
		{
			return token.name && !strcmp(token.name,m_name);
		}
	};
	
	struct CTokenPredicateID {
		int				m_id;

		CTokenPredicateID(int id) noexcept : m_id(id) { }

		bool operator()(const xr_token &token) const
		{
			return token.name && (token.id == m_id);
		}
	};

protected:
	TOKEN_LIST					m_token_list;

protected:
			iterator			token				(const char* name);
			iterator			token				(int id);

public:
								CScriptTokenList	();
								~CScriptTokenList	() noexcept;
			void				add					(const char* name, int id);
			void				remove				(const char* name);
			void				clear				();
			int					id					(const char* name);
			const char*			name				(int id);
			const TOKEN_LIST	&tokens() const noexcept { return m_token_list; }
			TOKEN_LIST			&tokens()       noexcept { return m_token_list; }
};
