#pragma once
#ifndef _CBS_CBSSSTRUCT_H_
#define _CBS_CBSSSTRUCT_H_

#include <string>
#include "CharBuf.h"
#include "ParamMapInterface.h"
#include "ParamMap.h"
#include "PMINode.h"
#include "LinkListUtil.h"
class CBSSStruct
{
public:
	CBSSStruct() {m_bRet=true;m_pmiMaster=new ParamMap;m_pminDetail=0;}
	CBSSStruct(const CBSSStruct& cbsss)
	{
		m_bRet=cbsss.m_bRet;
		m_strErrMsg=cbsss.m_strErrMsg;
		m_strERPCode=cbsss.m_strERPCode;
		m_strBankCode=cbsss.m_strBankCode;
		m_strOpCode=cbsss.m_strOpCode;
		m_strERPUniqueSerial=cbsss.m_strERPUniqueSerial;
		m_cbOriginalDG=cbsss.m_cbOriginalDG;
		m_pmiMaster=cbsss.m_pmiMaster->clone();
		LinkListUtil<PMINode>::llcopy(m_pminDetail,cbsss.m_pminDetail);
	}
	void operator=(const CBSSStruct& cbsss)
	{
		if(&cbsss==this) return ;
		m_bRet=cbsss.m_bRet;
		m_strErrMsg=cbsss.m_strErrMsg;
		m_strERPCode=cbsss.m_strERPCode;
		m_strBankCode=cbsss.m_strBankCode;
		m_strOpCode=cbsss.m_strOpCode;
		m_strERPUniqueSerial=cbsss.m_strERPUniqueSerial;
		m_cbOriginalDG=cbsss.m_cbOriginalDG;
		if(m_pmiMaster) {m_pmiMaster->release();m_pmiMaster=0;}
		m_pmiMaster=cbsss.m_pmiMaster->clone();
		LinkListUtil<PMINode>::llcopy(m_pminDetail,cbsss.m_pminDetail);
	}
	void copyHead(const CBSSStruct& cbsss)
	{
		if(&cbsss==this) return ;
		m_strERPCode=cbsss.m_strERPCode;
		m_strBankCode=cbsss.m_strBankCode;
		m_strOpCode=cbsss.m_strOpCode;
		m_strERPUniqueSerial=cbsss.m_strERPUniqueSerial;
	}
	virtual ~CBSSStruct()
	{
		if(m_pmiMaster) {m_pmiMaster->release();m_pmiMaster=0;}
		if(m_pminDetail) LinkListUtil<PMINode>::lldelete(m_pminDetail);
	}

	bool m_bRet;//��Ϊ����ʱ��д��true��ʾ�ɹ���false��ʾʧ��
	int m_iErrStep;//00=׼�������쳣��ʧ��
				   //11=ǩ�������쳣 12=ǩ�����ַ����쳣 13=ǩ��ȫ�������쳣 14=ǩ�����ֽ����쳣 15=ǩ��ȫ�������쳣
				   //21=���������쳣 22=���ײ��ַ����쳣 23=����ȫ�������쳣 24=���ײ��ֽ����쳣 25=����ȫ�������쳣
				   //31=��ǩ�����쳣 32=��ǩ���ַ����쳣 33=��ǩȫ�������쳣 34=��ǩ���ֽ����쳣 35=��ǩȫ�������쳣
				   //40=���з����쳣��ʧ��
	std::string m_strErrMsg;//��m_bRet=falseʱ��д������Ϣ

	std::string m_strERPCode;
	std::string m_strBankCode;
	std::string m_strOpCode;
	std::string m_strERPUniqueSerial;
	ParamMapInterface* m_pmiMaster;//�洢�˾���Ψһ��ʶ���ֶ�����ֵ�������ѯ�����ʻ����ʱ���˻����ƺ��˺ŵ�
	PMINode* m_pminDetail;//�洢���ѭ�����������������ת�˵�֧���嵥�ȡ���ѯ����˻����ʱ���˺��嵥
	CharBuf m_cbOriginalDG;//ԭʼ���ģ���ʱÿ�θ���
};

#endif //_CBS_CBSSSTRUCT_H_
