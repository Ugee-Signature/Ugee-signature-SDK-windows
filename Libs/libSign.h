//////////////////////////////////////////////////////////////////////////
//���ƣ���λ��ͨ��������
//�汾��1.1.0.9
//���ߣ�UGEE Technology 
//���ڣ�2020-09-09
//////////////////////////////////////////////////////////////////////////

#ifndef _libSign_H
#define _libSign_H

#ifndef  DLL_EXPORT
#define  DLL_EXPORT __declspec(dllexport)
#else
#define  DLL_EXPORT 
#endif

#include <windows.h>

namespace UG_LIBSIGN
{

	//ö�����Ͷ���
	//�¼�״̬ö��
	enum EventType
	{
		EventType_Pen = 1,
		EventType_Key = 2,
		EventType_Eraser = 3,
		EventType_Wheel = 4,
		EventType_ALL = 0xfe
	};

	//��״̬ö��
	enum  PenStatus
	{
		PenStatus_Hover,				//����
		PenStatus_Down,					//����
		PenStatus_Move,					//�ƶ�
		PenStatus_Up,					//̧��
		PenStatus_Leave					//�뿪
	};

	//����״̬ö��
	enum KeyStatus
	{
		KeyStatus_Up,					//����̧��
		KeyStatus_Down					//��������
	};

	//�ʰ���ö��
	enum ButtonStatus
	{
		ButtonStatus_Up,				//���ϰ���̧��
		ButtonStatus_Down				//���ϰ�������
	};

	//Touch״̬
	enum  TouchStatus
	{
		TouchStatus_Up,
		TouchStatus_Down,
		TouchStatus_Move
	};

	//�豸����״̬
	enum  DeviceStatus
	{
		DeviceStatus_Disconnected=0,
		DeviceStatus_Connected,
		DeviceStatus_Sleep,
		DeviceStatus_Awake
	};

	//�豸����ģʽ
	enum DeviceRunMode
	{
		DeviceRunMode_Mouse = 1,						//ϵͳ���
		DeviceRunMode_Pen = 2,							//������
		DeviceRunMode_MousePen = 3,						//ϵͳ���+������
		DeviceRunMode_StdPen = 4						//��׼��λ��
	};

	//�豸��ʽ
	enum DeviceType
	{
		DeviceType_Normal = 0,							//�����豸
		DeviceType_UG05 = 1,							//UG05�豸
		DeviceType_HANKSON = 2,							//HANKSON �����
	};


	//////////////////////////////////////////////////////////////////////////
	//����ֵ����
	#define			ERR_OK						0
	#define			ERR_DEVICE_NOTFOUND			-1
	#define			ERR_DEVICE_OPENFAIL			-2
	#define			ERR_DEVICE_NOTCONNECTED		-3
	#define			ERR_DATFILEFAIL		        -4

	#define			ERR_INVALIDPARAM			-101
	#define			ERR_NOSUPPORTED				-102


	//����û���� ������28bd mi02��ͨ���豸id
	#define			GENERAL_DEVICES_INDEX		150

	//////////////////////////////////////////////////////////////////////////
	//���ݽṹ����
	//��λ��X/Y�᷶Χ
	typedef		struct  tagAXIS
	{
		unsigned long	min;
		unsigned long	max;
	}AXIS, *PAXIS;

	//��λ���豸��Ϣ
	typedef struct tagTABLET_DEVICEINFO
	{
		AXIS				axisX;					//X�᷶Χ
		AXIS				axisY;					//Y�᷶Χ
		unsigned long		pressure;				//ѹ�м���
		char				vendor[32];				//��������
		char				product[32];			//��Ʒ����
		unsigned long		version;				//�����ӿڰ汾
		char				serialnum[32];			//�豸���к�
	}TABLET_DEVICEINFO, *PTABLET_DEVICEINFO;

	//��λ�����ݰ�
	typedef struct  tagDATAPACKET
	{
		EventType			eventtype;				//�¼�����	4
		unsigned short		physical_key;			//������	2
		unsigned short		virtual_key;			//���ⰴ��	2
		KeyStatus			keystatus;				//����״̬	4
		PenStatus			penstatus;				//�ʼ�״̬	4
		int 				x;// unsigned short		x;	//x����		2
		int 				y;//unsigned short		y;	//y����		2
		int 				pressure;// unsigned short		pressure;		//ѹ��		2
		short				wheel_direction;		//ת����ת�����ʶ	2
		unsigned short		button;					//����������		2
		char				tiltX;					//б��X
		char				tiltY;					//б��Y
	}DATAPACKET, *PDATAPACKET;

	typedef struct tagTOUCHDATA
	{
		TouchStatus			status[10];
		unsigned int		x[10];
		unsigned int		y[10];

	}TOUCHDATA, *PTOUCHDATA;

	//�豸����״̬
	typedef struct  tagSTATUSPACKET
	{
		int			penAlive;
		int			penBattery;
		int			status;						//0  DISCONNECTED  1 CONNECTED  2 SLEEP  3 AWAKE
	}STATUSPACKET, *PSTATUSPACKET;

	typedef struct  tagETAINFO
	{
		char		barcode[32];			//
	}ETAINFO;

	typedef		int (_stdcall * PACKDATAPROC)(DATAPACKET pktObj);
	typedef		int (_stdcall * DEVNOTIFYPROC)(STATUSPACKET pktObj);
	typedef		int(_stdcall * DEVOPENFYPROC)(int bOpen);
	typedef		int (_stdcall * TOUCHPROC)(TOUCHDATA td);
	typedef		int(_stdcall * ETAINFOPROC)(ETAINFO pktObj);

	#ifdef __cplusplus
	extern "C" {
	#endif 
		DLL_EXPORT	int		_stdcall	signInitialize();
		DLL_EXPORT	void	_stdcall	signClean();
		DLL_EXPORT	int		_stdcall	signGetDeviceStatus();
		DLL_EXPORT	int		_stdcall	signGetDeviceOpenStatus();
		DLL_EXPORT	int		_stdcall	signOpenDevice();
		DLL_EXPORT	int		_stdcall	signCloseDevice();

		DLL_EXPORT	int		_stdcall	signGetDeviceInfo(TABLET_DEVICEINFO* lpDeviceInfo);
		DLL_EXPORT	long	_stdcall	signRegisterDataCallBack(PACKDATAPROC lpPackDataProc);
		DLL_EXPORT	void	_stdcall	signUnregisterDataCallBack(long handler);
		DLL_EXPORT	long	_stdcall	signRegisterDevNotifyCallBack(DEVNOTIFYPROC lpDevNotifyProc);
		DLL_EXPORT	long	_stdcall	signRegisterDevOpenCallBack(DEVOPENFYPROC lpDevNotifyProc);
		
		DLL_EXPORT	void	_stdcall	signUnregisterDevOpenCallBack(long handler);
		DLL_EXPORT	void	_stdcall	signUnregisterDevNotifyCallBack(long handler);
		DLL_EXPORT  long	_stdcall	signRegisterTouchCallBack(TOUCHPROC lpTouchProc);
		DLL_EXPORT	void	_stdcall	signUnregisterTouchCallBack(long handler);

		DLL_EXPORT	int		_stdcall	signChangeDeviceMode(int mode);
		//��Ļ֧��API
		DLL_EXPORT	int		_stdcall	signGetScreenRect(RECT* lpRect);
		DLL_EXPORT	bool	_stdcall	signMouseControl(bool bControlled);
		DLL_EXPORT	void	_stdcall	signSetExtendDisplay(bool bExtendDisplay);
		DLL_EXPORT	int		_stdcall	signRotateMode(int mode);
		DLL_EXPORT	long	_stdcall	RegisterReadBarCodeCallBack(ETAINFOPROC lpReadBarCodeProc);
		DLL_EXPORT	void	_stdcall	OpenReadBarCode();
		DLL_EXPORT	void	_stdcall	CloseReadBarCode();
	#ifdef __cplusplus
	}
	#endif

}
#endif