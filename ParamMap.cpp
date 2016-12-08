#include "ParamMap.h"
#include "SetString.h"

ParamMap::ParamMap()
{
	m_ssi=new SetString;
}

ParamMap::~ParamMap()
{
	if(m_ssi) {m_ssi->release();m_ssi=0;} m_mss.clear();
}

void ParamMap::set(const char* pcName,const char* pcValue) {m_ssi->insert(pcName);m_mss[pcName]=pcValue;}

void ParamMap::add(ParamMapInterface* &pPMI) throw(ExceptionParamDuplicate,ExceptionParamNotFound)
{
	SSInterface* l_css=pPMI->get();
	const char* l_pcSetit;
	for( l_pcSetit = l_css->first(); l_pcSetit != 0; l_pcSetit = l_css->next() )
	{
		if(m_ssi->find(l_pcSetit))
		{
			std::string l_strExp;
			l_strExp="parameter duplicate '";
			l_strExp+=l_pcSetit;
			l_strExp+="'";
			throw ExceptionParamDuplicate(l_strExp.c_str());
		}
		set( l_pcSetit, pPMI->get( l_pcSetit ) );
	}
}

void ParamMap::set(ParamMapInterface* &pPMI) throw(ExceptionParamNotFound)
{
	SSInterface* l_css=pPMI->get();
	const char* l_pcSetit;
	for( l_pcSetit = l_css->first(); l_pcSetit != 0; l_pcSetit = l_css->next() )
	{
		set( l_pcSetit, pPMI->get( l_pcSetit ) );
	}
}

const char* ParamMap::get(const char* pcName) throw(ExceptionParamNotFound)
{
	if(m_mss.find(pcName)==m_mss.end())
	{
		std::string l_str;
		l_str="Param '";l_str+=pcName;l_str+="' wanted";
		throw ExceptionParamNotFound(l_str.c_str());
	}
	return m_mss[pcName].c_str();
}

SSInterface* ParamMap::get() const
{
	return m_ssi;
}

void ParamMap::clear() {m_mss.clear();m_ssi->clear();}

ParamMapInterface* ParamMap::clone()
{
	if(m_mss.empty()) return new ParamMap;
	ParamMap* l_pPM=new ParamMap;
	std::map<std::string,std::string>::iterator l_it;
	for(l_it=m_mss.begin();l_it!=m_mss.end();l_it++)
	{
		l_pPM->set(l_it->first.c_str(),l_it->second.c_str());
	}
	return l_pPM;
}

void ParamMap::release() {delete this;}
