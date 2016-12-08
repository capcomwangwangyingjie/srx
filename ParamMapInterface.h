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
	//���ã��޸ģ������һ����ֵ
	virtual void set(const char* pcName,const char* pcValue)=0;
	//��pPMI������ӵ���ǰʵ���У���������ظ��ģ����׳��쳣
	virtual void add(ParamMapInterface* &pPMI) throw(ExceptionParamDuplicate,ExceptionParamNotFound)=0;
	//��pPMI��ֵ������ǰʵ���У��൱����һ����������������ʹ��pPMI��ֵ
	virtual void set(ParamMapInterface* &pPMI) throw(ExceptionParamNotFound)=0;
	//����pcName������ȡ��Ӧ��ֵ
	virtual const char* get(const char* pcName) throw(ExceptionParamNotFound)=0;
	//��ȡ�����嵥
	virtual SSInterface* get() const=0;
	//������м�ֵ
	virtual void clear()=0;
	//��¡��ǰʵ��������
	virtual ParamMapInterface* clone()=0;
	//�ͷŵ�ǰʵ������һ����PMI�������ڽ�������
	virtual void release()=0;
};

#endif //_PARAMMAPINTERFACE_H_
