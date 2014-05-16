// ----------------------------------------------------------------------------
//
// ladder version 1.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#include <QString>
#include <QTextStream>
#include <QSet>

// ----------------------------------------------------------------------------
// LadderItem
// ----------------------------------------------------------------------------
class LadderItem
{
public:
    int height;
    int axis;

public:
    LadderItem()
    {
        height = 0;
        axis   = 0;
    }

    LadderItem(int height, int axis)
    {
        this->height = height;
        this->axis   = axis;
    }

    bool operator == (const LadderItem& b) const
    {
        if (height != b.height) return false;
        if (axis   != b.axis)   return false;
        return true;
    }
};

int qHash(LadderItem item)
{
    return (item.height << 16) + item.axis;
}

// ----------------------------------------------------------------------------
// LadderItems
// ----------------------------------------------------------------------------
typedef QSet<LadderItem> LadderItems;

// ----------------------------------------------------------------------------
// Ladder
// ----------------------------------------------------------------------------
class Ladder
{
protected:
    int         maxHeight;
    LadderItems items;

public:
    Ladder()
    {
        maxHeight = 0;
    }

public:
    void addItem(int height, int axis)
    {
        LadderItem item(height, axis);
        items.insert(item);
        if (height > maxHeight) maxHeight = height;
    }

    int  move(int axis)
    {
        int height = 0;

        while (true)
        {
            //
            // increment height
            //
            if (++height > maxHeight) break;

            //
            // left move
            //
            LadderItem leftItem(height, axis - 1);
            if (items.find(leftItem) != items.end())
            {
                axis--;
                continue;
            }

            //
            // right move
            //
            LadderItem rightItem(height, axis);
            if (items.find(rightItem) != items.end())
            {
                axis++;
                continue;
            }
        }
        return axis;
    }
};

// ----------------------------------------------------------------------------
// main
// ----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QTextStream cin(stdin);
    QTextStream cout(stdout);
    Ladder      ladder;

    //
    // input items
    //
    while (true)
    {
        QString s; cin >> s;
        if (s == "x") break;
        int height = s.toInt();
        int axis; cin >> axis;
        ladder.addItem(height, axis);
    }

    //
    // input axis and write axis
    //
    while (true)
    {
        QString s; cin >> s;
        if (s == "x") break;
        int startAxis = s.toInt();
        int endAxis = ladder.move(startAxis);
        cout << endAxis << "\n";
        cout.flush();
    }
}
