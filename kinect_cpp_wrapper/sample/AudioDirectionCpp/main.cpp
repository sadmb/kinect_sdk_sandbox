// 中心の距離を表示するサンプル
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <tchar.h>
#include <strsafe.h>
#include <conio.h>

#include "kinect\nui\Kinect.h"
#include "kinect\nui\WaveFileWriter.h"

void main()
{
    try {
        kinect::nui::Kinect kinect;
		kinect.Initialize(NUI_INITIALIZE_FLAG_USES_AUDIO);

		kinect::nui::AudioStream& audio = kinect.AudioStream();
		audio.Open();
		kinect::nui::WaveFileWriter wave;
		LPCTSTR szOutputFile = _T("AECOut.wav");
		TCHAR szOutfileFullName[MAX_PATH];
		DWORD dwRet = GetFullPathName(szOutputFile, (DWORD)ARRAYSIZE(szOutfileFullName), szOutfileFullName, NULL);
		wave.Initialize(szOutputFile, audio.GetWaveFormat().nSamplesPerSec, audio.GetWaveFormat().wBitsPerSample, audio.GetWaveFormat().nChannels);

        while ( 1 ) {
            // データの更新を待つ
            kinect.WaitAndUpdateAll();

            // 次のフレームのデータを取得する(OpenNIっぽく)
			std::vector<BYTE> source = audio.Read();

			if(source.size() != 0){
				wave.Write(source, source.size());
			}

			std::cout << "Position: "<< audio.GetAudioBeamAngle() << "\t\tConfidence: " << audio.GetAudioAngle() << "\t\tBeam Angle = " << audio.GetAudioAngleConfidence() << "\r" << std::endl;

			if(_kbhit())
			{
				break;
			}

        }

		wave.Flush();

	}catch ( std::exception& ex ) {
        std::cout << ex.what() << std::endl;
    }
}
