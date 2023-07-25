/*
Cách lấy tên tỉnh từ mã tỉnh: map[to_Int(hs[i].maTinh)].tenTinh
trong đó to_Int là hàm chuyển từ string sang int
*/

#include<stdio.h>
#include<string.h>

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
} hs[1100006]; // các thí sinh được lưu từ hs[0] đến hs[SoLuongHs - 1]

int main()
{
    XuLyTenTinh();
    FILE *f = fopen("diem_thi_thpt_2023.txt", "r");
    char line[2306];
    fgets(line, sizeof line, f);
    // printf("%s\n", line);
    int SoLuongHS = 0; // tổng số học sinh dự thi
    char sbd[10];
    while(!feof(f))
    {
        fgets(hs[SoLuongHS].sbd, 9, f); //sbd
        if(strcmp(hs[SoLuongHS].sbd, "*") == 0)
        {
            break;
        }
        for(int i = 0; i < 9; i++)
        {
            fgetc(f); //nhap dau ,
            if(fscanf(f, "%lf", &hs[SoLuongHS].diem[i]) == 0)   hs[SoLuongHS].diem[i] = -1;
        }
        fgetc(f);//nhap dau ,
        fgets(hs[SoLuongHS].ma_ngoai_ngu, 4, f);
        int i = 0;
        while(hs[SoLuongHS].ma_ngoai_ngu[i] != '\n')
        {
            i++;
        }
        
        hs[SoLuongHS].ma_ngoai_ngu[i] = '\0';
        // Xu ly SBD de ra duoc ma tinh
        hs[SoLuongHS].maTinh[0] = hs[SoLuongHS].sbd[0];
        hs[SoLuongHS].maTinh[1] = hs[SoLuongHS].sbd[1];
        SoLuongHS++;
    }

    // for(int i = 956354; i < 956380; i++)
    // {
    //     printf("SBD: %s ", hs[i].sbd);
    //     for(int j = 0; j < 9; j++)
    //     {
    //         printf("%.2lf ", hs[i].diem[j]);
    //     }
    //     printf("%s\n", hs[i].ma_ngoai_ngu);
    //     printf("%s\n", map[to_Int(hs[i].maTinh)].tenTinh);
    // }
}

/*
01 - THÀNH PHỐ HÀ NỘI
02 - THÀNH PHỐ HỒ CHÍ MINH
03 - THÀNH PHỐ HẢI PHÒNG
04 - THÀNH PHỐ ĐÀ NẴNG
05 - TỈNH HÀ GIANG
06 - TỈNH CAO BẰNG
07 - TỈNH LAI CHÂU
08 - TỈNH LÀO CAI
09 - TỈNH TUYÊN QUANG
10 - TỈNH LẠNG SƠN
11 - TỈNH BẮC KẠN
12 - TỈNH THÁI NGUYÊN
13 - TỈNH YÊN BÁI
14 - TỈNH SƠN LA
15 - TỈNH PHÚ THỌ
16 - TỈNH VĨNH PHÚC
17 - TỈNH QUẢNG NINH
18 - TỈNH BẮC GIANG
19 - TỈNH BẮC NINH
21 - TỈNH HẢI DƯƠNG
22 - TỈNH HƯNG YÊN
23 - TỈNH HÒA BÌNH
24 - TỈNH HÀ NAM
25 - TỈNH NAM ĐỊNH
26 – TỈNH THÁI BÌNH
27 – TỈNH NINH BÌNH
28 – TỈNH THANH HÓA
29 – TỈNH NGHỆ AN
30 – TỈNH HÀ TĨNH
31 – TỈNH QUẢNG BÌNH
32 – TỈNH QUẢNG TRỊ
33 – TỈNH THỪA THIÊN - HUẾ
34 – TỈNH QUẢNG NAM
35 – TỈNH QUẢNG NGÃI
36 – TỈNH KON TUM
37 – TỈNH BÌNH ĐỊNH
38 – TỈNH GIA LAI
39 – TỈNH PHÚ YÊN
40 – TỈNH ĐẮK LẮK
41 – TỈNH KHÁNH HÒA
42 – TỈNH LÂM ĐỒNG
43 – TỈNH BÌNH PHƯỚC
44 – TỈNH BÌNH DƯƠNG
45 – TỈNH NINH THUẬN
46 – TỈNH TÂY NINH
47 – TỈNH BÌNH THUẬN
48 – TỈNH ĐỒNG NAI
49 – TỈNH LONG AN
50 – TỈNH ĐỒNG THÁP
51 – TỈNH AN GIANG
52 – TỈNH BÀ RỊA – VŨNG TÀU
53 – TỈNH TIỀN GIANG
54 – TỈNH KIÊN GIANG
55 – THÀNH PHỐ CẦN THƠ
56 – TỈNH BẾN TRE
57 – TỈNH VĨNH LONG
58 – TỈNH TRÀ VINH
59 – TỈNH SÓC TRĂNG
60 – TỈNH BẠC LIÊU
61 – TỈNH CÀ MAU
62 – TỈNH ĐIỆN BIÊN
63 – TỈNH ĐĂK NÔNG
64 – TỈNH HẬU GIANG
*/