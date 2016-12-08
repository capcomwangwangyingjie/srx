#ifndef _PARAMMAP_H_
#define _PARAMMAP_H_

#include <string>
#include <map>
#include "ParamMapInterface.h"
class ParamMap : public ParamMapInterface
{
public:
	ParamMap();
	~ParamMap();
	void set(const char* pcName,const char* pcValue);
	void add(ParamMapInterface* &pPMI) throw(ExceptionParamDuplicate,ExceptionParamNotFound);
	void set(ParamMapInterface* &pPMI) throw(ExceptionParamNotFound);
	const char* get(const char* pcName) throw(ExceptionParamNotFound);
	SSInterface* get() const;
	void clear();
	ParamMapInterface* clone();
	void release();
private:
	std::map<std::string,std::string> m_mss;
	SSInterface* m_ssi;
};

#endif //_PARAMMAP_H_
