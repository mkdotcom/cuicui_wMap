#pragma once

#include "cuicui_core/cuicui.h"

// EXPERIMENTAL map widget.
// UWP: Bing Maps control (MapControl). Web: Google Maps JavaScript API. Android / iOS: not implemented.
// Dev docs:
// UWP: https://learn.microsoft.com/windows/uwp/maps-and-location/display-maps
// Web: https://developers.google.com/maps/documentation/javascript/overview

namespace cui {
class wMap : public wWidget
{
protected:
#if defined(CUICUI_UWP)
	Maps::MapControl ^mapControl = nullptr;
#endif

public:
	wMap();
	~wMap() {}

	// false on the platforms where the widget is an empty placeholder
	static bool IsSupported();

	// UWP: the Bing Maps "MapServiceToken". Web: no effect (the key is in the script tag of index.html).
	wMap* SetMapToken(const std::string &s);
	wMap* SetCameraPosition(double latitude, double longitude, double zoom);

	// the size can't be MIN (a map has no natural size)
	static wMap *Create(Length xem, Length yem) { auto c = new wMap(); assert(!xem.IsMin()); assert(!yem.IsMin()); c->XemYem(xem, yem); return c; }
};
} // namespace cui
