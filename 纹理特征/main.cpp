#include"GLCM_GM.h"

int main()
{
	VecGLCM VecGlcm(256);
	for (int i = 0; i < 256; i++)
	{
		VecGlcm[i].resize(256);
	}
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			VecGlcm[i][j] = 0;
		}
	}
	ValueWrite(ImageFileRead("E:\\学习资料\\2020图像特征计算与表示课件\\烟叶分级的作业\\烟叶识别作业\\烟叶识别作业\\test_351\\B2F\\*.jpg", VecGlcm, 256), "test_B2F.txt",1);     //写操作
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\学习资料\\2020图像特征计算与表示课件\\烟叶分级的作业\\烟叶识别作业\\烟叶识别作业\\test_351\\B3F\\*.jpg", VecGlcm, 256), "test_B3F.txt",2);     //写操作
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\学习资料\\2020图像特征计算与表示课件\\烟叶分级的作业\\烟叶识别作业\\烟叶识别作业\\test_351\\C2F\\*.jpg", VecGlcm, 256), "test_C2F.txt",3);     //写操作
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\学习资料\\2020图像特征计算与表示课件\\烟叶分级的作业\\烟叶识别作业\\烟叶识别作业\\test_351\\C3F\\*.jpg", VecGlcm, 256), "test_C3F.txt",4);     //写操作
	InitVecGLCM(VecGlcm, 256);
	ValueWrite(ImageFileRead("E:\\学习资料\\2020图像特征计算与表示课件\\烟叶分级的作业\\烟叶识别作业\\烟叶识别作业\\test_351\\C4F\\*.jpg", VecGlcm, 256), "test_C4F.txt",5);     //写操作
	return 0;
}
