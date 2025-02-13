/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FIRELANDS_OBJECTGRIDLOADER_H
#define FIRELANDS_OBJECTGRIDLOADER_H

#include "TypeList.h"
#include "Define.h"
#include "GridLoader.h"
#include "GridDefines.h"
#include "Cell.h"

class MapObject;
class ObjectWorldLoader;

class FC_GAME_API ObjectGridLoader
{
    friend class ObjectWorldLoader;

    public:
        ObjectGridLoader(NGridType& grid, Map* map, Cell const& cell)
            : i_cell(cell), i_grid(grid), i_map(map), i_gameObjects(0), i_creatures(0), i_corpses (0)
            { }

        void Visit(GameObjectMapType &m);
        void Visit(CreatureMapType &m);
        void Visit(CorpseMapType &) const { }
        void Visit(DynamicObjectMapType&) const { }
        void Visit(AreaTriggerMapType &) const { }

        void LoadN(void);

        static void SetObjectCell(MapObject* obj, CellCoord const& cellCoord);

    private:
        Cell i_cell;
        NGridType &i_grid;
        Map* i_map;
        uint32 i_gameObjects;
        uint32 i_creatures;
        uint32 i_corpses;
};

//Stop the creatures before unloading the NGrid
class FC_GAME_API ObjectGridStoper
{
    public:
        void Visit(CreatureMapType &m);
        template<class T> void Visit(GridRefManager<T> &) { }
};

//Move the foreign creatures back to respawn positions before unloading the NGrid
class FC_GAME_API ObjectGridEvacuator
{
    public:
        void Visit(CreatureMapType &m);
        void Visit(GameObjectMapType &m);
        template<class T> void Visit(GridRefManager<T> &) { }
};

//Clean up and remove from world
class ObjectGridCleaner
{
    public:
        template<class T> void Visit(GridRefManager<T> &);
};

//Delete objects before deleting NGrid
class ObjectGridUnloader
{
    public:
        void Visit(CorpseMapType& /*m*/) { }    // corpses are deleted with Map
        template<class T> void Visit(GridRefManager<T> &m);
};
#endif
