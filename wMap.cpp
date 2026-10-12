#include "wMap.h"

namespace cui {

// TODO: make the initial position a parameter of Create()? Google Maps requires one (we pass 0,0)

bool wMap::IsSupported()
{
#if defined(CUICUI_UWP) || defined(CUICUI_WEB)
	return true;
#else
	return false;
#endif
}

wMap::wMap() : wWidget()
{
	debugName = "wMap";

#if defined(CUICUI_UWP)
	mapControl = ref new Maps::MapControl();
	b->Children->Append(mapControl);
#elif defined(CUICUI_WEB)
	EM_ASM_({
			var elem = getUnattachedElementsFromId($0.toString());
			if (elem == null)
			{
				console.log("wMap: element not found: " + $0);
				return;
			}
			if (typeof google === 'undefined' || !google.maps)
			{
				console.log("wMap: the Google Maps script is not loaded (see the wMap README)");
				return;
			}

			var params = {};
			params.center = {};
			params.center.lat = 0;
			params.center.lng = 0;
			params.zoom = 12;
			var map = new google.maps.Map(elem, params);
			if (window.cuicui_wMap_ObjectRefs == null)
				window.cuicui_wMap_ObjectRefs = [];
			window.cuicui_wMap_ObjectRefs[$0] = map;
		}, htmlId);
#else
	LogWarning("wMap is not implemented on this platform");
#endif
}

wMap* wMap::SetMapToken(const std::string &s)
{
#if defined(CUICUI_UWP)
	mapControl->MapServiceToken = StdStringToUwpString(s);
#endif
	return this;
}

wMap* wMap::SetCameraPosition(double latitude, double longitude, double zoom)
{
#if defined(CUICUI_UWP)
	using namespace Windows::Devices::Geolocation;

	BasicGeoposition bg;
	bg.Latitude = latitude;
	bg.Longitude = longitude;

	mapControl->Center = ref new Geopoint(bg);
	mapControl->ZoomLevel = zoom;
#elif defined(CUICUI_WEB)
	EM_ASM_({
		var refs = window.cuicui_wMap_ObjectRefs;
		var map = refs ? refs[$0] : null;
		if (map == null)
		{
			console.log("wMap::SetCameraPosition: map not found (not created, or destroyed)");
			return;
		}
		map.panTo(new google.maps.LatLng($1, $2));
		map.setZoom($3);
	}, htmlId, latitude, longitude, zoom);
#endif
	return this;
}

} // namespace cui
