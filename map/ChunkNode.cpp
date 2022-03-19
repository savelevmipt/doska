//
// Created by Matvey on 12.03.2022.
//
#include "ChunkNode.h"

bool ChunkRect::intersects(ChunkRect oth) const {
    return (ox + w > oth.ox && oth.ox + oth.w > ox)
           && (oy + h > oth.oy && oth.oy + oth.h > oy);
}

bool ChunkRect::contains(int x, int y) const {
    return ox <= x && x < ox + w && oy <= y && y < oy + h;
}

void ChunkRect::toParent(int parent_idx) {
    switch (parent_idx) {
        case 0:
            ox -= w;
            oy -= h;
            break;
        case 1:
            ox -= w;
            break;
        case 3:
            oy -= h;
            break;
        default:
            break;
    }
    w *= 2;
    h *= 2;
}

void ChunkRect::toChild(int child_id) {
    w /= 2;
    h /= 2;
    switch (child_id) {
        case 0:
            ox += w;
            oy += w;
            break;
        case 1:
            ox += w;
            break;
        case 3:
            oy += h;
            break;
        default:
            break;
    }
}

int ChunkRect::getChildIdx(int x, int y) const {
    if (x < ox || x > ox + w || y < oy || y > oy + h)
        return -1;
    bool bx = x < ox + w / 2;
    bool by = y < oy + h / 2;
    return bx ? (by ? 2 : 3) : (by ? 1 : 0);
}

ChunkNode::ChunkNode(int parent_idx, ChunkNode* parent):parent_idx(parent_idx), parent(parent) {
    ch[0] = nullptr;
    ch[1] = nullptr;
    ch[2] = nullptr;
    ch[3] = nullptr;
}
void ChunkNode::setPar(int _parent_idx, ChunkNode *_parent) {
    parent_idx = _parent_idx;
    parent = _parent;
}