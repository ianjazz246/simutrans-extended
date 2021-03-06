/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#ifndef GUI_GOODS_STATS_T_H
#define GUI_GOODS_STATS_T_H


#include "../simtypes.h"
#include "components/gui_component.h"



class goods_stats_t : public gui_world_component_t
{
private:
	uint16 *goodslist;
	uint32 vehicle_speed;
	uint8 comfort;
	uint8 catering_level;
	uint32 distance_meters;
	uint8 g_class;

	// The number of goods to be displayed. May be less than maximum number of goods possible,
	// if we are filtering to only the goods being produced by factories in the current game.
	int listd_goods;

public:
	goods_stats_t();

	// update list and resize
	void update_goodslist(uint16 *g, uint32 vehicle_speed, int listd_goods, uint32 distance, uint8 comfort, uint8 catering, uint8 g_class);

	/**
	* Draw the component
	* @author Hj. Malthaner
	*/
	void draw(scr_coord offset);
};

#endif
