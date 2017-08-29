/******************************************************************/
/** �ļ���:VS_MicroService.h
** ��Ȩ�����������������޹�˾
** ������:����ï
** �� ��:2017-06-16
** �޸���:����ï
** �� ��:2017-07-05
** �� ��:��������΢����ע��ͷ���ģ����ͷ�ļ�
** �� ��:0.2
**/
/******************************************************************/
#ifndef __VS_MICRO_SERVICE_H__
#define __VS_MICRO_SERVICE_H__

#include <string>
#include <vector>

#include <iostream>
//boost header
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/high_resolution_timer.hpp>

#include "etcd/Client.hpp"
#include "etcd/Watcher.hpp"

using namespace std;
using namespace etcd;
//using namespace boost;
//using namespace boost::system;

//typedef	void(__stdcall *watcher_callback)(etcd::Response const & resp,void* ptr);

namespace VorxSoft{

	std::time_t getTimeStamp();

	const std::string VS_MicroServicePath = "/service";
	const std::string version = "4.0.0.1";
	/*****************************************************************/
	/** ������:GetVersion
	** ��������:��ȡ��ǰ��İ汾��
	**����:��
	**����ֵ��std::string
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	std::string GetCurrentVersion();

class VS_MicroService
{
public:
	enum PolicyType
	{
		ROUND = 1,
		RANDOM = 2,
		PERFORMANECE = 3
	};
	/*****************************************************************/
	/** ������:VS_MicroService
	** ��������:VS_MicroServiceĬ�Ϲ��캯���������ڲ���Ա����ΪĬ��ֵ
	**����:
	** ������ 1 ��I-����/O-���������˵��
	** ������ 2��I-����/O-���������˵��
	**����ֵ����
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	VS_MicroService();

	/*****************************************************************/
	/** ������:VS_MicroService
	** ��������:VS_MicroService���캯����������ע�����ĵ����ӣ��ɹ���pclient_ָ�벻Ϊ��
	**����:
	** ������ target ��I-���롿ע�����ĵ�ַ �ַ������� ����"http://192.168.20.251:2379"
	** ������ 2��I-����/O-���������˵��
	**����ֵ����
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	VS_MicroService(std::string target);

	/*****************************************************************/
	/** ������:VS_MicroService
	** ��������:VS_MicroService���캯����ִ����Ϻ���ע�����������ϣ���������ָ���ŵ�pclient_�У�������Ӧ�ĳ�Ա����Ҳ�Դ˸�ֵ
	**����:
	** ������ name ��I-���롿�������ƣ��ַ������� ����"vag"
	** ������ host��I-���롿������������ip��ַ���ַ�������������"192.168.1.1"
	** ������ port ��I-���롿����Ķ˿ں� ���α��� ����1234
	** ������ target ��I-���롿ע�����ĵ�ַ �ַ������� ����"http://192.168.20.251:2379"
	** ������ ttl��I-���롿����˵�� ���α��� ����ע����ϻ�ʱ�� ��λΪ��
	**����ֵ����
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	VS_MicroService::VS_MicroService(std::string name, std::string host, int port, std::string target, ::google::protobuf::int64 ttl);
	
	/*****************************************************************/
	/** ������:~VS_MicroService
	** ��������:VS_MicroServiceĬ����������
	**����:��
	** ������ 1 ��I-����/O-���������˵��
	** ������ 2��I-����/O-���������˵��
	**����ֵ����
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	~VS_MicroService();

	/*****************************************************************/
	/** ������:CreateLease
	** ��������:������Լ
	**����:
	** ������ ttl ��I-���롿���α��� ����ע����ϻ�ʱ��
	          pclient_ ��I-���롿 ����ע�����ĵ�ָ��
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int VS_MicroService::CreateLease(::google::protobuf::int64 ttl, etcd::Client* pclient);

	/*****************************************************************/
	/** ������:CreateLease
	** ��������:������Լ
	**����:
	** ������ ttl ��I-���롿����ע����ϻ�ʱ��
	��������,pclient_ �ڲ�������ע�����ĵ�ָ��
	�������������ڵ���ǰ�Լ���ʼ�����
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
		int VS_MicroService::CreateLease(::google::protobuf::int64 ttl);

	/*****************************************************************/
	/** ������:CreateLease
	** ��������:������Լ
	**����:��
	��������,ttl_ �ڲ��ķ���ע����ϻ�ʱ��
	pclient_ �ڲ�������ע�����ĵ�ָ��
	�������������ڵ���ǰ�Լ���ʼ�����
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int VS_MicroService::CreateLease();

	/*****************************************************************/
	/** ������:Registe
	** ��������:��ע������ע�ᣬע��ɹ�����{VS_MicroServicePath}/{name_}·���½���һ��host_:port_��key��valueΪĬ��ֵ����ǰϵͳ��ʱ���
	**����:�� 
	    Ĭ��ʹ��name_,host_��port_��Ϊ������
	    name_ ��I-���롿�������ƣ��ַ������� ����"vag"
	    host_��I-���롿������������ip��ַ���ַ�������������"192.168.1.1"
	    port_ ��I-���롿����Ķ˿ں� ���α��� ����1234
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int Registe();

	/*****************************************************************/
	/** ������:Registe
	** ��������:��ע������ע�ᣬע��ɹ�����{VS_MicroServicePath}/{name}·���½���һ��host:port��key��valueΪĬ��ֵ����ǰϵͳ��ʱ���
	**����:
	** ������ name ��I-���롿�������ƣ��ַ������� ����"vag"
	** ������ host��I-���롿������������ip��ַ���ַ�������������"192.168.1.1"
	** ������ port ��I-���롿����Ķ˿ں� ���α��� ����1234
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/

	int Registe(std::string name,std::string host, int port);
	/*****************************************************************/
	/** ������:RegisteWithValue
	** ��������:��ע������ע�ᣬע��ɹ�����{VS_MicroServicePath}/{name}·���½���һ��host:port��key��valueΪvalue
	**����:
	** ������ name ��I-���롿�������ƣ��ַ������� ����"vag"
	** ������ host��I-���롿������������ip��ַ���ַ�������������"192.168.1.1"
	** ������ port ��I-���롿����Ķ˿ں� ���α��� ����1234
	** ������ value ��I-���롿ע����ʹ�õ�value  �ַ������� ����"123456"
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int RegisteWithValue(string name, string host, int port,  std::string value);

	/*****************************************************************/
	/** ������:SendHeartBeat
	** ��������:��ע������ע��ɹ���������Լ��΢������ע�����ķ���������Ϣ��
	             ��ֹע��ķ�����Ϊ�ﵽ�ϻ�ʱ�䣬����ע������ɾ��
	**����:�� ���β�������
	          ** ������ leaseId_ �ɹ�ע���ķ������Լid��
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int SendHeartBeat();
	/*****************************************************************/
	/** ������:SendHeartBeat
	** ��������:��ע������ע��ɹ���������Լ��΢������ע�����ķ���������Ϣ��
	��ֹע��ķ�����Ϊ�ﵽ�ϻ�ʱ�䣬����ע������ɾ��
	**����:
	** ������ id ��Ҫ����������Ϣ�ķ������Լid��
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int SendHeartBeat(::google::protobuf::int64 id);

	/*****************************************************************/
	/** ������:UnRegiste
	** ��������:������ע�����Ľ��ע��
	**����:�� ���β�������
	       ** ������ name_ ��I-���롿�������ƣ����Ա��������ǰ���ʼ�����
	       ** ������ host_��I-���롿������������ip��ַ�����Ա��������ǰ���ʼ�����
	       ** ������ port_ ��I-���롿����Ķ˿ں� ���Ա��������ǰ���ʼ�����
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int UnRegiste();

	/*****************************************************************/
	/** ������:UnRegiste
	** ��������:������ע�����Ľ��ע��
	**����:
	** ������ name ��I-���롿�������ƣ��ַ������� ����"vag"
	** ������ host��I-���롿������������ip��ַ���ַ�������������"192.168.1.1"
	** ������ port ��I-���롿����Ķ˿ں� ���α��� ����1234
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	int UnRegiste(std::string name, std::string host, int port);

	/*****************************************************************/
	/** ������:Reslove
	** ��������:��ע�����Ľ������񣬻�ȡ�����ַ��Ĭ�ϲ���ʹ��RANDOM����
	**����:�� Ĭ�ϲ���Ϊname_�������ƣ��ַ������� ����"vag"
	**����ֵ���ɹ��������ط���ĵ�ַ�ַ���������"192.168.1.100:2000",ʧ�ܷ��ؿ��ַ���""
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	std::string Reslove();

	/*****************************************************************/
	/** ������:Reslove
	** ��������:��ע�����Ľ������񣬻�ȡ�����ַ��Ĭ�ϲ���ʹ��RANDOM����
	**����:
	** ������ name ��I-���롿�������ƣ��ַ������� ����"vag"
	**����ֵ���ɹ��������ط���ĵ�ַ�ַ���������"192.168.1.100:2000",ʧ�ܷ��ؿ��ַ���""
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	std::string Reslove(std::string name);

	/*****************************************************************/
	/** ������:Reslove
	** ��������:��ע�����Ľ������񣬻�ȡ�����ַ
	**����:
	** ������ name ��I-���롿�������ƣ��ַ������� ����"vag"
	** ������ policy��I-���롿�������ԣ�ö�����ͣ�ROUND��RANDOM ��PERFORMANECE 
	          ��������Ĭ����RANDOM���ǻ��β��ԣ�ѡ������ַ��RANDOM��������ԣ�PERFORMANECE�ǰ�����������ѡ������ַ
	**����ֵ���ɹ��������ط���ĵ�ַ�ַ���������"192.168.1.100:2000",ʧ�ܷ��ؿ��ַ���""
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	std::string Reslove(std::string name, PolicyType policy);

	/*****************************************************************/
	/** ������:SetWatcher
	** ��������:���÷������Լ�����仯��Ļص�
	**����:
	** ������ key ��I-���롿��Ҫ���ķ����keyֵ������ȫ·�����ַ������� ����"/service/vag/192.168.1.100:2000"
	** ������ callback��I-���롿�����ص������óɹ���keyֵ�����仯�󣬵��ûص�����
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	void SetWatcher(std::string key, std::function<void(Response)> callback);
	/*****************************************************************/
	/** ������:SetWatcher
	** ��������:���÷������Լ�����仯��Ļص�
	**����:
		** ������ callback��I-���롿�����ص������óɹ���keyֵ�����仯�󣬵��ûص�����
		�������� ��ĳ�Ա����name_,host_��port_,�����������Ҫ��ص�keyֵ
	**����ֵ��0���ɹ���-1��ʧ��
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	void SetWatcher(std::function<void(Response)> callback);
	
	void SetAutoHeartBeat();

	/*****************************************************************/
	/** ������:TimerThread
	** ��������:����������Ϣ�߳�������
	**����:��
	**����ֵ����
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	void TimerThread(int ttl);
	/*****************************************************************/
	/** ������:NewAutoHeartBeatThread
	** ��������:�½��Զ�����������Ϣ�̣߳����߳��Զ�����
	**����:
	** ������ ttl ��I-���롿�Զ�������������¼������ÿ������¼����֮ǰ�����̻߳��Զ�����һ��������Ϣ��ע������
	**����ֵ����
	** ȫ�ֱ���:��
	** ����ģ��:
	** �� ��:����ï
	** �� ��:2017-07-05
	** �� ��:����ï
	** �� ��:2017-07-05
	** �汾0.2
	*/
	/****************************************************************/
	void NewAutoHeartBeatThread(int ttl);

	void SetWatcher(std::string target, std::string key, std::function<void(Response)> callback);
private:
	static void AutoHeartBeat(const boost::system::error_code& e, boost::asio::deadline_timer* t, int ttl, void* ptr);
	void SetAutoHeartBeat(int ttl);

	//΢��������
	std::string name_;
	//΢�����ṩ�ߵ�ip
	std::string host_;
	//΢����Ķ˿�
	unsigned short  port_;
	//����ע�����ĵĿͻ���ָ�룬��ʼ��ʱΪNULL
	etcd::Client* pclient_;
	//������ָ�룬��ʼ��ʱΪNULL
	etcd::Watcher* pwatch_;
	//ע���΢������ϻ�ʱ�䣬�������������ʱ��
	::google::protobuf::int64 ttl_;
	//ע��΢�������Լ��һ��һ����Լ��Ӧһ���ϻ�ʱ��
	::google::protobuf::int64 leaseId_;
	//ע�����ĵ�ַ������"http://192.168.20.251:2379"
	std::string target_;
	//����΢�����ַ����
	PolicyType policy_;

};

class VS_MicroServiceWatcher {
public:
	VS_MicroServiceWatcher() {
		target_ = ""; 
		pwatch_ = NULL;
	}
	~VS_MicroServiceWatcher() {
		delWatcher();
	}
	void SetWatcher(std::string target, std::string key, std::function<void(Response)> callback);
	void SetWatcher(std::string target, std::string name, std::string ip, int port,std::function<void(Response)> callback);
	void SetWatcher2(std::string target, std::string name, std::string ip, int port, watcher_callback f, void* ptr);
	void SetWatcher2(std::string target, std::string key, watcher_callback f, void* ptr);
	void SetWatcher2(std::string target, std::string name, std::string address,watcher_callback f,void* ptr);
	void delWatcher();
private:
	std::string target_;
	std::string key_;
	etcd::Watcher* pwatch_;
};
}
#endif // !__VORX_SERVICE_H__