#include"GLCM_GM.h"

//==============================================================================
// 函数名称: VecGLCMCount0
// 参数说明: PriImage为初始的图片，nCols为列，nRows为行数
// 函数功能: 进行0度方向的共生矩阵求解 
//==============================================================================

void VecGLCMCount0(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	for (int i = 0; i < nRows; i++)
	{
		p = PriImage.ptr<uchar>(i);//获取每行首地址
		for (int j = 0; j < nCols - 1; ++j)
		{
			VecGLCM_Col = p[j];
			VecGLCM_Row = p[j + 1];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}


//改1：改为45度方向，前面的才0度方向
/*
void VecGLCMCount45(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	for (int i = 0; i < nRows-1; i++)
	{
		for (int j = 0; j < nCols-1; j++)
		{
			VecGLCM_Col = PriImage.at<uchar>(i, j);
			VecGLCM_Row = PriImage.at<uchar>(i + 1, j + 1);
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}
*/

void VecGLCMCount45(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	uchar* p1;
	for (int i = 0; i < nRows-1; i++)
	{
		p = PriImage.ptr<uchar>(i);//获取每行首地址
		for (int j = 0; j < nCols - 1; ++j)
		{
			VecGLCM_Col = p[j];
			p1 = PriImage.ptr<uchar>(i + 1);
			VecGLCM_Row = p1[j + 1];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}

void VecGLCMCount90(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	uchar* p1;
	for (int i = 0; i < nRows - 1; i++)
	{
		p = PriImage.ptr<uchar>(i);//获取每行首地址
		for (int j = 0; j < nCols; ++j)
		{
			VecGLCM_Col = p[j];
			p1 = PriImage.ptr<uchar>(i + 1);
			VecGLCM_Row = p1[j];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}

void VecGLCMCount135(VecGLCM& GM_VecGLCM, cv::Mat PriImage, int nCols, int nRows)
{
	int VecGLCM_Col;
	int VecGLCM_Row;
	uchar* p;
	uchar* p1;
	for (int i = 1; i < nRows ; i++)
	{
		p = PriImage.ptr<uchar>(i);//获取每行首地址
		for (int j = 0; j < nCols - 1; ++j)
		{
			VecGLCM_Col = p[j];
			p1 = PriImage.ptr<uchar>(i - 1);
			VecGLCM_Row = p1[j + 1];
			GM_VecGLCM[VecGLCM_Col][VecGLCM_Row]++;
		}
	}
}
//==============================================================================
// 函数名称: ComputeEntropy
// 参数说明: GM_VecGLCM为共生矩阵，size为矩阵的大小（size X size）
// 函数功能: 求共生矩阵的熵
//==============================================================================
double ComputeEntropy(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	vector<vector<uchar>>::iterator IE;

	vector<uchar>::iterator it;
	for (IE = GM_VecGLCM.begin(); IE < GM_VecGLCM.end(); IE++)
	{
		for (it = (*IE).begin(); it < (*IE).end(); it++)
		{
			if ((*it) != 0)  sum += -(*it) * log(*it);
			//cout << *it << " ";
		}
	}
	return sum;
}

//上述用迭代器更安全
/*
double ComputeEntropy(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	for(int i=0;i<size;i++)
		for (int j = 0; j < size ; j++)
		{
			if (GM_VecGLCM[i][j] != 0)
			{
				sum += -GM_VecGLCM[i][j] * log(GM_VecGLCM[i][j]);
			}
		}
	return sum;
}
*/

//==============================================================================
// 函数名称: ComputeEnergy
// 参数说明: GM_VecGLCM为共生矩阵，size为矩阵的大小（size X size）
// 函数功能: 求共生矩阵的能量
//==============================================================================
double ComputeEnergy(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	vector<vector<uchar>>::iterator IE;
	vector<uchar>::iterator it;
	for (IE = GM_VecGLCM.begin(); IE < GM_VecGLCM.end(); IE++)
	{
		for (it = (*IE).begin(); it < (*IE).end(); it++)
		{
			sum += (*it) ^ 2;
		}
	}
	return sum;
}

//==============================================================================
// 函数名称: ComputeContrast
// 参数说明: GM_VecGLCM为共生矩阵，size为矩阵的大小（size X size）
// 函数功能: 求共生矩阵的对比度
//==============================================================================
double ComputeContrast(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += (i - j) ^ 2 * GM_VecGLCM[i][j];
		}
	}
	return sum;
}

//==============================================================================
// 函数名称: ComputeUniformity
// 参数说明: GM_VecGLCM为共生矩阵，size为矩阵的大小（size X size）
// 函数功能: 求共生矩阵的均匀度
//==============================================================================
double ComputeUniformity(VecGLCM& GM_VecGLCM, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += GM_VecGLCM[i][j] / (1 + abs(i - j));
		}
	}
	return sum;
}

//==============================================================================
// 函数名称: ComputeCorrelation
// 参数说明: GM_VecGLCM为共生矩阵，size为矩阵的大小（size X size）
// 函数功能: 求共生矩阵的相关性
//==============================================================================
double ComputeCorrelation(VecGLCM& GM_VecGLCM, int size)
{
	double Ui = 0;
	double Uj = 0;
	double Si = 0;
	double Sj = 0;
	double Si_Square = 0;    //Si的平方为Si_Square
	double Sj_Square = 0;    //Sj的平方为Sj_Square
	double COR = 0;  //相关性
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Ui += (i+1) * GM_VecGLCM[i][j];
			Uj += (j+1) * GM_VecGLCM[i][j];
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Si_Square += GM_VecGLCM[i][j] * (i+1 - Ui) * (i+1 - Ui);
			Sj_Square += GM_VecGLCM[i][j] * (j+1 - Uj) * (j+1 - Uj);
		}
	}
	Si = sqrt(Si_Square);
	Sj = sqrt(Sj_Square);
	for (int i=0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			COR += (((i + 1) * (j + 1)) * GM_VecGLCM[i][j] - Ui * Uj)/(Si*Sj);
		}
	}
	return COR;
}

//==============================================================================
// 函数名称: ImageFileRead
// 参数说明: PatternJPG为文件名，形如"E:\\图片\\*.jpg",GM_VecGLCM为共生矩阵，size为矩阵的大小
// 函数功能: 批量处理图片文件，并计算共生矩阵的熵、能量、对比度和均匀度返回一个num X 4的矩阵（num为图片的总数）
//==============================================================================
vector<vector<double>> ImageFileRead(string PatternJPG, VecGLCM& GM_VecGLCM, int size)
{
	vector<string> ImageFile;
	glob(PatternJPG, ImageFile);    //将PatternJPG路径下的所用文件名存进ImageFile中
	if (ImageFile.size() == 0) {
		cout << "NO image file[jpg]" << endl;
	}

	//二维矩阵创建，ValueVec中保存各个图片的共生矩阵的四个参数信息
	vector<vector<double>> ValueVec;
	int num = ImageFile.size();
	ValueVec.resize(num);
	for (int i = 0; i < num  ; i++)
	{
		ValueVec[i].resize(1);
	}

	for (unsigned int frame = 0; frame < ImageFile.size(); ++frame)
	{
		Mat image = cv::imread(ImageFile[frame], IMREAD_GRAYSCALE);
		cout << ImageFile[frame] << "读取成功！" << endl;
		int nRows = image.rows;
		int nCols = image.cols;
		VecGLCMCount0(GM_VecGLCM, image, nCols, nRows);
		//ValueVec[frame][0] = ComputeEntropy(GM_VecGLCM, size);       //计算熵值
		//ValueVec[frame][1] = ComputeEnergy(GM_VecGLCM, size);       //计算能量
		//ValueVec[frame][2] = ComputeContrast(GM_VecGLCM, size);       //计算对比度
		//ValueVec[frame][3] = ComputeUniformity(GM_VecGLCM, size);     //计算均匀度
		ValueVec[frame][0] = ComputeCorrelation(GM_VecGLCM, size);
		InitVecGLCM(GM_VecGLCM, size);  //重新将GM_VecGLCM变为全0的矩阵
	}
	return ValueVec;
}

//==============================================================================
// 函数名称: ValueWrite
// 参数说明: Matrix为矩阵名，FileName为需要写如的文件名，如"B2F.txt"
// 函数功能: 文件写操作，将Matrix中的内容写入文件FileName中
//==============================================================================
void ValueWrite(vector<vector<double>> Matrix, string FileName,int n)
{
	ofstream in;
	in.open(FileName, ios::trunc);  //ios::tuunc表示在打开文件前将文件清空，由于是写入，文件不存在则创建
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix[i].size(); j++)
		{
			in << Matrix[i][j] << "\t";
		}
		in << n << "\t";
		in << "\n";
	}
}

void InitVecGLCM(VecGLCM& GM_VecGLCM, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			GM_VecGLCM[i][j] = 0;
		}
	}
}