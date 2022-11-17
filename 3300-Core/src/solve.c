#include "solve.h"
#include <string.h>

void rotateCube(cube_t *c, uint8_t move)
{
    char temp[54];
    memcpy(temp, c->face, 54);
    for (int i = 0; i < 54; i++)
        c->face[i] = temp[transMat[move][i]];
    c->route[c->routeLen++] = move;
    if(move == T)
    {
        uint8_t route_temp[18];
        memcpy(route_temp, route_mask, 18);
        for (int i = 0; i < 18; i++)
            route_mask[i] = route_temp[route_trans[i]];
    }
}
void formular11(cube_t *c)
{
    uint8_t n = 0;
    for (size_t i = 1; i < 6; i++)
    {
        n = 0;
        for (size_t j = 3; j < 6; j += 2)
        {
            if (c->face[i * 9 + j] == 'D')
            {
                while (c->face[face_index1[i - 1][n]] == 'D')
                    rotateCube(c, U);
                rotateCube(c, rotate_index1[i - 1][n]);
            }
            n++;
        }
    }
    for (size_t i = 1; i < 6; i++)
    {
        n = 0;
        for (size_t j = 1; j < 8; j += 6)
        {
            if (c->face[i * 9 + j] == 'D')
            {
                while (c->face[face_index2[i - 1][n]] == 'D')
                    rotateCube(c, U);
                rotateCube(c, rotate_index2[i - 1][n]);
            }
            n++;
        }
    }
}
void formular12(cube_t *c)
{
    while (c->face[19] != c->face[22] || c->face[7] != 'D')
        rotateCube(c, U);
    rotateCube(c, F2);
    while (c->face[46] != c->face[49] || c->face[1] != 'D')
        rotateCube(c, U);
    rotateCube(c, B2);
    while (c->face[37] != c->face[40] || c->face[3] != 'D')
        rotateCube(c, U);
    rotateCube(c, L2);
    while (c->face[10] != c->face[13] || c->face[5] != 'D')
        rotateCube(c, U);
    rotateCube(c, R2);
}
void formular13(cube_t *c)
{
    rotateCube(c, R);
    rotateCube(c, U);
    rotateCube(c, R3);
}
void formular14(cube_t *c)
{
    rotateCube(c, F3);
    rotateCube(c, U3);
    rotateCube(c, F);
}

void formular15(cube_t *c)
{
    if (c->face[29] == c->face[31] && c->face[22] == c->face[26] && c->face[15] == c->face[13])
        return;
    size_t i = 0;
    for (; i < 4;)
    {
        if (c->face[8] == c->face[13] && c->face[22] == c->face[20] && c->face[9] == c->face[31])
        {
            formular13(c);
            return;
        }
        else if (c->face[8] == c->face[31] && c->face[13] == c->face[20] && c->face[9] == c->face[22])
        {
            formular13(c);
            formular13(c);
            rotateCube(c, U3);
            formular13(c);
            return;
        }
        else if (c->face[8] == c->face[22] && c->face[20] == c->face[31] && c->face[9] == c->face[13])
        {
            formular14(c);
            return;
        }
        else
        {
            if (++i == 4)
                break;
            rotateCube(c, U);
        }
    }
    if (i == 4)
        formular13(c);
}
void formular21(cube_t *c)
{
    rotateCube(c, U3);
    rotateCube(c, F3);
    rotateCube(c, U);
    rotateCube(c, F);
    rotateCube(c, U);
    rotateCube(c, R);
    rotateCube(c, U3);
    rotateCube(c, R3);
}
void formular22(cube_t *c)
{
    rotateCube(c, U);
    rotateCube(c, R);
    rotateCube(c, U3);
    rotateCube(c, R3);
    rotateCube(c, U3);
    rotateCube(c, F3);
    rotateCube(c, U);
    rotateCube(c, F);
}
void formular23(cube_t *c)
{
    if (c->face[23] == c->face[22] && c->face[12] == c->face[13])
        return;
    size_t i = 0;
    for (; i < 4;)
    {
        if (c->face[19] == c->face[22] && c->face[7] == c->face[13])
        {
            formular22(c);
            break;
        }
        else if (c->face[5] == c->face[22] && c->face[10] == c->face[13])
        {
            formular21(c);
            break;
        }
        else
        {
            if (++i == 4)
                break;
            rotateCube(c, U);
        }
    }
    if (i == 4)
        formular21(c);
}
void formular31(cube_t *c)
{
    rotateCube(c, F);
    rotateCube(c, R);
    rotateCube(c, U);
    rotateCube(c, R3);
    rotateCube(c, U3);
    rotateCube(c, F3);
}
void formular32(cube_t *c)
{
    if (c->face[1] == c->face[4] && c->face[7] == c->face[4])
        rotateCube(c, U);
    if (c->face[3] == c->face[4] && c->face[5] == c->face[4])
    {
        formular31(c);
        return;
    }
    while (c->face[19] != c->face[4] || c->face[10] != c->face[4])
        rotateCube(c, U);
    if (c->face[3] == c->face[4] && c->face[1] == c->face[4])
        formular31(c);
    else
    {
        formular31(c);
        rotateCube(c, U);
        formular31(c);
    }
}
void formular41(cube_t *c)
{
    rotateCube(c, R3);
    rotateCube(c, U2);
    rotateCube(c, R);
    rotateCube(c, U);
    rotateCube(c, R3);
    rotateCube(c, U);
    rotateCube(c, R);
}
void formular42(cube_t *c)
{
    rotateCube(c, U3);
    rotateCube(c, R);
    rotateCube(c, U2);
    rotateCube(c, R3);
    rotateCube(c, U3);
    rotateCube(c, R);
    rotateCube(c, U3);
    rotateCube(c, R3);
}
void formular43(cube_t *c)
{
    uint8_t cnt = 0;
    for (size_t i = 0; i < 9; i++)
    {
        if (c->face[i] == c->face[4])
            cnt++;
    }
    if (cnt == 6)
    {
        while (1)
        {
            uint8_t case1 = c->face[47] == c->face[4] && c->face[38] == c->face[4] && c->face[11] == c->face[4];
            uint8_t case2 = c->face[45] == c->face[4] && c->face[36] == c->face[4] && c->face[18] == c->face[4];
            if (case1)
            {
                formular41(c);
                return;
            }
            else if (case2)
            {
                formular42(c);
                return;
            }
            else
                rotateCube(c, U);
        }
    }
    else if (cnt == 5)
    {
        while (1)
        {
            uint8_t case3 = c->face[11] == c->face[4] && c->face[36] == c->face[4] && c->face[18] == c->face[4] && c->face[20] == c->face[4];
            uint8_t case4 = c->face[45] == c->face[4] && c->face[47] == c->face[4] && c->face[18] == c->face[4] && c->face[20] == c->face[4];
            if (case3)
            {
                formular41(c);
                rotateCube(c, U3);
                formular41(c);
                break;
            }
            else if (case4)
            {
                formular41(c);
                formular41(c);
                break;
            }
            else
                rotateCube(c, U);
        }
    }
    else if (cnt == 7)
    {
        while (1)
        {
            uint8_t case5 = c->face[18] == c->face[4] && c->face[20] == c->face[4];
            uint8_t case6 = c->face[45] == c->face[4] && c->face[20] == c->face[4];
            uint8_t case7 = c->face[47] == c->face[4] && c->face[9] == c->face[4];
            if (case5)
            {
                formular42(c);
                rotateCube(c, U2);
                formular41(c);
                return;
            }
            else if (case6)
            {
                formular42(c);
                formular41(c);
                return;
            }
            else if (case7)
            {
                formular41(c);
                formular42(c);
                return;
            }
            else
            {
                rotateCube(c, U);
            }
        }
    } // printf("case1 = %d, case2 = %d, case3 = %d, case4 = %d, case5 = %d, case6 = %d, case7 = %d\n", case1, case2, case3, case4, case5, case6, case7);
}
void formular51(cube_t *c)
{
    rotateCube(c, R);
    rotateCube(c, B3);
    rotateCube(c, R);
    rotateCube(c, F2);
    rotateCube(c, R3);
    rotateCube(c, B);
    rotateCube(c, R);
    rotateCube(c, F2);
    rotateCube(c, R2);
}
void formular52(cube_t *c)
{
    printf("formular52\n");
    if (c->face[18] == c->face[20] && c->face[9] == c->face[11] && c->face[36] == c->face[38])
    {
        while (c->face[18] != c->face[22])
            rotateCube(c, U);
        return;
    }
    uint8_t routeCnt = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if (c->face[18] != c->face[20])
        {
            rotateCube(c, U);
            routeCnt++;
        }
        else
            break;
    }
    formular51(c);
    if (routeCnt == 4)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (c->face[18] != c->face[20])
                rotateCube(c, U);
            else
                break;
        }
        formular51(c);
    }
    while (c->face[18] != c->face[22])
        rotateCube(c, U);
}
void formular61(cube_t *c)
{
    rotateCube(c, R);
    rotateCube(c, U3);
    rotateCube(c, R);
    rotateCube(c, U);
    rotateCube(c, R);
    rotateCube(c, U);
    rotateCube(c, R);
    rotateCube(c, U3);
    rotateCube(c, R3);
    rotateCube(c, U3);
    rotateCube(c, R2);
}
void formular62(cube_t *c)
{
    while (1)
    {
        if (c->face[19] == c->face[22] && c->face[37] == c->face[40])
        {
            break;
        }
        if (c->face[19] == c->face[13] && c->face[10] == c->face[40] && c->face[37] == c->face[22])
        {
            formular61(c);
            break;
        }
        else if (c->face[37] == c->face[13] && c->face[19] == c->face[40] && c->face[10] == c->face[22])
        {
            formular61(c);
            formular61(c);
            break;
        }
        else if (c->face[19] == c->face[49] && c->face[46] == c->face[22] && c->face[37] == c->face[13] && c->face[10] == c->face[40])
        {
            formular61(c);
            rotateCube(c, U);
            formular61(c);
            break;
        }
        else if (c->face[19] == c->face[13] && c->face[10] == c->face[22] && c->face[37] == c->face[49] && c->face[46] == c->face[40])
        {
            formular61(c);
            rotateCube(c, U3);
            formular61(c);
            break;
        }
        else
            rotateCube(c, T);
    }
}
void solve_Naive(cube_t *c)
{
    // 1. get the botton face cross
    while (c->face[1] != 'D' || c->face[3] != 'D' || c->face[5] != 'D' || c->face[7] != 'D')
        formular11(c);
    formular12(c);
    // 2. get the botton corner
    while (c->face[26] != c->face[22] || c->face[17] != c->face[13] || c->face[53] != c->face[49] || c->face[40] != c->face[44] ||
           c->face[24] != c->face[22] || c->face[15] != c->face[13] || c->face[51] != c->face[49] || c->face[40] != c->face[42])
    {
        formular15(c);
        rotateCube(c, T);
    }
    while (c->face[23] != c->face[22] || c->face[14] != c->face[13] || c->face[50] != c->face[49] || c->face[40] != c->face[39] ||
           c->face[21] != c->face[22] || c->face[12] != c->face[13] || c->face[48] != c->face[49] || c->face[40] != c->face[41])
    {
        formular23(c);
        rotateCube(c, T);
    }
    while (c->face[1] != c->face[4] || c->face[3] != c->face[4] || c->face[5] != c->face[4] || c->face[7] != c->face[4])
    {
        formular32(c);
    }
    formular43(c);
    formular52(c);
    formular62(c);
    while (c->face[9] != c->face[13])
    {
        rotateCube(c, U);
    }
}

// int main(int argc, char **argv)
// {
//     char solution[80];
//     if (argc == 2)
//     {
//         cube_t c;
//         printf("argv[1]=%s\n", argv[1]);
//         memcpy(c.face, argv[1], 54);
//         printCube(&c);
//         solve_Naive(&c);
//         printCube(&c);

//         int len = c.routeLen;
//         printf("LENGTH=%d\n", len);
//     }
//     else
//     {
//         cube_t c;
//         printf("no input.\n");
//         printf("Usage: %s BBBFULRUBUURFRRRDFDFLUFDLRUUUFFDRLDLRRFLLBBLFDLUBBDDBD\n", argv[0]);
//         printf("Run auto test.\n");
//         FILE *f = fopen("test_case.txt", "r");
//         char line_buffer[80];
//         if (f != NULL)
//         {
//             int min = 99, max = 0, avg = 0;
//             for (int i = 0; i < 10000; i++)
//             {
//                 fgets(line_buffer, 79, f);
//                 printf("i=%d %s", i, line_buffer);
//                 memcpy(c.face, line_buffer, 54);
//                 printCube(&c);
//                 solve_Naive(&c);
//                 printCube(&c);

//                 int len = c.routeLen;
//                 printf("length: %d\n", len);
//                 if (len < 10)
//                     break;
//                 if (len > max)
//                 {
//                     max = len;
//                 }
//                 if (len < min)
//                 {
//                     min = len;
//                 }
//                 avg += len;
//             }
//             fclose(f);
//             printf("min=%d, max=%d, avg=%.2f\n", min, max, avg / 10000.0);
//         }
//     }
//     return 0;
// }
