SA-MP Streamer Plugin
=====================

v2.7.7
------

- Fixed bugs with Streamer_(Get/Set)MaxItems and
  IsPlayerIn(Any)DynamicArea
- Ordered the results stored in the GetPlayerDynamicAreas array by
  player distance from the area
- Added GetDynamicAreasForPoint (also ordered by distance) and
  GetNumberDynamicAreasForPoint
- Added IsDynamicObjectMaterialUsed and
  IsDynamicObjectMaterialTextUsed
- Added "STREAMER_ENABLE_TAGS" definition to include file which
  turns on tags for all types of items (in the format of
  "DynamicObject:", for example)

v2.7.6
------

- Fixed various bugs
- Added a delay to setting checkpoints in an attempt to fix the
  checkpoint size bug
- Made some improvements to EditDynamicObject and
  AttachCameraToDynamicObject for non-streamed objects
- Added SetDynamicObjectNoCameraCol, Streamer_(Is)ToggleCameraUpdate,
  and Streamer_(Is)ToggleStaticItem

v2.7.5.2
--------

- Added Streamer_OnPluginError, Streamer_ToggleErrorCallback, and
  Streamer_IsToggleErrorCallback

v2.7.5.1
--------

- Fixed pickup crash
- Fixed moving object rotation bug

v2.7.5
------

- Updated sampgdk, resolving some issues with callbacks
- Added type parameter to Streamer_Update(Ex)
- Added AttachDynamicObjectToObject and AttachDynamicObjectToPlayer
  (requires YSF by kurta999 to be loaded)
- Made visible item amounts configurable per player
- Added Streamer_(Get/Set)RadiusMultiplier
- Made items static if a negative stream distance is specified

v2.7.4
------

- Made OnPlayerLeaveDynamicArea callbacks execute when areas are
  destroyed
- Made OnPlayerLeaveDynamicArea callbacks execute before
  OnPlayerEnterDynamicArea callbacks (regression from a previous
  version)
- Updated libraries, fixing some miscellaneous bugs

v2.7.3
------

- Allowed moving object rotations to be set
- Added integrated callback hooks from sampgdk
- Renamed CreateDynamicCube to CreateDynamicCuboid
- Added CreateDynamicCylinder

v2.7.2
------

- Made E_STREAMER_EXTRA_ID data sequential and allowed multiple
  amounts of the same value to be used
- Allowed Streamer_(Get/Set)IntData to be used with
  E_STREAMER_EXTRA_ID, E_STREAMER_INTERIOR_ID,
  E_STREAMER_PLAYER_ID, and E_STREAMER_WORLD_ID

v2.7.1
------

- Fixed some minor bugs
- Updated sampgdk version

v2.7
----

- Added OnPlayerShootDynamicObject for 0.3z
- Added Streamer_GetItemInternalID and Streamer_GetItemStreamerID for
  getting SA-MP IDs from streamer IDs and vice versa
- Added Streamer_GetTickRate, Streamer_GetMaxItems,
  Streamer_GetVisibleItems, Streamer_GetCellDistance,
  Streamer_GetCellSize, Streamer_IsToggleIdleUpdate,
  Streamer_IsToggleItemUpdate, Streamer_DestroyAllItems,
  Streamer_CountItems, GetDynamicPolygonPoints,
  GetDynamicPolygonNumberPoints, IsAnyPlayerInDynamicArea,
  IsAnyPlayerInAnyDynamicArea, GetPlayerDynamicAreas, and
  GetPlayerNumberDynamicAreas
- Renamed Streamer_TickRate, Streamer_VisibleItems,
  Streamer_CellDistance, and Streamer_CellSize (all natives begin
  with Streamer_Set* now, but old natives are still usable)
- Deprecated DestroyAllDynamic* and CountDynamic* natives (new
  natives Streamer_DestroyAllItems and Streamer_CountItems are
  preferred now, but old natives are still usable)
- Added a new parameter called "serverwide" to the destroy and count
  natives that makes them work either across all scripts or only
  within the calling script
- Added a new parameter called "recheck" to
  Is(Any)PlayerIn(Any)DynamicArea which allows an area check to occur
  without issuing a full update for the player
- Added a "dimensions" parameter to Streamer_GetDistanceToItem which
  allows the script to specify whether a 2D or 3D distance check
  should be performed
- Added "drawdistance" to the end of CreateDynamicObject and "style"
  to the end of CreateDynamicMapIcon

v2.6.1
------

- Added AttachCameraToDynamicObject
- Added AttachDynamicObjectToVehicle
- Added EditDynamicObject
- Added OnPlayerEditDynamicObject
- Added OnPlayerSelectDynamicObject
- Added GetDynamicObjectMaterial and SetDynamicObjectMaterial
- Added GetDynamicObjectMaterialText and SetDynamicObjectMaterialText
- Added Streamer_ToggleItemUpdate
- Allowed NPCs to trigger area and checkpoint callbacks
- Fixed IsPlayerInDynamicRaceCP

v2.6
----

- Adjusted algorithm for searching cells that contain visible items,
  improving performance for players moving around the map frequently
- Greatly improved speed of spatial queries
- Implemented predictive streaming algorithm based on the player's
  current velocity and the average time between updates
- Replaced PAWN invoke system with Zeex's SA-MP GDK, improving
  overall performance
- Added functionality for preventing runtime errors due to outdated
  include files
- Added check for include file version in the plugin
- Fixed rare bug that sometimes stopped updates from occurring when
  Streamer_TickRate was used
- Changed interior check implementation to allow an unlimited number
  of interiors to be added per item, fixing the crash that occurred
  when players were in interior IDs 20 or above
- Changed virtual world check implementation for pickups to allow an
  unlimited number to be added
- Slightly improved streaming algorithm for pickups
- Made OnPlayerLeaveDynamicArea callbacks execute before
  OnPlayerEnterDynamicArea callbacks
- Added Streamer_ToggleIdleUpdate for allowing or disallowing updates
  to process for players who are not moving
- Added CreateDynamicPolygon
- Added IsPlayerInAnyDynamicArea
- Added optional parameters to Streamer_UpdateEx for specifying the
  world ID and interior ID
- Added rotation parameters to MoveDynamicObject (SA-MP 0.3d only)
- Added IsDynamicObjectMoving
- Added extended natives for item creation with up-to-date parameters
- Added Streamer_GetArrayData and Streamer_SetArrayData
- Added Streamer_ProcessActiveItems to force updates for moving and
  attached items
- Added Streamer_GetDistanceToItem
- Added GetPlayerVisibleDynamicCP and GetPlayerVisibleDynamicRaceCP
- Added IsPointInDynamicArea and IsPointInAnyDynamicArea
- Added AttachDynamicAreaToObject
- Added GetDynamic3DTextLabelText

v2.5.2
------

- Fixed some minor bugs
- Added support for map icon styles in 0.3c

v2.5.1
------

- Made cell boundaries contiguous
- Improved speed of spatial queries
- Fixed visibility of items with large streaming distances
- Added natives for attaching areas to players and vehicles
- Implemented functionality for adding and removing multiple virtual
  worlds, interiors, and players to and from items
- Update: Fixed bug with array bounds check and made attached areas
  and 3D text labels stream out when their positions cannot be
  retrieved

v2.5
----

- Added grid system for partitioning the game world into cells
- Added hash tables for numerous performance improvements
- Improved object streaming algorithm

v2.3.8
------

- Optimized a lot of streaming code
- Improved checkpoint handling
- Improved moving objects
- Resolved possible callback bugs
- Added Streamer_IsItemVisible, Streamer_DestroyAllVisibleItems,
  Streamer_CountVisibleItems, and Streamer_GetUpperBound

v2.3.7
------

- Fixed 3D text label crash
- Optimized more streaming code
- Resolved some checkpoint problems
- Added area detection natives and callbacks

v2.3.6
------

- Optimized some streaming code
- Fixed crash that may have occurred when destroying objects under
  OnDynamicObjectMoved
- Added plural tags to the data manipulation natives so that 3D text
  labels can be passed to them without a tag mismatch warning
- Added an extra ID to every item that can be set and retrieved with
  Streamer_SetIntData and Streamer_GetIntData
- Made any item that is altered with Streamer_SetFloatData or
  Streamer_SetIntData restream for every player automatically
- Added natives for each item to check if they're valid
- Consolidated all of the settings natives (with the exception of
  Streamer_TickRate) into Streamer_MaxItems and Streamer_VisibleItems

v2.3.5
------

- Added data manipulation natives: Streamer_GetFloatData,
  Streamer_GetIntData, Streamer_SetFloatData, and Streamer_SetIntData

v2.3.4
------

- Fixed bug with OnPlayerPickUpDynamicPickup that resulted in it
  being called too many times when multiple scripts were loaded
- Fixed bug with checkpoints and race checkpoints that caused none to
  be streamed until the one that was visible was no longer in range
- Slightly improved native address finding and added an error message
  that prints in the server log when all natives cannot be found
- Consolidated all of the update natives into Streamer_Update
- Added Streamer_UpdateEx for loading items in a specified area

v2.3.3
------

- Cleaned up and reorganized code
- Made the plugin automatically destroy all items created in a script
  when it is unloaded

v2.3.2
------

- Added natives for toggling all dynamic checkpoints and race
  checkpoints
- Made a check to prevent too many objects, pickups, or 3D text
  labels from being created

v2.3.1
------

- Fixed 3D text label attachment bug
- Fixed internal map icon ID assignment bug
- Rewrote PAWN invoke function

v2.3
----
- Fixed PAWN invoke bug in Linux (thanks pod)

v2.2
----

- Fixed item ID assignment bug
- Corrected another typo in the include file
- Improved moving objects slightly
- Made a few adjustments to the default streaming distances

v2.1
----

- Made all streaming distances customizable via an extra optional
  parameter
- Removed global distance natives and slightly renamed a few other
  natives related to the settings to make them a bit less confusing
- Fixed a small issue with pickups that involved a typo in the
  include file
- Renamed the custom pickup callback to OnPlayerPickUpDynamicPickup
  (note the capitalization)

v2.0
----

- Numerous bug fixes and optimizations
- Added support for pickups, checkpoints, race checkpoints,
  map icons, and 3D text labels
- Added optional parameters for specifying virtual worlds, interiors,
  and/or players
- Added more natives and callbacks for the new items
- Renamed and reorganized several natives

v1.1
----

- Heavily modified dynamic moving objects so that they now are
  tracked in the plugin and synchronized with all players
- MoveDynamicObject now returns the time in milliseconds that it will
  take to reach the destination (just like the default native)
- Added CreatePlayerDynamicObject, CreateVWDynamicObject,
  DestroyAllDynamicObjects, CountDynamicObjects, and
  OnDynamicObjectMoved
- Optimized some streaming code and fixed a few bugs in the automatic
  setup system

v1.0
----

- Initial release
