/**
* \brief zebra��ĿGateway������,�����û�ָ����ת�������ܽ��ܵ�
*/
#ifndef __GATEWAYSERVER_H_
#define __GATEWAYSERVER_H_


#include "zSubNetService.h"
#include "Zebra.h"
#include "zMisc.h"
#include "SuperCommand.h"
#include "SessionClient.h"
#include "CountryInfo.h"
#include <vector>
#include <string>


// */
// [ranqd] Add ������״̬
enum SERVER_STATE 
{
	STATE_SERVICING	=	0, // ά��
	STATE_NOMARL	=	1, // ����
	STATE_GOOD		=	2, // ����
	STATE_BUSY		=	3, // ��æ
	STATE_FULL		=	4, // ����
};
// [ranqd] Add ����������
enum SERVER_TYPE
{
	TYPE_GENERAL		=	0, // ��ͨ
	TYPE_PEACE		=	1,     // ��ƽ
};

/**
* \brief �������ط�����
*
* �����ʹ����Singleton���ģʽ����֤��һ��������ֻ��һ�����ʵ��
*
*/
class GatewayService : public zSubNetService
{

public:

	bool msgParse_SuperService(const Cmd::t_NullCmd *pNullCmd,const DWORD nCmdLen);

	const int getPoolSize() const
	{
		if (taskPool)
		{
			return taskPool->getSize();
		}
		else
		{
			return 0;
		}
	}

	const int getPoolState() const
	{
		return taskPool->getState();
	}

	bool notifyLoginServer();

	/**
	* \brief У��ͻ��˰汾��
	*/
	DWORD verify_client_version;

	/**
	* \brief ����������
	*
	*/
	~GatewayService()
	{
		if (sessionClient)
		{
			sessionClient->final();
			sessionClient->join();
			SAFE_DELETE(sessionClient);
		}

	}

	/**
	* \brief �������Ψһʵ��
	*
	* \return ���Ψһʵ��
	*/
	static GatewayService &getInstance()
	{
		if (NULL == instance)
			instance = new GatewayService();

		return *instance;
	}

	/**
	* \brief �ͷ����Ψһʵ��
	*
	*/
	static void delInstance()
	{
		//�ر��̳߳�
		if (taskPool)
		{
			taskPool->final();
			SAFE_DELETE(taskPool);
		}

		SAFE_DELETE(instance);
	}

	void reloadConfig();
	bool isSequeueTerminate() 
	{
		return taskPool == NULL;
	}


private:

	/**
	* \brief ���Ψһʵ��ָ��
	*
	*/
	static GatewayService *instance;

	static zTCPTaskPool *taskPool;        /**< TCP���ӳص�ָ�� */


	//��������(��ͼ)��Ϣ

	/**
	* \brief ���캯��
	*
	*/
	GatewayService() : zSubNetService("���ط�����",GATEWAYSERVER)
	{
		rolereg_verify = true;
		taskPool = NULL;
		startUpFinish = false;
	}

	bool init();
	void newTCPTask(const int sock,const struct sockaddr_in *addr);
	void final();

	/**
	* \brief ȷ�Ϸ�������ʼ���ɹ��������������ص�����
	*
	* �����������t_Startup_OKָ����ȷ�Ϸ����������ɹ�
	* ����֪ͨ���е�½����������̨���ط�����׼������
	*
	* \return ȷ���Ƿ�ɹ�
	*/
	virtual bool validate()
	{
		zSubNetService::validate();
		return notifyLoginServer();
	}


public:
	bool sendCmdToZone(DWORD zone, const void *cmd, int len);

	CountryInfo country_info;
	bool rolereg_verify;
	static bool service_gold;
	static bool service_stock;
	bool startUpFinish;


};

#endif





