// �A�N�e�B�u��Kinect�̐����擾����T���v��
#include <iostream>

// MSR_NuiApi.h�̑O��Windows.h���C���N���[�h����
#include <Windows.h>
#include <MSR_NuiApi.h>

void main()
{
	int count = 0;
	::MSR_NUIGetDeviceCount( &count );
	std::cout << count << " kinects" << std::endl;;
	Sleep(5000);
}
