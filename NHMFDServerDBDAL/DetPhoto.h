/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetPhoto.h
* 文件标识：
* 描述：检测照片表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Cyx
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Cyx
* 描述：正在开发
*/


#if !defined (NHMFDSERVERDBMODEL_DETPHOTO_H)
#define NHMFDSERVERDBMODEL_DETPHOTO_H


#include <string>
#include <memory>
typedef unsigned char BYTE;

struct SDetPhoto
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 照片路径数组，共30张照片，照片1路径对应strPhotoPath[1],如此类推
	std::wstring strPhotoPath[31];
	// 照片1
	BYTE *pbPhoto1;
	// 照片1序号
	std::wstring strPhoto1SN;
	// 照片1拍照时间(年月日时分秒)
	std::wstring strPhoto1Time;
	// 照片2
	BYTE *pbPhoto2;
	// 照片2序号
	std::wstring strPhoto2SN;
	// 照片2拍照时间(年月日时分秒)
	std::wstring strPhoto2Time;
	// 照片3
	BYTE *pbPhoto3;
	// 照片3序号
	std::wstring strPhoto3SN;
	// 照片3拍照时间(年月日时分秒)
	std::wstring strPhoto3Time;
	// 照片4
	BYTE *pbPhoto4;
	// 照片4序号
	std::wstring strPhoto4SN;
	// 照片4拍照时间(年月日时分秒)
	std::wstring strPhoto4Time;
	// 照片5
	BYTE *pbPhoto5;
	// 照片5序号
	std::wstring strPhoto5SN;
	// 照片5拍照时间(年月日时分秒)
	std::wstring strPhoto5Time;
	// 照片6
	BYTE *pbPhoto6;
	// 照片6序号
	std::wstring strPhoto6SN;
	// 照片6拍照时间(年月日时分秒)
	std::wstring strPhoto6Time;
	// 照片7
	BYTE *pbPhoto7;
	// 照片7序号
	std::wstring strPhoto7SN;
	// 照片7拍照时间(年月日时分秒)
	std::wstring strPhoto7Time;
	// 照片8
	BYTE *pbPhoto8;
	// 照片8序号
	std::wstring strPhoto8SN;
	// 照片8拍照时间(年月日时分秒)
	std::wstring strPhoto8Time;
	// 照片9
	BYTE *pbPhoto9;
	// 照片9序号
	std::wstring strPhoto9SN;
	// 照片9拍照时间(年月日时分秒)
	std::wstring strPhoto9Time;
	// 照片10
	BYTE *pbPhoto10;
	// 照片10序号
	std::wstring strPhoto10SN;
	// 照片10拍照时间(年月日时分秒)
	std::wstring strPhoto10Time;

	// 照片11
	BYTE *pbPhoto11;
	// 照片1序号
	std::wstring strPhoto11SN;
	// 照片1拍照时间(年月日时分秒)
	std::wstring strPhoto11Time;
	// 照片12
	BYTE *pbPhoto12;
	// 照片12序号
	std::wstring strPhoto12SN;
	// 照片12拍照时间(年月日时分秒)
	std::wstring strPhoto12Time;
	// 照片13
	BYTE *pbPhoto13;
	// 照片3序号
	std::wstring strPhoto13SN;
	// 照片3拍照时间(年月日时分秒)
	std::wstring strPhoto13Time;
	// 照片14
	BYTE *pbPhoto14;
	// 照片4序号
	std::wstring strPhoto14SN;
	// 照片4拍照时间(年月日时分秒)
	std::wstring strPhoto14Time;
	// 照片15
	BYTE *pbPhoto15;
	// 照片15序号
	std::wstring strPhoto15SN;
	// 照片15拍照时间(年月日时分秒)
	std::wstring strPhoto15Time;
	// 照片16
	BYTE *pbPhoto16;
	// 照片16序号
	std::wstring strPhoto16SN;
	// 照片16拍照时间(年月日时分秒)
	std::wstring strPhoto16Time;
	// 照片17
	BYTE *pbPhoto17;
	// 照片17序号
	std::wstring strPhoto17SN;
	// 照片17拍照时间(年月日时分秒)
	std::wstring strPhoto17Time;
	// 照片18
	BYTE *pbPhoto18;
	// 照片18序号
	std::wstring strPhoto18SN;
	// 照片18拍照时间(年月日时分秒)
	std::wstring strPhoto18Time;
	// 照片19
	BYTE *pbPhoto19;
	// 照片19序号
	std::wstring strPhoto19SN;
	// 照片19拍照时间(年月日时分秒)
	std::wstring strPhoto19Time;
	// 照片20
	BYTE *pbPhoto20;
	// 照片20序号
	std::wstring strPhoto20SN;
	// 照片20拍照时间(年月日时分秒)
	std::wstring strPhoto20Time;

	// 照片21
	BYTE *pbPhoto21;
	// 照片21序号
	std::wstring strPhoto21SN;
	// 照片21拍照时间(年月日时分秒)
	std::wstring strPhoto21Time;
	// 照片22
	BYTE *pbPhoto22;
	// 照片22序号
	std::wstring strPhoto22SN;
	// 照片22拍照时间(年月日时分秒)
	std::wstring strPhoto22Time;
	// 照片23
	BYTE *pbPhoto23;
	// 照片23序号
	std::wstring strPhoto23SN;
	// 照片23拍照时间(年月日时分秒)
	std::wstring strPhoto23Time;
	// 照片24
	BYTE *pbPhoto24;
	// 照片24序号
	std::wstring strPhoto24SN;
	// 照片24拍照时间(年月日时分秒)
	std::wstring strPhoto24Time;
	// 照片25
	BYTE *pbPhoto25;
	// 照片25序号
	std::wstring strPhoto25SN;
	// 照片25拍照时间(年月日时分秒)
	std::wstring strPhoto25Time;
	// 照片26
	BYTE *pbPhoto26;
	// 照片26序号
	std::wstring strPhoto26SN;
	// 照片26拍照时间(年月日时分秒)
	std::wstring strPhoto26Time;
	// 照片27
	BYTE *pbPhoto27;
	// 照片27序号
	std::wstring strPhoto27SN;
	// 照片27拍照时间(年月日时分秒)
	std::wstring strPhoto27Time;
	// 照片28
	BYTE *pbPhoto28;
	// 照片28序号
	std::wstring strPhoto28SN;
	// 照片8拍照时间(年月日时分秒)
	std::wstring strPhoto28Time;
	// 照片29
	BYTE *pbPhoto29;
	// 照片29序号
	std::wstring strPhoto29SN;
	// 照片29拍照时间(年月日时分秒)
	std::wstring strPhoto29Time;
	// 照片30
	BYTE *pbPhoto30;
	// 照片30序号
	std::wstring strPhoto30SN;
	// 照片30拍照时间(年月日时分秒)
	std::wstring strPhoto30Time;


	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;

	// 以下字段不和数据库字段对应，指示图片缓冲区大小
	unsigned int nPhoto1Size;
	unsigned int nPhoto2Size;
	unsigned int nPhoto3Size;
	unsigned int nPhoto4Size;
	unsigned int nPhoto5Size;
	unsigned int nPhoto6Size;
	unsigned int nPhoto7Size;
	unsigned int nPhoto8Size;
	unsigned int nPhoto9Size;
	unsigned int nPhoto10Size;
	unsigned int nPhoto11Size;
	unsigned int nPhoto12Size;
	unsigned int nPhoto13Size;
	unsigned int nPhoto14Size;
	unsigned int nPhoto15Size;
	unsigned int nPhoto16Size;
	unsigned int nPhoto17Size;
	unsigned int nPhoto18Size;
	unsigned int nPhoto19Size;
	unsigned int nPhoto20Size;
	unsigned int nPhoto21Size;
	unsigned int nPhoto22Size;
	unsigned int nPhoto23Size;
	unsigned int nPhoto24Size;
	unsigned int nPhoto25Size;
	unsigned int nPhoto26Size;
	unsigned int nPhoto27Size;
	unsigned int nPhoto28Size;
	unsigned int nPhoto29Size;
	unsigned int nPhoto30Size;

	SDetPhoto()
	{
		pbPhoto1 = NULL;
		pbPhoto2 = NULL;
		pbPhoto3 = NULL;
		pbPhoto4 = NULL;
		pbPhoto5 = NULL;
		pbPhoto6 = NULL;
		pbPhoto7 = NULL;
		pbPhoto8 = NULL;
		pbPhoto9 = NULL;
		pbPhoto10 = NULL;
		pbPhoto11 = NULL;
		pbPhoto12 = NULL;
		pbPhoto13 = NULL;
		pbPhoto14 = NULL;
		pbPhoto15 = NULL;
		pbPhoto16 = NULL;
		pbPhoto17 = NULL;
		pbPhoto18 = NULL;
		pbPhoto19 = NULL;
		pbPhoto20 = NULL;
		pbPhoto21 = NULL;
		pbPhoto22 = NULL;
		pbPhoto23 = NULL;
		pbPhoto24 = NULL;
		pbPhoto25 = NULL;
		pbPhoto26 = NULL;
		pbPhoto27 = NULL;
		pbPhoto28 = NULL;
		pbPhoto29 = NULL;
		pbPhoto30 = NULL;

		nPhoto1Size = 0;
		nPhoto2Size = 0;
		nPhoto3Size = 0;
		nPhoto4Size = 0;
		nPhoto5Size = 0;
		nPhoto6Size = 0;
		nPhoto7Size = 0;
		nPhoto8Size = 0;
		nPhoto9Size = 0;
		nPhoto10Size = 0;
		nPhoto11Size = 0;
		nPhoto12Size = 0;
		nPhoto13Size = 0;
		nPhoto14Size = 0;
		nPhoto15Size = 0;
		nPhoto16Size = 0;
		nPhoto17Size = 0;
		nPhoto18Size = 0;
		nPhoto19Size = 0;
		nPhoto20Size = 0;
		nPhoto21Size = 0;
		nPhoto22Size = 0;
		nPhoto23Size = 0;
		nPhoto24Size = 0;
		nPhoto25Size = 0;
		nPhoto26Size = 0;
		nPhoto27Size = 0;
		nPhoto28Size = 0;
		nPhoto29Size = 0;
		nPhoto30Size = 0;
	}
	
	~SDetPhoto()
	{
		if (pbPhoto1 != NULL)
		{
			delete pbPhoto1;
			pbPhoto1 = NULL;
		}
		if (pbPhoto2 != NULL)
		{
			delete pbPhoto2;
			pbPhoto2 = NULL;
		}
		if (pbPhoto3 != NULL)
		{
			delete pbPhoto3;
			pbPhoto3 = NULL;
		}
		if (pbPhoto4 != NULL)
		{
			delete pbPhoto4;
			pbPhoto4 = NULL;
		}
		if (pbPhoto5 != NULL)
		{
			delete pbPhoto5;
			pbPhoto5 = NULL;
		}
		if (pbPhoto6 != NULL)
		{
			delete pbPhoto6;
			pbPhoto6 = NULL;
		}
		if (pbPhoto7 != NULL)
		{
			delete pbPhoto7;
			pbPhoto7 = NULL;
		}
		if (pbPhoto8 != NULL)
		{
			delete pbPhoto8;
			pbPhoto8 = NULL;
		}
		if (pbPhoto9 != NULL)
		{
			delete pbPhoto9;
			pbPhoto9 = NULL;
		}
		if (pbPhoto10 != NULL)
		{
			delete pbPhoto10;
			pbPhoto10 = NULL;
		}

		if (pbPhoto11 != NULL)
		{
			delete pbPhoto11;
			pbPhoto11 = NULL;
		}
		if (pbPhoto12 != NULL)
		{
			delete pbPhoto12;
			pbPhoto12 = NULL;
		}
		if (pbPhoto13 != NULL)
		{
			delete pbPhoto13;
			pbPhoto13 = NULL;
		}
		if (pbPhoto14 != NULL)
		{
			delete pbPhoto14;
			pbPhoto14 = NULL;
		}
		if (pbPhoto15 != NULL)
		{
			delete pbPhoto15;
			pbPhoto15 = NULL;
		}
		if (pbPhoto16 != NULL)
		{
			delete pbPhoto16;
			pbPhoto16 = NULL;
		}
		if (pbPhoto17 != NULL)
		{
			delete pbPhoto17;
			pbPhoto17 = NULL;
		}
		if (pbPhoto18 != NULL)
		{
			delete pbPhoto18;
			pbPhoto18 = NULL;
		}
		if (pbPhoto19 != NULL)
		{
			delete pbPhoto19;
			pbPhoto19 = NULL;
		}
		if (pbPhoto20 != NULL)
		{
			delete pbPhoto20;
			pbPhoto20 = NULL;
		}

		if (pbPhoto21 != NULL)
		{
			delete pbPhoto21;
			pbPhoto21 = NULL;
		}
		if (pbPhoto22 != NULL)
		{
			delete pbPhoto22;
			pbPhoto22 = NULL;
		}
		if (pbPhoto23 != NULL)
		{
			delete pbPhoto23;
			pbPhoto23 = NULL;
		}
		if (pbPhoto24 != NULL)
		{
			delete pbPhoto24;
			pbPhoto24 = NULL;
		}
		if (pbPhoto25 != NULL)
		{
			delete pbPhoto25;
			pbPhoto25 = NULL;
		}
		if (pbPhoto26 != NULL)
		{
			delete pbPhoto26;
			pbPhoto26 = NULL;
		}
		if (pbPhoto27 != NULL)
		{
			delete pbPhoto27;
			pbPhoto27 = NULL;
		}
		if (pbPhoto28 != NULL)
		{
			delete pbPhoto28;
			pbPhoto28 = NULL;
		}
		if (pbPhoto29 != NULL)
		{
			delete pbPhoto29;
			pbPhoto29 = NULL;
		}
		if (pbPhoto30 != NULL)
		{
			delete pbPhoto30;
			pbPhoto30 = NULL;
		}
	}

	void SetPhoto1Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto1, pbPhotoData, nSize);
		nPhoto1Size = nSize;
	}
	void SetPhoto2Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto2, pbPhotoData, nSize);
		nPhoto2Size = nSize;
	}
	void SetPhoto3Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto3, pbPhotoData, nSize);
		nPhoto3Size = nSize;
	}
	void SetPhoto4Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto4, pbPhotoData, nSize);
		nPhoto4Size = nSize;
	}
	void SetPhoto5Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto5, pbPhotoData, nSize);
		nPhoto5Size = nSize;
	}
	void SetPhoto6Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto6, pbPhotoData, nSize);
		nPhoto6Size = nSize;
	}
	void SetPhoto7Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto7, pbPhotoData, nSize);
		nPhoto7Size = nSize;
	}
	void SetPhoto8Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto8, pbPhotoData, nSize);
		nPhoto8Size = nSize;
	}
	void SetPhoto9Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto9, pbPhotoData, nSize);
		nPhoto9Size = nSize;
	}
	void SetPhoto10Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto10, pbPhotoData, nSize);
		nPhoto10Size = nSize;
	}

	void SetPhoto11Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto11, pbPhotoData, nSize);
		nPhoto11Size = nSize;
	}
	void SetPhoto12Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto12, pbPhotoData, nSize);
		nPhoto12Size = nSize;
	}
	void SetPhoto13Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto13, pbPhotoData, nSize);
		nPhoto13Size = nSize;
	}
	void SetPhoto14Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto14, pbPhotoData, nSize);
		nPhoto14Size = nSize;
	}
	void SetPhoto15Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto15, pbPhotoData, nSize);
		nPhoto15Size = nSize;
	}
	void SetPhoto16Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto16, pbPhotoData, nSize);
		nPhoto16Size = nSize;
	}
	void SetPhoto17Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto17, pbPhotoData, nSize);
		nPhoto17Size = nSize;
	}
	void SetPhoto18Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto18, pbPhotoData, nSize);
		nPhoto18Size = nSize;
	}
	void SetPhoto19Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto19, pbPhotoData, nSize);
		nPhoto19Size = nSize;
	}
	void SetPhoto20Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto20, pbPhotoData, nSize);
		nPhoto20Size = nSize;
	}

		void SetPhoto21Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto21, pbPhotoData, nSize);
		nPhoto21Size = nSize;
	}
	void SetPhoto22Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto22, pbPhotoData, nSize);
		nPhoto22Size = nSize;
	}
	void SetPhoto23Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto23, pbPhotoData, nSize);
		nPhoto23Size = nSize;
	}
	void SetPhoto24Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto24, pbPhotoData, nSize);
		nPhoto24Size = nSize;
	}
	void SetPhoto25Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto25, pbPhotoData, nSize);
		nPhoto25Size = nSize;
	}
	void SetPhoto26Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto26, pbPhotoData, nSize);
		nPhoto26Size = nSize;
	}
	void SetPhoto27Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto27, pbPhotoData, nSize);
		nPhoto27Size = nSize;
	}
	void SetPhoto28Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto28, pbPhotoData, nSize);
		nPhoto28Size = nSize;
	}
	void SetPhoto29Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto29, pbPhotoData, nSize);
		nPhoto29Size = nSize;
	}
	void SetPhoto30Data(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbPhoto30, pbPhotoData, nSize);
		nPhoto30Size = nSize;
	}
	void LoadPhoto1FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto1, nPhoto1Size, pszFilePath);
	}
	void LoadPhoto2FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto2, nPhoto2Size, pszFilePath);
	}
	void LoadPhoto3FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto3, nPhoto3Size, pszFilePath);
	}
	void LoadPhoto4FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto4, nPhoto4Size, pszFilePath);
	}
	void LoadPhoto5FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto5, nPhoto5Size, pszFilePath);
	}
	void LoadPhoto6FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto6, nPhoto6Size, pszFilePath);
	}
	void LoadPhoto7FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto7, nPhoto7Size, pszFilePath);
	}
	void LoadPhoto8FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto8, nPhoto8Size, pszFilePath);
	}
	void LoadPhoto9FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto9, nPhoto9Size, pszFilePath);
	}
	void LoadPhoto10FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto10, nPhoto10Size, pszFilePath);
	}

	void LoadPhoto11FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto11, nPhoto11Size, pszFilePath);
	}
	void LoadPhoto12FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto12, nPhoto12Size, pszFilePath);
	}
	void LoadPhoto13FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto13, nPhoto13Size, pszFilePath);
	}
	void LoadPhoto14FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto14, nPhoto14Size, pszFilePath);
	}
	void LoadPhoto15FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto15, nPhoto15Size, pszFilePath);
	}
	void LoadPhoto16FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto16, nPhoto16Size, pszFilePath);
	}
	void LoadPhoto17FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto17, nPhoto17Size, pszFilePath);
	}
	void LoadPhoto18FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto18, nPhoto18Size, pszFilePath);
	}
	void LoadPhoto19FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto19, nPhoto19Size, pszFilePath);
	}
	void LoadPhoto20FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto20, nPhoto20Size, pszFilePath);
	}

		void LoadPhoto21FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto21, nPhoto21Size, pszFilePath);
	}
	void LoadPhoto22FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto22, nPhoto22Size, pszFilePath);
	}
	void LoadPhoto23FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto23, nPhoto23Size, pszFilePath);
	}
	void LoadPhoto24FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto24, nPhoto24Size, pszFilePath);
	}
	void LoadPhoto25FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto25, nPhoto25Size, pszFilePath);
	}
	void LoadPhoto26FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto26, nPhoto26Size, pszFilePath);
	}
	void LoadPhoto27FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto27, nPhoto27Size, pszFilePath);
	}
	void LoadPhoto28FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto28, nPhoto28Size, pszFilePath);
	}
	void LoadPhoto29FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto29, nPhoto29Size, pszFilePath);
	}
	void LoadPhoto30FromFile(const wchar_t * pszFilePath)
	{
		LoadPhotoFromFile(&pbPhoto30, nPhoto30Size, pszFilePath);
	}
private:
	// 拷贝数据到Photo字段，内存动态申请，析构时自动释放
	inline void SetPhotoData(BYTE **pbPhotoBuf, const BYTE *pbPhotoData, const unsigned int nSize)
	{
		if (nSize != 0)
		{
			if (*pbPhotoBuf != NULL)
			{
				delete *pbPhotoBuf;
				*pbPhotoBuf = NULL;
			}
			*pbPhotoBuf = new BYTE[nSize];
			memset(*pbPhotoBuf, 0, nSize);
			memcpy(*pbPhotoBuf, pbPhotoData, nSize);
		}
	}
	// 从文件载入图像数据
	inline void LoadPhotoFromFile(BYTE **pbPhotoBuf, unsigned int &nSize, const wchar_t *pszFilePath)
	{
		FILE *fp = NULL;
		_wfopen_s(&fp, pszFilePath, L"rb");
		if (fp != NULL)
		{
			// 游标移到文件尾
			fseek(fp, 0L, SEEK_END);
			// 获取文件大小
			nSize = ftell(fp);
			// 游标移到文件头
			fseek(fp, 0L, SEEK_SET);
			
			if (*pbPhotoBuf != NULL)
			{
				delete *pbPhotoBuf;
				*pbPhotoBuf = NULL;
			}
			// copy文件数据到结构体缓冲区
			*pbPhotoBuf = new BYTE[nSize];
			fread(*pbPhotoBuf, nSize, 1, fp);

			fclose(fp);
		}
	}
};

#endif