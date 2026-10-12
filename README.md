# cuicui_wMap

Map widget module for [cuicui](https://github.com/mkdotcom/cuicui_core).

> **Status: experimental.** Old code (2019), barely maintained. Each platform uses a different map
> provider, and most platforms are missing:
>
> | Platform | Provider | Status |
> |---|---|---|
> | Web | Google Maps JavaScript API | compiles; not run since the port to the current core (needs your own API key) |
> | UWP | Bing Maps `MapControl` | not rebuilt since the port to the current core; the Bing Maps service is retired by Microsoft |
> | Android | – | not implemented (empty widget) |
> | iOS | – | not implemented (empty widget) |
>
> Use `wMap::IsSupported()` to know if the map is available on the current platform.

## Setup

1. Clone this repository into the `modules` folder of your app:
   ```
   cd modules
   git clone https://github.com/mkdotcom/cuicui_wMap.git
   ```
2. Add `modules/cuicui_wMap/wMap.cpp` to your build (CMake, file list, Visual Studio project, ...).
3. Include it: `#include "modules/cuicui_wMap/wMap.h"`.

### Web
Add the Google Maps script to your `index.html`, with **your own** API key
([get one here](https://developers.google.com/maps/documentation/javascript/get-api-key); restrict it to
your domain):

```html
<script>
function initMap() { console.log("cuicui_wMap: Google Maps API is ready"); }
</script>
<script src="https://maps.googleapis.com/maps/api/js?key=YOUR_GOOGLE_MAPS_API_KEY&callback=initMap" async defer></script>
```

### UWP
Call `SetMapToken()` with your Bing Maps `MapServiceToken`.

## Usage

```cpp
dc += map = wMap::Create(FILL, FILL); // the size can't be MIN
map->SetMapToken("...");             // UWP only, no effect on the web
map->SetCameraPosition(48.8566, 2.3522, 12); // latitude, longitude, zoom
```

## License

MIT, see [LICENSE](LICENSE).
