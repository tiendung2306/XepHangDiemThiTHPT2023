#include<stdio.h>
#include<string.h>
#include<time.h>
 
//*************************************************** XU LY SO LIEU THO ***********************************************************
 
int SoLuongHS = 0;
 
struct Map
{
    char maTinh[3];
    char tenTinh[2306];
};
 
struct Map map[65];
 
int to_Int(char s[])
{
    return  (s[0] - '0') * 10 + (s[1] - '0');
}
 
void XuLyTenTinh()
{
    FILE *f = fopen("MaTinh.txt", "r");
    char maTinh[3], tmp[10], tenTinh[2306];
    char tiento[2306] = "SO GIAO DUC VA DAO TAO ";
    while(!feof(f))
    {
        fgets(maTinh, 3, f);
        fgets(tmp, 4, f);
        fgets(tenTinh, sizeof tenTinh, f);
        int i = 0;
        while(tenTinh[i] != '\n')   i++;
        tenTinh[i] = '\0';
        int _maTinh = to_Int(maTinh);
        char tam[2306];
        strcpy(tam, tiento);
        strcat(tam, tenTinh);
        strcpy(tenTinh, tam);
        strcpy(map[_maTinh].maTinh, maTinh);
        strcpy(map[_maTinh].tenTinh, tenTinh);
 
    }
    fclose(f);
    // for(int i = 1; i <= 64; i++)
    // {
    //     printf("%s\n", map[i].tenTinh);
    // }
}
 
struct HS
{
    char sbd[10];
    double diem[9]; // diem[0] la diem toan, diem[1] la diem van, diem[2] la diem ngoai ngu, ... theo tu tu diem ben duoi
    double diem_toan, diem_van, diem_ngoai_ngu, diem_ly, diem_hoa, diem_sinh, diem_su, diem_dia, diem_gdcd;
    char ma_ngoai_ngu[10];
    char maTinh[3];
    struct 
    	{
    		int khoi[7];//chia theo 7 khoi
    	}rank[2];//rank theo ca nuoc,theo tinh.
 
} hs[1100006];
 
void crawl_data()
{
 
	FILE *f = fopen("diem_thi_thpt_2023.txt", "r");
    char line[2306];
    fgets(line, sizeof line, f);
    // printf("%s\n", line);
    char sbd[10];
    char str[256];
    int len, idx_diem, idx_ma_ngoai_ngu;
    int after_dot, pre_comma;
    double hang_thap_phan = 10;
    while(!feof(f))
    {
        fgets(hs[SoLuongHS].sbd, 9, f); //sbd
        if(strcmp(hs[SoLuongHS].sbd, "*") == 0)
        {
            break;
        }
        // Bat dau xu ly input diem va ma ngoai ngu
        fgets(str, 255, f);
        for(int i = 0; i < 9; i++)
        {
            hs[SoLuongHS].diem[i] = 0;
        }
        len = strlen(str);
        idx_diem = -1;
        after_dot = 0;
        idx_ma_ngoai_ngu = 0;
        pre_comma = 0;
        for(int i = 0; i < len; i++)
        {
            if(str[i] == ',')   
            {
                if(pre_comma == 1)  hs[SoLuongHS].diem[idx_diem] = -1;
                pre_comma = 1;
                idx_diem ++;
                after_dot = 0;
                hang_thap_phan = 10;
                continue;
            }
            else if(str[i] == '.')
            {
                pre_comma = 0;
                after_dot = 1;
                continue;
            }
            else 
            {
                pre_comma = 0;
                if(idx_diem == 9) //Nhap den Ma Ngoai Ngu
                {
                    hs[SoLuongHS].ma_ngoai_ngu[idx_ma_ngoai_ngu++] = str[i];
                }
                else if(after_dot == 0)  hs[SoLuongHS].diem[idx_diem] = hs[SoLuongHS].diem[idx_diem] * 10 + (double)(str[i] - '0'); 
                else 
                {
                    hs[SoLuongHS].diem[idx_diem] = hs[SoLuongHS].diem[idx_diem] + (double)(str[i] - '0') / hang_thap_phan;
                    hang_thap_phan *= 10;
                }
            }
        }
        // for(int i = 0; i < 9; i++)
        // {
        //     fgetc(f); //nhap dau ,
        //     if(fscanf(f, "%lf", &hs[SoLuongHS].diem[i]) == 0)   hs[SoLuongHS].diem[i] = -1;
        // }
        // fgetc(f);//nhap dau ,
        // fgets(hs[SoLuongHS].ma_ngoai_ngu, 4, f);
        int i = 0;
        while(hs[SoLuongHS].ma_ngoai_ngu[i] != '\n')
        {
            i++;
        }
 
        hs[SoLuongHS].ma_ngoai_ngu[i] = '\0';
         //Xu ly SBD de ra duoc ma tinh
        hs[SoLuongHS].maTinh[0] = hs[SoLuongHS].sbd[0];
        hs[SoLuongHS].maTinh[1] = hs[SoLuongHS].sbd[1];
        SoLuongHS++;
    }
 
    // for(int i = 0; i < 10; i++)
    // {
    //     printf("%s\n", hs[i].sbd);
    //     for(int j = 0; j < 9; j++)
    //     {
    //         printf("%lf ", hs[i].diem[j]);
    //     }
    //     printf("\n%s\n", hs[i].ma_ngoai_ngu);
    // } 
} 
 
 
//***************************************************  XU LY DIEM VA SAP XEP THU TU ***********************************************
 
 
 
//---------------------------------------  HAM VAO DIEM THEO CAC KHOI -----------------------------------------
void vao_diem_khoi (int sttkhoi,int a,int b,int c,double hss[]) //a,b,c la ma cac mon
{
	for(int i = 0; i < SoLuongHS;i++)
	{
		if(hs[i].diem[a] == -1||hs[i].diem[b] == -1|| hs[i].diem[c] == -1)//loai cac thi sinh khong thi
		 	hss[i] = -1;
		else
			hss[i] = hs[i].diem[a] + hs[i].diem[b] + hs[i].diem[c];//vao diem cac thi sinh co thi
		if(sttkhoi == 5 ||sttkhoi == 6 || sttkhoi == 1)//loai bo cac thi sinh thi tieng Nga, Phap,...
		{
			if(strcmp(hs[i].ma_ngoai_ngu,"N1"))
				hss[i] = -1;
		}
	}
}
 
//--------------------------------------   HAM VA THUAT TOAN SAP XEP   ----------------------------------------
 
 
int tmp1[1100006],tmp2[1100006];//Mang 1 lam viec voi so thu tu cua arr[] va mang 2 de luu gia tri tam thoi khi doi vi tri
double hss1[1100006],hss2[1100006],hss3[1100006],hss4[1100006],hss5[1100006],hss6[1100006],hss0[1100006];//Mang de luu diem theo khoi cua cac thi sinh
 
void merge(int sttkhoi,double dau,double cuoi,double hss[])
{
	int z = (int)dau;
	int i = (int)dau;
	int j;
	if((int)cuoi - (int)dau < 2)
		j = (int)cuoi;
	else
		j = (int)((cuoi + dau)/2 +1);
	while(z != (int)cuoi + 1)
	{
		if( i == (int)((dau + cuoi)/2 + 1))
		{
			for(i = j;i <= (int)cuoi;i++)
			{
				tmp2[i] = tmp1[i] ;
			}
			break;
		}
 
		if( j == (int)cuoi + 1)
		{
			for(j = i;j <= (int)((dau + cuoi)/2);j++)
			{
				tmp2[z] = tmp1[j] ;
				z++;		
			}
			break;
		}
		if(hss[tmp1[i]] < hss[tmp1[j]])
		{
			tmp2[z] = tmp1[j];
			z++;
			j++;
		}
		else
		{
			tmp2[z] = tmp1[i];
			z++;
			i++;
		}
 
	}
		for(z = (int)dau;z <= (int)cuoi;z++){
				tmp1[z] = tmp2[z];
			}
}
 
//----------------------------------------------------------------------------------------------------------------------------
 
void mergesort (int sttkhoi,double dau,double cuoi,double hss[]) /*Ham sap xep de quy(sap xep 1 mang tu vi tri arr[dau] den arr[cuoi])
													 Ham se tach mang arr[] thanh cac mang con de ham merge gop va 
													 sap xep lai */
{
 
	if((int)cuoi - (int)dau > 1)
	{
		cuoi = (dau + cuoi)/2;
		mergesort(sttkhoi,dau,cuoi,hss);
		cuoi = 2 * cuoi - dau;
 
		dau = (dau + cuoi)/2 + 1;
		mergesort(sttkhoi,dau,cuoi,hss);
		dau = 2 * (dau - 1) - cuoi;
	}
	merge(sttkhoi,dau,cuoi,hss);
 
}
 
//-------------------------------------------------------------------------------------------------------------------------
 
void sapxep(int sttkhoi,int stt_rank,double dau,double cuoi,double hss[]) /*Ham sap xep hoan chinh :
															    Sau khi sap xep thu tu cua mang arr[] thong qua mang tmp1
																thi luu so thu tu cua phan tu vao bien rank.khoi
																luu y cac hoc sinh co diem = nhau se co rank = nhau
																VD:
																     Diem : 10 9 9 8 8 8 8 7
																	 Rank :  1 2 2 4 4 4 4 8
															*/
{
	int cnt = (int)dau;
	for(int i = (int)dau;i <= (int)cuoi;i++)
		tmp1[i] = i;
	mergesort (sttkhoi,dau,cuoi,hss);
	for(int i = (int)dau;i <= (int)cuoi;i++)
		if(hss[tmp1[i]] != hss[tmp1[i + 1]] || i == (int)cuoi)
		{
			for(int j = cnt; j <= i;j++ )
					hs[tmp1[j]].rank[stt_rank].khoi[sttkhoi] = cnt + 1 - (int)dau;
			cnt = i + 1 ;
		}
}
 
//-------------------------------------------------------------------------------------------------------------------------
 
 
int phamvi(int matinh) //Ham lay moc dau va cuoi cho ham sap xep phia tren dua vao ma tinh
{
	if(matinh == 65)
		return SoLuongHS - 1;
	if(matinh == 20)
		return phamvi(21);
	else
		for(int i = 0;i < SoLuongHS ;i++)
			if(matinh == to_Int(hs[i].maTinh))
				{
					return i;
					break;
				}
}
 
//-------------------------------------------------------------------------------------------------------------------------
 
void vaodiem_sapxep()//Ham thuc thi tat ca cac ham ben tren
{
	//vao diem cac khoi tung hoc sinh vao cac mang hss0,hss1,hss2,...
	vao_diem_khoi(0,0,3,4,hss0);//A00
	vao_diem_khoi(1,0,3,2,hss1);//A01
	vao_diem_khoi(2,0,4,5,hss2);//B00
	vao_diem_khoi(3,1,6,7,hss3);//C00
	vao_diem_khoi(4,1,0,6,hss4);//C03
	vao_diem_khoi(5,1,0,2,hss5);//D01
	vao_diem_khoi(6,0,4,2,hss6);//D07
 
	//sap xep theo khoi tren ca nuoc luu vao rank[0].khoi
	sapxep(0,0,0,SoLuongHS - 1,hss0);//A00
	sapxep(1,0,0,SoLuongHS - 1,hss1);//A01
	sapxep(2,0,0,SoLuongHS - 1,hss2);//B00
	sapxep(3,0,0,SoLuongHS - 1,hss3);//C00
	sapxep(4,0,0,SoLuongHS - 1,hss4);//C01
	sapxep(5,0,0,SoLuongHS - 1,hss5);//D01
	sapxep(6,0,0,SoLuongHS - 1,hss6);//D07
}
 
//*************************************************** XU LY SO BAO DANH VA IN KET QUA ***********************************************
 
 
void in_ket_qua(double hss[],int sbd,int sttkhoi)//ham in ket qua ra man hinh (viet ham rieng ra de do phai viet di viet lai cac mang hss)
{
	char makhoi[][4] = {"A00" , "A01" , "B00" , "C00" , "C03" , "D01" , "D07"};
	printf("\t\t\t%s",makhoi[sttkhoi]);
	if(hss[sbd] == -1)
		printf("\tBan khong thi khoi nay\n");
	else
		printf("%11.d %10.d \n",hs[sbd].rank[0].khoi[sttkhoi],hs[sbd].rank[1].khoi[sttkhoi]);
 
}
 
void timkiem(int sbd)//Ham tim kem va in ket qua
{
	int dau = phamvi(to_Int(hs[sbd].maTinh));
	int cuoi = phamvi(to_Int(hs[sbd].maTinh) + 1) - 1;
 
	//ham sap xep theo khoi tren tinh cua sbd vua nhap roi in vao rank[1].khoi
	sapxep(0,1,dau,cuoi,hss0);
	sapxep(1,1,dau,cuoi,hss1);
	sapxep(2,1,dau,cuoi,hss2);
	sapxep(3,1,dau,cuoi,hss3);
	sapxep(4,1,dau,cuoi,hss4);
	sapxep(5,1,dau,cuoi,hss5);
	sapxep(6,1,dau,cuoi,hss6);
 
	//In ket qua ra man hinh
	printf("--------------------------------------------------------------------------------\n");
	printf("\t\tBan thuoc khu vuc ");
	printf("%s", map[to_Int(hs[sbd].maTinh)].tenTinh);
	printf("\n\t\t   Ket qua xep hang thi tot nghiep cua ban la:\n");
	printf("\t\t\t        Ca nuoc    Trong tinh\n");
	//In lan luot tung khoi
	in_ket_qua(hss0,sbd,0);//A00
	in_ket_qua(hss1,sbd,1);//A01
	in_ket_qua(hss2,sbd,2);//B00
	in_ket_qua(hss3,sbd,3);//C00
	in_ket_qua(hss4,sbd,4);//C01
	in_ket_qua(hss5,sbd,5);//D01
	in_ket_qua(hss6,sbd,6);//D07
	printf("--------------------------------------------------------------------------------\n");
}
 
int main()
{
	//khai bao
	int option,flag;
	char sobaodanh[10];
 
    printf("Vui long cho trong giay lat....\n");
 
	//xu ly du lieu
    XuLyTenTinh();
    crawl_data();
    vaodiem_sapxep();
 
    //chuong trinh chinh
	printf("********************Chuong trinh tra cuu ket qua tot nghiep*********************\n");
 
	while(1)
	{
		printf("Vui long nhap so bao danh: ");
		fflush(stdin);
		gets(sobaodanh);
		for	(int i = 0;i < SoLuongHS ;i++ )
			if(!strcmp(sobaodanh,hs[i].sbd))
			{
				timkiem(i);
				flag = 1;//kiem tra nhap sai sbd
			}
		if(flag != 1)
			printf("So bao danh khong chinh xac hoac khong ton tai!!\nLuu y nhap so bao danh khong dau cach giua cac chu so hay o cuoi so bao danh!!\n");
		printf("\n********************Chuong trinh tra cuu ket qua tot nghiep*********************\n");
		printf("Tiep tuc tra cuu?\n");
		printf("Vui long nhan :\n");
		printf("0.Tiep tuc\n");
		printf("1.Thoat chuong trinh\n");
		scanf("%d",&option);
		if(option)
		{
			printf("Xin Cam On");
			break;
		}
		else
			flag = 0;
	}

}