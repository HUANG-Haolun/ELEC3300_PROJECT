#include "solve.h"
const uint8_t edge_to_face[12][2] = {
    {7, 19}, {5, 10}, {1, 46}, {3, 37}, {28, 25}, {32, 16}, {34, 52}, {30, 43}, {23, 12}, {21, 41}, {48, 14}, {50, 39}};
const uint8_t corner_to_face[8][3] = {
    {8, 20, 9}, {2, 11, 45}, {0, 47, 36}, {6, 38, 18}, {29, 15, 26}, {27, 24, 44}, {33, 42, 53}, {35, 51, 17}};
const char edge_index[24][2] = {
    "UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "FL", "BR", "BL",
    "FU", "RU", "BU", "LU", "FD", "RD", "BD", "LD", "RF", "LF", "RB", "LB"};
const char corner_index[24][3] = {
    "UFR", "URB", "UBL", "ULF", "DRF", "DFL", "DLB", "DBR",
    "FRU", "RBU", "BLU", "LFU", "RFD", "FLD", "LBD", "BRD",
    "RUF", "BUR", "LUB", "FUL", "FDR", "LDF", "BDL", "RDB"};

const uint8_t route_edge[18][12] = {
    {}, // L  0
    {}, // L' 1
    {}, // L2 2
    {}, // R  3
    {}, // R' 4
    {}, // R2 5
    {}, // U  6
    {}, // U' 7
    {}, // U2 8
    {}, // D  9
    {}, // D' 10
    {}, // D2 11
    {}, // F  12
    {}, // F' 13
    {}, // F2 14
    {}, // B  15
    {}, // B' 16
    {}  // B2 17
};

const uint8_t route_corner[18][8] = {
    {0, 1, 6, 2, 4, 3, 5, 7}, // L  0
    {0, 1, 3, 5, 4, 6, 2, 7}, // L' 1
    {0, 1, 5, 6, 4, 2, 3, 7}, // L2 2
    {4, 0, 2, 3, 7, 5, 6, 1}, // R  3
    {1, 7, 2, 3, 0, 5, 6, 4}, // R' 4
    {7, 4, 2, 3, 1, 5, 6, 0}, // R2 5
    {1, 2, 3, 0, 4, 5, 6, 7}, // U  6
    {3, 0, 1, 2, 4, 5, 6, 7}, // U' 7
    {2, 3, 0, 1, 4, 5, 6, 7}, // U2 8
    {0, 1, 2, 3, 5, 6, 7, 4}, // D  9
    {0, 1, 2, 3, 7, 4, 5, 6}, // D' 10
    {0, 1, 2, 3, 6, 7, 4, 5}, // D2 11
    {3, 1, 2, 5, 0, 4, 6, 7}, // F  12
    {4, 1, 2, 0, 5, 3, 6, 7}, // F' 13
    {5, 1, 2, 4, 3, 0, 6, 7}, // F2 14
    {0, 7, 1, 3, 4, 5, 2, 6}, // B  15
    {0, 2, 6, 3, 4, 5, 7, 1}, // B' 16
    {0, 6, 7, 3, 4, 5, 1, 2}  // B2 17
};

const uint8_t rotate[18][8] = {
    {0, 1, 6, 2, 4, 3, 5, 7}, // L  0
    {0, 1, 3, 5, 4, 6, 2, 7}, // L' 1
    {0, 1, 5, 6, 4, 2, 3, 7}, // L2 2
    {4, 0, 2, 3, 7, 5, 6, 1}, // R  3
    {1, 7, 2, 3, 0, 5, 6, 4}, // R' 4
    {7, 4, 2, 3, 1, 5, 6, 0}, // R2 5
    {1, 2, 3, 0, 4, 5, 6, 7}, // U  6
    {3, 0, 1, 2, 4, 5, 6, 7}, // U' 7
    {2, 3, 0, 1, 4, 5, 6, 7}, // U2 8
    {0, 1, 2, 3, 5, 6, 7, 4}, // D  9
    {0, 1, 2, 3, 7, 4, 5, 6}, // D' 10
    {0, 1, 2, 3, 6, 7, 4, 5}, // D2 11
    {3, 1, 2, 5, 0, 4, 6, 7}, // F  12
    {4, 1, 2, 0, 5, 3, 6, 7}, // F' 13
    {5, 1, 2, 4, 3, 0, 6, 7}, // F2 14
    {0, 7, 1, 3, 4, 5, 2, 6}, // B  15
    {0, 2, 6, 3, 4, 5, 7, 1}, // B' 16
    {0, 6, 7, 3, 4, 5, 1, 2}  // B2 17
};rotate

void face_to_cube(cube_t *c)
{
    for (int i = 0; i < 12; i++)
    {
        int index_a = edge_to_face[i][0];
        int index_b = edge_to_face[i][1];
        int tmp = 0;
        for (; tmp < 24; tmp++)
        {
            if (edge_index[tmp][0] == c->face[index_a] &&
                edge_index[tmp][1] == c->face[index_b])
            {
                break;
            }
        }
        c->edges[i] = tmp;
    }
    for (int i = 0; i < 8; i++)
    {
        int index_a = corner_to_face[i][0];
        int index_b = corner_to_face[i][1];
        int index_c = corner_to_face[i][2];
        int tmp = 0;
        for (; tmp < 24; tmp++)
        {
            if (corner_index[tmp][0] == c->face[index_a] &&
                corner_index[tmp][1] == c->face[index_b] &&
                corner_index[tmp][2] == c->face[index_c])
            {
                break;
            }
        }
        c->corners[i] = tmp;
    }
}
void cube_to_face(cube_t *c)
{
    memset(c->face, 0, 54);
    c->face[4] = 'U';
    c->face[13] = 'R';
    c->face[22] = 'F';
    c->face[31] = 'D';
    c->face[40] = 'L';
    c->face[49] = 'B';
    for (int i = 0; i < 12; i++)
    {
        int index_a = edge_to_face[i][0];
        int index_b = edge_to_face[i][1];
        const char *s = edge_index[c->edges[i]];
        c->face[index_a] = s[0];
        c->face[index_b] = s[1];
    }
    for (int i = 0; i < 8; i++)
    {
        int index_a = corner_to_face[i][0];
        int index_b = corner_to_face[i][1];
        int index_c = corner_to_face[i][2];
        const char *s = corner_index[c->corners[i]];
        c->face[index_a] = s[0];
        c->face[index_b] = s[1];
        c->face[index_c] = s[2];
    }
}