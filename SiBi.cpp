// SiBi.cpp : Test only
//

#include <iostream>
#include <cmath>

#include "bmap.h"
#include "denc.h"

using namespace std;

int main()
{
    int sx = 200, sy = 299;
    BMap bm(sx, sy);
    //std::cout << bm.bit(7, 8);
    //bm.clear(7, 8);
    //std::cout << bm.bit(7, 8);
    ////bm.set(7, 8);
    ////std::cout << bm.bit(7, 8);
    //std::cout << std::endl;

    // a rectangle
    for (int y = 30; y < 60; y++)
        for (int x = 123; x < 130; x++)
            bm.clear(x, y);

    // circles
    int cx = 150, cy = 76, cr = 34;
    for (int y = 0; y < sy; y++)
        for (int x = 0; x < sx; x++)
            if (((x - cx) * (x - cx) + (y - cy) * (y - cy)) < cr * cr)
                bm.clear(x, y);

    cx = 35; cy = 212; cr = 78;
    for (int y = 0; y < sy; y++)
        for (int x = 0; x < sx; x++)
            if (((x - cx) * (x - cx) + (y - cy) * (y - cy)) < cr * cr)
                bm.clear(x, y);

    cx = 79; cy = 235; cr = 135;
    for (int y = 0; y < sy; y++)
        for (int x = 0; x < sx; x++)
            if (((x - cx) * (x - cx) + (y - cy) * (y - cy)) < cr * cr)
                bm.clear(x, y);

    Bitstream s;
    std::cout << std::endl << bm.dsize() * 8 << std::endl;
    bm.pack(s);
    //bm.dump(std::string("file.raw"));
    std::cout << s.v.size() * 8 << std::endl;
    auto v(s.v);
    RLE(s.v, s.v);
    std::cout << s.v.size() * 8 << std::endl;
    unRLE(s.v, s.v);
    std::cout << s.v.size() * 8 << std::endl;
    for (int i = 0; i < v.size(); i++)
        if (v[i] != s.v[i])
            break;

    BMap bm1(sx, sy);
    bm1.unpack(s);
    bm1.compare(bm);

    // Now for the RGB image, read from a PNM file
    // Image is 3776x2520x3, starts at offset 16
    FILE* f;
    if (fopen_s(&f, "input.pnm", "rb") || ! f) {
        cerr << "Can't open input file";
        exit(errno);
    }
    fseek(f, 17, SEEK_SET);
    vector<uint8_t> image(3776*2520*3);
    fread(image.data(), 3776, 2520 * 3, f);
    fclose(f);
    // 

}
