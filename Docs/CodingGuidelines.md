These guidelines are instended to promote good coding practices and keep the code base manageable and consistent.

## Namespaces
- Using namespaces properly allows to avoid name conflicts and subtle issues with wrong names being used.

### WaterWays namespace
- This project (Waterways) uses the "WaterWays" namespace for all the code that is produced for the project.

So any new code should be placed inside the "WaterWays" namespace.

Example:

```
namespace WaterWays {

class LayerSceneInterface {
public:
    ...
    virtual void onLayerChanged(const QRectF& bound_rect = QRectF{}) = 0;
};

} // namespace WaterWays

```

Nested workspaces under the "WaterWays" namespace are fine.

Example:

```
namespace WaterWays {
namespace MetaLayerModelItems {

class Item: public LayerModelItem {
public:
    ...
};

} // namespace MetaLayerModelItems
} // namespace WaterWays

```

### Anonymous namespace
- All source file functions and static variables should be placed into anonymous namespaces.

Example:
SomeSourceFile.cpp
```
#include "NodeLayerItem.h"

namespace WaterWays {

namespace {
    // Static constants, global variables
    static constexpr double node_width    = 200;
    static constexpr double node_height   = 200;    

    auto some_global_var = 123;

    void someStaticFunction(int param) {
        ...
    }
} // anonymous
...
} // namespace WaterWays

```

To be continued ...