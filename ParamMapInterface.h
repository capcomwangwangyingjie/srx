#ifndef _PARAMMAPINTERFACE_H_
#define _PARAMMAPINTERFACE_H_

#include <string>
#include <set>
#include <map>
#include "ExceptionParamNotFound.h"
#include "ExceptionParamDuplicate.h"
#include "SSInterface.h"
class ParamMapInterface
{
public:
	virtual ~ParamMapInterface() {}
	//设置（修改）或添加一个键值
	virtual void set(const char* pcName,const char* pcValue)=0;
	//将pPMI对象添加到当前实例中，如果出现重复的，则抛出异常
	virtual void add(ParamMapInterface* &pPMI) throw(ExceptionParamDuplicate,ExceptionParamNotFound)=0;
	//将pPMI的值赋到当前实例中，相当于做一个并集操作，优先使用pPMI的值
	virtual void set(ParamMapInterface* &pPMI) throw(ExceptionParamNotFound)=0;
	//根据pcName主键获取对应的值
	virtual const char* get(const char* pcName) throw(ExceptionParamNotFound)=0;
	//获取主键清单
	virtual SSInterface* get() const=0;
	//清除所有键值
	virtual void clear()=0;
	//克隆当前实例并返回
	virtual ParamMapInterface* clone()=0;
	//释放当前实例对象，一般在PMI生命周期结束调用
	virtual void release()=0;
};

#endif //_PARAMMAPINTERFACE_H_
