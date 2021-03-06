/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#ifndef GUI_COMPONENTS_GUI_IMAGE_LIST_H
#define GUI_COMPONENTS_GUI_IMAGE_LIST_H


#include "gui_action_creator.h"
#include "gui_component.h"
#include "../../tpl/vector_tpl.h"
#include "../../display/simimg.h"
#include "../../simcolor.h"

#define EMPTY_IMAGE_BAR (255)

/**
 * Updated! class is used only for the vehicle dialog. SO I changed some things
 * for the new one::
 * - cannot select no-image fields any more
 * - numbers can be drawn ontop an images
 * - color bar can be added to the images
 *
 *
 * @author Volker Meyer
 * @date  09.06.2003
 *
 * A component that represents a list of images.
 * @author Hj. Malthaner
 */
class gui_image_list_t :
	public gui_action_creator_t,
	public gui_component_t
{
public:
	struct image_data_t {
		const char *text;  ///< can be NULL, used to store external data
		image_id   image;  ///< the image
		sint16     count;  ///< display this number as overlay
		COLOR_VAL  lcolor; ///< color of left half of color bar, use EMPTY_IMAGE_BAR to display no bar
		COLOR_VAL  rcolor; ///< color of right half of color bar, use EMPTY_IMAGE_BAR to display no bar
		uint8 basic_coupling_constraint_prev; // basic_coupling_constraint for the shape of color bar of left side
		uint8 basic_coupling_constraint_next; // basic_coupling_constraint for the shape of color bar of right side
		uint8 interactivity; // bidirectional flags and has_power(motor/engine) flag
		uint8 has_upgrade;

		image_data_t(const char *text_, image_id image_, sint16 count_=0, COLOR_VAL lcolor_=EMPTY_IMAGE_BAR, COLOR_VAL rcolor_=EMPTY_IMAGE_BAR, uint8 basic_coupling_constraint_prev_=0, uint8 basic_coupling_constraint_next_ = 0, uint8 interactivity_ = 0, uint8 has_upgrade_ = 0)
		: text(text_), image(image_), count(count_), lcolor(lcolor_), rcolor(rcolor_), basic_coupling_constraint_prev(basic_coupling_constraint_prev_), basic_coupling_constraint_next(basic_coupling_constraint_next_), interactivity(interactivity_), has_upgrade(has_upgrade_) {}
	};

	/**
	 * Graphic layout:
	 * size of borders around the whole area (there are no borders around
	 * individual images)
	 *
	 * @author Volker Meyer
	 * @date  07.06.2003
	 */
	enum { BORDER = 4 };

private:
	vector_tpl<image_data_t*> *images;

	scr_coord grid;
	scr_coord placement;

	/**
	 * Rows or columns?
	 * @author Volker Meyer
	 * @date  20.06.2003
	 */
	int use_rows;

	/**
	 * Player number to obtain player color used to display the images.
	 * @author Hj. Malthaner
	 */
	sint8 player_nr;

	sint8 focus;

public:
	/**
	 * Constructor: takes pointer to vector with image_data_t
	 * @param images pointer to vector of pointers to image_data_t
	 * @author Hj. Malthaner
	 */
	gui_image_list_t(vector_tpl<image_data_t*> *images);

	/**
	 * This set horizontal and vertical spacing for the images.
	 * @author Volker Meyer
	 * @date  20.06.2003
	 */
	void set_grid(scr_coord grid) { this->grid = grid; }

	/**
	 * This set the offset for the images.
	 * @author Volker Meyer
	 * @date  20.06.2003
	 */
	void set_placement(scr_coord placement) { this->placement = placement; }

	void set_player_nr(sint8 player_nr) { this->player_nr = player_nr; }

	// Do not use for the lower panel because it does not support matrices - Ranran
	void set_focus(sint8 index) { this->focus = index; }

	bool infowin_event(event_t const*) OVERRIDE;

	/**
	 * Draw/record the picture
	 * @author Hj. Malthaner
	 */
	virtual void draw(scr_coord offset) OVERRIDE;

	/**
	 * Looks for the image at given position.
	 * xpos and ypos relative to parent window.
	 *
	 * @author Volker Meyer
	 * @date  07.06.2003
	 */
	int index_at(scr_coord parent_pos, int xpos, int ypos) const;

	void recalc_size();
};

#endif
