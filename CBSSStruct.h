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

	bool m_bRet;//作为返回时填写，true表示成功，false表示失败
	int m_iErrStep;//00=准备数据异常或失败
				   //11=签名连接异常 12=签名部分发送异常 13=签名全部发送异常 14=签名部分接收异常 15=签名全部接收异常
				   //21=交易连接异常 22=交易部分发送异常 23=交易全部发送异常 24=交易部分接收异常 25=交易全部接收异常
				   //31=验签连接异常 32=验签部分发送异常 33=验签全部发送异常 34=验签部分接收异常 35=验签全部接收异常
				   //40=银行返回异常或失败
	std::string m_strErrMsg;//当m_bRet=false时填写错误信息

	std::string m_strERPCode;
	std::string m_strBankCode;
	std::string m_strOpCode;
	std::string m_strERPUniqueSerial;
	ParamMapInterface* m_pmiMaster;//存储了具有唯一标识的字段名及值，比如查询单个帐户余额时的账户名称和账号等
	PMINode* m_pminDetail;//存储多个循环域的链表，比如批量转账的支付清单等、查询多个账户余额时的账号清单
	CharBuf m_cbOriginalDG;//原始报文，暂时每次复制
};

#endif //_CBS_CBSSSTRUCT_H_
