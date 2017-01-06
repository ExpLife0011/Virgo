#include "DriverEntry.h"
#include "FsProctect.cpp"
#include "PsProtect.cpp"
#include "MsFiliter.cpp"
#include "RegMonitor.cpp"

/************************************************************************************************************************************
		 
															Author: Jin Liang
				
		1.�ļ���д����

		 HarddiskVolume2 -> E��: ��ֹֻ�������ļ�ɾ������

		 HarddiskVolume3 -> F��: �ܾ��� "\����Ŀ¼" �ķ���
								 ��ֹ��Explorer���������в���
								 ��ֹ��Explorer���̴�������
								 ��ֹ�����޸Ĳ���
								 ����Ŀ¼͸������
					   
		 2.ģ���������
  
			ִ���ļ�: ������ǩ����(Tencent, Baidu, Ava)		����
            ������ģ�飺(WebChat, QQ)						����
			�����ļ�: (ת�Ƶ�ע�����)

		3.ע�����
   
			������: 
				��ֹ����:
						1.HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
						2.HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
						3.HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run

			������:
				����:
					1.HKEY_LOCAL_MACHINE\SYSTEM\ControlSet\services\;	Boot Type: Auto

		Minifiliter:	�ܲ�������ֻ������һ��΢С�Ĺ�����

************************************************************************************************************************************/


NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
   	NTSTATUS ntStatus = STATUS_SUCCESS;


	#ifdef _DEBUG
	DriverObject->DriverUnload = DriverUnload;
	#endif

	/*�������̱���*/

	InstallDiskProtect(DriverObject);
	
	DbgPrint("[Anti-BTA] fsProtect Installed!\n");

	/*����ģ�����μ��*/

	InstallModuleFiliter();
	
	DbgPrint("[Anti-BTA] PsMonitor Installed!\n");

	/*����ע�����*/

	InstallRegMonitor();

	DbgPrint("[Anti-BTA] CmpRegister Installed!\n");

	/*�������̱���*/

	InstallProcessProtect();

	DbgPrint("[Anti-BTA] PsProcect Enabled!\n");
	

	DbgPrint("[Anti-BTA] Passed!\n");

	return ntStatus;
}



VOID
DriverUnload (PDRIVER_OBJECT DriverObject)
{
	UnInstallModuleFiliter();

	UnInstallRegMonitor();

	UnInstallProcessProtect();

	DbgPrint("[Anti-BTA] Excited!\n");
}